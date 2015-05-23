#ifndef __PWN_FUNDECLNODE_H__
#define __PWN_FUNDECLNODE_H__

#include <cdk/basic_type.h>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/identifier_node.h>
#include <iostream>

namespace pwn {

  /**
   * Class for describing fundecl nodes.
   */
  class fundecl_node: public cdk::basic_node {
    bool _local;
    bool _import;
    std::string *_funId;
    basic_type *_returnType;
    cdk::sequence_node *_arguments;

  public:
    inline fundecl_node(int lineno, bool local, bool import, std::string *funId, basic_type *returnType, cdk::sequence_node *arguments) :
        cdk::basic_node(lineno), _local(local), _import(import), _funId(funId), _returnType(returnType), _arguments(arguments) {
    }

  public:
    inline bool local() {
      return _local;
    }
    
    inline bool import() {
      return _import;
    }
    
    inline const std::string *funId() {
      return _funId;
    }
    
    inline basic_type *returnType() {
      return _returnType;
    }
    
    inline cdk::sequence_node *arguments() {
      return _arguments;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_fundecl_node(this, level);
    }

  };

} // pwn

#endif
