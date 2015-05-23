%option c++ yyclass="pwn_scanner" outfile="pwn_scanner.cpp"
%option stack noyywrap yylineno 8bit
%{ 
/* $Id: pwn_scanner.l,v 1.8 2015/05/20 08:33:26 ist170916 Exp $ */
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include "pwn_scanner.h"
#include "pwn_parser.tab.h"

// don't change this
#define yyerror LexerError
%}
%x X_STRING X_CMT
%%

"//".*                      ; /* ignore explicative comments */

<INITIAL,X_CMT>"/*"         yy_push_state(X_CMT);
<X_CMT>"*/"                 yy_pop_state();
<X_CMT>.|\n                 ; /* ignore operational comments */

">="                        return tGE; 
"<="                        return tLE; 
"=="                        return tEQ;
"<>"                        return tNE;
"!!"                        return tPRINTLN;

"local"                     return tLOCAL;
"import"                    return tIMPORT;
"next"                      return tNEXT;
"stop"                      return tSTOP;
"return"                    return tRETURN;
"noob"                      return tNOOB;
"repeat"                    return tREPEAT;
"if"                        return tIF; 
"else"                      return tELSE;

[A-Za-z_][A-Za-z0-9_]*      yylval.s = new std::string(yytext); return tIDENTIFIER;

\"                          yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\"                yy_pop_state(); return tSTRING;
<X_STRING>\\\"              *yylval.s += yytext + 1;
<X_STRING>.                 *yylval.s += yytext;
<X_STRING>\\n               *yylval.s += "\n";
<X_STRING>\\t               *yylval.s += "\t";
<X_STRING>\\r               *yylval.s += "\r";
<X_STRING>\\[0-9a-fA-F][0-9a-fA-F]  {int val = strtol(yytext + 1, nullptr, 16); *yylval.s += val; }
<X_STRING>\\[0-9a-fA-F]             {int val = strtol(yytext + 1, nullptr, 16); *yylval.s += val; }
<X_STRING>\\0.*\"           yy_pop_state(); return tSTRING;
<X_STRING>\n                yyerror("newline in string");

[0-9]+                      yylval.i = strtol(yytext, nullptr, 10); return tINTEGER;
0x[0-9A-Fa-f]+              yylval.i = strtol(yytext, nullptr, 16); return tINTEGER;
[0-9]+\.[0-9]+              yylval.d = strtod(yytext, nullptr); return tDOUBLE; /* TODO: .x   x.  xE+-y */

[-()<>=+*/%;{}.,~&|#$?[\]@!] return *yytext;

[ \t\n]+                    ; /* ignore whitespace */

.                           yyerror("Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int pwn_scanner::yywrap() { return 1; }
