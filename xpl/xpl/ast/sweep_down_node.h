#ifndef __XPL_SWEEPDOWNNODE_H__
#define __XPL_SWEEPDOWNNODE_H__

#include <cdk/ast/basic_node.h>

namespace xpl {

  /**
   * Class for describing sweep- nodes.
   */
  class sweep_down_node: public cdk::basic_node {
    cdk::lvalue_node *_lvalue;
    cdk::expression_node *_expression1;
    cdk::expression_node *_expression2;
    cdk::expression_node *_expression3;
    cdk::basic_node *_block;

  public:
    inline sweep_down_node(int lineno, cdk::lvalue_node *lvalue, cdk::expression_node *expression1, cdk::expression_node *expression2, cdk::expression_node *expression3, cdk::basic_node *block) :
        cdk::basic_node(lineno), _lvalue(lvalue), _expression1(expression1), _expression2(expression2), _expression3(expression3), _block(block) {
    }
    

  public:
    inline cdk::lvalue_node *lvalue() {
      return _lvalue;
    }
    
    inline cdk::expression_node *expression1() {
      return _expression1;
    }
    
    inline cdk::expression_node *expression2() {
      return _expression2;
    }
    
    inline cdk::expression_node *expression3() {
      return _expression3;
    }
    
    inline cdk::basic_node *block() {
      return _block;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_sweep_down_node(this, level);
    }

  };

} // xpl

#endif
