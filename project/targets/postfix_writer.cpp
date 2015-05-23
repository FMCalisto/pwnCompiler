// $Id: postfix_writer.cpp,v 1.20 2015/05/20 10:53:12 ist170916 Exp $ -*- c++ -*-
#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"  // all.h is automatically generated

//---------------------------------------------------------------------------
//     THIS IS THE VISITOR'S DEFINITION
//---------------------------------------------------------------------------

void pwn::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void pwn::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  _pf.INT(node->value()); // push an integer
}

void pwn::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  int lbl1;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.STR(node->value()); // output string characters

  /* leave the address on the stack */
  _pf.TEXT(); // return to the TEXT segment
  _pf.ADDR(mklbl(lbl1)); // the string to be printed
}

//---------------------------------------------------------------------------

void pwn::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  // logical negation
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value
  _pf.NEG(); // 2-complement
}

//---------------------------------------------------------------------------

void pwn::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	
	pwn::postfix_writer::convert_binary_expr_subnodes(node, lvl);
	
	if(node->type()->size() == 4) {
		_pf.ADD();
	} else if (node->type()->size() == 8) {
		_pf.DADD();
	}
}

void pwn::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	
	pwn::postfix_writer::convert_binary_expr_subnodes(node, lvl);
	
	if(node->type()->size() == 4) {
		_pf.SUB();
	} else if (node->type()->size() == 8) {
		_pf.DSUB();
	}
}
void pwn::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	
	pwn::postfix_writer::convert_binary_expr_subnodes(node, lvl);
	
	if(node->type()->size() == 4) {
		_pf.MUL();
	} else if (node->type()->size() == 8) {
		_pf.DMUL();
	}
}
void pwn::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	
	pwn::postfix_writer::convert_binary_expr_subnodes(node, lvl);
	
	if(node->type()->size() == 4) {
		_pf.DIV();
	} else if (node->type()->size() == 8) {
		_pf.DDIV();
	}
}
void pwn::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}

void pwn::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  pwn::postfix_writer::convert_binary_expr_subnodes(node, lvl);
  if(node->type()->size() == 4) {
    _pf.LT();
  } else if (node->type()->size() == 8) {
    _pf.DCMP();
    _pf.INT(0);
    _pf.LT();
  }
}
void pwn::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  pwn::postfix_writer::convert_binary_expr_subnodes(node, lvl);
  if(node->type()->size() == 4) {
    _pf.LE();
  } else if (node->type()->size() == 8) {
    _pf.DCMP();
    _pf.INT(0);
    _pf.LE();
  }
}
void pwn::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  pwn::postfix_writer::convert_binary_expr_subnodes(node, lvl);
  if(node->type()->size() == 4) {
    _pf.GE();
  } else if (node->type()->size() == 8) {
    _pf.DCMP();
    _pf.INT(0);
    _pf.GE();
  }
}
void pwn::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  pwn::postfix_writer::convert_binary_expr_subnodes(node, lvl);
  if(node->type()->size() == 4) {
    _pf.GT();
  } else if (node->type()->size() == 8) {
    _pf.DCMP();
    _pf.INT(0);
    _pf.GT();
  }
}
void pwn::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  pwn::postfix_writer::convert_binary_expr_subnodes(node, lvl);
  if(node->type()->size() == 4) {
    _pf.NE();
  } else if (node->type()->size() == 8) {
    _pf.DCMP();
    _pf.INT(0);
    _pf.NE();
  }
}
void pwn::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  pwn::postfix_writer::convert_binary_expr_subnodes(node, lvl);
  if(node->type()->size() == 4) {
    _pf.EQ();
  } else if (node->type()->size() == 8) {
    _pf.DCMP();
    _pf.INT(0);
    _pf.EQ();
  }
}

//---------------------------------------------------------------------------

void pwn::postfix_writer::do_rvalue_node(pwn::rvalue_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->lvalue()->accept(this, lvl);
  if (node->type()->size() == 4) {
      _pf.LOAD();
  } else if (node->type()->size() == 8) {
     _pf.DLOAD();
  }
}

//---------------------------------------------------------------------------

void pwn::postfix_writer::do_assignment_node(pwn::assignment_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->rvalue()->accept(this, lvl); // determine the new value
  if(node->rvalue()->type()->size() == 4) {
    _pf.DUP();
    node->lvalue()->accept(this, lvl); // where to store the value
    _pf.STORE(); // store the value at address
  } else if (node->rvalue()->type()->size() == 8) {
    _pf.DDUP();
    node->lvalue()->accept(this, lvl); // where to store the value
    _pf.DSTORE(); // store the value at address
  }
}

//---------------------------------------------------------------------------

void pwn::postfix_writer::do_evaluation_node(pwn::evaluation_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.TRASH(4); // delete the evaluated value
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.TRASH(4); // delete the evaluated value's address
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.TRASH(8); // delete the evaluated value's address
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_POINTER) {
    _pf.TRASH(4); // delete the evaluated value's address
  }
  else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
}

void pwn::postfix_writer::do_print_node(pwn::print_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.CALL("printd");
    _pf.TRASH(8); // delete the printed value's address
  }
  else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
}

//---------------------------------------------------------------------------

void pwn::postfix_writer::do_read_node(pwn::read_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  _pf.CALL("readi");
  _pf.PUSH();
}

//---------------------------------------------------------------------------

void pwn::postfix_writer::do_if_node(cdk::if_node * const node, int lvl) {
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void pwn::postfix_writer::do_if_else_node(cdk::if_else_node * const node, int lvl) {
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}

//--------------- Nodes specific for PWN ------------------------------------
void pwn::postfix_writer::do_basic_lvalue_node(pwn::basic_lvalue_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  // load global variables addresses TODO: block variables
  const std::string &varId = *(node->varId());
  std::shared_ptr<pwn::symbol> symbol = _symtab.find(varId);
  _pf.ADDR(mklbl(symbol->value()));
}

void pwn::postfix_writer::do_indexed_lvalue_node(pwn::indexed_lvalue_node * const node, int lvl) {
  // TODO: Implement this method
  // get left and right exprs and add them
}

void pwn::postfix_writer::do_noob_node(pwn::noob_node * const node, int lvl) {
    _pf.INT(0);
}

void pwn::postfix_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  // TODO: Implement this method
}

void pwn::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
	int lbl = ++_lbl;
	_pf.RODATA();
	_pf.LABEL(mklbl(lbl));
	_pf.DOUBLE(node->value());
	_pf.TEXT();
	_pf.ADDR(mklbl(lbl));
	_pf.DLOAD();
}

void pwn::postfix_writer::do_and_node(pwn::and_node * const node, int lvl) {
    CHECK_TYPES(_compiler, _symtab, node);
    int lbl = ++_lbl;
    
    node->left()->accept(this, lvl + 2);
    _pf.JZ(mklbl(lbl));
    node->right()->accept(this, lvl + 2);
    _pf.AND();
    _pf.LABEL(mklbl(lbl));
}

void pwn::postfix_writer::do_or_node(pwn::or_node * const node, int lvl) {
    CHECK_TYPES(_compiler, _symtab, node);
    int lbl = ++_lbl;
    
    node->left()->accept(this, lvl + 2);
    _pf.JNZ(mklbl(lbl));
    node->right()->accept(this, lvl + 2);
    _pf.OR();
    _pf.LABEL(mklbl(lbl));
}

void pwn::postfix_writer::do_identity_node(pwn::identity_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	node->argument()->accept(this, lvl);
}

void pwn::postfix_writer::do_symmetric_node(pwn::symmetric_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	node->argument()->accept(this, lvl);
	if(node->type()->size() == 4) {
		_pf.NEG();
	} else if(node->type()->size() == 8) {
		_pf.DNEG();
	}
}

void pwn::postfix_writer::do_stackalloc_node(pwn::stackalloc_node * const node, int lvl) {
  // TODO: Implement this method
}

void pwn::postfix_writer::do_println_node(pwn::println_node * const node, int lvl) {
  node->print()->accept(this, lvl);
  _pf.CALL("println");
}

void pwn::postfix_writer::do_repeat_node(pwn::repeat_node * const node, int lvl) {
  int lbl_cond = ++_lbl;
  int lbl_step = ++_lbl;
  int lbl_end = ++_lbl;
  
  // to allow stop and next
  _repeat_endlbl_vec->push_back(lbl_end);
  _repeat_steplbl_vec->push_back(lbl_cond);
  
  node->init()->accept(this, lvl);
  _pf.LABEL(mklbl(lbl_cond));
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl_end));
  node->block()->accept(this, lvl);
  _pf.LABEL(mklbl(lbl_step));
  node->step()->accept(this, lvl);
  _pf.JMP(mklbl(lbl_cond));
  _pf.LABEL(mklbl(lbl_end));
  
  // no need to store the labels anymore
  _repeat_endlbl_vec->pop_back();
  _repeat_steplbl_vec->pop_back();
}

void pwn::postfix_writer::do_stop_node(pwn::stop_node * const node, int lvl) {
    CHECK_TYPES(_compiler, _symtab, node);
    
    // FIXME: argument should have been passed as int and not integer node (will not be visited)
    _pf.JMP(mklbl(_repeat_endlbl_vec->at(_repeat_endlbl_vec->size() - node->argument()->value())));
}

void pwn::postfix_writer::do_next_node(pwn::next_node * const node, int lvl) {
    CHECK_TYPES(_compiler, _symtab, node);
    
    // FIXME: argument should have been passed as int and not integer node (will not be visited)
    _pf.JMP(mklbl(_repeat_steplbl_vec->at(_repeat_steplbl_vec->size() - node->argument()->value())));
}
void pwn::postfix_writer::do_return_node(pwn::return_node * const node, int lvl) {
  // TODO: Implement this method
  
  const std::string &varId = "teste"; // TODO: get func symbol

  if (_symtab.find(varId)) {
      _pf.ADDR(varId);
      _pf.STORE(); //TODO: DSTORE too...
  }
  
}

void pwn::postfix_writer::do_fundecl_node(pwn::fundecl_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  const std::string &funId = *(node->funId());
  basic_type *type = new basic_type(node->returnType()->size(), node->returnType()->name());  
  std::shared_ptr<pwn::symbol> symbol = std::make_shared<pwn::symbol>(type, funId, ++_lbl);
  _symtab.insert(funId, symbol);_pf.DATA();
  // reserve space for return values
  _pf.ALIGN();
  _pf.LABEL(mklbl(symbol->value()));
  if(node->returnType()->size() == 4)
	_pf.CONST(0); // default init
  else if(node->returnType()->size() == 8)
	_pf.DOUBLE(0); // default init
  _pf.TEXT();
  
  if(funId == "pwn") {
      _pf.GLOBAL("_main", _pf.FUNC());
	  // these are just a few library function imports
	  _pf.EXTERN("readi");
	  _pf.EXTERN("printi");
	  _pf.EXTERN("printd");
	  _pf.EXTERN("prints");
	  _pf.EXTERN("println");
  } else if (funId == "_main") {
	  _pf.GLOBAL("._main", _pf.FUNC());
  } else {
	  _pf.GLOBAL(funId, _pf.FUNC());
  }
}

void pwn::postfix_writer::do_fundef_node(pwn::fundef_node * const node, int lvl) {
  std::string id;
  
  _func_param_bytes = 0;
  node->header()->accept(this, lvl + 2); // this will change _func_param_bytes
  
  if(*(node->header()->funId()) == "pwn") {
	  id = std::string("_main");
  } else if (*(node->header()->funId()) == "_main") {
	  id = std::string("._main");
  } else {
	  id = *(node->header()->funId());
  }
  
  _pf.TEXT();
  _pf.ALIGN();
  
  _pf.LABEL(id);
  _pf.ENTER(_func_param_bytes);
  
  if(*(node->header()->funId()) == "pwn") {
	  // initialize global vars
	  for(uint i = 0 ; i < glob_var_inits->size() ; i++) {
	      glob_var_inits->at(i)->accept(this, lvl + 2);
	  }
  }

  _symtab_level++;
  node->body()->accept(this, lvl + 2);
  
  // end the function:
  // functions are in the global scope
  const std::string &funId = *(node->header()->funId());
  std::shared_ptr<pwn::symbol> symbol = _symtab.find(funId);
  
  _pf.ADDR(mklbl(symbol->value()));
  if(node->header()->returnType()->size() == 4) {
    _pf.LOAD();
    _pf.POP();
  } else if(node->header()->returnType()->size() == 8) {
    _pf.DLOAD();
    _pf.DPOP();
  }
  _pf.LEAVE();
  _pf.RET();
}

void pwn::postfix_writer::do_funcall_node(pwn::funcall_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  // functions are in the global scope
  const std::string &funId = *(node->funId());
  std::shared_ptr<pwn::symbol> symbol = _symtab.find(funId);
  
  node->arguments()->accept(this, lvl);
  _pf.CALL(mklbl(symbol->value()));
  /* TODO: store return type of function when declaring... 
  if(node->returnType()->size() == 4)
    _pf.PUSH();
  else if(node->returnType()->size() == 8)
    _pf.DPUSH();
  */
}

void pwn::postfix_writer::do_vardecl_node(pwn::vardecl_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  const std::string &varId = *(node->varId());
  
  basic_type *type = new basic_type(node->type()->size(), node->type()->name());  
  std::shared_ptr<pwn::symbol> symbol = std::make_shared<pwn::symbol>(type, varId, ++_lbl);
  _symtab.insert(varId, symbol);
  
  _pf.DATA();
  _pf.ALIGN();
  _pf.GLOBAL(mklbl(symbol->value()), _pf.OBJ());
  _pf.LABEL(mklbl(symbol->value()));
  
  if(node->type()->size() == 4)
	_pf.CONST(0); // default init
  else if(node->type()->size() == 8)
	_pf.DOUBLE(0); // default init
  else
    throw "error";
  _pf.TEXT();
  
  if(node->initializer()) {
    if(_symtab_level == 0)
      glob_var_inits->push_back(node->initializer());
    else
      node->initializer()->accept(this, lvl);
  }
}

void pwn::postfix_writer::convert_binary_expr_subnodes(cdk::binary_expression_node * const node, int lvl) {
	if(node->type()->size() == 4) {
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
	} else if (node->type()->size() == 8) {
		if (node->left()->type()->size() == 4) {
			node->left()->accept(this, lvl);
			_pf.I2D();
			node->right()->accept(this, lvl);
		} else if (node->right()->type()->size() == 4) {
			node->left()->accept(this, lvl);
			node->right()->accept(this, lvl);
			_pf.I2D();
		} else {
			// both are of size 8
			node->left()->accept(this, lvl);
			node->right()->accept(this, lvl);
		}
	}
}
