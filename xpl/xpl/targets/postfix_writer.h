#ifndef __XPL_SEMANTICS_POSTFIX_WRITER_H__
#define __XPL_SEMANTICS_POSTFIX_WRITER_H__

#include <string>
#include <iostream>
#include <vector>
#include <cdk/symbol_table.h>
#include <cdk/emitters/basic_postfix_emitter.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace xpl {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class postfix_writer: public basic_ast_visitor {
    cdk::symbol_table<xpl::symbol> &_symtab;
    cdk::basic_postfix_emitter &_pf;
    int _lbl;
    
    std::shared_ptr<xpl::symbol> _current_function = NULL;              //Function currently being visited (NULL is global)
    int _current_function_end_label;                                    //End of function label
    int _current_offset;                                                //Variables offset in local context
    std::vector<int> _cycles_stack_next;                                //Stack to know in which cycle we are
    std::vector<int> _cycles_stack_stop;                                //Stack to know in which cycle we are
    std::string _current_id_init;                                       //Identifier of global variable being initialized
    std::map<std::string, std::shared_ptr<xpl::symbol>> _declarations;  //Declared functions not yet defined
    std::map<std::string, std::shared_ptr<xpl::symbol>> _definitions;   //Defined functions
    std::map<std::string, std::shared_ptr<xpl::symbol>> _invocations;   //Function called at least once

  public:
    postfix_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<xpl::symbol> &symtab,
                   cdk::basic_postfix_emitter &pf) :
        basic_ast_visitor(compiler), _symtab(symtab), _pf(pf), _lbl(0) {
    }

  public:
    ~postfix_writer() {
      os().flush();
    }
    
    private:
      inline bool is_int(cdk::expression_node * const node);
      inline bool is_real(cdk::expression_node * const node);
      inline bool is_string(cdk::expression_node * const node);
      inline bool is_pointer(cdk::expression_node * const node);
      inline bool same_type(cdk::expression_node * const node, unsigned long int type);
      inline void processComparingBinaryExpression(cdk::binary_expression_node * const node, int lvl);

  private:
    /** Method used to generate sequential labels. */
    inline std::string mklbl(int lbl) {
      std::ostringstream oss;
      if (lbl < 0)
        oss << ".L" << -lbl;
      else
        oss << "_L" << lbl;
      return oss.str();
    }
    
    inline std::shared_ptr<xpl::symbol> current_function() {
      return _current_function;
    }
 
    inline void current_function(std::shared_ptr<xpl::symbol> func) {
      _current_function = func;
    }
    
     inline bool add_declaration(std::string name, std::shared_ptr<xpl::symbol> symbol) {
            auto it = _declarations.find(name);
            if (it == _declarations.end()) {
              _declarations[name] = symbol;
              return true;
            }
            return false;
    }
    inline bool add_definition(std::string name, std::shared_ptr<xpl::symbol> symbol) {
            auto it = _definitions.find(name);
            if (it == _definitions.end()) {
              _definitions[name] = symbol;
              return true;
            }
            return false;
    }
    inline bool add_invocation(std::string name, std::shared_ptr<xpl::symbol> symbol) {
            auto it = _invocations.find(name);
            if (it == _invocations.end()) {
              _invocations[name] = symbol;
              return true;
            }
            return false;
    }
    
    inline void externs();
    

  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl);

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl);
    void do_double_node(cdk::double_node * const node, int lvl);
    void do_string_node(cdk::string_node * const node, int lvl);
    void do_null_node(xpl::null_node * const node, int lvl);

  public:
    void do_neg_node(cdk::neg_node * const node, int lvl);
    void do_not_node(cdk::not_node * const node, int lvl);
    void do_address_node(xpl::address_node * const node, int lvl);

  public:
    void do_add_node(cdk::add_node * const node, int lvl);
    void do_sub_node(cdk::sub_node * const node, int lvl);
    void do_mul_node(cdk::mul_node * const node, int lvl);
    void do_div_node(cdk::div_node * const node, int lvl);
    void do_mod_node(cdk::mod_node * const node, int lvl);
    void do_lt_node(cdk::lt_node * const node, int lvl);
    void do_le_node(cdk::le_node * const node, int lvl);
    void do_ge_node(cdk::ge_node * const node, int lvl);
    void do_gt_node(cdk::gt_node * const node, int lvl);
    void do_ne_node(cdk::ne_node * const node, int lvl);
    void do_eq_node(cdk::eq_node * const node, int lvl);
    void do_and_node(cdk::and_node * const node, int lvl);
    void do_or_node(cdk::or_node * const node, int lvl);

  public:
    void do_identifier_node(cdk::identifier_node * const node, int lvl);
    void do_rvalue_node(cdk::rvalue_node * const node, int lvl);
    void do_assignment_node(cdk::assignment_node * const node, int lvl);
    void do_var_declaration_node(xpl::var_declaration_node * const node, int lvl);
    void do_var_inicialization_node(xpl::var_inicialization_node * const node, int lvl);
    void do_mem_alloc_node(xpl::mem_alloc_node * const node, int lvl);
    void do_index_node(xpl::index_node * const node, int lvl);
    void do_identity_node(xpl::identity_node * const node, int lvl);

  public:
    void do_func_definition_node(xpl::func_definition_node * const node, int lvl);
    void do_func_declaration_node(xpl::func_declaration_node * const node, int lvl);
    void do_func_invocation_node(xpl::func_invocation_node * const node, int lvl);
    void do_evaluation_node(xpl::evaluation_node * const node, int lvl);
    void do_print_node(xpl::print_node * const node, int lvl);
    void do_read_node(xpl::read_node * const node, int lvl);
    void do_print_line_node(xpl::print_line_node * const node, int lvl);
    void do_block_node(xpl::block_node * const node, int lvl);

  public:
    void do_while_node(xpl::while_node * const node, int lvl);
    void do_if_node(xpl::if_node * const node, int lvl);
    void do_if_else_node(xpl::if_else_node * const node, int lvl);
    void do_next_node(xpl::next_node * const node, int lvl);
    void do_stop_node(xpl::stop_node * const node, int lvl);
    void do_return_node(xpl::return_node * const node, int lvl);
    void do_sweep_up_node(xpl::sweep_up_node * const node, int lvl);
    void do_sweep_down_node(xpl::sweep_down_node * const node, int lvl);
    void do_apply_function_node(xpl::apply_function_node * const node, int lvl);

  };

} // xpl

#endif
