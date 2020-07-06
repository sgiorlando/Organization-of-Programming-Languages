(* Scott Giorlando and Zachary Palmer *)

(*******************************************************************
   This file ("translator.ml") provides stub functions for the extra
   code you need to write for this assignment.

   There are two major stub functions in "translator.ml":
   "ast_ize_P" (which transforms a parse tree for a program into
   an abstract syntax tree[AST]); and
   "translate" (which translates an AST into an equivalent C program).

   You are also being provided with a file called "parser.ml" which
   contains working code to produce a parse tree for a program.
   Everything in the file "parser.ml" is complete and usable as-is.

   The major entry point for the parser provided in "parser.ml" is
   a function called "parse" invoked with two parameters: A parse table,
   and a string containing a calculator language program.

   The file "parser.ml" constructs two example parse tables:
   "cg_parse_table" (for the original calculator language grammar), and
   "ecg_parse_table" (for the extended calculator language grammar).

   Here are two parser examples which will work as-is:

   parse cg_parse_table sum_ave_prog;;
   parse ecg_parse_table primes_prog;;

   "sum_ave_prog" and "primes_prog" are provided at the end of this
   file (as strings). "sum_ave_prog" uses the original calculator
   language grammar, while "primes_prog" uses the extended calculator
   language grammar.

   When complete, your translator code should work when invoked as
   follows:


   print_string
   (snd
   (translate
   (ast_ize_P
   (parse ecg_parse_table primes_prog)
   )
   )
   );;

   The result of this invocation should be a C program on standard
   output, which can be compiled and run to produce the first N primes
   (where N is a number typed by the user).
 *******************************************************************)


#use "parser.ml";;


(*******************************************************************
   Declarations and functions to transform a parse tree into an
   abstract syntax tree (AST)
 *******************************************************************)

type ast_sl = ast_s list
and ast_s =
    | AST_error
    | AST_assign of (string * ast_e)
    | AST_read of string
    | AST_write of ast_e
    | AST_if of (ast_comp * ast_sl)
    | AST_do of ast_sl
    | AST_check of ast_e
and ast_e =
    | AST_binop of (string * ast_e * ast_e)
    | AST_id of string
    | AST_num of string

and ast_comp = (string * ast_e * ast_e);;

let rec ast_ize_P (p:parse_tree) : ast_sl =
  match p with
    | PT_nt ("P", [sl; PT_term "$$"]) -> (ast_ize_SL sl)
    | _ -> raise (Failure "malformed parse tree in ast_ize_P")

and ast_ize_SL (sl:parse_tree) : ast_sl =
  match sl with
    | PT_nt ("SL", []) -> []
    | PT_nt ("SL", [s; sl]) -> [ast_ize_S s] @ (ast_ize_SL sl)
    | _ -> raise (Failure "malformed parse tree in ast_ize_SL")

and ast_ize_S (s:parse_tree) : ast_s =
  match s with
    | PT_nt ("S", [PT_id lhs; PT_term ":="; expr])
      -> AST_assign (lhs, (ast_ize_expr expr))
    | PT_nt ("S", [PT_term "read"; PT_id id]) ->
        AST_read id
    | PT_nt ("S", [PT_term "write"; expr]) ->
        AST_write (ast_ize_expr expr)
    | PT_nt ("S", [PT_term "if";
                   cond;
                   sl;
                   PT_term "end"]) ->
        AST_if ((ast_ize_compare cond), (ast_ize_SL sl))
    | _ -> raise (Failure "malformed parse tree in ast_ize_S")

and ast_ize_expr (e:parse_tree) : ast_e =
  (* e is an R, E, T, or F parse tree node *)
  match e with
    | PT_nt ("E", [term; termtail])
      -> let lhs = ast_ize_term term in
          ast_ize_reln_tail lhs termtail
    | _ -> raise (Failure "malformed parse tree in ast_ize_expr")

and ast_ize_term (t:parse_tree) : ast_e =
  match t with
    | PT_nt ("T", [factor; factortail])
      -> let lhs = ast_ize_fact factor in
          ast_ize_expr_tail lhs factortail
    | _ -> raise (Failure "malformed parse tree in ast_ize_term")

and ast_ize_fact (f:parse_tree) : ast_e =
  match f with
    | PT_nt ("F", [PT_num num]) -> AST_num num
    | PT_nt ("F", [PT_id id]) -> AST_id id
    | PT_nt ("F", [PT_term "("; expr; PT_term ")"]) -> ast_ize_expr expr
    | _ -> raise (Failure "malformed parse tree in ast_ize_fact")

and ast_ize_reln_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs in an inheritec attribute.
     tail is an ET parse tree node *)
  match tail with
    | PT_nt ("TT", []) -> lhs
    | PT_nt ("TT", [PT_nt ("ao", [PT_term ao]); term; termtail])
      ->(ast_ize_reln_tail (AST_binop(ao, lhs, (ast_ize_term term))) termtail)
    | _ -> raise (Failure "malformed parse tree in ast_ize_reln_tail")

and ast_ize_expr_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs in an inherited attribute.
     tail is a TT or FT parse tree node *)
  match tail with
    | PT_nt ("FT", []) ->
        lhs
    | PT_nt ("TT", []) ->
        lhs
    | PT_nt ("FT", [PT_nt ("mo", [PT_term op]);
                    factor;
                    PT_nt ("FT", [])]) ->
        AST_binop (op, lhs, (ast_ize_expr factor))
    | PT_nt ("TT", [PT_nt ("ao", [PT_term op]);
                    term;
                    PT_nt ("TT", [])]) ->
        AST_binop (op, lhs, (ast_ize_expr term))
    | _ -> raise (Failure "malformed parse tree in ast_ize_expr_tail")

and ast_ize_compare (c:parse_tree) : ast_comp =
  match c with
    | PT_nt ("C", [lhs; PT_nt ("rn", [PT_term rn]); rhs])
      -> (rn, ast_ize_expr lhs, ast_ize_expr rhs)
    | _ -> raise (Failure "malformed parse tree in ast_ize_compare")
;;


(*******************************************************************
   Functions to translate an AST into C
 *******************************************************************)

(* The code below is (obviously) a bare stub. The intent is that when
   you run translate on a full, correct AST, you'll get back code for an
   equivalent C program. If there are any variables that are written in
   the program but never read, you'll also get a warning message
   indicating their names and the lines on which the writes occur. Your
   C program should contain code to check for dynamic semantic errors. *)

let str_cat a b =
  match (a, b) with
  | (a, "") -> a
  | ("", b) -> b
  | (_, _) -> a ^ " " ^ b;;

type memory = (string * int) list;;

let rec translate (ast:ast_sl) (full_input:string) : string =
  let inp = split (regexp "[ \t\n]+") full_input in
  let (_, _, _, outp) = translate_sl ast [] inp [] in
    (fold_left str_cat "" outp) ^ "\n"

and translate_sl (sl:ast_sl) (mem:memory)
      (inp:string list) (outp:string list)
  : bool * memory * string list * string list =
  match sl with
    | [] -> (true, mem, inp, outp)
    | h::t -> let (ok, new_mem, new_inp, new_outp) =
      try (translate_s h mem inp outp) with e-> (false, [], [],["error while translating"])
        in (translate_sl t new_mem new_inp new_outp)

and translate_s (s:ast_s) (mem:memory)
      (inp:string list) (outp:string list)
  : bool * memory * string list * string list =
  match s with
    | AST_assign(id, expr) -> translate_assign id expr mem inp outp
    | AST_read(id)         -> translate_read id mem inp outp
    | AST_write(expr)      -> translate_write expr mem inp outp
    | AST_if(cond, sl)     -> translate_if cond sl mem inp outp
    | AST_error            -> raise (Failure "cannot translate erroneous tree")

and translate_assign (lhs:string) (rhs:ast_e) (mem:memory)
      (inp:string list) (outp:string list)
  : bool * memory * string list * string list =
  let rec all_mem_but_this nv 1 =
    let rec helper k ls acc : memory =
      match ls with
        | [] -> acc
        | h::tail -> if ((fst k) <> (fst h))
            then helper k tail ([h] @ acc)
            else helper k tail acc
    in helper nv l []
  in let res_r = (fst (translate_expr rhs mem)) in match res_r with
    | Value (vr) -> let new_nv = (lhs, vr)
        in let rest_mem = all_mem_but_this new_nv mem
        in (true, [new_nv] @ rest_mem, inp, outp)
    | _ -> raise (Failure "match AST_num fail in translate_assign")

and translate_read (id:string) (mem:memory)
      (inp:string list) (outp:string list)
  : bool * memory * string list * string list =
  let cnt_input = try (hd inp) with e -> raise e
  in let value:int = try int_of_string cnt_input with e -> raise e
  in let nv:string * int = (id, value)
  in (true, [nv] @ mem, tl inp, outp)

and translate_write (expr:ast_e) (mem:memory)
      (inp:string list) (outp:string list)
  : bool * memory * string list * string list =
  let res = (fst(translate_check(op, lh, rh) mem)) in
    match expr with
      | AST_num num -> (true, mem, inp, outp @ [num])
      | AST_id id -> let nv = find (fun pair -> (fst pair) = id) mem in
            (true, mem, inp, outp @ [(string_of_int (snd nv))])
      | AST_binop (_, _, _) -> match res with
        | Value(v) -> (true, mem, inp, outp @ [string_of_int v])
        | Error(err_msg) -> (false, mem, inp, outp @ [err_msg])
        | _ -> raise (Failure "match AST_write translate_write")
        | _ -> raise (Failure "match AST_write translate_write")

and translate_if (cond:ast_comp) (sl:ast_sl) (mem:memory)
      (inp:string list) (outp:string list)
  : bool * memory * string list * string list =
  let (op, lh, rh) = cond
  in let res_eval:value = (fst (translate_check (op, lh, rh) mem))
  in match res_eval with
    | Value (1) -> (translate_sl sl mem inp outp)
    | Value (0) -> (true, mem, inp, outp)
    | Error (err_msg) -> (false, mem, inp, outp @ [err_msg])
    | _ -> raise (Failure "translate_if error eval fail")

and translate_do (cond:ast_comp) (sl:ast_sl) (mem:memory)
      (inp:string list) (outp:string list)
  : bool * memory * string list * string list =
  let (op, lh, rh) = cond
  in let res_eval:value = (fst (translate_check (op, lh, rh) mem))
  in match res_eval with
    | Value (1) -> let (_, new_mem, new_inp, new_outp) = translate_sl sl mem inp outp
        in (translate_while cond sl new_mem new_inp new_outp)
    | Value (0) -> (true, mem, inp, outp @ [err_msg])
    | _ -> raise (Failure "translate_if error eval fail")

and translate_check ((op:string), (lo:ast_e), (ro:ast_e)) (mem:memory)
  : value * memory =
  let Value (lv) = (fst(translate_expr lo mem)) in
  let Value (rv) = (fst(translate_expr lo mem)) in
    match (op, lv, rv) with
      | ("==", lv, rv) -> if lv = rv then (Value(1), mem) else (Value(0), mem)
      | ("!=", lv, rv) -> if lv <> rv then (Value(1), mem) else (Value(0), mem)
      | ("<=", lv, rv) -> if lv <= rv then (Value(1), mem) else (Value(0), mem)
      | (">=", lv, rv) -> if lv >= rv then (Value(1), mem) else (Value(0), mem)
      | ("<", lv, rv) -> if lv < rv then (Value(1), mem) else (Value(0), mem)
      | (">", lv, rv) -> if lv > rv then (Value(1), mem) else (Value(0), mem)
      | _ -> (Error("code not written yet"), mem)

and translate_expr (expr:ast_e) (mem:memory) : value * memory =
  match expr with
    | AST_id id -> (Value (snd (find (fun x -> (fst x) = id) mem)), mem)
    | AST_num num -> (Value (int_of_string num), mem)
    | AST_binop (binop, lhs, rhs) -> let Value(lv) = (fst (translate_expr lhs mem))
        in let Value(rv) = (fst (translate_expr rhs mem))
        in match binop with
          | "*" -> (Value(lv * rv), mem)
          | "/" -> if rv <> 0 then (Value(lv / rv), mem) else (Error("divide by zero"), mem)
          | "+" -> (Value(lv + rv), mem)
          | "-" -> (Value(lv - rv), mem)
          | _ -> (Error("code not written yet"), mem)

(*******************************************************************
   Sample programs in the calculator language
 *******************************************************************)

let sum_ave_prog = "
read a
read b
sum := a + b
write sum
write sum / 2";;

let primes_prog = "
read n
cp := 2
do check n > 0
found := 0
cf1 := 2
cf1s := cf1 * cf1
do check cf1s <= cp
cf2 := 2
pr := cf1 * cf2
do check pr <= cp
if pr == cp
found := 1
fi
cf2 := cf2 + 1
pr := cf1 * cf2
od
cf1 := cf1 + 1
cf1s := cf1 * cf1
od
if found == 0
write cp
n := n - 1
fi
cp := cp + 1
od";;
