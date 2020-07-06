/* Definitions the scanner shares with the parser
    Michael L. Scott, 2008-2017.
*/

//Tokens that must be added for new functions:
// t_if (begin if) | t_fi (end fi) | t_do (begin do) | t_od (end do)
// t_check (check) | t_equal | t_notEqual | t_less | t_great
// t_lessEq | t_greatEq
typedef enum {t_read, t_write, t_id, t_literal, t_gets,
                t_add, t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof,
                t_if, t_fi, t_do, t_od, t_check, t_equal, t_notEqual,
                t_less, t_great, t_lessEq, t_greatEq, t_endPrgm} token;

extern char token_image[100];

extern token scan();
