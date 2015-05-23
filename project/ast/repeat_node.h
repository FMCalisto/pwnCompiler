#ifndef __PWN_REPEATNODE_H__
#define __PWN_REPEATNODE_H__

#include <cdk/ast/sequence_node.h>

namespace pwn {

  /**
   * Class for describing repeat-cycle nodes.
   */
  class repeat_node: public cdk::basic_node {
    cdk::sequence_node *_init;
    cdk::sequence_node *_condition;
    cdk::sequence_node *_step;
    cdk::basic_node *_block;

  public:
    inline repeat_node(int lineno, cdk::sequence_node *init, cdk::sequence_node *condition, cdk::sequence_node *step, cdk::basic_node *block) :
        cdk::basic_node(lineno), _init(init), _condition(condition), _step(step), _block(block) {
    }

  public:
    inline cdk::sequence_node *init() {
      return _init;
    }
    inline cdk::sequence_node *condition() {
      return _condition;
    }
    inline cdk::sequence_node *step() {
      return _step;
    }
    inline cdk::basic_node *block() {
      return _block;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_repeat_node(this, level);
    }

  };

} // cdk

#endif
