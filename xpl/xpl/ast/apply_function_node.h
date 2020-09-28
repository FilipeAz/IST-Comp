#ifndef __CDK_APPLYFUNCTIONNODE_H__
#define __CDK_APPLYFUNCTIONNODE_H__

#include <string>
#include <cdk/ast/basic_node.h>

namespace xpl {

  /**
   * Class for describing apply_function nodes.
   */
  class apply_function_node: public cdk::basic_node {
    cdk::expression_node *_lowIndex;
    cdk::expression_node *_highIndex;
    std::string *_vector_name;
    std::string *_func_name;

  public:
    inline apply_function_node(int lineno, cdk::expression_node *lowIndex, cdk::expression_node *highIndex, std::string *vector_name, std::string *func_name) :
        basic_node(lineno), _lowIndex(lowIndex), _highIndex(highIndex), _vector_name(vector_name), _func_name(func_name) {
    }

  public:
    inline cdk::expression_node *lowIndex() {
      return _lowIndex;
    }
    inline cdk::expression_node *highIndex() {
      return _highIndex;
    }
    inline std::string *vector_name() {
      return _vector_name;
    }
    inline std::string *func_name() {
      return _func_name;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_apply_function_node(this, level);
    }

  };

} // xpl

#endif
