#ifndef __PWN_AST_EXPRESSION_STACKALLOC_H__
#define __PWN_AST_EXPRESSION_STACKALLOC_H__

#include <cdk/ast/unary_expression_node.h>

namespace pwn {

  /**
   * Class for describing the negation operator
   */
  class stackalloc_node: public cdk::unary_expression_node {
  public:
    inline stackalloc_node(int lineno, cdk::expression_node *arg) :
        cdk::unary_expression_node(lineno, arg) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_stackalloc_node(this, level);
    }

  };

} // pwn

#endif
