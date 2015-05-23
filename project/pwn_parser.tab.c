/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "pwn_parser.y"
/* $Id: pwn_parser.y,v 1.18 2015/05/20 08:33:26 ist170916 Exp $*/
/*-- don't change *any* of these: if you do, you'll break the compiler.*/
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
/*-- don't change *any* of these --- END!*/

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

#line 31 "pwn_parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  int                   i;	/* integer value */
  double                d;      /* double value */
  std::string          *s;	/* symbol name or string literal */
  basic_type           *btype;
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  pwn::lvalue_node  *lvalue;
  pwn::fundecl_node *fundeclnode;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 74 "pwn_parser.y"
/*-- The rules below will be included in yyparse, the main parsing function.*/
#line 70 "pwn_parser.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define tINTEGER 257
#define tDOUBLE 258
#define tIDENTIFIER 259
#define tSTRING 260
#define tREPEAT 261
#define tIF 262
#define tPRINT 263
#define tREAD 264
#define tBEGIN 265
#define tEND 266
#define tPRINTLN 267
#define tLOCAL 268
#define tIMPORT 269
#define tNEXT 270
#define tSTOP 271
#define tRETURN 272
#define tNOOB 273
#define tIFX 274
#define tELSE 275
#define tEQ 276
#define tNE 277
#define tGE 278
#define tLE 279
#define tUNARY 280
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,   10,   10,   11,   11,    4,    4,    9,    9,    8,
    8,   13,   13,    6,    6,    7,    7,   18,   18,   18,
   12,   12,   12,   12,    1,    1,    1,    1,   17,   17,
   17,    3,    3,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,   14,   14,   14,   14,   14,
   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,
   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,
   14,   14,   19,   19,    5,    5,    5,    5,   16,   16,
   16,   16,   15,   15,
};
static const YYINT yylen[] = {                            2,
    1,    2,    1,    3,    2,    2,    1,    2,    1,    3,
    2,    3,    1,    1,    0,    1,    3,    1,    1,    0,
    4,    3,    3,    2,    6,    4,    6,    4,    1,    1,
    1,    1,    2,    2,    2,    2,    3,    3,    2,    2,
    1,    9,    5,    7,    1,    1,    1,    1,    1,    2,
    2,    2,    2,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    1,    1,
    3,    4,    1,    2,    3,    5,    5,    7,    1,    1,
    1,    1,    1,    4,
};
static const YYINT yydefred[] = {                         0,
   18,   19,    0,    0,    7,    3,    0,    0,    0,    0,
   33,    6,    2,    0,    0,   82,   80,   79,   81,    0,
   46,   49,    0,   73,    0,    0,    0,    0,   41,   47,
    0,    0,    0,    0,    0,   24,   69,    9,    0,    0,
    0,   45,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   40,    0,   39,    0,    0,    0,    0,
    0,    5,   22,    8,   23,    0,    0,   36,   35,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   53,
    0,    0,    0,    0,   34,    0,    0,   74,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   38,   37,
   68,   67,    4,   21,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   11,   13,    0,    0,    0,    0,    0,   72,    0,    0,
    0,   84,   10,    0,   29,   31,   30,   27,    0,   25,
    0,    0,    0,   12,    0,    0,    0,    0,   44,    0,
   42,
};
static const YYINT yydgoto[] = {                          3,
    4,   38,    5,    6,    7,   94,   95,   90,   40,    8,
   41,   42,  123,   43,   44,   20,  138,   45,   46,
};
static const YYINT yysindex[] = {                      -248,
    0,    0,    0, -115,    0,    0,  -32, -248,  324,  630,
    0,    0,    0, -224,   21,    0,    0,    0,    0, -220,
    0,    0,    7,    0,   26,   43,  -56,  -54,    0,    0,
  872,  872,  872,  872,  872,    0,    0,    0,  -10,  804,
  750,    0,  221,   11,  152, -175,   48,   30,  -21,  872,
  872,  872,   36,    0,   39,    0,  680,  258,  258,  528,
  606,    0,    0,    0,    0,   47,  864,    0,    0,  872,
  872,  872,  872,  872,  872,  872,  872,  872,  872,    0,
  872,  872,  872,  872,    0,  872, -170,    0,  -41,   53,
 -151,  872,   61,   68,   83,  738,   72,  646,    0,    0,
    0,    0,    0,    0,  539,  680,  749,  749,  148,  148,
  148,  148,  258,  258,   44,   44,   44,  673,  738,   78,
    0,    0,   23, -156,   80,  738, -156,    0,  872,  872,
  960,    0,    0, -248,    0,    0,    0,    0,  872,    0,
  738,   84, -130,    0,  738,  872,  960,  108,    0,  960,
    0,
};
static const YYINT yyrindex[] = {                       435,
    0,    0,    0,   17,    0,    0,    0,  298,    0,  237,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -31,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  237,    0,    0,   37,    0,   74,    0,    0,   98,  118,
  101,    0,    0,    0,    0,    0,  786,  249,  284,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  237,    1,
    0,    0,    9,    0,  -37,  -18,    0,    0,    0,    0,
    0,    0,    0,    0,  208,  787,  387,  496,  330,  400,
  425,  471,  337,  362,  109,  137,  172,    0,   32,   27,
    0,    0,    0,    0,   46,   79,    0,    0,    0,  101,
    0,    0,    0,  237,    0,    0,    0,    0,    0,    0,
   85,    0,  922,    0,  114,  118,    0,    0,    0,    0,
    0,
};
static const YYINT yygindex[] = {                         0,
    0,   73,    0,  154,   14,  -36,    0,  115,  122,    0,
    0,  162,    0, 1173,    0,    3,   49,   25,    0,
};
#define YYTABLESIZE 1319
static const YYINT yytable[] = {                        121,
   28,   83,   54,   14,   56,   83,   83,   10,   26,   83,
   83,   83,   83,   83,   97,   83,   32,   48,   89,    1,
    2,   14,   16,   39,    9,   16,   12,   83,   83,   83,
   83,   83,    9,   28,   47,   28,   28,   28,   49,   92,
   16,   26,   28,   26,   26,   26,   50,   87,   62,   32,
   26,   32,   32,   32,   66,   18,   19,   17,   32,   83,
   28,   83,   16,  133,   71,   51,  134,   75,   26,   70,
   75,   86,   71,   70,   70,   71,   32,   70,   70,   70,
   70,   70,   52,   70,   88,   75,   77,   89,  120,   77,
   71,   91,   83,  142,   99,   70,   70,  100,   70,   70,
  135,  136,  122,  137,   77,  103,   48,  125,  128,  148,
   48,   48,   64,  124,   48,   48,   48,   48,   48,   76,
   48,  127,   76,   28,   71,   17,  129,   70,   17,   70,
  130,   26,   48,   48,   84,   48,   48,   76,   92,   64,
  139,   56,  146,   17,  147,   56,   56,  144,  150,   56,
   56,   56,   56,   56,   78,   56,   75,   78,   15,   15,
   70,   13,   67,   93,   48,   11,   48,   56,   56,   57,
   56,   56,   78,   57,   57,  140,    0,   57,   57,   57,
   57,   57,    0,   57,   83,    0,   18,   19,   17,   81,
   78,    0,   79,   16,   82,   57,   57,   48,   57,   57,
   53,   56,   55,  143,   58,    0,    0,    0,   58,   58,
   80,   15,   58,   58,   58,   58,   58,    0,   58,  149,
    0,    0,  151,    0,    0,    0,    1,    2,    0,   57,
   58,   58,   56,   58,   58,   83,    0,    0,   84,    0,
   62,    0,    0,    0,   83,   83,   83,   83,   62,    0,
    0,   62,    0,   69,    0,    0,    0,   83,   71,    0,
   57,    0,   81,   78,   58,   79,   62,   82,   28,   28,
    0,   20,   20,   20,    0,    0,   26,   26,   20,   85,
   77,   51,   76,   80,   32,   32,   51,    0,    0,   51,
    0,   51,   51,   51,   83,   58,   20,    1,   71,   81,
   62,    0,    0,   70,   82,    0,    0,   51,   51,    0,
   51,   84,   70,   70,   70,   70,   50,    0,    0,    0,
   80,   50,    0,    0,   50,    0,   50,   50,   50,    0,
   20,   62,   20,   20,   20,    0,    0,    0,    0,   20,
   48,   51,   50,   50,   70,   50,    0,    0,   84,   48,
   48,   48,   48,    0,    0,    0,   14,   20,   18,   19,
   17,    0,   63,    0,    0,   16,    0,   63,    0,   54,
   63,    0,   51,   63,   54,   56,   50,   54,    0,   54,
   54,   54,    0,   15,   56,   56,   56,   56,   63,   63,
    0,   63,    0,    0,   55,   54,   54,    0,   54,   55,
    0,    0,   55,   57,   55,   55,   55,   50,    0,    0,
    0,    0,   57,   57,   57,   57,    0,    0,    0,   66,
   55,   55,   63,   55,   66,    0,    0,   66,    0,   54,
   66,    0,   64,    0,    0,    0,    0,   64,   58,    0,
   64,    0,    0,   64,    0,   66,    0,   58,   58,   58,
   58,    0,    0,   63,   55,    0,    0,   60,   64,   64,
   54,   64,   60,    0,    0,   60,    0,   20,   60,   20,
   20,   20,    0,    0,   62,    0,   20,    0,    0,   66,
    0,    0,    0,   60,   60,   55,   60,   68,    0,    0,
    0,    0,   64,    0,   20,    0,   72,   73,   74,   75,
    0,    0,    0,   59,    0,    0,    0,    0,   59,    0,
   66,   59,    0,    0,   59,   51,    0,   60,    0,    0,
    0,    0,    0,   64,   51,   51,   51,   51,   65,   59,
   59,    0,   59,   65,    0,    0,   65,    0,    0,   65,
    0,    0,    0,    0,    0,    0,    0,    0,   60,    0,
   50,    0,    0,    0,   65,    0,    0,    0,    0,   50,
   50,   50,   50,   59,   83,   71,    0,    0,    0,   81,
   78,    0,   79,    0,   82,   83,   71,    0,    0,    0,
   81,   78,    0,   79,    0,   82,    0,   77,   65,   76,
   80,    0,    0,    0,   59,    0,   63,    0,   77,    0,
   76,   80,    0,   54,    0,   63,   63,   63,   63,    0,
    0,    0,   54,   54,   54,   54,    0,    0,   84,   65,
  101,    0,    0,    0,    0,    0,    0,    0,   55,   84,
    0,    0,    0,    0,    0,    0,    0,   55,   55,   55,
   55,    0,   83,   71,    0,    0,  102,   81,   78,    0,
   79,   70,   82,   66,    0,    0,    0,    0,    0,    0,
    0,    0,   66,   66,    0,   77,   64,   76,   80,   35,
    0,    0,   32,    0,   33,   64,   64,   64,   64,    0,
    0,    0,   83,   71,    0,    0,  131,   81,   78,    0,
   79,   60,   82,   37,    0,    0,   84,    0,    0,    0,
   60,   60,   60,   60,    0,   77,    0,   76,   80,   83,
   71,    0,    0,    0,   81,   78,   83,   79,    0,   82,
   34,   81,   78,    0,   79,    0,   82,    0,    0,   70,
    0,    0,   77,    0,   76,   80,   84,   59,    0,   77,
    0,   76,   80,    0,    0,    0,   59,   59,   59,   59,
    0,    0,   10,    0,   36,   31,    0,    0,    0,    0,
    0,    0,   65,   84,    0,  132,    0,    0,    0,   70,
   84,   65,   65,    0,   83,   71,    0,    0,    0,   81,
   78,    0,   79,    0,   82,   83,    0,    0,    0,   35,
   81,   78,   32,   79,   33,   82,   70,   77,    0,   76,
   80,    0,    0,   72,   73,   74,   75,    0,   77,    0,
   76,   80,    0,   37,   72,   73,   74,   75,   52,   61,
    0,    0,    0,   52,   61,    0,   52,   61,   84,   52,
   61,    0,    0,    0,    0,    0,    0,    0,    0,   84,
   34,    0,    0,   35,   52,   61,   32,    0,   33,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   70,    0,    0,    0,    0,    0,   37,    0,    0,
    0,    0,   10,    0,   65,   31,    0,    0,   52,   61,
    0,   72,   73,   74,   75,    0,   21,   22,   23,   24,
   25,   26,    0,    0,   34,    0,    0,    1,    2,   27,
   28,   29,   30,   35,    0,    0,   32,    0,   33,   52,
   61,   35,    0,    0,   32,    0,   33,    0,    0,    0,
    0,   72,   73,   74,   75,    0,   10,   37,   63,   31,
    0,    0,    0,    0,    0,   37,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   72,   73,
   74,   75,    0,    0,   34,   72,   73,   74,   75,    0,
    0,   43,   34,    0,   43,    0,   43,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   43,   10,    0,  104,   31,
    0,    0,    0,    0,    0,    0,    0,   31,    0,   35,
    0,    0,   32,    0,   33,    0,   21,   22,   23,   24,
   25,   26,   43,   72,   73,   74,   75,    1,    2,   27,
   28,   29,   30,   37,    0,    0,   74,   75,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   43,    0,   43,   43,    0,    0,
   34,    0,   52,   61,    0,    0,    0,    0,    0,    0,
   21,   22,   23,   24,   25,   26,    0,    0,    0,    0,
    0,    0,    0,   27,   28,   29,   30,    0,    0,    0,
    0,    0,   10,    0,    0,   31,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   21,   22,   23,   24,   25,   26,    0,    0,   21,   22,
   23,   24,    0,   27,   28,   29,   30,    0,    0,    0,
    0,    0,    0,    0,   30,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   43,   43,
   43,   43,   43,   43,    0,    0,    0,    0,    0,    0,
    0,   43,   43,   43,   43,    0,    0,    0,    0,    0,
    0,    0,    0,   57,   58,   59,   60,   61,    0,    0,
    0,    0,    0,    0,    0,    0,   21,   22,   23,   24,
   25,   26,   96,   96,   98,    0,    0,    0,    0,   27,
   28,   29,   30,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  105,  106,  107,  108,  109,  110,  111,  112,
  113,  114,    0,  115,  116,  117,  118,    0,  119,    0,
    0,    0,    0,    0,  126,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  141,   96,    0,    0,    0,    0,    0,    0,    0,
    0,  145,    0,    0,    0,    0,    0,    0,   96,
};
static const YYINT yycheck[] = {                         41,
    0,   33,   59,   41,   59,   37,   38,  123,    0,   41,
   42,   43,   44,   45,   51,   47,    0,   15,   40,  268,
  269,   59,   41,   10,    0,   44,   59,   59,   60,   61,
   62,   63,    8,   33,  259,   35,   36,   37,  259,   61,
   59,   33,   42,   35,   36,   37,   40,   45,   59,   33,
   42,   35,   36,   37,   41,   35,   36,   37,   42,   91,
   60,   93,   42,   41,   33,   40,   44,   41,   60,   33,
   44,   61,   41,   37,   38,   44,   60,   41,   42,   43,
   44,   45,   40,   47,  260,   59,   41,   40,  259,   44,
   59,   62,  124,  130,   59,   59,   60,   59,   62,   63,
  257,  258,   89,  260,   59,   59,   33,  259,   41,  146,
   37,   38,   40,   61,   41,   42,   43,   44,   45,   41,
   47,   61,   44,  123,   93,   41,   44,   91,   44,   93,
   59,  123,   59,   60,   91,   62,   63,   59,   61,   67,
   61,   33,   59,   59,  275,   37,   38,  134,   41,   41,
   42,   43,   44,   45,   41,   47,   59,   44,   41,   59,
  124,    8,   41,   49,   91,    4,   93,   59,   60,   33,
   62,   63,   59,   37,   38,  127,   -1,   41,   42,   43,
   44,   45,   -1,   47,   37,   -1,   35,   36,   37,   42,
   43,   -1,   45,   42,   47,   59,   60,  124,   62,   63,
  257,   93,  257,  131,   33,   -1,   -1,   -1,   37,   38,
   63,   60,   41,   42,   43,   44,   45,   -1,   47,  147,
   -1,   -1,  150,   -1,   -1,   -1,  268,  269,   -1,   93,
   59,   60,  124,   62,   63,  267,   -1,   -1,   91,   -1,
   33,   -1,   -1,   -1,  276,  277,  278,  279,   41,   -1,
   -1,   44,   -1,   33,   -1,   -1,   -1,   37,   38,   -1,
  124,   -1,   42,   43,   93,   45,   59,   47,  268,  269,
   -1,   35,   36,   37,   -1,   -1,  268,  269,   42,   59,
   60,   33,   62,   63,  268,  269,   38,   -1,   -1,   41,
   -1,   43,   44,   45,   37,  124,   60,    0,  267,   42,
   93,   -1,   -1,  267,   47,   -1,   -1,   59,   60,   -1,
   62,   91,  276,  277,  278,  279,   33,   -1,   -1,   -1,
   63,   38,   -1,   -1,   41,   -1,   43,   44,   45,   -1,
   33,  124,   35,   36,   37,   -1,   -1,   -1,   -1,   42,
  267,   93,   59,   60,  124,   62,   -1,   -1,   91,  276,
  277,  278,  279,   -1,   -1,   -1,   33,   60,   35,   36,
   37,   -1,   33,   -1,   -1,   42,   -1,   38,   -1,   33,
   41,   -1,  124,   44,   38,  267,   93,   41,   -1,   43,
   44,   45,   -1,   60,  276,  277,  278,  279,   59,   60,
   -1,   62,   -1,   -1,   33,   59,   60,   -1,   62,   38,
   -1,   -1,   41,  267,   43,   44,   45,  124,   -1,   -1,
   -1,   -1,  276,  277,  278,  279,   -1,   -1,   -1,   33,
   59,   60,   93,   62,   38,   -1,   -1,   41,   -1,   93,
   44,   -1,   33,   -1,   -1,   -1,   -1,   38,  267,   -1,
   41,   -1,   -1,   44,   -1,   59,   -1,  276,  277,  278,
  279,   -1,   -1,  124,   93,   -1,   -1,   33,   59,   60,
  124,   62,   38,   -1,   -1,   41,   -1,   33,   44,   35,
   36,   37,   -1,   -1,  267,   -1,   42,   -1,   -1,   93,
   -1,   -1,   -1,   59,   60,  124,   62,  267,   -1,   -1,
   -1,   -1,   93,   -1,   60,   -1,  276,  277,  278,  279,
   -1,   -1,   -1,   33,   -1,   -1,   -1,   -1,   38,   -1,
  124,   41,   -1,   -1,   44,  267,   -1,   93,   -1,   -1,
   -1,   -1,   -1,  124,  276,  277,  278,  279,   33,   59,
   60,   -1,   62,   38,   -1,   -1,   41,   -1,   -1,   44,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,   -1,
  267,   -1,   -1,   -1,   59,   -1,   -1,   -1,   -1,  276,
  277,  278,  279,   93,   37,   38,   -1,   -1,   -1,   42,
   43,   -1,   45,   -1,   47,   37,   38,   -1,   -1,   -1,
   42,   43,   -1,   45,   -1,   47,   -1,   60,   93,   62,
   63,   -1,   -1,   -1,  124,   -1,  267,   -1,   60,   -1,
   62,   63,   -1,  267,   -1,  276,  277,  278,  279,   -1,
   -1,   -1,  276,  277,  278,  279,   -1,   -1,   91,  124,
   93,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  267,   91,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  276,  277,  278,
  279,   -1,   37,   38,   -1,   -1,   41,   42,   43,   -1,
   45,  124,   47,  267,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  276,  277,   -1,   60,  267,   62,   63,   40,
   -1,   -1,   43,   -1,   45,  276,  277,  278,  279,   -1,
   -1,   -1,   37,   38,   -1,   -1,   41,   42,   43,   -1,
   45,  267,   47,   64,   -1,   -1,   91,   -1,   -1,   -1,
  276,  277,  278,  279,   -1,   60,   -1,   62,   63,   37,
   38,   -1,   -1,   -1,   42,   43,   37,   45,   -1,   47,
   91,   42,   43,   -1,   45,   -1,   47,   -1,   -1,  124,
   -1,   -1,   60,   -1,   62,   63,   91,  267,   -1,   60,
   -1,   62,   63,   -1,   -1,   -1,  276,  277,  278,  279,
   -1,   -1,  123,   -1,  125,  126,   -1,   -1,   -1,   -1,
   -1,   -1,  267,   91,   -1,   93,   -1,   -1,   -1,  124,
   91,  276,  277,   -1,   37,   38,   -1,   -1,   -1,   42,
   43,   -1,   45,   -1,   47,   37,   -1,   -1,   -1,   40,
   42,   43,   43,   45,   45,   47,  124,   60,   -1,   62,
   63,   -1,   -1,  276,  277,  278,  279,   -1,   60,   -1,
   62,   63,   -1,   64,  276,  277,  278,  279,   33,   33,
   -1,   -1,   -1,   38,   38,   -1,   41,   41,   91,   44,
   44,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   91,
   91,   -1,   -1,   40,   59,   59,   43,   -1,   45,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  124,   -1,   -1,   -1,   -1,   -1,   64,   -1,   -1,
   -1,   -1,  123,   -1,  125,  126,   -1,   -1,   93,   93,
   -1,  276,  277,  278,  279,   -1,  257,  258,  259,  260,
  261,  262,   -1,   -1,   91,   -1,   -1,  268,  269,  270,
  271,  272,  273,   40,   -1,   -1,   43,   -1,   45,  124,
  124,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,
   -1,  276,  277,  278,  279,   -1,  123,   64,  125,  126,
   -1,   -1,   -1,   -1,   -1,   64,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  276,  277,
  278,  279,   -1,   -1,   91,  276,  277,  278,  279,   -1,
   -1,   40,   91,   -1,   43,   -1,   45,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   64,  123,   -1,  125,  126,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  126,   -1,   40,
   -1,   -1,   43,   -1,   45,   -1,  257,  258,  259,  260,
  261,  262,   91,  276,  277,  278,  279,  268,  269,  270,
  271,  272,  273,   64,   -1,   -1,  278,  279,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  123,   -1,  125,  126,   -1,   -1,
   91,   -1,  267,  267,   -1,   -1,   -1,   -1,   -1,   -1,
  257,  258,  259,  260,  261,  262,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  270,  271,  272,  273,   -1,   -1,   -1,
   -1,   -1,  123,   -1,   -1,  126,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  257,  258,  259,  260,  261,  262,   -1,   -1,  257,  258,
  259,  260,   -1,  270,  271,  272,  273,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  273,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,
  259,  260,  261,  262,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  270,  271,  272,  273,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   31,   32,   33,   34,   35,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,  260,
  261,  262,   50,   51,   52,   -1,   -1,   -1,   -1,  270,
  271,  272,  273,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   70,   71,   72,   73,   74,   75,   76,   77,
   78,   79,   -1,   81,   82,   83,   84,   -1,   86,   -1,
   -1,   -1,   -1,   -1,   92,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  129,  130,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  139,   -1,   -1,   -1,   -1,   -1,   -1,  146,
};
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 280
#define YYUNDFTOKEN 302
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,"'#'","'$'","'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,
0,0,0,0,0,0,0,0,0,0,"';'","'<'","'='","'>'","'?'","'@'",0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"'{'","'|'","'}'","'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"tINTEGER",
"tDOUBLE","tIDENTIFIER","tSTRING","tREPEAT","tIF","tPRINT","tREAD","tBEGIN",
"tEND","tPRINTLN","tLOCAL","tIMPORT","tNEXT","tSTOP","tRETURN","tNOOB","tIFX",
"tELSE","tEQ","tNE","tGE","tLE","tUNARY",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : file",
"file : declist",
"declist : declist declaration",
"declist : declaration",
"declistInsideBlock : declistInsideBlock vardec ';'",
"declistInsideBlock : vardec ';'",
"declaration : vardec ';'",
"declaration : function",
"stmtlist : stmtlist stmt",
"stmtlist : stmt",
"varlist : '(' varvars ')'",
"varlist : '(' ')'",
"varvars : varvars ',' vardec",
"varvars : vardec",
"exprlist : exprlist2",
"exprlist :",
"exprlist2 : expr",
"exprlist2 : exprlist2 ',' expr",
"qualifier : tLOCAL",
"qualifier : tIMPORT",
"qualifier :",
"block : '{' declistInsideBlock stmtlist '}'",
"block : '{' stmtlist '}'",
"block : '{' declistInsideBlock '}'",
"block : '{' '}'",
"fundecl : qualifier type tIDENTIFIER varlist '=' literal",
"fundecl : qualifier type tIDENTIFIER varlist",
"fundecl : qualifier '!' tIDENTIFIER varlist '=' literal",
"fundecl : qualifier '!' tIDENTIFIER varlist",
"literal : tINTEGER",
"literal : tSTRING",
"literal : tDOUBLE",
"function : fundecl",
"function : fundecl block",
"stmt : expr ';'",
"stmt : expr '!'",
"stmt : expr tPRINTLN",
"stmt : tSTOP tINTEGER ';'",
"stmt : tNEXT tINTEGER ';'",
"stmt : tSTOP ';'",
"stmt : tNEXT ';'",
"stmt : tRETURN",
"stmt : tREPEAT '(' exprlist ';' exprlist ';' exprlist ')' stmt",
"stmt : tIF '(' expr ')' stmt",
"stmt : tIF '(' expr ')' stmt tELSE stmt",
"stmt : block",
"expr : tINTEGER",
"expr : tNOOB",
"expr : strings",
"expr : tDOUBLE",
"expr : '-' expr",
"expr : '+' expr",
"expr : '~' expr",
"expr : expr '?'",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '%' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr '&' expr",
"expr : expr '|' expr",
"expr : expr tGE expr",
"expr : expr tLE expr",
"expr : expr tNE expr",
"expr : expr tEQ expr",
"expr : '(' expr ')'",
"expr : '[' expr ']'",
"expr : '@'",
"expr : lval",
"expr : lval '=' expr",
"expr : tIDENTIFIER '(' exprlist ')'",
"strings : tSTRING",
"strings : strings tSTRING",
"vardec : qualifier type tIDENTIFIER",
"vardec : qualifier type tIDENTIFIER '=' expr",
"vardec : qualifier '<' type '>' tIDENTIFIER",
"vardec : qualifier '<' type '>' tIDENTIFIER '=' expr",
"type : '#'",
"type : '%'",
"type : '$'",
"type : '*'",
"lval : tIDENTIFIER",
"lval : expr '[' expr ']'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 203 "pwn_parser.y"

#line 630 "pwn_parser.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 78 "pwn_parser.y"
	{ compiler->ast(yystack.l_mark[0].sequence); }
break;
case 2:
#line 81 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 3:
#line 82 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 4:
#line 85 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].node, yystack.l_mark[-2].sequence); }
break;
case 5:
#line 86 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].node); }
break;
case 6:
#line 89 "pwn_parser.y"
	{ yyval.node = yystack.l_mark[-1].node; }
break;
case 7:
#line 90 "pwn_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 8:
#line 93 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 9:
#line 94 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 10:
#line 97 "pwn_parser.y"
	{ yyval.sequence = yystack.l_mark[-1].sequence; }
break;
case 11:
#line 98 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, new cdk::nil_node(LINE)); }
break;
case 12:
#line 101 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-2].sequence); }
break;
case 13:
#line 102 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 14:
#line 105 "pwn_parser.y"
	{ yyval.sequence = yystack.l_mark[0].sequence; }
break;
case 15:
#line 106 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, new cdk::nil_node(LINE)); }
break;
case 16:
#line 109 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression); }
break;
case 17:
#line 110 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression, yystack.l_mark[-2].sequence); }
break;
case 18:
#line 113 "pwn_parser.y"
	{ yyval.i = LOCAL; }
break;
case 19:
#line 114 "pwn_parser.y"
	{ yyval.i = IMPORT; }
break;
case 20:
#line 115 "pwn_parser.y"
	{ yyval.i = NOQUALIFIER; }
break;
case 21:
#line 118 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].sequence, yystack.l_mark[-2].sequence); /* FIXME: BLOCK NODE. Allow func decls in some blocks??? */ }
break;
case 22:
#line 119 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].sequence); }
break;
case 23:
#line 120 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].sequence); }
break;
case 24:
#line 121 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, new cdk::nil_node(LINE)); }
break;
case 25:
#line 124 "pwn_parser.y"
	{ yyval.fundeclnode = new pwn::fundecl_node(LINE, isLocal(yystack.l_mark[-5].i), isImport(yystack.l_mark[-5].i), yystack.l_mark[-3].s, yystack.l_mark[-4].btype, new cdk::sequence_node(LINE, yystack.l_mark[-2].sequence)); /* FIXME: add default return */ }
break;
case 26:
#line 125 "pwn_parser.y"
	{ yyval.fundeclnode = new pwn::fundecl_node(LINE, isLocal(yystack.l_mark[-3].i), isImport(yystack.l_mark[-3].i), yystack.l_mark[-1].s, yystack.l_mark[-2].btype, new cdk::sequence_node(LINE, yystack.l_mark[0].sequence)); }
break;
case 27:
#line 126 "pwn_parser.y"
	{ yyval.fundeclnode = new pwn::fundecl_node(LINE, isLocal(yystack.l_mark[-5].i), isImport(yystack.l_mark[-5].i), yystack.l_mark[-3].s, new basic_type(sizeof(int), basic_type::TYPE_VOID), new cdk::sequence_node(LINE, yystack.l_mark[-2].sequence)); /* FIXME: add default return */ }
break;
case 28:
#line 127 "pwn_parser.y"
	{ yyval.fundeclnode = new pwn::fundecl_node(LINE, isLocal(yystack.l_mark[-3].i), isImport(yystack.l_mark[-3].i), yystack.l_mark[-1].s, new basic_type(sizeof(int), basic_type::TYPE_VOID), new cdk::sequence_node(LINE, yystack.l_mark[0].sequence)); }
break;
case 29:
#line 130 "pwn_parser.y"
	{ yyval.btype = new basic_type(sizeof(int), basic_type::TYPE_INT); }
break;
case 30:
#line 131 "pwn_parser.y"
	{ yyval.btype = new basic_type(sizeof(int), basic_type::TYPE_STRING); }
break;
case 31:
#line 132 "pwn_parser.y"
	{ yyval.btype = new basic_type(sizeof(int), basic_type::TYPE_DOUBLE); }
break;
case 32:
#line 135 "pwn_parser.y"
	{ yyval.node = yystack.l_mark[0].fundeclnode; }
break;
case 33:
#line 136 "pwn_parser.y"
	{ if(isImport(yystack.l_mark[-1].fundeclnode->import())) { yyerror("Can not define imported function."); } else { yyval.node = new pwn::fundef_node(LINE, yystack.l_mark[-1].fundeclnode, yystack.l_mark[0].sequence); } }
break;
case 34:
#line 139 "pwn_parser.y"
	{ yyval.node = new pwn::evaluation_node(LINE, yystack.l_mark[-1].expression); }
break;
case 35:
#line 140 "pwn_parser.y"
	{ yyval.node = new pwn::print_node(LINE, yystack.l_mark[-1].expression); }
break;
case 36:
#line 141 "pwn_parser.y"
	{ yyval.node = new pwn::println_node(LINE, new pwn::print_node(LINE, yystack.l_mark[-1].expression)); }
break;
case 37:
#line 142 "pwn_parser.y"
	{ yyval.node = new pwn::stop_node(LINE, new cdk::integer_node(LINE, yystack.l_mark[-1].i)); }
break;
case 38:
#line 143 "pwn_parser.y"
	{ yyval.node = new pwn::next_node(LINE, new cdk::integer_node(LINE, yystack.l_mark[-1].i)); }
break;
case 39:
#line 144 "pwn_parser.y"
	{ yyval.node = new pwn::stop_node(LINE, new cdk::integer_node(LINE, 1)); }
break;
case 40:
#line 145 "pwn_parser.y"
	{ yyval.node = new pwn::next_node(LINE, new cdk::integer_node(LINE, 1)); }
break;
case 41:
#line 146 "pwn_parser.y"
	{ yyval.node = new pwn::return_node(LINE); }
break;
case 42:
#line 147 "pwn_parser.y"
	{ yyval.node = new pwn::repeat_node(LINE, yystack.l_mark[-6].sequence, yystack.l_mark[-4].sequence, yystack.l_mark[-2].sequence, yystack.l_mark[0].node); }
break;
case 43:
#line 148 "pwn_parser.y"
	{ yyval.node = new cdk::if_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].node); }
break;
case 44:
#line 149 "pwn_parser.y"
	{ yyval.node = new cdk::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].node, yystack.l_mark[0].node); }
break;
case 45:
#line 150 "pwn_parser.y"
	{ yyval.node = yystack.l_mark[0].sequence; }
break;
case 46:
#line 153 "pwn_parser.y"
	{ yyval.expression = new cdk::integer_node(LINE, yystack.l_mark[0].i); }
break;
case 47:
#line 154 "pwn_parser.y"
	{ yyval.expression = new pwn::noob_node(LINE); }
break;
case 48:
#line 155 "pwn_parser.y"
	{ yyval.expression = new cdk::string_node(LINE, yystack.l_mark[0].s); }
break;
case 49:
#line 156 "pwn_parser.y"
	{ yyval.expression = new cdk::double_node(LINE, yystack.l_mark[0].d); }
break;
case 50:
#line 157 "pwn_parser.y"
	{ yyval.expression = new pwn::symmetric_node(LINE, yystack.l_mark[0].expression); }
break;
case 51:
#line 158 "pwn_parser.y"
	{ yyval.expression = new pwn::identity_node(LINE, yystack.l_mark[0].expression); }
break;
case 52:
#line 159 "pwn_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 53:
#line 160 "pwn_parser.y"
	{ /* TODO: address node */ }
break;
case 54:
#line 161 "pwn_parser.y"
	{ yyval.expression = new cdk::add_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 55:
#line 162 "pwn_parser.y"
	{ yyval.expression = new cdk::sub_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 56:
#line 163 "pwn_parser.y"
	{ yyval.expression = new cdk::mul_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 57:
#line 164 "pwn_parser.y"
	{ yyval.expression = new cdk::div_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 58:
#line 165 "pwn_parser.y"
	{ yyval.expression = new cdk::mod_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 59:
#line 166 "pwn_parser.y"
	{ yyval.expression = new cdk::lt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 60:
#line 167 "pwn_parser.y"
	{ yyval.expression = new cdk::gt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 61:
#line 168 "pwn_parser.y"
	{ yyval.expression = new pwn::and_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 62:
#line 169 "pwn_parser.y"
	{ yyval.expression = new pwn::or_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 63:
#line 170 "pwn_parser.y"
	{ yyval.expression = new cdk::ge_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 64:
#line 171 "pwn_parser.y"
	{ yyval.expression = new cdk::le_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 65:
#line 172 "pwn_parser.y"
	{ yyval.expression = new cdk::ne_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 66:
#line 173 "pwn_parser.y"
	{ yyval.expression = new cdk::eq_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 67:
#line 174 "pwn_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 68:
#line 175 "pwn_parser.y"
	{ yyval.expression = new pwn::stackalloc_node(LINE, yystack.l_mark[-1].expression); }
break;
case 69:
#line 176 "pwn_parser.y"
	{ yyval.expression = new pwn::read_node(LINE); }
break;
case 70:
#line 177 "pwn_parser.y"
	{ yyval.expression = new pwn::rvalue_node(LINE, yystack.l_mark[0].lvalue); }
break;
case 71:
#line 178 "pwn_parser.y"
	{ yyval.expression = new pwn::assignment_node(LINE, yystack.l_mark[-2].lvalue, yystack.l_mark[0].expression); }
break;
case 72:
#line 179 "pwn_parser.y"
	{ yyval.expression = new pwn::funcall_node(LINE, yystack.l_mark[-3].s, yystack.l_mark[-1].sequence); }
break;
case 73:
#line 182 "pwn_parser.y"
	{ yyval.s = yystack.l_mark[0].s; }
break;
case 74:
#line 183 "pwn_parser.y"
	{ yyval.s = new std::string(*yystack.l_mark[-1].s+*yystack.l_mark[0].s); }
break;
case 75:
#line 186 "pwn_parser.y"
	{ yyval.node = new pwn::vardecl_node(LINE, isLocal(yystack.l_mark[-2].i), isImport(yystack.l_mark[-2].i), yystack.l_mark[0].s, yystack.l_mark[-1].btype); }
break;
case 76:
#line 187 "pwn_parser.y"
	{ yyval.node = new pwn::vardecl_node(LINE, isLocal(yystack.l_mark[-4].i), isImport(yystack.l_mark[-4].i), yystack.l_mark[-2].s, yystack.l_mark[-3].btype, new pwn::assignment_node(LINE, new pwn::basic_lvalue_node(LINE, yystack.l_mark[-2].s), yystack.l_mark[0].expression)); }
break;
case 77:
#line 188 "pwn_parser.y"
	{ yyval.node = new pwn::vardecl_node(LINE, isLocal(yystack.l_mark[-4].i), isImport(yystack.l_mark[-4].i), yystack.l_mark[0].s, yystack.l_mark[-2].btype); }
break;
case 78:
#line 189 "pwn_parser.y"
	{ yyval.node = new pwn::vardecl_node(LINE, isLocal(yystack.l_mark[-6].i), isImport(yystack.l_mark[-6].i), yystack.l_mark[-2].s, yystack.l_mark[-4].btype, new pwn::assignment_node(LINE, new pwn::basic_lvalue_node(LINE, yystack.l_mark[-2].s), yystack.l_mark[0].expression)); }
break;
case 79:
#line 192 "pwn_parser.y"
	{ yyval.btype = new basic_type(sizeof(int), basic_type::TYPE_INT); }
break;
case 80:
#line 193 "pwn_parser.y"
	{ yyval.btype = new basic_type(sizeof(double), basic_type::TYPE_DOUBLE); }
break;
case 81:
#line 194 "pwn_parser.y"
	{ yyval.btype = new basic_type(sizeof(std::string), basic_type::TYPE_STRING); }
break;
case 82:
#line 195 "pwn_parser.y"
	{ yyval.btype = new basic_type(sizeof(void*), basic_type::TYPE_POINTER); }
break;
case 83:
#line 198 "pwn_parser.y"
	{ yyval.lvalue = new pwn::basic_lvalue_node(LINE, yystack.l_mark[0].s); }
break;
case 84:
#line 199 "pwn_parser.y"
	{ yyval.lvalue = new pwn::indexed_lvalue_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[-1].expression); }
break;
#line 1168 "pwn_parser.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
