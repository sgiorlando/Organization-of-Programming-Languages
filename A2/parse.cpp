/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
    Michael L. Scott, 2008-2017.
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include "scan.hpp"

using namespace std;

// names added to match the new tokens added "refer to scan.hpp"
const string names[] = {"read", "write", "id", "literal", "gets",
                       "add", "sub", "mul", "div", "lparen", "rparen", "eof",
                       "if", "fi", "do", "od", "check", "equal", "notEqual",
                       "less", "great", "lessEq", "greatEq", "endPrgm"};


stringstream outputStream; //output to stream to construct and return our output
bool error;

static token input_token;


void match (token expected) {
    if (input_token == expected) {
    input_token = scan ();
    }
    else
    {
      cout << "\nToken Expected was: " << names[expected] << endl;
      string unexpected = names[input_token];
      input_token = expected;
      error = true;
      throw string(unexpected);
    }

}

void program ();
void stmt_list ();
void stmt ();
void relation ();
void expr_tail ();
void expr ();
void term_tail ();
void term ();
void factor_tail ();
void factor ();
void rel_op (); //new func for ro
void add_op ();
void mul_op ();

// P -> SL
void program () { //DONE DONT MODIFY
  try{
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
        case t_if:
        case t_do:
        case t_check:
        case t_endPrgm:
            outputStream << "(program\n";
            outputStream << "[ ";
            stmt_list ();
            outputStream << "]\n";
            match (t_endPrgm);
            match (t_eof);
            outputStream << ")\n\n";
            break;
        default: throw string("Well that's a weird error");
    }
  } catch (string s) {
    cout << "Unexpected token: " << s << endl;
  }
}

// SL -> S SL
// No match so no need for a try-catch
void stmt_list () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_if:
        case t_do:
        case t_check:
            stmt ();
            stmt_list ();
            break;
        case t_eof:
        case t_od:
        case t_fi:
        case t_endPrgm:
            break;
    }
}


void stmt () {
  try{
    switch (input_token) {
        case t_id:
            match (t_id);
            outputStream << "(:= \"" << token_image << "\" "; // (:= "id" relation
            match (t_gets);
            relation ();
            outputStream << ")\n"; // )
            break;
        case t_read:
            match (t_read);
            outputStream << "(read \"" << token_image << "\")\n"; // (read "id")
            match (t_id);
            break;
        case t_write:
            match (t_write);
            outputStream << "(write \"" ; // (write relation
            relation ();
            outputStream << ")\n"; // )
            break;
      case t_if:
            match (t_if);
            outputStream << "(if\n(";
            relation ();
            outputStream << ")\n[ ";
            stmt_list ();
            outputStream << "]\n";
            match (t_fi);
            outputStream << ")\n";
            break;
      case t_do:
            match (t_do);
            outputStream << "(do\n[ ";
            stmt_list ();
            match (t_od);
            outputStream << "]\n)\n";
            break;
      case t_check:
            match (t_check);
            outputStream << "(check ";
            relation ();
            outputStream << ")\n";
            break;
    }
  } catch (string s) {
    cout << "Unexpected token: " << s << endl;
  }
}

// R -> E ET
void relation () {
  switch (input_token) {
    case t_id:
    case t_literal:
    case t_lparen:
    case t_check:
        expr ();
        expr_tail ();
        break;
  }
}


// E -> T TT
void expr () {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            term ();
            term_tail ();
            break;
    }
}

// F -> ( R ) | id | lit
void factor () {
  try{
    switch (input_token) {
        case t_id :
            outputStream << "(";
            outputStream << "id \"" << token_image << "\"";
            match (t_id);
            outputStream << ")";
            break;
        case t_literal:
            outputStream << "(";
            outputStream << "num \"" << token_image << "\"";
            match (t_literal);
            outputStream << ")";
            break;
        case t_lparen:
            match (t_lparen);
            outputStream << "(";
            relation ();
            match (t_rparen);
            outputStream << ")";
            break;
    }
  } catch (string s) {
    cout << "Unexpected token: " << s << endl;
  }
}

// ET -> ro E
void expr_tail() {
    switch (input_token) {
      case t_equal:
      case t_notEqual:
      case t_less:
      case t_great:
      case t_lessEq:
      case t_greatEq:
        rel_op ();
        expr ();
        break;
      case t_rparen:
      case t_id:
      case t_read:
      case t_write:
      case t_eof:
      case t_do:
      case t_od:
      case t_if:
      case t_fi:
      case t_check:
        break;          /*  epsilon production */
}
}

// TT -> ao T TT
void term_tail () {
    switch (input_token) {
        case t_add:
        case t_sub:
            add_op ();
            term ();
            term_tail ();
            break;
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
        case t_do:
        case t_od:
        case t_if:
        case t_fi:
        case t_gets:
        case t_greatEq:
        case t_lessEq:
        case t_less:
        case t_great:
        case t_equal:
            break;          /*  epsilon production */
    }
}

// T -> F FT
void term () {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
        case t_check:
            factor ();
            factor_tail ();
            break;
    }
}

// FT -> mo F FT
void factor_tail () {
    switch (input_token) {
        case t_mul:
        case t_div:
            mul_op ();
            factor ();
            factor_tail ();
            break;
        case t_add:
        case t_sub:
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
        case t_do:
        case t_od:
        case t_if:
        case t_fi:
        case t_gets:
        case t_greatEq:
        case t_lessEq:
        case t_less:
        case t_great:
        case t_equal:
            break;          /*  epsilon production */
    }
}



// rel_op is a new functions for the ro part of the language which we are implementing
// ro -> == | <> | < | > | <= | >=
void rel_op () {
  try{
    switch (input_token) {
        case t_equal:
              match (t_equal);
              outputStream << " == ";
              break;
        case t_notEqual:
              match (t_notEqual);
              outputStream << " <> ";
              break;
        case t_less:
              match (t_less);
              outputStream << " < ";
              break;
        case t_great:
              match (t_great);
              outputStream << " > ";
              break;
        case t_lessEq:
              match (t_lessEq);
              outputStream << " <= ";
              break;
        case t_greatEq:
              match (t_greatEq);
              outputStream << " >= ";
              break;
    }
  } catch (string s) {
    cout << "Unexpected token: " << s << endl;
  }
}

// ao -> + | -
void add_op () {
  try{
    switch (input_token) {
        case t_add:
            match (t_add);
            outputStream << " + ";
            break;
        case t_sub:
            match (t_sub);
            outputStream << " - ";
            break;
    }
  } catch (string s) {
    cout << "Unexpected token: " << s << endl;
  }
}

// mo -> * | /
void mul_op () {
  try{
    switch (input_token) {
        case t_mul:
            match (t_mul);
            outputStream << " * ";
            break;
        case t_div:
            match (t_div);
            outputStream << " ( ";
            break;
    }
  } catch (string s) {
    cout << "Unexpected token: " << s << endl;
  }
}

int main () {
    error = false;
    outputStream << "\n\nBegin Output:\n\n";
    input_token = scan ();
    program ();
    if(!error){
      cout << outputStream.str();
    } else {
      cout << "\nProgram had the above syntax errors fix them before running the program again"
      << " in order to generate a correct syntax tree.\nBelow is the best syntactically correct version"
      << " that this program can generate:\n";
      cout << outputStream.str();
    }
    return 0;
}
