#ifndef __XPL_FUNCINVOCATIONNODE_H__
#define __XPL_FUNCINVOCATIONNODE_H__

#include <cdk/ast/expression_node.h>

namespace xpl {

  /**
   * Class for describing function invocation nodes.
   */
  class func_invocation_node: public cdk::expression_node {
    std::string *_identifier;
    cdk::sequence_node *_args;
    

  public:
    inline func_invocation_node(int lineno, std::string *identifier, cdk::sequence_node *args) :
        cdk::expression_node(lineno),  _identifier(identifier), _args(args) {
    }

  public:
    inline std::string *identifier() {
        return _identifier;
    }

    inline cdk::sequence_node *args() {
        return _args;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_func_invocation_node(this, level);
    }

  };

} // xpl

#endif