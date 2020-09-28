%option c++ yyclass="xpl_scanner" outfile="xpl_scanner.cpp"
%option stack noyywrap yylineno 8bit
%{ 
/* $Id: xpl_scanner.l,v 1.5 2017/05/19 23:03:20 ist182468 Exp $ */
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/expression_node.h>
#include <cdk/ast/sequence_node.h>
#include "xpl_scanner.h"
#include "xpl_parser.tab.h"

// don't change this
#define yyerror LexerError
%}
%x X_STRING X_COMMENT X_ZEROSTRING

REAL_1              [0-9]+\.[0-9]*([eE][-+]?[0-9]+)?
REAL_2              [0-9]*\.[0-9]+([eE][-+]?[0-9]+)?
REAL_3              [0-9]+([eE][-+]?[0-9]+)
REAL                ({REAL_1}|{REAL_2}|{REAL_3})
%%
                        
                        {set_debug(1);}


"//".*$                ; /* ignore comments */

"/*"                   yy_push_state(X_COMMENT);
<X_COMMENT>"/*"        yy_push_state(X_COMMENT);
<X_COMMENT>"*/"        yy_pop_state();
<X_COMMENT>.|\n        ;

">="                   return tGE; 
"<="                   return tLE; 
"=="                   return tEQ; 
"!="                   return tNE; 

"while"                return tWHILE; 
"next"                 return tNEXT;
"stop"                 return tSTOP;
"return"               return tRETURN;
"if"                   return tIF; 
"elsif"                return tELSIF;
"else"                 return tELSE; 
"!!"                   return tPRINTLINE; 
"sweep"                return tSWEEP;
"from"                 return tFROM;
"to"                   return tTO;
"apply"                return tAPPLY;
"procedure"            return tPROCEDURE;
"public"               return tPUBLIC;
"use"                  return tUSE;
"null"                 return tNULL;
"int"                  return tTYPEINT;
"real"                 return tTYPEREAL;
"string"               return tTYPESTRING;

[A-Za-z_][A-Za-z0-9_]*  yylval.s = new std::string(yytext); return tIDENTIFIER;

\"                                      yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\"                            yy_pop_state(); return tSTRING;
<X_STRING>"\\\\"                        *yylval.s += '\\';
<X_STRING>\\\"                          *yylval.s += '"';
<X_STRING>"\\n"                         *yylval.s += '\n';
<X_STRING>"\\t"                         *yylval.s += '\t';
<X_STRING>"\\r"                         *yylval.s += '\r';
<X_STRING>"\\"0[0]?                     BEGIN(X_ZEROSTRING); return tSTRING;
<X_STRING>"\\"[0-9A-Fa-f][0-9A-Fa-f]?   *yylval.s += strtol(yytext+1,NULL,16);
<X_STRING>.                             *yylval.s += yytext;
<X_STRING>\n                            yyerror("newline character in string");

<X_ZEROSTRING>\"                        BEGIN(INITIAL);
<X_ZEROSTRING>\\\"                      ;
<X_ZEROSTRING>\\\\                      ;
<X_ZEROSTRING>.                         ;
<X_ZEROSTRING>\n                        yyerror("newline in string");

0[0-9]+                yyerror("Non null number starting with zero");

0|0[Xx]0               yylval.i = 0; return tINTEGER;

[0-9]+                 {errno = 0;
                        yylval.i = strtol(yytext, nullptr, 10); 
                        if(errno == ERANGE)
                            yyerror("Overflow");
                        else
                            return tINTEGER;
                       }
                       
0x[0-9a-fA-F]+         {errno = 0;
                        yylval.i = strtol(yytext, nullptr, 16); 
                        if(errno == ERANGE)
                            yyerror("Overflow");
                        else
                            return tINTEGER;
                       }

                       
{REAL}                             {errno = 0;
                                     yylval.r = strtod(yytext, nullptr);
                                     if(errno == ERANGE)
                                        yyerror("Overflow");
                                     else
                                        return tREAL;
                                    }


[-()<>=+*/%;{}.?~&#!$@,:]|"["|"]"|"|"       return *yytext;

[ \r\t\n]+               ; /* ignore whitespace */

.                      yyerror("Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int xpl_scanner::yywrap() { return 1; }
