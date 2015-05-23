#ifndef __PWN_VARDECLNODE_H__
#define __PWN_VARDECLNODE_H__

#include <cdk/basic_type.h>
#include <cdk/ast/identifier_node.h>
#include <cdk/ast/simple_value_node.h>
#include <iostream>

namespace pwn {

  /**
   * Class for describing vardecl nodes.
   */
  class vardecl_node: public cdk::basic_node {
    bool _local;
    bool _import;
    std::string *_varId;
    basic_type *_type;
    assignment_node *_initializer;

  public:
    inline vardecl_node(int lineno, bool local, bool import, std::string *varId, basic_type *type, assignment_node *initializer) :
        cdk::basic_node(lineno), _local(local), _import(import), _varId(varId), _type(type), _initializer(initializer) {
    }
    
    inline vardecl_node(int lineno, bool local, bool import, std::string *varId, basic_type *type) :
        cdk::basic_node(lineno), _local(local), _import(import), _varId(varId), _type(type) {
    }

  public:
    inline bool local() {
      return _local;
    }
    
    inline bool import() {
      return _import;
    }
    
    inline std::string *varId() {
      return _varId;
    }
    
    inline basic_type *type() {
      return _type;
    }
    
    inline assignment_node *initializer() {
      return _initializer;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_vardecl_node(this, level);
    }

  };

} // pwn

#endif
