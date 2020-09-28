#define tINTEGER 257
#define tREAL 258
#define tIDENTIFIER 259
#define tSTRING 260
#define tWHILE 261
#define tNEXT 262
#define tSTOP 263
#define tRETURN 264
#define tIF 265
#define tELSIF 266
#define tPRINTLINE 267
#define tSWEEP 268
#define tFROM 269
#define tTO 270
#define tAPPLY 271
#define tPROCEDURE 272
#define tPUBLIC 273
#define tUSE 274
#define tNULL 275
#define tTYPEINT 276
#define tTYPEREAL 277
#define tTYPESTRING 278
#define tIFX 279
#define tELSE 280
#define tEQ 281
#define tNE 282
#define tGE 283
#define tLE 284
#define tUNARY 285
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  int                   i;	/* integer value */
  double                r;      /* real value */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;
  basic_type           *type;
  xpl::block_node      *block;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
