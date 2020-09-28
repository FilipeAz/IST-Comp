#ifndef __XPL_VARINICIALIZATIONNODE_H__
#define __XPL_VARINICIALIZATIONNODE_H__

#include <cdk/ast/basic_node.h>

namespace xpl {

  /**
   * Class for describing variable inicialization nodes.
   */
  class var_inicialization_node: public cdk::basic_node {
    bool _isPublic;
    basic_type *_type;
    std::string *_identifier;
    cdk::expression_node *_expression;
    

  public:
    inline var_inicialization_node(int lineno, bool isPublic, basic_type *type, std::string *identifier, cdk::expression_node *expression) :
        cdk::basic_node(lineno), _isPublic(isPublic), _type(type), _identifier(identifier), _expression(expression) {
    }


  public:

    inline bool isPublic() {
        return _isPublic;
    }
      
    inline std::string *identifier() {
        return _identifier;
    }
    
    inline basic_type *type() {
        return _type;
    }

    inline cdk::expression_node *expression() {
        return _expression;
    }


    void accept(basic_ast_visitor *sp, int level) {
      sp->do_var_inicialization_node(this, level);
    }

  };

} // xpl

#endif