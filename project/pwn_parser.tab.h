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
extern YYSTYPE yylval;
