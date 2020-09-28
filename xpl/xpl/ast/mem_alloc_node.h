#ifndef __XPL_MEMALLOCNODE_H__
#define __XPL_MEMALLOCNODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/unary_expression_node.h>

namespace xpl {

  /**
   * Class for describing memory_allocation nodes.
   */
  class mem_alloc_node: public cdk::unary_expression_node {

  public:
    inline mem_alloc_node(int lineno, cdk::expression_node *arg) :
        cdk::unary_expression_node(lineno, arg) {
    }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_mem_alloc_node(this, level);
    }

  };

} // xpl

#endif