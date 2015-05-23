#ifndef __PWN_AST_EXPRESSION_NOOB_H__
#define __PWN_AST_EXPRESSION_NOOB_H__

#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Class for describing syntactic tree leaves for holding a no-object.
   * All pointers are represented by double precision values.
   */
  class noob_node: public virtual cdk::expression_node {
  public:
    inline noob_node(int lineno) : cdk::expression_node(lineno) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_noob_node(this, level);
    }

  };

} // pwn

#endif
