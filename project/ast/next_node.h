#ifndef __PWN_NEXTNODE_H__
#define __PWN_NEXTNODE_H__

#include <cdk/ast/integer_node.h>

namespace pwn {

  /**
   * Class for describing next nodes.
   */
  class next_node: public cdk::basic_node {
    cdk::integer_node *_argument;

  public:
    inline next_node(int lineno, cdk::integer_node *argument) :
        cdk::basic_node(lineno), _argument(argument) {
    }

  public:
    inline cdk::integer_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_next_node(this, level);
    }

  };

} // pwn

#endif
