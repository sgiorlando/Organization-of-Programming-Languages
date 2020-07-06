/* Simple ad-hoc scanner for the calculator language.
    Michael L. Scott, 2008-2017.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include "scan.hpp"

using namespace std;

char token_image[100];

token scan() {
    static int c = ' ';
        /* next available char; extra (int) width accommodates EOF */
    int i = 0;              /* index into token_image */
    /* skip white space */
    while (isspace(c)) {
        c = getchar();
    }
    if (c == EOF)
        return t_eof;
    if (isalpha(c)) {

        do {
            token_image[i++] = c;
            c = getchar();
        } while (isalpha(c) || isdigit(c) || c == '_');
        token_image[i] = '\0';
        if (!strncmp(token_image, "read", i)) return t_read;
        else if (!strncmp(token_image, "write", i)) return t_write;
        else if (!strncmp(token_image, "if", i)) return t_if;
        else if (!strncmp(token_image, "fi", i)) return t_fi;
        else if (!strncmp(token_image, "do", i)) return t_do;
        else if (!strncmp(token_image, "od", i)) return t_od;
        else if (!strncmp(token_image, "check", i)) return t_check;
        else return t_id;
    }
    else if (isdigit(c)) {
        do {
            token_image[i++] = c;
            c = getchar();
        } while (isdigit(c));
        token_image[i] = '\0';
        return t_literal;
    } else switch (c) {
        //cases for <= <> <
        case '<':
            if ((c = getchar()) == '=') {
              c = getchar();
              return t_lessEq;
            } else
            if ((c = getchar()) == '>') {
              c = getchar();
              return t_notEqual;
            } else {
              return t_less;
            }
            break;
        //cases for > >=
        case '>':
                if ((c = getchar()) == '=') {
                  c = getchar();
                  return t_greatEq;
                } else {
                  return t_great;
                }
                break;
        //case for ==
        case '=':
                if ((c = getchar()) != '=') {
                      cout << stderr << "Error: = must be followed by =" << endl;
                      exit(1);
                } else {
                    c = getchar();
                    return t_equal;
                }
                break;
        //case for :=
        case ':':
                if ((c = getchar()) != '=') {
                    cout << stderr << "Error: : must be followed by =" << endl;
                    exit(1);
                } else {
                    c = getchar();
                    return t_gets;
                }
                break;
        case '$':
                if ((c = getchar()) != '$') {
                    c = getchar();
                    cout << stderr << "Error: $ must be followed by $" << endl;
                    exit(1);
                } else {
                    c = getchar();
                    return t_endPrgm;
                }
                break;
        case '+': c = getchar(); return t_add;
        case '-': c = getchar(); return t_sub;
        case '*': c = getchar(); return t_mul;
        case '/': c = getchar(); return t_div;
        case '(': c = getchar(); return t_lparen;
        case ')': c = getchar(); return t_rparen;
        default:
            cout << i << c << "error" << token_image << endl;
            exit(1);
    }
}
