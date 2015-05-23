%{
// $Id: pwn_parser.y,v 1.18 2015/05/20 08:33:26 ist170916 Exp $
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!

int LOCAL = 1, IMPORT = 2, NOQUALIFIER = 3;

bool isImport(int qualifier) {
  if(qualifier == IMPORT)
    return true;
  else
    return false;
}

bool isLocal(int qualifier) {
  if(qualifier == LOCAL)
    return true;
  else
    return false;
}

%}

%union {
  int                   i;	/* integer value */
  double                d;      /* double value */
  std::string          *s;	/* symbol name or string literal */
  basic_type           *btype;
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  pwn::lvalue_node  *lvalue;
  pwn::fundecl_node *fundeclnode;
};

%token <i> tINTEGER
%token <d> tDOUBLE
%token <s> tIDENTIFIER tSTRING
%token tREPEAT tIF tPRINT tREAD tBEGIN tEND tPRINTLN tLOCAL tIMPORT tNEXT tSTOP tRETURN tNOOB

%nonassoc tIFX
%nonassoc tELSE

%nonassoc '!'
%right '='
%left '|'
%left '&'
%nonassoc '~'
%left tEQ tNE
%left tGE tLE '>' '<'
%left '+' '-'
%nonassoc tUNARY
%nonassoc '?'
%left '*' '/' '%'
%right '['

%type <fundeclnode> fundecl
%type <node> stmt function declaration vardec
%type <sequence> exprlist exprlist2 varlist stmtlist declist declistInsideBlock block varvars
%type <expression> expr tRETURN
%type <lvalue> lval
%type <btype> type literal
%type <i> qualifier
%type <s> strings

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

file : declist                { compiler->ast($1); }
     ;

declist : declist declaration { $$ = new cdk::sequence_node(LINE, $2, $1); }
        | declaration         { $$ = new cdk::sequence_node(LINE, $1); }
        ;
        
declistInsideBlock : declistInsideBlock vardec ';' { $$ = new cdk::sequence_node(LINE, $2, $1); }
                   | vardec ';'                    { $$ = new cdk::sequence_node(LINE, $1); }
                   ;
        
declaration : vardec ';'         { $$ = $1; }
            | function           { $$ = $1; }
            ;

stmtlist : stmtlist stmt  { $$ = new cdk::sequence_node(LINE, $2, $1); }
         | stmt           { $$ = new cdk::sequence_node(LINE, $1); }
         ;
         
varlist : '(' varvars ')'             { $$ = $2; }
        | '(' ')'                     { $$ = new cdk::sequence_node(LINE, new cdk::nil_node(LINE)); }
        ;
        
varvars : varvars ',' vardec          { $$ = new cdk::sequence_node(LINE, $3, $1); }
        | vardec                      { $$ = new cdk::sequence_node(LINE, $1); }
        ;

exprlist : exprlist2           { $$ = $1; }
         |                     { $$ = new cdk::sequence_node(LINE, new cdk::nil_node(LINE)); }
         ;

exprlist2 : expr               { $$ = new cdk::sequence_node(LINE, $1); }
          | exprlist2 ',' expr { $$ = new cdk::sequence_node(LINE, $3, $1); }
          ;
                  
qualifier : tLOCAL           { $$ = LOCAL; }
          | tIMPORT          { $$ = IMPORT; }
          |                  { $$ = NOQUALIFIER; }
          ;
 
block : '{' declistInsideBlock stmtlist '}'   { $$ = new cdk::sequence_node(LINE, $3, $2); /* FIXME: BLOCK NODE. Allow func decls in some blocks??? */ }
      | '{' stmtlist '}'                      { $$ = new cdk::sequence_node(LINE, $2); }
      | '{' declistInsideBlock '}'            { $$ = new cdk::sequence_node(LINE, $2); }
      | '{' '}'                               { $$ = new cdk::sequence_node(LINE, new cdk::nil_node(LINE)); }
      ;

fundecl : qualifier type tIDENTIFIER varlist '=' literal  { $$ = new pwn::fundecl_node(LINE, isLocal($1), isImport($1), $3, $2, new cdk::sequence_node(LINE, $4)); /* FIXME: add default return */ }
        | qualifier type tIDENTIFIER varlist              { $$ = new pwn::fundecl_node(LINE, isLocal($1), isImport($1), $3, $2, new cdk::sequence_node(LINE, $4)); }
        | qualifier '!' tIDENTIFIER varlist '=' literal   { $$ = new pwn::fundecl_node(LINE, isLocal($1), isImport($1), $3, new basic_type(sizeof(int), basic_type::TYPE_VOID), new cdk::sequence_node(LINE, $4)); /* FIXME: add default return */ }
        | qualifier '!' tIDENTIFIER varlist               { $$ = new pwn::fundecl_node(LINE, isLocal($1), isImport($1), $3, new basic_type(sizeof(int), basic_type::TYPE_VOID), new cdk::sequence_node(LINE, $4)); }
        ;

literal : tINTEGER     { $$ = new basic_type(sizeof(int), basic_type::TYPE_INT); }
        | tSTRING      { $$ = new basic_type(sizeof(int), basic_type::TYPE_STRING); }
        | tDOUBLE      { $$ = new basic_type(sizeof(int), basic_type::TYPE_DOUBLE); }
        ;
         
function : fundecl         { $$ = $1; }
         | fundecl block   { if(isImport($1->import())) { yyerror("Can not define imported function."); } else { $$ = new pwn::fundef_node(LINE, $1, $2); } }
         ;

stmt : expr ';'                                                    { $$ = new pwn::evaluation_node(LINE, $1); }
     | expr '!'                                                    { $$ = new pwn::print_node(LINE, $1); }
     | expr tPRINTLN                                               { $$ = new pwn::println_node(LINE, new pwn::print_node(LINE, $1)); }
     | tSTOP tINTEGER ';'                                          { $$ = new pwn::stop_node(LINE, new cdk::integer_node(LINE, $2)); }
     | tNEXT tINTEGER ';'                                          { $$ = new pwn::next_node(LINE, new cdk::integer_node(LINE, $2)); }
     | tSTOP ';'                                                   { $$ = new pwn::stop_node(LINE, new cdk::integer_node(LINE, 1)); }
     | tNEXT ';'                                                   { $$ = new pwn::next_node(LINE, new cdk::integer_node(LINE, 1)); }
     | tRETURN                                                     { $$ = new pwn::return_node(LINE); }
     | tREPEAT '(' exprlist ';' exprlist ';' exprlist ')' stmt     { $$ = new pwn::repeat_node(LINE, $3, $5, $7, $9); }
     | tIF '(' expr ')' stmt %prec tIFX                            { $$ = new cdk::if_node(LINE, $3, $5); }
     | tIF '(' expr ')' stmt tELSE stmt                            { $$ = new cdk::if_else_node(LINE, $3, $5, $7); }
     | block                                                       { $$ = $1; }
     ;

expr : tINTEGER                  { $$ = new cdk::integer_node(LINE, $1); }
     | tNOOB                     { $$ = new pwn::noob_node(LINE); }
     | strings                   { $$ = new cdk::string_node(LINE, $1); }
     | tDOUBLE                   { $$ = new cdk::double_node(LINE, $1); }
     | '-' expr %prec tUNARY     { $$ = new pwn::symmetric_node(LINE, $2); }
     | '+' expr %prec tUNARY     { $$ = new pwn::identity_node(LINE, $2); }
     | '~' expr                  { $$ = new cdk::neg_node(LINE, $2); }
     | expr '?'                  { /* TODO: address node */ }
     | expr '+' expr	         { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr	         { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr	         { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr	         { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr	         { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr	         { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr	         { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr '&' expr	         { $$ = new pwn::and_node(LINE, $1, $3); }
     | expr '|' expr	         { $$ = new pwn::or_node(LINE, $1, $3); }
     | expr tGE expr	         { $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr             { $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tNE expr             { $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr tEQ expr             { $$ = new cdk::eq_node(LINE, $1, $3); }
     | '(' expr ')'              { $$ = $2; }
     | '[' expr ']'              { $$ = new pwn::stackalloc_node(LINE, $2); }
     | '@'                            { $$ = new pwn::read_node(LINE); }
     | lval                           { $$ = new pwn::rvalue_node(LINE, $1); }
     | lval '=' expr                  { $$ = new pwn::assignment_node(LINE, $1, $3); }
     | tIDENTIFIER '(' exprlist ')'   { $$ = new pwn::funcall_node(LINE, $1, $3); }
     ;
     
strings : tSTRING              { $$ = $1; }
        | strings tSTRING      { $$ = new std::string(*$1+*$2); }
        ;
        
vardec : qualifier type tIDENTIFIER                     { $$ = new pwn::vardecl_node(LINE, isLocal($1), isImport($1), $3, $2); }
       | qualifier type tIDENTIFIER '=' expr            { $$ = new pwn::vardecl_node(LINE, isLocal($1), isImport($1), $3, $2, new pwn::assignment_node(LINE, new pwn::basic_lvalue_node(LINE, $3), $5)); }
       | qualifier '<' type '>' tIDENTIFIER             { $$ = new pwn::vardecl_node(LINE, isLocal($1), isImport($1), $5, $3); }
       | qualifier '<' type '>' tIDENTIFIER '=' expr    { $$ = new pwn::vardecl_node(LINE, isLocal($1), isImport($1), $5, $3, new pwn::assignment_node(LINE, new pwn::basic_lvalue_node(LINE, $5), $7)); }
       ;

type : '#'                     { $$ = new basic_type(sizeof(int), basic_type::TYPE_INT); }
     | '%'                     { $$ = new basic_type(sizeof(double), basic_type::TYPE_DOUBLE); }
     | '$'                     { $$ = new basic_type(sizeof(std::string), basic_type::TYPE_STRING); }
     | '*'                     { $$ = new basic_type(sizeof(void*), basic_type::TYPE_POINTER); }
     ;

lval : tIDENTIFIER         { $$ = new pwn::basic_lvalue_node(LINE, $1); }
     | expr '[' expr ']'   { $$ = new pwn::indexed_lvalue_node(LINE, $1, $3); }
     ;

%%

