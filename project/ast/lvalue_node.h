// $Id: lvalue_node.h,v 1.3 2015/04/14 02:32:01 ist169984 Exp $
// modified by group 45 2015/03/25 01:07

#ifndef __PWN_NODE_EXPRESSION_LEFTVALUE_H__
#define __PWN_NODE_EXPRESSION_LEFTVALUE_H__

#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Abstract lvalue
   */
  class lvalue_node: public cdk::expression_node {

  public:
    lvalue_node(int lineno) : cdk::expression_node(lineno) {}
    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) = 0;

  };

} // pwn

#endif
