/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20150711

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "xpl_parser.y"
/* $Id: xpl_parser.y,v 1.8 2017/05/19 23:03:20 ist182468 Exp $*/
/*-- don't change *any* of these: if you do, you'll break the compiler.*/
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
/*-- don't change *any* of these --- END!*/
#line 14 "xpl_parser.y"
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
#line 56 "xpl_parser.y"
/*-- The rules below will be included in yyparse, the main parsing function.*/
#line 53 "xpl_parser.tab.c"

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
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    1,    1,   10,   10,    7,   16,   16,    2,
    2,    2,    2,    2,   12,   12,   11,   11,    9,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,   20,   20,   20,   20,   21,   22,   22,   22,   22,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
   14,   14,    5,    8,    8,    8,    6,    6,    6,    6,
    6,   17,   17,   17,   17,   17,   17,   17,   17,   17,
   17,   17,   17,   17,   17,   17,   17,   17,   17,   17,
   17,   17,   17,   17,   17,   13,   13,   15,   15,   18,
   18,   18,   18,   23,   23,   19,   19,
};
static const YYINT yylen[] = {                            2,
    1,    0,    2,    1,    1,    2,    2,    1,    2,    5,
    4,    3,    3,    2,    1,    0,    1,    3,    2,    9,
    8,    7,    6,    7,    6,    6,    6,    6,    5,    6,
    5,    1,    1,    1,    3,    1,    4,    3,    3,    2,
    2,    2,    2,    1,    1,    1,    1,    1,    1,    8,
    1,    2,    2,    4,    6,    6,    5,   12,   10,   12,
   10,    1,    1,    2,    2,    2,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    2,    3,    3,
    3,    3,    1,    3,    4,    1,    3,    1,    0,    1,
    1,    1,    1,    1,    2,    1,    4,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,   32,   33,   34,    0,    0,    5,    0,
    4,    0,    0,    0,    0,    0,    0,    0,    0,    3,
    6,    0,    0,    0,    0,    0,    0,   35,    0,    0,
   17,    0,    0,    0,    0,    0,    0,    0,    0,   90,
   91,    0,   94,   93,    0,    0,    0,    0,    0,   63,
    0,   62,    0,    0,    0,    0,    0,   19,    0,    0,
    0,    0,    0,    0,   78,   65,   64,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   66,   95,    0,   18,    0,   25,
   36,    0,    0,   30,   28,    0,    0,    0,   82,   81,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   23,    0,   44,   45,
   46,    0,    0,    0,    0,    0,    0,   40,    0,   51,
   47,   48,    8,    0,    0,    0,    0,   49,   24,    0,
   22,    0,   85,   97,    0,    0,    0,   53,    0,    0,
    0,    0,    0,    7,   39,   52,   38,    9,    0,   43,
   41,   42,    0,    0,    0,   21,    0,    0,    0,    0,
    0,    0,   13,   37,   20,    0,    0,    0,    0,    0,
    0,   57,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   56,   55,    0,    0,    0,    0,    0,   50,    0,
    0,    0,    0,   59,    0,   61,    0,    0,    0,   58,
   60,
};
static const YYINT yydgoto[] = {                          8,
    9,   10,   11,  130,  131,  132,  133,  148,   31,   12,
   32,   33,   96,  134,   97,  135,  136,   52,   53,   34,
   90,  138,   54,
};
static const YYINT yysindex[] = {                       -82,
 -255,  -53,  -35,    0,    0,    0,  -32,    0,    0,  -40,
    0,  -82, -225,    5, -205, -204, -195, -184,  -17,    0,
    0,  -22,  -32,   42,  -20,   44,   50,    0,   -3,  -32,
    0,   59,   68, -168,  -32,   -3,  -32,  -32,  -32,    0,
    0,   90,    0,    0,   -3,   -3,   -3,   -3,   -3,    0,
 1037,    0,    7, -146,   97,  -32,   16,    0,   99, 1037,
  103,  111,  112,   -3,    0,    0,    0,  754,  659,   -3,
   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
   -3,   -3,   -3,   -3,    0,    0,  -58,    0, 1143,    0,
    0,   16,  -56,    0,    0,   87,  113, 1037,    0,    0,
 1103,  553, 1131, 1131,  434,  434,  434,  434,   10,   10,
   66,   66,   66,  765, 1037, -171,    0,  118,    0,    0,
    0,  121,   83,   -3,  -32,  -32,  999,    0,  109,    0,
    0,    0,    0, 1113, 1173,  427,  -90,    0,    0, -171,
    0,   -3,    0,    0,   16,   -3,   -3,    0,  130,  135,
  786,  -83,  -79,    0,    0,    0,    0,    0, 1203,    0,
    0,    0,  116,   16, 1037,    0,  812,  823,   -3,   -3,
   -3,  126,    0,    0,    0, 1266, 1266, 1037,   39,   47,
  853,    0, -245,   -3,   -3,  -70,  121, 1266,  888,  916,
  -77,    0,    0,   -3,   -3,  -57,  624,  720,    0, 1266,
   -3, 1266,   -3,    0,  928,    0,  968, 1266, 1266,    0,
    0,
};
static const YYINT yyrindex[] = {                       204,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  205,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  148,  168,    0,  153,    0,  154,    0,    0,  168,
    0,  180,    0,    0,  168,    0,  168,  168,  168,    0,
    0,  -31,    0,    0,    0,    0,    0,    0,    0,    0,
  163,    0,   74,   36,    0,    0,    1,    0,    0,  167,
    0,    0,    0,  188,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    8,    0,    0,    0,
    0,   15,   22,    0,    0,  189,    0,  -18,    0,    0,
  727, 1186,  310,  409,  369,  447,  470,  506,  271,  339,
  104,  141,  173,    0,   -8,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  148,    0,   81,    0,    0,    0,    0,    0,
    0,  153,    0,    0,    0,    0,    0,    0, 1071, 1071,
    0,    0, 1240,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,
};
static const YYINT yygindex[] = {                         0,
  226,  -72,    0,  426,    0,    0,  114,   60,  192,    0,
    0,  297,    0,  123,    0,    0, 1503, -116, -126,   46,
  -21,   63,    0,
};
#define YYTABLESIZE 1706
static const YYINT yytable[] = {                        145,
   31,   96,  116,   14,  140,   96,   96,   29,    7,   96,
   96,   96,   96,   96,   27,   96,  129,   30,   20,   37,
  187,   26,   86,  164,   84,   86,   96,   96,   96,   96,
   96,   96,   84,   22,  188,   84,   49,    7,   29,   46,
   36,   47,  179,  180,   23,   13,   82,   16,   18,   84,
   84,   80,   19,   24,   25,    7,   81,   13,    7,   96,
   50,   96,  129,   26,   89,  117,   89,   84,   92,   85,
  139,  141,   92,   92,   27,   28,   92,   92,   92,   92,
   92,   35,   92,   38,   84,   40,   41,   48,   43,   39,
   58,   31,   96,   92,   92,   92,  184,   92,   29,   84,
   83,   85,   56,   44,  185,   27,   83,   84,   57,   85,
   83,   83,   26,   86,   83,   83,   83,   83,   83,   91,
   83,   87,   45,  166,   87,  149,   92,  150,   92,   64,
  142,   83,   83,   83,  137,   83,   69,   87,   89,   92,
   69,   69,  175,   93,   69,   69,   69,   69,   69,   91,
   69,   94,   95,  143,   91,   91,   83,  146,   92,   92,
  147,   69,   69,   69,   83,   69,   83,  154,  163,  169,
  152,  153,   19,   70,  170,  172,   29,   70,   70,  173,
  137,   70,   70,   70,   70,   70,   36,   70,  191,    1,
    2,    3,  196,    4,    5,    6,   69,   83,   70,   70,
   70,  199,   70,    2,    1,   71,   14,   91,   16,   71,
   71,   12,   13,   71,   71,   71,   71,   71,   15,   71,
   15,   11,    4,    5,    6,   10,   91,   69,   89,   88,
   71,   71,   71,   70,   71,   96,   17,   21,   96,   96,
    4,    5,    6,    4,    5,    6,  192,   88,  158,   96,
   96,   96,   96,   40,   41,   42,   43,  159,   84,    0,
    0,   84,   84,    0,   70,   71,    0,    0,    0,    0,
    0,   44,   31,   31,   31,    0,   31,   31,   31,   29,
   29,   29,    0,   29,   29,   29,   27,   27,   27,    0,
   27,   27,   27,   26,   26,   26,   71,   26,   26,   26,
    0,    0,   92,   67,    0,   92,   92,    0,   67,    0,
    0,   67,    0,   67,   67,   67,   92,   92,   92,   92,
    0,    0,    0,    0,    0,    0,   55,    0,   67,   67,
   67,   59,   67,   61,   62,   63,    0,    0,    0,    0,
   83,    0,   77,   83,   83,    0,    0,   77,    0,    0,
   77,    0,    0,   77,   83,   83,   83,   83,    0,    0,
    0,    0,    0,   67,    0,    0,    0,   77,   77,    0,
   69,   68,    0,   69,   69,    0,   68,    0,    0,   68,
    0,   68,   68,   68,   69,   69,   69,   69,    0,    0,
    0,    0,    0,    0,   67,    0,   68,   68,   68,    0,
   68,   74,   77,    0,    0,    0,   74,   70,    0,   74,
   70,   70,   74,    0,    0,    0,    0,    0,    0,    0,
    0,   70,   70,   70,   70,    0,   74,   74,   74,    0,
   74,   68,    0,   77,    0,    0,    0,    0,    0,   71,
    0,   76,   71,   71,    0,    0,   76,    0,    0,   76,
    0,    0,   76,   71,   71,   71,   71,    0,    0,  162,
    0,   74,   68,   82,   71,    0,   76,   76,   80,   78,
   82,   79,    0,   81,    0,   80,   78,    0,   79,   75,
   81,    0,    0,    0,   75,  161,   77,   75,   76,    0,
   75,    0,   74,    0,    0,    0,    0,    0,    0,    0,
    0,   76,   73,    0,   75,   75,   75,   73,   75,    0,
   73,    0,    0,   73,    0,    0,    0,   83,    0,    0,
    0,    0,    0,    0,   83,    0,    0,   73,   73,   73,
    0,   73,   76,    0,    0,    0,    0,   67,   72,   75,
   67,   67,    0,   72,    0,    0,   72,    0,    0,   72,
   70,   67,   67,   67,   67,    0,    0,    0,    0,  156,
    0,    0,   73,   72,   72,   72,    0,   72,    0,    0,
   75,    0,    0,    0,    0,    0,   77,    0,    0,   77,
   77,    0,    0,    0,  156,    0,    0,    0,    0,   82,
   77,   77,    0,   73,   80,   78,    0,   79,   72,   81,
    0,  182,  183,    0,    0,   68,    0,    0,   68,   68,
    0,    0,   77,  193,   76,    0,    0,    0,    0,   68,
   68,   68,   68,    0,    0,  204,    0,  206,    0,   72,
    0,    0,    0,  210,  211,   74,    0,    0,   74,   74,
    0,    0,    0,   83,    0,    0,    0,    0,    0,   74,
   74,   74,   74,    0,    0,    0,    0,    0,    0,    0,
   82,   71,    0,    0,  200,   80,   78,    0,   79,    0,
   81,    0,    0,    0,    0,   76,    0,    0,   76,   76,
    0,  201,    0,   77,    0,   76,    0,    0,    0,   76,
   76,    0,    0,  160,    0,   82,   71,    0,    0,  100,
   80,   78,    0,   79,    0,   81,    0,   72,   73,   74,
   75,    0,    0,   75,   83,    0,   75,   75,   77,    0,
   76,    0,    0,    0,    0,    0,    0,   75,   75,   75,
   75,    0,    0,    0,    0,    0,   73,    0,    0,   73,
   73,    0,    0,    0,    0,    0,    0,   70,    0,   83,
   73,   73,   73,   73,    0,    0,   82,   71,    0,   80,
  202,   80,   78,    0,   79,    0,   81,   80,    0,    0,
   80,    0,   72,    0,    0,   72,   72,  203,    0,   77,
    0,   76,   70,    0,   80,   80,   72,   72,   72,   72,
   82,   71,    0,    0,    0,   80,   78,    0,   79,    0,
   81,   82,   71,    0,    0,    0,   80,   78,    0,   79,
   83,   81,    0,   77,    0,   76,    0,    0,    0,   80,
    0,    0,   82,   71,   77,    0,   76,   80,   78,    0,
   79,    0,   81,   72,   73,   74,   75,    0,    0,    0,
    0,    0,    0,   70,   83,   77,   99,   76,   82,   71,
   80,    0,  176,   80,   78,   83,   79,  144,   81,   82,
   71,    0,    0,  177,   80,   78,    0,   79,    0,   81,
    0,   77,    0,   76,    0,    0,   83,   70,    0,    0,
    0,    0,   77,    0,   76,    0,    0,    0,   70,   82,
   71,    0,    0,    0,   80,   78,    0,   79,    0,   81,
    0,    0,   83,    0,   72,   73,   74,   75,    0,   70,
    0,    0,   77,   83,   76,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   82,   71,    0,    0,    0,   80,
   78,    0,   79,    0,   81,   70,    0,    0,    0,   72,
   73,   74,   75,   83,    0,  194,   70,   77,    0,   76,
    0,    0,   82,   71,    0,    0,    0,   80,   78,    0,
   79,    0,   81,    0,   82,   71,    0,    0,  208,   80,
   78,    0,   79,  195,   81,   77,   70,   76,   83,    0,
    0,    0,    0,    0,    0,    0,    0,   77,    0,   76,
    0,    0,    0,   80,    0,    0,   80,   80,    0,    0,
   72,   73,   74,   75,   82,   71,   83,    0,  209,   80,
   78,   70,   79,    0,   81,    0,    0,    0,   83,    0,
    0,    0,    0,    0,    0,    0,    0,   77,    0,   76,
    0,    0,    0,    0,   72,   73,   74,   75,   49,   70,
    0,   46,    0,   47,    0,   72,   73,   74,   75,    0,
    0,   70,    0,    0,    0,  171,    0,    0,   83,    0,
    0,    0,   50,    0,    0,    0,   72,   73,   74,   75,
    0,    0,    0,   82,   71,    0,    0,    0,   80,   78,
    0,   79,    0,   81,    0,    0,    0,    0,    0,  127,
    0,   70,   72,   73,   74,   75,   77,    0,   76,    0,
    0,    0,    0,   72,   73,   74,   75,   83,   83,    0,
    0,    0,   83,   83,    0,   83,    0,   83,    0,    0,
    0,    0,    0,  186,   45,    0,    0,   83,    0,    0,
   83,    0,   83,   72,   73,   74,   75,    0,    0,   82,
   71,    0,    0,    0,   80,   78,    0,   79,    0,   81,
    0,    0,   49,    0,    0,   46,    0,   47,    0,    0,
   70,   83,   77,    0,   76,    0,    0,   82,   72,   73,
   74,   75,   80,   78,    0,   79,   50,   81,    0,    0,
    0,    0,   49,    0,    0,   46,    0,   47,    0,    0,
   77,    0,   76,   83,   83,    0,   72,   73,   74,   75,
    0,    0,    0,   48,    0,    0,   50,    0,   72,   73,
   74,   75,   49,    0,    0,   46,    0,   47,   79,    0,
    0,   83,    0,   79,    0,    0,   79,    0,    0,   79,
    0,    0,    0,  127,    0,   89,   50,  155,   45,    0,
    0,    0,   49,   79,   79,   46,    0,   47,   72,   73,
   74,   75,    0,    0,    0,   40,   41,   42,   43,    0,
    0,    0,    0,  127,    0,   89,   50,  128,   45,    0,
    0,    0,    0,   44,    4,    5,    6,    0,   79,   54,
    0,    0,   54,    0,   54,    0,    0,    0,    0,    0,
    0,    0,    0,   48,    0,   89,    0,  157,   45,    0,
    0,    0,    0,   54,    0,   49,    0,    0,   46,   79,
   47,    0,    0,    0,    0,    0,    0,   72,   73,   74,
   75,    0,    0,    0,    0,   89,    0,  174,   45,   50,
   54,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   83,   83,   83,   83,    0,   48,    0,    0,    0,
    0,    0,   54,    0,   54,   54,    0,    0,    0,   40,
   41,   42,   43,  118,  119,  120,  121,  122,    0,    0,
  123,  124,    0,   72,   73,   74,   75,   44,   89,    0,
    0,   45,    0,    0,    0,    0,    0,    0,    0,   40,
   41,   42,   43,  118,  119,  120,  121,  122,    0,    0,
  123,  124,    0,   74,   75,  125,  126,   44,    4,    5,
    6,    0,    0,    0,    0,    0,    0,    0,    0,   40,
   41,   42,   43,  118,  119,  120,  121,  122,    0,    0,
  123,  124,    0,    0,    0,  125,  126,   44,    4,    5,
    6,    0,   79,    0,    0,   79,   79,    0,    0,   40,
   41,   42,   43,  118,  119,  120,  121,  122,    0,    0,
  123,  124,    0,    0,    0,    0,    0,   44,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   54,   54,   54,   54,
   54,   54,   54,   54,   54,    0,    0,   54,   54,    0,
    0,    0,    0,    0,   54,    0,    0,    0,    0,    0,
    0,    0,   40,   41,   42,   43,  118,  119,  120,  121,
  122,   51,    0,  123,  124,    0,    0,    0,   60,    0,
   44,    0,    0,    0,    0,    0,    0,   65,   66,   67,
   68,   69,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   98,    0,    0,    0,
    0,    0,  101,  102,  103,  104,  105,  106,  107,  108,
  109,  110,  111,  112,  113,  114,  115,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  151,    0,    0,   68,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  165,    0,    0,    0,  167,  168,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  178,  178,  181,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  189,  190,    0,    0,
    0,    0,    0,    0,    0,    0,  197,  198,    0,    0,
    0,    0,    0,  205,    0,  207,
};
static const YYINT yycheck[] = {                        116,
    0,   33,   61,  259,   61,   37,   38,    0,   91,   41,
   42,   43,   44,   45,    0,   47,   89,   40,   59,   40,
  266,    0,   41,  140,   33,   44,   58,   59,   60,   61,
   62,   63,   41,  259,  280,   44,   40,   91,   61,   43,
   61,   45,  169,  170,   40,    0,   37,    2,    3,   58,
   59,   42,    7,  259,  259,   91,   47,   12,   91,   91,
   64,   93,  135,  259,  123,   87,  123,   61,   33,   63,
   92,   93,   37,   38,  259,   93,   41,   42,   43,   44,
   45,   40,   47,   40,   93,  257,  258,   91,  260,   40,
  259,   91,  124,   58,   59,   60,   58,   62,   91,   61,
   91,   63,   44,  275,   58,   91,   33,   61,   41,   63,
   37,   38,   91,  260,   41,   42,   43,   44,   45,   57,
   47,   41,  126,  145,   44,   43,   91,   45,   93,   40,
   44,   58,   59,   60,   89,   62,   33,   41,  123,   41,
   37,   38,  164,   41,   41,   42,   43,   44,   45,   87,
   47,   41,   41,   41,   92,   93,   91,   40,  123,  124,
   40,   58,   59,   60,   91,   62,   93,   59,  259,   40,
  125,  126,  127,   33,   40,  259,   61,   37,   38,  259,
  135,   41,   42,   43,   44,   45,   61,   47,  259,  272,
  273,  274,  270,  276,  277,  278,   93,  124,   58,   59,
   60,  259,   62,    0,    0,   33,   59,  145,   41,   37,
   38,   59,   59,   41,   42,   43,   44,   45,  272,   47,
   41,   59,  276,  277,  278,   59,  164,  124,   41,   41,
   58,   59,   60,   93,   62,  267,  272,   12,  270,  271,
  276,  277,  278,  276,  277,  278,  187,   56,  135,  281,
  282,  283,  284,  257,  258,  259,  260,  135,  267,   -1,
   -1,  270,  271,   -1,  124,   93,   -1,   -1,   -1,   -1,
   -1,  275,  272,  273,  274,   -1,  276,  277,  278,  272,
  273,  274,   -1,  276,  277,  278,  272,  273,  274,   -1,
  276,  277,  278,  272,  273,  274,  124,  276,  277,  278,
   -1,   -1,  267,   33,   -1,  270,  271,   -1,   38,   -1,
   -1,   41,   -1,   43,   44,   45,  281,  282,  283,  284,
   -1,   -1,   -1,   -1,   -1,   -1,   30,   -1,   58,   59,
   60,   35,   62,   37,   38,   39,   -1,   -1,   -1,   -1,
  267,   -1,   33,  270,  271,   -1,   -1,   38,   -1,   -1,
   41,   -1,   -1,   44,  281,  282,  283,  284,   -1,   -1,
   -1,   -1,   -1,   93,   -1,   -1,   -1,   58,   59,   -1,
  267,   33,   -1,  270,  271,   -1,   38,   -1,   -1,   41,
   -1,   43,   44,   45,  281,  282,  283,  284,   -1,   -1,
   -1,   -1,   -1,   -1,  124,   -1,   58,   59,   60,   -1,
   62,   33,   93,   -1,   -1,   -1,   38,  267,   -1,   41,
  270,  271,   44,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  281,  282,  283,  284,   -1,   58,   59,   60,   -1,
   62,   93,   -1,  124,   -1,   -1,   -1,   -1,   -1,  267,
   -1,   33,  270,  271,   -1,   -1,   38,   -1,   -1,   41,
   -1,   -1,   44,  281,  282,  283,  284,   -1,   -1,   33,
   -1,   93,  124,   37,   38,   -1,   58,   59,   42,   43,
   37,   45,   -1,   47,   -1,   42,   43,   -1,   45,   33,
   47,   -1,   -1,   -1,   38,   59,   60,   41,   62,   -1,
   44,   -1,  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   93,   33,   -1,   58,   59,   60,   38,   62,   -1,
   41,   -1,   -1,   44,   -1,   -1,   -1,   91,   -1,   -1,
   -1,   -1,   -1,   -1,   91,   -1,   -1,   58,   59,   60,
   -1,   62,  124,   -1,   -1,   -1,   -1,  267,   33,   93,
  270,  271,   -1,   38,   -1,   -1,   41,   -1,   -1,   44,
  124,  281,  282,  283,  284,   -1,   -1,   -1,   -1,  134,
   -1,   -1,   93,   58,   59,   60,   -1,   62,   -1,   -1,
  124,   -1,   -1,   -1,   -1,   -1,  267,   -1,   -1,  270,
  271,   -1,   -1,   -1,  159,   -1,   -1,   -1,   -1,   37,
  281,  282,   -1,  124,   42,   43,   -1,   45,   93,   47,
   -1,  176,  177,   -1,   -1,  267,   -1,   -1,  270,  271,
   -1,   -1,   60,  188,   62,   -1,   -1,   -1,   -1,  281,
  282,  283,  284,   -1,   -1,  200,   -1,  202,   -1,  124,
   -1,   -1,   -1,  208,  209,  267,   -1,   -1,  270,  271,
   -1,   -1,   -1,   91,   -1,   -1,   -1,   -1,   -1,  281,
  282,  283,  284,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   37,   38,   -1,   -1,   41,   42,   43,   -1,   45,   -1,
   47,   -1,   -1,   -1,   -1,  267,   -1,   -1,  270,  271,
   -1,   58,   -1,   60,   -1,   62,   -1,   -1,   -1,  281,
  282,   -1,   -1,  267,   -1,   37,   38,   -1,   -1,   41,
   42,   43,   -1,   45,   -1,   47,   -1,  281,  282,  283,
  284,   -1,   -1,  267,   91,   -1,  270,  271,   60,   -1,
   62,   -1,   -1,   -1,   -1,   -1,   -1,  281,  282,  283,
  284,   -1,   -1,   -1,   -1,   -1,  267,   -1,   -1,  270,
  271,   -1,   -1,   -1,   -1,   -1,   -1,  124,   -1,   91,
  281,  282,  283,  284,   -1,   -1,   37,   38,   -1,   33,
   41,   42,   43,   -1,   45,   -1,   47,   41,   -1,   -1,
   44,   -1,  267,   -1,   -1,  270,  271,   58,   -1,   60,
   -1,   62,  124,   -1,   58,   59,  281,  282,  283,  284,
   37,   38,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,
   47,   37,   38,   -1,   -1,   -1,   42,   43,   -1,   45,
   91,   47,   -1,   60,   -1,   62,   -1,   -1,   -1,   93,
   -1,   -1,   37,   38,   60,   -1,   62,   42,   43,   -1,
   45,   -1,   47,  281,  282,  283,  284,   -1,   -1,   -1,
   -1,   -1,   -1,  124,   91,   60,   93,   62,   37,   38,
  124,   -1,   41,   42,   43,   91,   45,   93,   47,   37,
   38,   -1,   -1,   41,   42,   43,   -1,   45,   -1,   47,
   -1,   60,   -1,   62,   -1,   -1,   91,  124,   -1,   -1,
   -1,   -1,   60,   -1,   62,   -1,   -1,   -1,  124,   37,
   38,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,
   -1,   -1,   91,   -1,  281,  282,  283,  284,   -1,  124,
   -1,   -1,   60,   91,   62,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   37,   38,   -1,   -1,   -1,   42,
   43,   -1,   45,   -1,   47,  124,   -1,   -1,   -1,  281,
  282,  283,  284,   91,   -1,   58,  124,   60,   -1,   62,
   -1,   -1,   37,   38,   -1,   -1,   -1,   42,   43,   -1,
   45,   -1,   47,   -1,   37,   38,   -1,   -1,   41,   42,
   43,   -1,   45,   58,   47,   60,  124,   62,   91,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,   -1,   62,
   -1,   -1,   -1,  267,   -1,   -1,  270,  271,   -1,   -1,
  281,  282,  283,  284,   37,   38,   91,   -1,   41,   42,
   43,  124,   45,   -1,   47,   -1,   -1,   -1,   91,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,   -1,   62,
   -1,   -1,   -1,   -1,  281,  282,  283,  284,   40,  124,
   -1,   43,   -1,   45,   -1,  281,  282,  283,  284,   -1,
   -1,  124,   -1,   -1,   -1,  270,   -1,   -1,   91,   -1,
   -1,   -1,   64,   -1,   -1,   -1,  281,  282,  283,  284,
   -1,   -1,   -1,   37,   38,   -1,   -1,   -1,   42,   43,
   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   91,
   -1,  124,  281,  282,  283,  284,   60,   -1,   62,   -1,
   -1,   -1,   -1,  281,  282,  283,  284,   37,   38,   -1,
   -1,   -1,   42,   43,   -1,   45,   -1,   47,   -1,   -1,
   -1,   -1,   -1,  271,  126,   -1,   -1,   91,   -1,   -1,
   60,   -1,   62,  281,  282,  283,  284,   -1,   -1,   37,
   38,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,
   -1,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,
  124,   91,   60,   -1,   62,   -1,   -1,   37,  281,  282,
  283,  284,   42,   43,   -1,   45,   64,   47,   -1,   -1,
   -1,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,
   60,   -1,   62,   91,  124,   -1,  281,  282,  283,  284,
   -1,   -1,   -1,   91,   -1,   -1,   64,   -1,  281,  282,
  283,  284,   40,   -1,   -1,   43,   -1,   45,   33,   -1,
   -1,   91,   -1,   38,   -1,   -1,   41,   -1,   -1,   44,
   -1,   -1,   -1,   91,   -1,  123,   64,  125,  126,   -1,
   -1,   -1,   40,   58,   59,   43,   -1,   45,  281,  282,
  283,  284,   -1,   -1,   -1,  257,  258,  259,  260,   -1,
   -1,   -1,   -1,   91,   -1,  123,   64,  125,  126,   -1,
   -1,   -1,   -1,  275,  276,  277,  278,   -1,   93,   40,
   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   91,   -1,  123,   -1,  125,  126,   -1,
   -1,   -1,   -1,   64,   -1,   40,   -1,   -1,   43,  124,
   45,   -1,   -1,   -1,   -1,   -1,   -1,  281,  282,  283,
  284,   -1,   -1,   -1,   -1,  123,   -1,  125,  126,   64,
   91,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  281,  282,  283,  284,   -1,   91,   -1,   -1,   -1,
   -1,   -1,  123,   -1,  125,  126,   -1,   -1,   -1,  257,
  258,  259,  260,  261,  262,  263,  264,  265,   -1,   -1,
  268,  269,   -1,  281,  282,  283,  284,  275,  123,   -1,
   -1,  126,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,
  258,  259,  260,  261,  262,  263,  264,  265,   -1,   -1,
  268,  269,   -1,  283,  284,  273,  274,  275,  276,  277,
  278,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,
  258,  259,  260,  261,  262,  263,  264,  265,   -1,   -1,
  268,  269,   -1,   -1,   -1,  273,  274,  275,  276,  277,
  278,   -1,  267,   -1,   -1,  270,  271,   -1,   -1,  257,
  258,  259,  260,  261,  262,  263,  264,  265,   -1,   -1,
  268,  269,   -1,   -1,   -1,   -1,   -1,  275,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,  260,
  261,  262,  263,  264,  265,   -1,   -1,  268,  269,   -1,
   -1,   -1,   -1,   -1,  275,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  257,  258,  259,  260,  261,  262,  263,  264,
  265,   29,   -1,  268,  269,   -1,   -1,   -1,   36,   -1,
  275,   -1,   -1,   -1,   -1,   -1,   -1,   45,   46,   47,
   48,   49,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   64,   -1,   -1,   -1,
   -1,   -1,   70,   71,   72,   73,   74,   75,   76,   77,
   78,   79,   80,   81,   82,   83,   84,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  124,   -1,   -1,  127,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  142,   -1,   -1,   -1,  146,  147,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  169,  170,  171,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  184,  185,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  194,  195,   -1,   -1,
   -1,   -1,   -1,  201,   -1,  203,
};
#define YYFINAL 8
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 285
#define YYUNDFTOKEN 311
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,
0,0,0,0,0,"':'","';'","'<'","'='","'>'","'?'","'@'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"'{'","'|'","'}'","'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"tINTEGER","tREAL",
"tIDENTIFIER","tSTRING","tWHILE","tNEXT","tSTOP","tRETURN","tIF","tELSIF",
"tPRINTLINE","tSWEEP","tFROM","tTO","tAPPLY","tPROCEDURE","tPUBLIC","tUSE",
"tNULL","tTYPEINT","tTYPEREAL","tTYPESTRING","tIFX","tELSE","tEQ","tNE","tGE",
"tLE","tUNARY",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : file",
"file : decls",
"file :",
"decl : variable ';'",
"decl : function",
"decls : decl",
"decls : decls decl",
"declvar : variable ';'",
"declsvar : declvar",
"declsvar : declsvar declvar",
"variable : tPUBLIC type tIDENTIFIER '=' expr",
"variable : type tIDENTIFIER '=' expr",
"variable : tPUBLIC type tIDENTIFIER",
"variable : tUSE type tIDENTIFIER",
"variable : type tIDENTIFIER",
"functionvars : fvars",
"functionvars :",
"fvars : fvar",
"fvars : fvars ',' fvar",
"fvar : type tIDENTIFIER",
"function : tPUBLIC type tIDENTIFIER '(' functionvars ')' '=' literal body",
"function : type tIDENTIFIER '(' functionvars ')' '=' literal body",
"function : tPUBLIC type tIDENTIFIER '(' functionvars ')' body",
"function : type tIDENTIFIER '(' functionvars ')' body",
"function : tPUBLIC tPROCEDURE tIDENTIFIER '(' functionvars ')' body",
"function : tPROCEDURE tIDENTIFIER '(' functionvars ')' body",
"function : tPUBLIC type tIDENTIFIER '(' functionvars ')'",
"function : tPUBLIC tPROCEDURE tIDENTIFIER '(' functionvars ')'",
"function : tUSE type tIDENTIFIER '(' functionvars ')'",
"function : type tIDENTIFIER '(' functionvars ')'",
"function : tUSE tPROCEDURE tIDENTIFIER '(' functionvars ')'",
"function : tPROCEDURE tIDENTIFIER '(' functionvars ')'",
"type : tTYPEINT",
"type : tTYPEREAL",
"type : tTYPESTRING",
"type : '[' type ']'",
"body : block",
"block : '{' declsvar instrs '}'",
"block : '{' declsvar '}'",
"block : '{' instrs '}'",
"block : '{' '}'",
"instr : expr ';'",
"instr : expr '!'",
"instr : expr tPRINTLINE",
"instr : tNEXT",
"instr : tSTOP",
"instr : tRETURN",
"instr : condinstr",
"instr : loopinstr",
"instr : block",
"instr : tFROM expr tTO expr tAPPLY tIDENTIFIER tTO tIDENTIFIER",
"instrs : instr",
"instrs : instrs instr",
"condinstr : tIF condinstrelseif",
"condinstrelseif : '(' expr ')' instr",
"condinstrelseif : '(' expr ')' instr tELSE instr",
"condinstrelseif : '(' expr ')' instr tELSIF condinstrelseif",
"loopinstr : tWHILE '(' expr ')' instr",
"loopinstr : tSWEEP '+' '(' lval ':' expr ':' expr ':' expr ')' instr",
"loopinstr : tSWEEP '+' '(' lval ':' expr ':' expr ')' instr",
"loopinstr : tSWEEP '-' '(' lval ':' expr ':' expr ':' expr ')' instr",
"loopinstr : tSWEEP '-' '(' lval ':' expr ':' expr ')' instr",
"expr : literal",
"expr : '@'",
"expr : '-' expr",
"expr : '+' expr",
"expr : lval '?'",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '%' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr tGE expr",
"expr : expr tLE expr",
"expr : expr tNE expr",
"expr : expr tEQ expr",
"expr : '~' expr",
"expr : expr '&' expr",
"expr : expr '|' expr",
"expr : '(' expr ')'",
"expr : '[' expr ']'",
"expr : lval",
"expr : lval '=' expr",
"expr : tIDENTIFIER '(' functionargs ')'",
"exprs : expr",
"exprs : exprs ',' expr",
"functionargs : exprs",
"functionargs :",
"literal : tINTEGER",
"literal : tREAL",
"literal : strings",
"literal : tNULL",
"strings : tSTRING",
"strings : strings tSTRING",
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
#line 60 "xpl_parser.y"
	{ compiler->ast(yystack.l_mark[0].sequence); }
break;
case 2:
#line 61 "xpl_parser.y"
	{ yyval.node = NULL; }
break;
case 3:
#line 64 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[-1].node; }
break;
case 4:
#line 65 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 5:
#line 68 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node); }
break;
case 6:
#line 69 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node,yystack.l_mark[-1].sequence); }
break;
case 7:
#line 72 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[-1].node; }
break;
case 8:
#line 75 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node); }
break;
case 9:
#line 76 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node,yystack.l_mark[-1].sequence); }
break;
case 10:
#line 79 "xpl_parser.y"
	{ yyval.node = new xpl::var_inicialization_node(LINE,true,yystack.l_mark[-3].type,yystack.l_mark[-2].s,yystack.l_mark[0].expression); }
break;
case 11:
#line 80 "xpl_parser.y"
	{ yyval.node = new xpl::var_inicialization_node(LINE,false,yystack.l_mark[-3].type,yystack.l_mark[-2].s,yystack.l_mark[0].expression); }
break;
case 12:
#line 81 "xpl_parser.y"
	{ yyval.node = new xpl::var_declaration_node(LINE,true,false,yystack.l_mark[-1].type,yystack.l_mark[0].s); }
break;
case 13:
#line 82 "xpl_parser.y"
	{ yyval.node = new xpl::var_declaration_node(LINE,false,true,yystack.l_mark[-1].type,yystack.l_mark[0].s); }
break;
case 14:
#line 83 "xpl_parser.y"
	{ yyval.node = new xpl::var_declaration_node(LINE,false,false,yystack.l_mark[-1].type,yystack.l_mark[0].s); }
break;
case 15:
#line 86 "xpl_parser.y"
	{ yyval.sequence = yystack.l_mark[0].sequence; }
break;
case 16:
#line 87 "xpl_parser.y"
	{ yyval.sequence = NULL; }
break;
case 17:
#line 90 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node); }
break;
case 18:
#line 91 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node,yystack.l_mark[-2].sequence); }
break;
case 19:
#line 94 "xpl_parser.y"
	{ yyval.node = new xpl::var_declaration_node(LINE,false,false,yystack.l_mark[-1].type,yystack.l_mark[0].s); }
break;
case 20:
#line 97 "xpl_parser.y"
	{ yyval.node = new xpl::func_definition_node(LINE,true,yystack.l_mark[-7].type,yystack.l_mark[-6].s,yystack.l_mark[-4].sequence,yystack.l_mark[-1].expression,yystack.l_mark[0].block); }
break;
case 21:
#line 98 "xpl_parser.y"
	{ yyval.node = new xpl::func_definition_node(LINE,false,yystack.l_mark[-7].type,yystack.l_mark[-6].s,yystack.l_mark[-4].sequence,yystack.l_mark[-1].expression,yystack.l_mark[0].block); }
break;
case 22:
#line 99 "xpl_parser.y"
	{ yyval.node = new xpl::func_definition_node(LINE,true,yystack.l_mark[-5].type,yystack.l_mark[-4].s,yystack.l_mark[-2].sequence,NULL,yystack.l_mark[0].block); }
break;
case 23:
#line 100 "xpl_parser.y"
	{ yyval.node = new xpl::func_definition_node(LINE,false,yystack.l_mark[-5].type,yystack.l_mark[-4].s,yystack.l_mark[-2].sequence,NULL,yystack.l_mark[0].block); }
break;
case 24:
#line 101 "xpl_parser.y"
	{ yyval.node = new xpl::func_definition_node(LINE,true,new basic_type(0, basic_type::TYPE_VOID),yystack.l_mark[-4].s,yystack.l_mark[-2].sequence,NULL,yystack.l_mark[0].block); }
break;
case 25:
#line 102 "xpl_parser.y"
	{ yyval.node = new xpl::func_definition_node(LINE,false,new basic_type(0, basic_type::TYPE_VOID),yystack.l_mark[-4].s,yystack.l_mark[-2].sequence,NULL,yystack.l_mark[0].block); }
break;
case 26:
#line 103 "xpl_parser.y"
	{ yyval.node = new xpl::func_declaration_node(LINE,true,false,yystack.l_mark[-4].type,yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 27:
#line 104 "xpl_parser.y"
	{ yyval.node = new xpl::func_declaration_node(LINE,true,false,new basic_type(0, basic_type::TYPE_VOID),yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 28:
#line 105 "xpl_parser.y"
	{ yyval.node = new xpl::func_declaration_node(LINE,false,true,yystack.l_mark[-4].type,yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 29:
#line 106 "xpl_parser.y"
	{ yyval.node = new xpl::func_declaration_node(LINE,false,false,yystack.l_mark[-4].type,yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 30:
#line 107 "xpl_parser.y"
	{ yyval.node = new xpl::func_declaration_node(LINE,false,true,new basic_type(0, basic_type::TYPE_VOID),yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 31:
#line 108 "xpl_parser.y"
	{ yyval.node = new xpl::func_declaration_node(LINE,false,false,new basic_type(0, basic_type::TYPE_VOID),yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 32:
#line 112 "xpl_parser.y"
	{ yyval.type = new basic_type(sizeof(int), basic_type::TYPE_INT); }
break;
case 33:
#line 113 "xpl_parser.y"
	{ yyval.type = new basic_type(sizeof(double), basic_type::TYPE_DOUBLE); }
break;
case 34:
#line 114 "xpl_parser.y"
	{ yyval.type = new basic_type(sizeof(std::string), basic_type::TYPE_STRING); }
break;
case 35:
#line 115 "xpl_parser.y"
	{ yyval.type = new basic_type(sizeof(void*), basic_type::TYPE_POINTER); yyval.type->_subtype = yystack.l_mark[-1].type; }
break;
case 36:
#line 118 "xpl_parser.y"
	{ yyval.block = yystack.l_mark[0].block; }
break;
case 37:
#line 121 "xpl_parser.y"
	{ yyval.block = new xpl::block_node(LINE,yystack.l_mark[-2].sequence,yystack.l_mark[-1].sequence); }
break;
case 38:
#line 122 "xpl_parser.y"
	{ yyval.block = new xpl::block_node(LINE,yystack.l_mark[-1].sequence,NULL); }
break;
case 39:
#line 123 "xpl_parser.y"
	{ yyval.block = new xpl::block_node(LINE,NULL,yystack.l_mark[-1].sequence); }
break;
case 40:
#line 124 "xpl_parser.y"
	{ yyval.block = new xpl::block_node(LINE,NULL,NULL); }
break;
case 41:
#line 127 "xpl_parser.y"
	{ yyval.node = new xpl::evaluation_node(LINE,yystack.l_mark[-1].expression); }
break;
case 42:
#line 128 "xpl_parser.y"
	{ yyval.node = new xpl::print_node(LINE,yystack.l_mark[-1].expression);}
break;
case 43:
#line 129 "xpl_parser.y"
	{ yyval.node = new xpl::print_line_node(LINE,yystack.l_mark[-1].expression);}
break;
case 44:
#line 130 "xpl_parser.y"
	{ yyval.node = new xpl::next_node(LINE); }
break;
case 45:
#line 131 "xpl_parser.y"
	{ yyval.node = new xpl::stop_node(LINE); }
break;
case 46:
#line 132 "xpl_parser.y"
	{ yyval.node = new xpl::return_node(LINE); }
break;
case 47:
#line 133 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 48:
#line 134 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 49:
#line 135 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].block; }
break;
case 50:
#line 136 "xpl_parser.y"
	{ yyval.node = new xpl::apply_function_node(LINE,yystack.l_mark[-6].expression,yystack.l_mark[-4].expression,yystack.l_mark[-2].s,yystack.l_mark[0].s); }
break;
case 51:
#line 139 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node); }
break;
case 52:
#line 140 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node,yystack.l_mark[-1].sequence); }
break;
case 53:
#line 143 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 54:
#line 146 "xpl_parser.y"
	{ yyval.node = new xpl::if_node(LINE,yystack.l_mark[-2].expression,yystack.l_mark[0].node); }
break;
case 55:
#line 147 "xpl_parser.y"
	{ yyval.node = new xpl::if_else_node(LINE,yystack.l_mark[-4].expression,yystack.l_mark[-2].node,yystack.l_mark[0].node); }
break;
case 56:
#line 148 "xpl_parser.y"
	{ yyval.node = new xpl::if_else_node(LINE,yystack.l_mark[-4].expression,yystack.l_mark[-2].node,yystack.l_mark[0].node); }
break;
case 57:
#line 153 "xpl_parser.y"
	{ yyval.node = new xpl::while_node(LINE,yystack.l_mark[-2].expression,yystack.l_mark[0].node); }
break;
case 58:
#line 154 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_up_node(LINE,yystack.l_mark[-8].lvalue,yystack.l_mark[-6].expression,yystack.l_mark[-4].expression,yystack.l_mark[-2].expression,yystack.l_mark[0].node); }
break;
case 59:
#line 155 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_up_node(LINE,yystack.l_mark[-6].lvalue,yystack.l_mark[-4].expression,yystack.l_mark[-2].expression,new cdk::integer_node(LINE,1),yystack.l_mark[0].node); }
break;
case 60:
#line 156 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_down_node(LINE,yystack.l_mark[-8].lvalue,yystack.l_mark[-6].expression,yystack.l_mark[-4].expression,yystack.l_mark[-2].expression,yystack.l_mark[0].node); }
break;
case 61:
#line 157 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_down_node(LINE,yystack.l_mark[-6].lvalue,yystack.l_mark[-4].expression,yystack.l_mark[-2].expression,new cdk::integer_node(LINE,1),yystack.l_mark[0].node); }
break;
case 62:
#line 160 "xpl_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 63:
#line 161 "xpl_parser.y"
	{ yyval.expression = new xpl::read_node(LINE); }
break;
case 64:
#line 162 "xpl_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 65:
#line 163 "xpl_parser.y"
	{ yyval.expression = new xpl::identity_node(LINE, yystack.l_mark[0].expression); }
break;
case 66:
#line 164 "xpl_parser.y"
	{ yyval.expression = new xpl::address_node(LINE, yystack.l_mark[-1].lvalue); }
break;
case 67:
#line 165 "xpl_parser.y"
	{ yyval.expression = new cdk::add_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 68:
#line 166 "xpl_parser.y"
	{ yyval.expression = new cdk::sub_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 69:
#line 167 "xpl_parser.y"
	{ yyval.expression = new cdk::mul_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 70:
#line 168 "xpl_parser.y"
	{ yyval.expression = new cdk::div_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 71:
#line 169 "xpl_parser.y"
	{ yyval.expression = new cdk::mod_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 72:
#line 170 "xpl_parser.y"
	{ yyval.expression = new cdk::lt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 73:
#line 171 "xpl_parser.y"
	{ yyval.expression = new cdk::gt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 74:
#line 172 "xpl_parser.y"
	{ yyval.expression = new cdk::ge_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 75:
#line 173 "xpl_parser.y"
	{ yyval.expression = new cdk::le_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 76:
#line 174 "xpl_parser.y"
	{ yyval.expression = new cdk::ne_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 77:
#line 175 "xpl_parser.y"
	{ yyval.expression = new cdk::eq_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 78:
#line 176 "xpl_parser.y"
	{ yyval.expression = new cdk::not_node(LINE, yystack.l_mark[0].expression); }
break;
case 79:
#line 177 "xpl_parser.y"
	{ yyval.expression = new cdk::and_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 80:
#line 178 "xpl_parser.y"
	{ yyval.expression = new cdk::or_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 81:
#line 179 "xpl_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 82:
#line 180 "xpl_parser.y"
	{ yyval.expression = new xpl::mem_alloc_node(LINE,yystack.l_mark[-1].expression); }
break;
case 83:
#line 181 "xpl_parser.y"
	{ yyval.expression = new cdk::rvalue_node(LINE, yystack.l_mark[0].lvalue); }
break;
case 84:
#line 182 "xpl_parser.y"
	{ yyval.expression = new cdk::assignment_node(LINE, yystack.l_mark[-2].lvalue, yystack.l_mark[0].expression); }
break;
case 85:
#line 183 "xpl_parser.y"
	{ yyval.expression = new xpl::func_invocation_node(LINE,yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 86:
#line 187 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].expression); }
break;
case 87:
#line 188 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].expression,yystack.l_mark[-2].sequence); }
break;
case 88:
#line 191 "xpl_parser.y"
	{ yyval.sequence = yystack.l_mark[0].sequence; }
break;
case 89:
#line 192 "xpl_parser.y"
	{ yyval.sequence = NULL; }
break;
case 90:
#line 195 "xpl_parser.y"
	{ yyval.expression = new cdk::integer_node(LINE, yystack.l_mark[0].i); }
break;
case 91:
#line 196 "xpl_parser.y"
	{ yyval.expression = new cdk::double_node(LINE, yystack.l_mark[0].r); }
break;
case 92:
#line 197 "xpl_parser.y"
	{ yyval.expression = new cdk::string_node(LINE, yystack.l_mark[0].s); }
break;
case 93:
#line 198 "xpl_parser.y"
	{ yyval.expression = new xpl::null_node(LINE); }
break;
case 94:
#line 201 "xpl_parser.y"
	{ yyval.s = yystack.l_mark[0].s; }
break;
case 95:
#line 202 "xpl_parser.y"
	{ yyval.s = new std::string(*yystack.l_mark[-1].s + *yystack.l_mark[0].s); delete yystack.l_mark[-1].s; delete yystack.l_mark[0].s; }
break;
case 96:
#line 205 "xpl_parser.y"
	{ yyval.lvalue = new cdk::identifier_node(LINE, *yystack.l_mark[0].s); }
break;
case 97:
#line 206 "xpl_parser.y"
	{ yyval.lvalue = new xpl::index_node(LINE,yystack.l_mark[-3].expression,yystack.l_mark[-1].expression); }
break;
#line 1319 "xpl_parser.tab.c"
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
