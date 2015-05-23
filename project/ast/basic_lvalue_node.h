#ifndef __PWN_NODE_EXPRESSION_BASICLEFTVALUE_H__
#define __PWN_NODE_EXPRESSION_BASICLEFTVALUE_H__

#include "lvalue_node.h"
#include <cdk/ast/identifier_node.h>

namespace pwn {

  /**
   * Class for describing syntactic tree leaves for holding lvalues.
   */
  class basic_lvalue_node: public lvalue_node {
    std::string *_varId;
    
  public:
    inline basic_lvalue_node(int lineno, std::string *varId) :
        lvalue_node(lineno), _varId(varId) {
    }
    
    inline std::string *varId() {
        return _varId;
    }

  public:
    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_basic_lvalue_node(this, level);
    }
    
  };

} // pwn

#endif
