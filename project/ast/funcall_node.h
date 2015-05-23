#ifndef __PWN_FUNCALLNODE_H__
#define __PWN_FUNCALLNODE_H__

#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Class for describing funcall nodes.
   */
  class funcall_node: public cdk::expression_node {
    std::string *_funId;
    cdk::sequence_node *_arguments;

  public:
    inline funcall_node(int lineno, std::string *funId, cdk::sequence_node *arguments) :
        cdk::expression_node(lineno), _funId(funId), _arguments(arguments) {
    }

  public:
    inline std::string *funId() {
      return _funId;
    }
  
    inline cdk::sequence_node *arguments() {
      return _arguments;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_funcall_node(this, level);
    }

  };

} // pwn

#endif
