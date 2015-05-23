#ifndef __PWN_STOPNODE_H__
#define __PWN_STOPNODE_H__

#include <cdk/ast/integer_node.h>

namespace pwn {

  /**
   * Class for describing stop nodes.
   */
  class stop_node: public cdk::basic_node {
    cdk::integer_node *_argument;

  public:
    inline stop_node(int lineno, cdk::integer_node *argument) :
        cdk::basic_node(lineno), _argument(argument) {
    }

  public:
    inline cdk::integer_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_stop_node(this, level);
    }

  };

} // pwn

#endif
