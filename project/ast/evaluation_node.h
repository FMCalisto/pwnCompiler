// $Id: evaluation_node.h,v 1.1 2015/02/21 20:27:29 ist13500 Exp $
#ifndef __PWN_EVALUATIONNODE_H__
#define __PWN_EVALUATIONNODE_H__

#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Class for describing evaluation nodes.
   */
  class evaluation_node: public cdk::basic_node {
    cdk::expression_node *_argument;

  public:
    inline evaluation_node(int lineno, cdk::expression_node *argument) :
        cdk::basic_node(lineno), _argument(argument) {
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_evaluation_node(this, level);
    }

  };

} // pwn

#endif
