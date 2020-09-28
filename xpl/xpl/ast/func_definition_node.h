// $Id: func_definition_node.h,v 1.3 2017/04/21 09:30:47 ist182468 Exp $ -*- c++ -*-
#ifndef __XPL_FUNCDEFINITIONNODE_H__
#define __XPL_FUNCDEFINITIONNODE_H__

#include <cdk/ast/basic_node.h>

namespace xpl {

  /**
   * Class for describing program nodes.
   */
  class func_definition_node: public cdk::basic_node {
    bool _isPublic;
    basic_type *_return_type;
    std::string *_identifier;
    cdk::sequence_node *_args;
    cdk::expression_node *_literal;
    xpl::block_node *_statements;

  public:
    inline func_definition_node(int lineno, bool isPublic, basic_type *return_type, std::string *identifier, cdk::sequence_node *args, cdk::expression_node *literal,                              xpl::block_node *statements) :
        cdk::basic_node(lineno), _isPublic(isPublic), _return_type(return_type), _identifier(identifier), _args(args), _literal(literal), _statements(statements) {
    }

  public:
    inline bool isPublic() {
        return _isPublic;
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
    
    inline cdk::expression_node *literal() {
        return _literal;
    }  
      
    inline xpl::block_node *statements() {
      return _statements;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_func_definition_node(this, level);
    }

  };

} // xpl

#endif
