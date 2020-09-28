#ifndef __XPL_BLOCKNODE_H__
#define __XPL_BLOCKNODE_H__

#include <cdk/ast/basic_node.h>

namespace xpl {

  /**
   * Class for describing block nodes.
   */
  class block_node: public cdk::basic_node {
    cdk::sequence_node *_varSequence;
    cdk::sequence_node *_instrSequence;

  public:
    inline block_node(int lineno, cdk::sequence_node *varSequence, cdk::sequence_node *instrSequence) :
        cdk::basic_node(lineno), _varSequence(varSequence), _instrSequence(instrSequence) {
    }
    

  public:
    inline cdk::sequence_node *varSequence() {
        return _varSequence;
    }

    inline cdk::sequence_node *instrSequence() {
        return _instrSequence;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_block_node(this, level);
    }

  };

} // xpl

#endif