// $Id: rvalue_node.h,v 1.1 2015/02/21 20:27:31 ist13500 Exp $
#ifndef __PWN_RVALUE_NODE_H__
#define __PWN_RVALUE_NODE_H__

#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Class for describing rvalue nodes.
   */
  class rvalue_node: public cdk::expression_node {
    pwn::lvalue_node *_lvalue;

  public:
    inline rvalue_node(int lineno, pwn::lvalue_node *lvalue) :
        cdk::expression_node(lineno), _lvalue(lvalue) {
    }

  public:
    inline cdk::expression_node *lvalue() {
      return _lvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_rvalue_node(this, level);
    }

  };

} // pwn

#endif
