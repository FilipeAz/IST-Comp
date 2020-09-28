#ifndef __XPL_SEMANTICS_ARGUMENTS_VISITOR_H__
#define __XPL_SEMANTICS_ARGUMENTS_VISITOR_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/emitters/basic_postfix_emitter.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace xpl {

  //!
  //! Visitor to assert the number of bytes to we need to reserve for a function definition
  //!
  class locals_visitor: public basic_ast_visitor {
    int _lbl;
    
    int _num_bytes;

  public:
    locals_visitor(std::shared_ptr<cdk::compiler> compiler) :
        basic_ast_visitor(compiler), _lbl(0), _num_bytes(0) {
    }

  public:
    ~locals_visitor() {
      os().flush();
    }
    
    private:
      inline bool is_int(xpl::func_definition_node * const node);
      inline bool is_real(xpl::func_definition_node * const node);
      inline bool is_string(xpl::func_definition_node * const node);
      inline bool is_pointer(xpl::func_definition_node * const node);

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
    
    
  public:  
    int get_num_bytes() {
        return _num_bytes;
    }

  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl);

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl) {};
    void do_double_node(cdk::double_node * const node, int lvl) {};
    void do_string_node(cdk::string_node * const node, int lvl) {};
    void do_null_node(xpl::null_node * const node, int lvl) {};

  public:
    void do_neg_node(cdk::neg_node * const node, int lvl) {};
    void do_not_node(cdk::not_node * const node, int lvl) {};
    void do_address_node(xpl::address_node * const node, int lvl) {};

  public:
    void do_add_node(cdk::add_node * const node, int lvl) {};
    void do_sub_node(cdk::sub_node * const node, int lvl) {};
    void do_mul_node(cdk::mul_node * const node, int lvl) {};
    void do_div_node(cdk::div_node * const node, int lvl) {};
    void do_mod_node(cdk::mod_node * const node, int lvl) {};
    void do_lt_node(cdk::lt_node * const node, int lvl) {};
    void do_le_node(cdk::le_node * const node, int lvl) {};
    void do_ge_node(cdk::ge_node * const node, int lvl) {};
    void do_gt_node(cdk::gt_node * const node, int lvl) {};
    void do_ne_node(cdk::ne_node * const node, int lvl) {};
    void do_eq_node(cdk::eq_node * const node, int lvl) {};
    void do_and_node(cdk::and_node * const node, int lvl) {};
    void do_or_node(cdk::or_node * const node, int lvl) {};

  public:
    void do_identifier_node(cdk::identifier_node * const node, int lvl) {};
    void do_rvalue_node(cdk::rvalue_node * const node, int lvl) {};
    void do_assignment_node(cdk::assignment_node * const node, int lvl) {};
    void do_var_declaration_node(xpl::var_declaration_node * const node, int lvl);
    void do_var_inicialization_node(xpl::var_inicialization_node * const node, int lvl);
    void do_mem_alloc_node(xpl::mem_alloc_node * const node, int lvl) {};
    void do_index_node(xpl::index_node * const node, int lvl) {};
    void do_identity_node(xpl::identity_node * const node, int lvl) {};

  public:
    void do_func_definition_node(xpl::func_definition_node * const node, int lvl);
    void do_func_declaration_node(xpl::func_declaration_node * const node, int lvl) {};
    void do_func_invocation_node(xpl::func_invocation_node * const node, int lvl) {};
    void do_evaluation_node(xpl::evaluation_node * const node, int lvl) {};
    void do_print_node(xpl::print_node * const node, int lvl) {};
    void do_read_node(xpl::read_node * const node, int lvl) {};
    void do_print_line_node(xpl::print_line_node * const node, int lvl) {};
    void do_block_node(xpl::block_node * const node, int lvl);

  public:
    void do_while_node(xpl::while_node * const node, int lvl) {};
    void do_if_node(xpl::if_node * const node, int lvl) {};
    void do_if_else_node(xpl::if_else_node * const node, int lvl) {};
    void do_next_node(xpl::next_node * const node, int lvl) {};
    void do_stop_node(xpl::stop_node * const node, int lvl) {};
    void do_return_node(xpl::return_node * const node, int lvl) {};
    void do_sweep_up_node(xpl::sweep_up_node * const node, int lvl) {};
    void do_sweep_down_node(xpl::sweep_down_node * const node, int lvl) {};
    void do_apply_function_node(xpl::apply_function_node * const node, int lvl) {};

  };

} // xpl

#endif