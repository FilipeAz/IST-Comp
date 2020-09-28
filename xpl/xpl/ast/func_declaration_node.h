#ifndef __XPL_FUNCDECLARATIONNODE_H__
#define __XPL_FUNCDECLARATIONNODE_H__

#include <cdk/ast/basic_node.h>

namespace xpl {

  /**
   * Class for describing function declaration nodes.
   */
  class func_declaration_node: public cdk::basic_node {
    bool _isPublic;
    bool _hasUse;
    basic_type *_return_type;
    std::string *_identifier;
    cdk::sequence_node *_args;
    

  public:
    inline func_declaration_node(int lineno, bool isPublic, bool hasUse, basic_type *return_type, std::string *identifier, cdk::sequence_node *args) :
        cdk::basic_node(lineno), _isPublic(isPublic), _hasUse(hasUse), _return_type(return_type), _identifier(identifier), _args(args) {
    }

  public:
    inline bool isPublic() {
        return _isPublic;
    }

    inline bool hasUse() {
        return _hasUse;
    }

    inline basic_type *return_type() {
        return _return_type;
    }

    inline std::string *identifier() {
        return _identifier;
    }

    inline cdk::sequence_node *args() {
        return _args;
    }
    


    void accept(basic_ast_visitor *sp, int level) {
      sp->do_func_declaration_node(this, level);
    }

  };

} // xpl

#endif