#ifndef __PWN_NODE_EXPRESSION_INDEXEDLEFTVALUE_H__
#define __PWN_NODE_EXPRESSION_INDEXEDLEFTVALUE_H__

#include <string>
#include "lvalue_node.h"

namespace pwn {

  /**
   * Class for describing syntactic tree leaves for holding lvalues.
   */
  class indexed_lvalue_node: public lvalue_node {
    cdk::expression_node *_indexed_expr;
    cdk::expression_node *_index;
    
  public:
    inline indexed_lvalue_node(int lineno, cdk::expression_node *indexed_expr, cdk::expression_node *index) :
        lvalue_node(lineno), _indexed_expr(indexed_expr), _index(index) {
    }
    
    inline cdk::expression_node *indexed_expr() const { return _indexed_expr; }
    
    inline cdk::expression_node *index() const { return _index; }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_indexed_lvalue_node(this, level);
    }

  };

} // pwn

#endif
