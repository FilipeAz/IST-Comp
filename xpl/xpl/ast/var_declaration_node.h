#ifndef __XPL_VARDECLARATIONNODE_H__
#define __XPL_VARDECLARATIONNODE_H__

#include <cdk/ast/basic_node.h>

namespace xpl {

  /**
   * Class for describing variable declaration nodes.
   */
  class var_declaration_node: public cdk::basic_node {
    bool _isPublic;
    bool _hasUse;
    basic_type *_type;
    std::string *_identifier;

  public:
    inline var_declaration_node(int lineno, bool isPublic, bool hasUse, basic_type *type, std::string *identifier) :
        cdk::basic_node(lineno), _isPublic(isPublic), _hasUse(hasUse), _type(type), _identifier(identifier) {
    }

  public:
    inline bool isPublic() {
        return _isPublic;
    }

    inline bool hasUse() {
        return _hasUse;
    }

    inline basic_type *type() {
        return _type;
    }

    inline std::string *identifier() {
        return _identifier;
    }


    void accept(basic_ast_visitor *sp, int level) {
      sp->do_var_declaration_node(this, level);
    }

  };

} // xpl

#endif