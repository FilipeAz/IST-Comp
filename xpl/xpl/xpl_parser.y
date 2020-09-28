%{
// $Id: xpl_parser.y,v 1.8 2017/05/19 23:03:20 ist182468 Exp $
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
  int                   i;	/* integer value */
  double                r;      /* real value */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;
  basic_type           *type;
  xpl::block_node      *block;
};

%token <i> tINTEGER
%token <r> tREAL
%token <s> tIDENTIFIER tSTRING
%token tWHILE tNEXT tSTOP tRETURN tIF tELSIF tPRINTLINE tSWEEP tFROM tTO tAPPLY tPROCEDURE tPUBLIC tUSE tNULL tTYPEINT tTYPEREAL tTYPESTRING

%nonassoc tIFX
%nonassoc tELSIF
%nonassoc tELSE

%right '='
%left '|'
%left '&'
%nonassoc '~'
%left tEQ tNE
%left tGE tLE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%nonassoc '?'
%nonassoc '['
%nonassoc tUNARY

%type <node> file decl variable function instr condinstr loopinstr declvar condinstrelseif fvar
%type <sequence> decls fvars functionvars exprs instrs functionargs declsvar
%type <expression> expr literal
%type <lvalue> lval
%type <type> type
%type <block> body block 
%type <s> strings

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

file : decls            { compiler->ast($1); }
     |                  { $$ = NULL; }
     ;
     
decl : variable ';'    { $$ = $1; }
     | function        { $$ = $1; }
     ;
     
decls : decl           { $$ = new cdk::sequence_node(LINE,$1); }
      | decls decl     { $$ = new cdk::sequence_node(LINE,$2,$1); }
      ;
      
declvar : variable ';'      { $$ = $1; }
        ;
        
declsvar : declvar          { $$ = new cdk::sequence_node(LINE,$1); }
         | declsvar declvar { $$ = new cdk::sequence_node(LINE,$2,$1); }
         ;
      
variable : tPUBLIC type tIDENTIFIER '=' expr            { $$ = new xpl::var_inicialization_node(LINE,true,$2,$3,$5); }
         | type tIDENTIFIER '=' expr                    { $$ = new xpl::var_inicialization_node(LINE,false,$1,$2,$4); }
         | tPUBLIC type tIDENTIFIER                     { $$ = new xpl::var_declaration_node(LINE,true,false,$2,$3); }
         | tUSE type tIDENTIFIER                        { $$ = new xpl::var_declaration_node(LINE,false,true,$2,$3); }
         | type tIDENTIFIER                             { $$ = new xpl::var_declaration_node(LINE,false,false,$1,$2); }
         ;

functionvars : fvars                { $$ = $1; }
             |                      { $$ = NULL; }
             ;
             
fvars: fvar                     { $$ = new cdk::sequence_node(LINE,$1); }
     | fvars ',' fvar           { $$ = new cdk::sequence_node(LINE,$3,$1); }
     ;
     
fvar: type tIDENTIFIER          { $$ = new xpl::var_declaration_node(LINE,false,false,$1,$2); }
    ;
         
function : tPUBLIC type tIDENTIFIER '(' functionvars ')' '=' literal body          { $$ = new xpl::func_definition_node(LINE,true,$2,$3,$5,$8,$9); }
         | type tIDENTIFIER '(' functionvars ')' '=' literal body                  { $$ = new xpl::func_definition_node(LINE,false,$1,$2,$4,$7,$8); }
         | tPUBLIC type tIDENTIFIER '(' functionvars ')' body                      { $$ = new xpl::func_definition_node(LINE,true,$2,$3,$5,NULL,$7); }
         | type tIDENTIFIER '(' functionvars ')' body                              { $$ = new xpl::func_definition_node(LINE,false,$1,$2,$4,NULL,$6); }
         | tPUBLIC tPROCEDURE tIDENTIFIER '(' functionvars ')' body                { $$ = new xpl::func_definition_node(LINE,true,new basic_type(0, basic_type::TYPE_VOID),$3,$5,NULL,$7); }
         | tPROCEDURE tIDENTIFIER '(' functionvars ')' body                        { $$ = new xpl::func_definition_node(LINE,false,new basic_type(0, basic_type::TYPE_VOID),$2,$4,NULL,$6); }
         | tPUBLIC type tIDENTIFIER '(' functionvars ')'                           { $$ = new xpl::func_declaration_node(LINE,true,false,$2,$3,$5); }
         | tPUBLIC tPROCEDURE tIDENTIFIER '(' functionvars ')'                    { $$ = new xpl::func_declaration_node(LINE,true,false,new basic_type(0, basic_type::TYPE_VOID),$3,$5); }
         | tUSE type tIDENTIFIER '(' functionvars ')'                              { $$ = new xpl::func_declaration_node(LINE,false,true,$2,$3,$5); }
         | type tIDENTIFIER '(' functionvars ')'                                   { $$ = new xpl::func_declaration_node(LINE,false,false,$1,$2,$4); }
         | tUSE tPROCEDURE tIDENTIFIER '(' functionvars ')'                       { $$ = new xpl::func_declaration_node(LINE,false,true,new basic_type(0, basic_type::TYPE_VOID),$3,$5); }
         | tPROCEDURE tIDENTIFIER '(' functionvars ')'                           { $$ = new xpl::func_declaration_node(LINE,false,false,new basic_type(0, basic_type::TYPE_VOID),$2,$4); }
         ;

          
type : tTYPEINT            { $$ = new basic_type(sizeof(int), basic_type::TYPE_INT); }
     | tTYPEREAL           { $$ = new basic_type(sizeof(double), basic_type::TYPE_DOUBLE); }
     | tTYPESTRING         { $$ = new basic_type(sizeof(std::string), basic_type::TYPE_STRING); }
     | '[' type ']'        { $$ = new basic_type(sizeof(void*), basic_type::TYPE_POINTER); $$->_subtype = $2; }
     ;
     
body : block            { $$ = $1; }
     ;
         
block : '{' declsvar instrs '}'             { $$ = new xpl::block_node(LINE,$2,$3); }
      | '{' declsvar '}'                    { $$ = new xpl::block_node(LINE,$2,NULL); }
      | '{' instrs '}'                      { $$ = new xpl::block_node(LINE,NULL,$2); }
      | '{' '}'                             { $$ = new xpl::block_node(LINE,NULL,NULL); }
      ;
      
instr : expr ';'                        { $$ = new xpl::evaluation_node(LINE,$1); }
      | expr '!'                        { $$ = new xpl::print_node(LINE,$1);}
      | expr tPRINTLINE                 { $$ = new xpl::print_line_node(LINE,$1);}
      | tNEXT                           { $$ = new xpl::next_node(LINE); }
      | tSTOP                           { $$ = new xpl::stop_node(LINE); }
      | tRETURN                         { $$ = new xpl::return_node(LINE); }
      | condinstr                       { $$ = $1; }
      | loopinstr                       { $$ = $1; }
      | block                           { $$ = $1; }
      | tFROM expr tTO expr tAPPLY tIDENTIFIER tTO tIDENTIFIER     { $$ = new xpl::apply_function_node(LINE,$2,$4,$6,$8); }
      ;
      
instrs : instr                      { $$ = new cdk::sequence_node(LINE,$1); }
       | instrs instr               { $$ = new cdk::sequence_node(LINE,$2,$1); }
       ;
      
condinstr : tIF condinstrelseif                 { $$ = $2; }
          ;
          
condinstrelseif : '(' expr ')' instr %prec tIFX                           { $$ = new xpl::if_node(LINE,$2,$4); }
                | '(' expr ')' instr tELSE instr                          { $$ = new xpl::if_else_node(LINE,$2,$4,$6); }
                | '(' expr ')' instr tELSIF condinstrelseif               { $$ = new xpl::if_else_node(LINE,$2,$4,$6); }
                ;
          
  
                
loopinstr : tWHILE '(' expr ')' instr                                   { $$ = new xpl::while_node(LINE,$3,$5); }
          | tSWEEP '+' '(' lval ':' expr ':' expr ':' expr ')' instr      { $$ = new xpl::sweep_up_node(LINE,$4,$6,$8,$10,$12); }                                                       
          | tSWEEP '+' '(' lval ':' expr ':' expr ')' instr               { $$ = new xpl::sweep_up_node(LINE,$4,$6,$8,new cdk::integer_node(LINE,1),$10); }
          | tSWEEP '-' '(' lval ':' expr ':' expr ':' expr ')' instr    { $$ = new xpl::sweep_down_node(LINE,$4,$6,$8,$10,$12); }
          | tSWEEP '-' '(' lval ':' expr ':' expr ')' instr             { $$ = new xpl::sweep_down_node(LINE,$4,$6,$8,new cdk::integer_node(LINE,1),$10); }
          ;
         
expr : literal                          { $$ = $1; }
     | '@'                              { $$ = new xpl::read_node(LINE); }
     | '-' expr %prec tUNARY            { $$ = new cdk::neg_node(LINE, $2); }
     | '+' expr %prec tUNARY            { $$ = new xpl::identity_node(LINE, $2); }
     | lval '?'                         { $$ = new xpl::address_node(LINE, $1); }
     | expr '+' expr	                { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr	                { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr	                { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr	                { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr	                { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr	                { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr	                { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tGE expr	                { $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr                    { $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tNE expr	                { $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr tEQ expr	                { $$ = new cdk::eq_node(LINE, $1, $3); }
     | '~' expr %prec tUNARY            { $$ = new cdk::not_node(LINE, $2); }
     | expr '&' expr	                { $$ = new cdk::and_node(LINE, $1, $3); }
     | expr '|' expr	                { $$ = new cdk::or_node(LINE, $1, $3); }
     | '(' expr ')'                     { $$ = $2; }
     | '[' expr ']'                     { $$ = new xpl::mem_alloc_node(LINE,$2); }
     | lval                             { $$ = new cdk::rvalue_node(LINE, $1); }  //FIXME
     | lval '=' expr                    { $$ = new cdk::assignment_node(LINE, $1, $3); }
     | tIDENTIFIER '(' functionargs ')' { $$ = new xpl::func_invocation_node(LINE,$1,$3); }
     ;     

          
exprs : expr                    { $$ = new cdk::sequence_node(LINE,$1); }
      | exprs ',' expr          { $$ = new cdk::sequence_node(LINE,$3,$1); }
      ;
     
functionargs : exprs        { $$ = $1; }
             |              { $$ = NULL; }
             ;
     
literal : tINTEGER                 { $$ = new cdk::integer_node(LINE, $1); }
        | tREAL                    { $$ = new cdk::double_node(LINE, $1); }
        | strings                  { $$ = new cdk::string_node(LINE, $1); }
        | tNULL                    { $$ = new xpl::null_node(LINE); }
        ;
  
strings : tSTRING           { $$ = $1; }
        | strings tSTRING   { $$ = new std::string(*$1 + *$2); delete $1; delete $2; }
        ;
  
lval : tIDENTIFIER                                      { $$ = new cdk::identifier_node(LINE, *$1); }
     | expr '[' expr ']'                                { $$ = new xpl::index_node(LINE,$1,$3); }
     ;
     

%%
