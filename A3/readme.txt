Name: Scott Giorlando
Partner: Zachary Palmer
Assignment: Translation
Submission: 2

What works and what doesn't:

This is a partially working program that Me and Zach spent a ton of time trying to get this working successfully. We currently have the code in a condition that we thought would be working but the OCaml interpreter was giving us errors when we were trying to run it until
recently.  We're both a bit unsure of where to go from here.

Current output on #use "translator.ml";;

# #use "translator.ml";;
val compose : ('a -> 'b) -> ('c -> 'a) -> 'c -> 'b = <fun>
type symbol_productions = string * string list list
type grammar = symbol_productions list
type parse_table = (string * (string list * string list) list) list
val calc_gram : grammar =
  [("P", [["SL"; "$$"]]); ("SL", [["S"; "SL"]; []]);
   ("S", [["id"; ":="; "E"]; ["read"; "id"]; ["write"; "E"]]);
   ("E", [["T"; "TT"]]); ("T", [["F"; "FT"]]);
   ("TT", [["ao"; "T"; "TT"]; []]); ("FT", [["mo"; "F"; "FT"]; []]);
   ("ao", [["+"]; ["-"]]); ("mo", [["*"]; ["/"]]);
   ("F", [["id"]; ["num"]; ["("; "E"; ")"]])]
val ecg : grammar =
  [("P", [["SL"; "$$"]]); ("SL", [["S"; "SL"]; []]);
   ("S",
    [["id"; ":="; "E"]; ["read"; "id"]; ["write"; "E"];
     ["if"; "R"; "SL"; "fi"]; ["do"; "SL"; "od"]; ["check"; "R"]]);
   ("R", [["E"; "ET"]]); ("E", [["T"; "TT"]]); ("T", [["F"; "FT"]]);
   ("F", [["id"]; ["num"]; ["("; "E"; ")"]]); ("ET", [["ro"; "E"]; []]);
   ("TT", [["ao"; "T"; "TT"]; []]); ("FT", [["mo"; "F"; "FT"]; []]);
   ("ro", [["=="]; ["<>"]; ["<"]; [">"]; ["<="]; [">="]]);
   ("ao", [["+"]; ["-"]]); ("mo", [["*"]; ["/"]])]
val member : 'a -> 'a list -> bool = <fun>
val sort : 'a list -> 'a list = <fun>
val unique : 'a list -> 'a list = <fun>
val unique_sort : 'a list -> 'a list = <fun>
val productions :
  (string * string list list) list -> (string * string list) list = <fun>
val gsymbols : ('a * string list list) list -> string list = <fun>
val list_minus : 'a list -> 'a list -> 'a list = <fun>
val nonterminals : (string * 'a) list -> string list = <fun>
val terminals : (string * string list list) list -> string list = <fun>
val start_symbol : (string * 'a) list -> string = <fun>
val is_nonterminal : string -> (string * 'a) list -> bool = <fun>
val is_terminal : string -> (string * string list list) list -> bool = <fun>
val union : 'a list -> 'a list -> 'a list = <fun>
val suffix : 'a -> 'a list -> 'a list = <fun>
type right_context = (string * string list) list
val get_right_context :
  string -> (string * string list list) list -> right_context = <fun>
type symbol_knowledge = string * bool * string list * string list
type knowledge = symbol_knowledge list
val symbol_field : 'a * 'b * 'c * 'd -> 'a = <fun>
val eps_field : 'a * 'b * 'c * 'd -> 'b = <fun>
val first_field : 'a * 'b * 'c * 'd -> 'c = <fun>
val follow_field : 'a * 'b * 'c * 'd -> 'd = <fun>
val initial_knowledge : (string * 'a) list -> knowledge = <fun>
val get_symbol_knowledge : string -> knowledge -> symbol_knowledge = <fun>
val generates_epsilon :
  string list -> knowledge -> (string * string list list) list -> bool =
  <fun>
val first :
  string list -> knowledge -> (string * string list list) list -> string list =
  <fun>
val follow : string -> knowledge -> string list = <fun>
val map3 : ('a -> 'b -> 'c -> 'd) -> 'a list -> 'b list -> 'c list -> 'd list =
  <fun>
val get_knowledge : symbol_productions list -> knowledge = <fun>
val get_parse_table : grammar -> parse_table = <fun>
val explode : string -> char list = <fun>
val implode : char list -> string = <fun>
type token = string * string
val tokenize : string -> token list = <fun>
val grammar_of : parse_table -> grammar = <fun>
type parse_tree =
    PT_error
  | PT_id of string
  | PT_num of string
  | PT_term of string
  | PT_nt of (string * parse_tree list)
val reduce_1_prod : parse_tree list -> int -> parse_tree list = <fun>
type parse_action = PA_error | PA_prediction of string list
val get_parse_action : string -> string -> parse_table -> parse_action =
  <fun>
type ps_item = PS_end of int | PS_sym of string
val parse : parse_table -> string -> parse_tree = <fun>
val cg_parse_table : parse_table =
  [("P", [(["$$"; "id"; "read"; "write"], ["SL"; "$$"])]);
   ("SL", [(["id"; "read"; "write"], ["S"; "SL"]); (["$$"], [])]);
   ("S",
    [(["id"], ["id"; ":="; "E"]); (["read"], ["read"; "id"]);
     (["write"], ["write"; "E"])]);
   ("E", [(["("; "id"; "num"], ["T"; "TT"])]);
   ("T", [(["("; "id"; "num"], ["F"; "FT"])]);
   ("TT",
    [(["+"; "-"], ["ao"; "T"; "TT"]);
     (["$$"; ")"; "id"; "read"; "write"], [])]);
   ("FT",
    [(["*"; "/"], ["mo"; "F"; "FT"]);
     (["$$"; ")"; "+"; "-"; "id"; "read"; "write"], [])]);
   ("ao", [(["+"], ["+"]); (["-"], ["-"])]);
   ("mo", [(["*"], ["*"]); (["/"], ["/"])]);
   ("F", [(["id"], ["id"]); (["num"], ["num"]); (["("], ["("; "E"; ")"])])]
val ecg_parse_table : parse_table =
  [("P",
    [(["$$"; "check"; "do"; "id"; "if"; "read"; "write"], ["SL"; "$$"])]);
   ("SL",
    [(["check"; "do"; "id"; "if"; "read"; "write"], ["S"; "SL"]);
     (["$$"; "fi"; "od"], [])]);
   ("S",
    [(["id"], ["id"; ":="; "E"]); (["read"], ["read"; "id"]);
     (["write"], ["write"; "E"]); (["if"], ["if"; "R"; "SL"; "fi"]);
     (["do"], ["do"; "SL"; "od"]); (["check"], ["check"; "R"])]);
   ("R", [(["("; "id"; "num"], ["E"; "ET"])]);
   ("E", [(["("; "id"; "num"], ["T"; "TT"])]);
   ("T", [(["("; "id"; "num"], ["F"; "FT"])]);
   ("F", [(["id"], ["id"]); (["num"], ["num"]); (["("], ["("; "E"; ")"])]);
   ("ET",
    [(["<"; "<="; "<>"; "=="; ">"; ">="], ["ro"; "E"]);
     (["$$"; "check"; "do"; "fi"; "id"; "if"; "od"; "read"; "write"], [])]);
   ("TT",
    [(["+"; "-"], ["ao"; "T"; "TT"]);
     (["$$"; ")"; "<"; "<="; "<>"; "=="; ">"; ">="; "check"; "do"; "fi";
       "id"; "if"; "od"; "read"; "write"],
      [])]);
   ("FT",
    [(["*"; "/"], ["mo"; "F"; "FT"]);
     (["$$"; ")"; "+"; "-"; "<"; "<="; "<>"; "=="; ">"; ">="; "check"; "do";
       "fi"; "id"; "if"; "od"; "read"; "write"],
      [])]);
   ("ro",
    [(["=="], ["=="]); (["<>"], ["<>"]); (["<"], ["<"]); ([">"], [">"]);
     (["<="], ["<="]); ([">="], [">="])]);
   ("ao", [(["+"], ["+"]); (["-"], ["-"])]);
   ("mo", [(["*"], ["*"]); (["/"], ["/"])])]
type ast_sl = ast_s list
and ast_s =
    AST_error
  | AST_assign of (string * ast_e)
  | AST_read of string
  | AST_write of ast_e
  | AST_if of (ast_comp * ast_sl)
  | AST_do of ast_sl
  | AST_check of ast_e
and ast_e =
    AST_binop of (string * ast_e * ast_e)
  | AST_id of string
  | AST_num of string
and ast_comp = string * ast_e * ast_e
val ast_ize_P : parse_tree -> ast_sl = <fun>
val ast_ize_SL : parse_tree -> ast_sl = <fun>
val ast_ize_S : parse_tree -> ast_s = <fun>
val ast_ize_expr : parse_tree -> ast_e = <fun>
val ast_ize_term : parse_tree -> ast_e = <fun>
val ast_ize_fact : parse_tree -> ast_e = <fun>
val ast_ize_reln_tail : ast_e -> parse_tree -> ast_e = <fun>
val ast_ize_expr_tail : ast_e -> parse_tree -> ast_e = <fun>
val ast_ize_compare : parse_tree -> ast_comp = <fun>
val str_cat : string -> string -> string = <fun>
type memory = (string * int) list
File "translator.ml", line 196, characters 2-351:
Warning 8: this pattern-matching is not exhaustive.
Here is an example of a value that is not matched:
(AST_do _|AST_check _)
File "translator.ml", line 213, characters 17-18:
Error: Unbound value l
#
