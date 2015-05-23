#ifndef __PWN_AST_EXPRESSION_SYMMETRIC_H__
#define __PWN_AST_EXPRESSION_SYMMETRIC_H__

#include <cdk/ast/unary_expression_node.h>

namespace pwn {

  /**
   * Class for describing the symmetric (-) operator
   */
  class symmetric_node: public cdk::unary_expression_node {
  public:
    inline symmetric_node(int lineno, cdk::expression_node *arg) :
        cdk::unary_expression_node(lineno, arg) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_symmetric_node(this, level);
    }

  };

} // pwn

#endif
