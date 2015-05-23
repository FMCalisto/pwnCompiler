// $Id: postfix_writer.h,v 1.8 2015/05/20 10:53:12 ist170916 Exp $ -*- c++ -*-
#ifndef __PWN_SEMANTICS_PF_WRITER_H__
#define __PWN_SEMANTICS_PF_WRITER_H__

#include <string>
#include <vector>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/emitters/basic_postfix_emitter.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"
#include "ast/assignment_node.h"

namespace pwn {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class postfix_writer: public basic_ast_visitor {
    cdk::symbol_table<pwn::symbol> &_symtab;
    cdk::basic_postfix_emitter &_pf;
    int _lbl;
    int _symtab_level;
    int _func_param_bytes;
    std::vector<int> *_repeat_endlbl_vec;
    std::vector<int> *_repeat_steplbl_vec;
    std::vector<assignment_node*> *glob_var_inits;

  public:
    postfix_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<pwn::symbol> &symtab,
                   cdk::basic_postfix_emitter &pf) :
        basic_ast_visitor(compiler), _symtab(symtab), _pf(pf), _lbl(0), _symtab_level(0), _func_param_bytes(0), _repeat_endlbl_vec(new std::vector<int>()), _repeat_steplbl_vec(new std::vector<int>()), glob_var_inits(new std::vector<assignment_node*>()) {
    }

  public:
    ~postfix_writer() {
      os().flush();
    }

  private:
    /** Method used to generate sequential labels. */
    inline std::string mklbl(int lbl) {
      std::ostringstream oss;
      if (lbl < 0)
        oss << ".L" << -lbl;
      else
        oss << "_L" << lbl;
      return oss.str();
    }
    
    void convert_binary_expr_subnodes(cdk::binary_expression_node * const node, int lvl);

  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl);

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl);
    void do_string_node(cdk::string_node * const node, int lvl);

  public:
    void do_neg_node(cdk::neg_node * const node, int lvl);

  public:
    void do_add_node(cdk::add_node * const node, int lvl);
    void do_sub_node(cdk::sub_node * const node, int lvl);
    void do_mul_node(cdk::mul_node * const node, int lvl);
    void do_div_node(cdk::div_node * const node, int lvl);
    void do_mod_node(cdk::mod_node * const node, int lvl);
    void do_lt_node(cdk::lt_node * const node, int lvl);
    void do_le_node(cdk::le_node * const node, int lvl);
    void do_ge_node(cdk::ge_node * const node, int lvl);
    void do_gt_node(cdk::gt_node * const node, int lvl);
    void do_ne_node(cdk::ne_node * const node, int lvl);
    void do_eq_node(cdk::eq_node * const node, int lvl);

  public:
    void do_if_node(cdk::if_node * const node, int lvl);
    void do_if_else_node(cdk::if_else_node * const node, int lvl);

  public:
    void do_rvalue_node(pwn::rvalue_node * const node, int lvl);

  public:
    void do_evaluation_node(pwn::evaluation_node * const node, int lvl);
    void do_print_node(pwn::print_node * const node, int lvl);
    void do_read_node(pwn::read_node * const node, int lvl);
    void do_assignment_node(pwn::assignment_node * const node, int lvl);
    
  // Nodes specific for PWN
    void do_basic_lvalue_node(pwn::basic_lvalue_node * const node, int lvl);
    void do_indexed_lvalue_node(pwn::indexed_lvalue_node * const node, int lvl);
    void do_noob_node(pwn::noob_node * const node, int lvl);
    void do_identifier_node(cdk::identifier_node * const node, int lvl);
    void do_double_node(cdk::double_node * const node, int lvl);
    void do_and_node(pwn::and_node * const node, int lvl);
    void do_or_node(pwn::or_node * const node, int lvl);
    void do_identity_node(pwn::identity_node * const node, int lvl);
    void do_symmetric_node(pwn::symmetric_node * const node, int lvl);
    void do_stackalloc_node(pwn::stackalloc_node * const node, int lvl);
    void do_println_node(pwn::println_node * const node, int lvl);
    void do_repeat_node(pwn::repeat_node * const node, int lvl);
    void do_stop_node(pwn::stop_node * const node, int lvl);
    void do_next_node(pwn::next_node * const node, int lvl);
    void do_return_node(pwn::return_node * const node, int lvl);
    void do_fundecl_node(pwn::fundecl_node * const node, int lvl);
    void do_fundef_node(pwn::fundef_node * const node, int lvl);
    void do_funcall_node(pwn::funcall_node * const node, int lvl);
    void do_vardecl_node(pwn::vardecl_node * const node, int lvl);

  };

} // pwn

#endif
