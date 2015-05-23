// $Id: read_node.h,v 1.3 2015/04/30 18:55:09 ist169984 Exp $ -*- c++ -*-
#ifndef __PWN_READNODE_H__
#define __PWN_READNODE_H__

#include "ast/lvalue_node.h"

namespace pwn {

  /**
   * Class for describing read nodes.
   */
  class read_node: public cdk::expression_node {

  public:
    inline read_node(int lineno) :
        cdk::expression_node(lineno) {
    }

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_read_node(this, level);
    }

  };

} // pwn

#endif
