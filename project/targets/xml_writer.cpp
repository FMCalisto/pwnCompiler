// $Id: xml_writer.cpp,v 1.15 2015/05/20 08:33:26 ist170916 Exp $ -*- c++ -*-
#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

//---------------------------------------------------------------------------

void pwn::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  processSimple(node, lvl);
}

void pwn::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  processSimple(node, lvl);
}

//---------------------------------------------------------------------------

inline void pwn::xml_writer::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  // CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

inline void pwn::xml_writer::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
 // CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_rvalue_node(pwn::rvalue_node * const node, int lvl) {
  // CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_assignment_node(pwn::assignment_node * const node, int lvl) {
  // CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 2);
  openTag("rvalue", lvl + 2);
  node->rvalue()->accept(this, lvl + 4);
  closeTag("rvalue", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_evaluation_node(pwn::evaluation_node * const node, int lvl) {
  // CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_print_node(pwn::print_node * const node, int lvl) {
  // CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_read_node(pwn::read_node * const node, int lvl) {
  os() << std::string(lvl, ' ') + "<" + "read" + "/>";
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_if_node(cdk::if_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_if_else_node(cdk::if_else_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  openTag("else", lvl + 2);
  node->elseblock()->accept(this, lvl + 4);
  closeTag("else", lvl + 2);
  closeTag(node, lvl);
}

//--------------- Nodes specific for PWN ------------------------------------
void pwn::xml_writer::do_basic_lvalue_node(pwn::basic_lvalue_node * const node, int lvl) {
  // CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  os() << node->varId();
  closeTag(node, lvl);
}

void pwn::xml_writer::do_indexed_lvalue_node(pwn::indexed_lvalue_node * const node, int lvl) {
  // CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  openTag("indexed expr", lvl + 2);
  node->indexed_expr()->accept(this, lvl + 4);
  closeTag("indexed expr", lvl + 2);
  openTag("index", lvl + 2);
  node->index()->accept(this, lvl + 4);
  closeTag("index", lvl);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_noob_node(pwn::noob_node * const node, int lvl) {
  // FIXME: just print noob
  openTag(node, lvl);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  processSimple(node, lvl);
}

void pwn::xml_writer::do_double_node(cdk::double_node * const node, int lvl) {
  processSimple(node, lvl);
}

void pwn::xml_writer::do_and_node(pwn::and_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

void pwn::xml_writer::do_or_node(pwn::or_node * const node, int lvl){
  processBinaryExpression(node, lvl);
}

void pwn::xml_writer::do_identity_node(pwn::identity_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

void pwn::xml_writer::do_symmetric_node(pwn::symmetric_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

void pwn::xml_writer::do_stackalloc_node(pwn::stackalloc_node * const node, int lvl) {
  // CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_println_node(pwn::println_node * const node, int lvl) {
  // CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->print()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_repeat_node(pwn::repeat_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("init", lvl + 2);
  node->init()->accept(this, lvl + 4);
  closeTag("init", lvl + 2);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("step", lvl + 2);
  node->step()->accept(this, lvl + 4);
  closeTag("step", lvl + 2);
  openTag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("block", lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_stop_node(pwn::stop_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("argument", lvl + 2);
  node->argument()->accept(this, lvl + 4);
  closeTag("argument", lvl + 2);
}

void pwn::xml_writer::do_next_node(pwn::next_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("argument", lvl + 2);
  node->argument()->accept(this, lvl + 4);
  closeTag("argument", lvl + 2);
}
void pwn::xml_writer::do_return_node(pwn::return_node * const node, int lvl) {
  os() << std::string(lvl, ' ') + "<" + "return" + "/>";
}

void pwn::xml_writer::do_fundecl_node(pwn::fundecl_node * const node, int lvl) {
  openTag(node, lvl);
  // TODO: node->returnType();
  os() << std::string(lvl + 2, ' ') + "name: " << std::endl;
  os() << *(node->funId());
  os() << std::string(lvl + 2, ' ') + "qualifiers: "  << std::endl;
  os() << std::string(lvl + 4, ' ') + "isLocal = \'" << (node->local() ? "true" : "false") << "\'" << std::endl;
  os() << std::string(lvl + 4, ' ') + "isImported = \'" << (node->import() ? "true" : "false") << "\'" << std::endl;
  os() << std::string(lvl + 2, ' ') + "arguments: "  << std::endl;
  node->arguments()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_fundef_node(pwn::fundef_node * const node, int lvl) {
  openTag(node, lvl);
  node->header()->accept(this, lvl + 2);
  node->body()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_funcall_node(pwn::funcall_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("function identifier", lvl + 2);
  os() << *(node->funId());
  closeTag("function identifier", lvl + 2);
  openTag("arguments", lvl + 2);
  node->arguments()->accept(this, lvl + 4);
  closeTag("arguments", lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_vardecl_node(pwn::vardecl_node * const node, int lvl) {
  openTag(node, lvl);
  // FIXME: os() << std::string(lvl + 4, ' ') + "type: " << node->type()->name() << std::endl;
  os() << std::string(lvl + 2, ' ') + "name: " << *(node->varId()) << std::endl;
  os() << std::string(lvl + 2, ' ') + "qualifiers: "  << std::endl;
  os() << std::string(lvl + 4, ' ') + "isLocal = \'" << (node->local() ? "true" : "false") << "\'" << std::endl;
  os() << std::string(lvl + 4, ' ') + "isImported = \'" << (node->import() ? "true" : "false") << "\'" << std::endl;
  closeTag(node, lvl);
}
