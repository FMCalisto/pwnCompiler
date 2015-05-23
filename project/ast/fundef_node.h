#ifndef __PWN_FUNDEFNODE_H__
#define __PWN_FUNDEFNODE_H__

#include <cdk/ast/sequence_node.h>
#include "fundecl_node.h"

namespace pwn {

  /**
   * Class for describing fundef nodes.
   */
  class fundef_node: public cdk::basic_node {
    pwn::fundecl_node *_header;
    cdk::sequence_node *_body;

  public:
    inline fundef_node(int lineno, pwn::fundecl_node *header, cdk::sequence_node *body) :
        cdk::basic_node(lineno), _header(header), _body(body) {
    }
    
  public:
    inline pwn::fundecl_node *header() {
      return _header;
    }
    
    inline cdk::sequence_node *body() {
      return _body;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_fundef_node(this, level);
    }

  };

} // pwn

#endif
