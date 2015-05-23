#ifndef __PWN_PRINTLNNODE_H__
#define __PWN_PRINTLNNODE_H__

#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Class for describing println nodes.
   */
  class println_node: public cdk::basic_node {
    pwn::print_node *_print;

  public:
    inline println_node(int lineno, pwn::print_node *print) :
        cdk::basic_node(lineno), _print(print) {
    }

  public:
    inline pwn::print_node *print() {
      return _print;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_println_node(this, level);
    }

  };

} // pwn

#endif
