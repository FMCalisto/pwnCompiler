// $Id: type_checker.cpp,v 1.9 2015/05/20 08:33:26 ist170916 Exp $ -*- c++ -*-
#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------

void pwn::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void pwn::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

//---------------------------------------------------------------------------

inline void pwn::type_checker::processAritmeticUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() == basic_type::TYPE_INT)
    node->type(new basic_type(4, basic_type::TYPE_INT));
  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE)
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  else
    throw std::string("wrong type in argument of aritmetic unary expression (should be int or double)");
}

void pwn::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() == basic_type::TYPE_INT)
    node->type(new basic_type(4, basic_type::TYPE_INT));
  else
    throw std::string("wrong type in argument of logical negation (should be int)");
}

//---------------------------------------------------------------------------

inline void pwn::type_checker::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;

  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  
  if (node->left()->type()->name() == basic_type::TYPE_INT) {
    if(node->right()->type()->name() == basic_type::TYPE_INT) {
	  // int + int
      node->type(new basic_type(4, basic_type::TYPE_INT));
    } else if(node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
	  // int + double
	  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
	} else if(node->right()->type()->name() == basic_type::TYPE_POINTER) {
	  // int + pointer
	  node->type(new basic_type(8, basic_type::TYPE_POINTER));
	}
  } else
      throw std::string("incompatible types in assignment expression");
}

//---------------------------------------------------------------------------

inline void pwn::type_checker::processLogicalBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
    throw std::string("only integers are allowed in binary logical operators");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
    throw std::string("only integers are allowed in binary logical operators");

  // result of logical binary expressions is always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

//---------------------------------------------------------------------------

void pwn::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl); // TODO: also allow ptr - ptr
}
void pwn::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl); // TODO: only for int
}
void pwn::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::type_checker::do_rvalue_node(pwn::rvalue_node * const node, int lvl) {
  node->lvalue()->accept(this, lvl);
  node->type(node->lvalue()->type());
}

//---------------------------------------------------------------------------

void pwn::type_checker::do_assignment_node(pwn::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;

  node->lvalue()->accept(this, lvl + 2);
  node->rvalue()->accept(this, lvl + 2);
  
  const bool typesMatch = node->lvalue()->type()->name() == node->rvalue()->type()->name();
  const bool intToDouble = node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE && node->rvalue()->type()->name() == basic_type::TYPE_INT;
  
  if (typesMatch || intToDouble) {
    basic_type *type = new basic_type(node->lvalue()->type()->size(), node->lvalue()->type()->name());
    node->type(type);
  } else
    throw std::string("incompatible types in assignment expression");
}

//---------------------------------------------------------------------------

void pwn::type_checker::do_evaluation_node(pwn::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void pwn::type_checker::do_print_node(pwn::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void pwn::type_checker::do_read_node(pwn::read_node * const node, int lvl) {
	// TODO: Check if this can be deleted
}

//---------------------------------------------------------------------------

void pwn::type_checker::do_if_node(cdk::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void pwn::type_checker::do_if_else_node(cdk::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

//--------------- Nodes specific for PWN ------------------------------------
void pwn::type_checker::do_basic_lvalue_node(pwn::basic_lvalue_node * const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = *(node->varId());
  std::shared_ptr<pwn::symbol> symbol = _symtab.find(id);
  if (symbol == nullptr) throw id + " undeclared";
  
  basic_type *type = new basic_type(symbol->type()->size(), symbol->type()->name());
  node->type(type);
}

void pwn::type_checker::do_indexed_lvalue_node(pwn::indexed_lvalue_node * const node, int lvl) {
  // TODO: Implement this method
}

void pwn::type_checker::do_noob_node(pwn::noob_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(8, basic_type::TYPE_POINTER));
}

void pwn::type_checker::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  // TODO: Implement this method
}

void pwn::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void pwn::type_checker::do_and_node(pwn::and_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in left argument of and expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in right argument of and expression");

  // and is always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void pwn::type_checker::do_or_node(pwn::or_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in left argument of or expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in right argument of or expression");

  // oe is always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void pwn::type_checker::do_identity_node(pwn::identity_node * const node, int lvl) {
  processAritmeticUnaryExpression(node, lvl);
}

void pwn::type_checker::do_symmetric_node(pwn::symmetric_node * const node, int lvl) {
  processAritmeticUnaryExpression(node, lvl);
}

void pwn::type_checker::do_stackalloc_node(pwn::stackalloc_node * const node, int lvl) {
  // TODO: Implement this method INT
}

void pwn::type_checker::do_println_node(pwn::println_node * const node, int lvl) {
  node->print()->accept(this, lvl + 2);
}

void pwn::type_checker::do_repeat_node(pwn::repeat_node * const node, int lvl) {
  node->init()->accept(this, lvl + 4);
  node->condition()->accept(this, lvl + 4);
  node->step()->accept(this, lvl + 4);
}

void pwn::type_checker::do_stop_node(pwn::stop_node * const node, int lvl) {
  // does nothing because argument is an integer node... should be switched to a int value because node is never visited (see postfix writer)
}

void pwn::type_checker::do_next_node(pwn::next_node * const node, int lvl) {
  // does nothing because argument is an integer node... should be switched to a int value because node is never visited (see postfix writer)
}
void pwn::type_checker::do_return_node(pwn::return_node * const node, int lvl) {
  //  DO NOTHING
}

void pwn::type_checker::do_fundecl_node(pwn::fundecl_node * const node, int lvl) {
  // TODO: Implement this method
}

void pwn::type_checker::do_fundef_node(pwn::fundef_node * const node, int lvl) {
  // TODO: Implement this method
}

void pwn::type_checker::do_funcall_node(pwn::funcall_node * const node, int lvl) {
  // TODO: Implement this method
  // check args
}

void pwn::type_checker::do_vardecl_node(pwn::vardecl_node * const node, int lvl) {
  ASSERT_UNSPEC;
  std::string &id = *(node->varId());
  if (!_symtab.insert(id, std::make_shared<pwn::symbol>(node->type(), id, 0)))
    throw id + " redeclared";

  if (node->initializer()) {
    node->initializer()->accept(this, lvl+2);
    if (node->type()->name() != node->initializer()->type()->name())
      throw std::string("wrong type for initializer");
  }
}
