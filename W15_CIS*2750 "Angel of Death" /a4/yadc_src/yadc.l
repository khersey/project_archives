/* LEX */
/* filename:   yadc.l
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*2750
 * assignment: 3
 *
 */

%{
    #include <string.h>
    #include <stdlib.h>
    void yyerror(char *);
    #include "y.tab.h"
%}

%%

title           { return TITLE; }
fields          { return FIELDS; }
buttons         { return BUTTONS; }

[a-zA-z][_a-zA-Z0-9]+   { yylval = strdup(yytext); return VALUE; }

\"  { return QUOTE; }
=   { return EQUALS; }
;   { return SEMICOLON; }
"{"   { return OPENBR; }
"}"   { return CLOSEBR; }
,   { return COMMA; }

[ \t\n]         ;

#([^\n]*)\n     ; /* skip comments */

.               ; { printf("ERROR\n"); }

%%

int yywrap() {
    return 1;
}
