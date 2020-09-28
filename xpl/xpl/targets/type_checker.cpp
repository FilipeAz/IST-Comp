#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------


inline bool xpl::type_checker::is_int(cdk::expression_node * const node) {
    return (node->type()->name() & basic_type::TYPE_INT) != 0; 
}

inline bool xpl::type_checker::is_real(cdk::expression_node * const node) {
    return (node->type()->name() & basic_type::TYPE_DOUBLE) != 0; 
}

inline bool xpl::type_checker::is_string(cdk::expression_node * const node) {
    return (node->type()->name() & basic_type::TYPE_STRING) != 0; 
}

inline bool xpl::type_checker::is_pointer(cdk::expression_node * const node) {
    return (node->type()->name() & basic_type::TYPE_POINTER) != 0; 
}

inline bool xpl::type_checker::same_type(cdk::expression_node * const node, unsigned long int type) {
    return (node->type()->name() & type) != 0; 
}






void xpl::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void xpl::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->type(new basic_type(4, basic_type::TYPE_DOUBLE));
}

void xpl::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

void xpl::type_checker::do_null_node(xpl::null_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->type(new basic_type(4, basic_type::TYPE_POINTER));
}

//---------------------------------------------------------------------------

inline void xpl::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in argument of unary expression");

  // in XPL, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void xpl::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->argument()->accept(this, lvl + 2);
    
    if(is_int(node->argument())) {
        node->type(new basic_type(4, basic_type::TYPE_INT));
    }
    else if(is_real(node->argument())) {
        node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
    }
    else {
        throw std::string("wrong type in argument of neg node");
    }
    
}


void xpl::type_checker::do_identity_node(xpl::identity_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->argument()->accept(this, lvl + 2);
    
    if(is_int(node->argument())) {
        node->type(new basic_type(4, basic_type::TYPE_INT));
    }
    else if(is_real(node->argument())) {
        node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
    }
    else {
        throw std::string("wrong type in argument of identity node");
    }
}

void xpl::type_checker::do_not_node(cdk::not_node * const node, int lvl) {
    processUnaryExpression(node, lvl);
    
}

void xpl::type_checker::do_address_node(xpl::address_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->argument()->accept(this, lvl + 2);
    
    node->type(new basic_type(4, basic_type::TYPE_POINTER));
}


void xpl::type_checker::do_mem_alloc_node(xpl::mem_alloc_node * const node, int lvl) {
    node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in argument of unary expression");

  // in XPL, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_POINTER));
}

//---------------------------------------------------------------------------

inline void xpl::type_checker::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (!is_int(node->left()) && !is_real(node->left()))
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (!is_int(node->left()) && !is_real(node->left()))
    throw std::string("wrong type in right argument of binary expression");

  // in XPL, expressions are always int or real??
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void xpl::type_checker::processBinaryEqNEqExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (is_string(node->left()))
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (is_string(node->right()))
    throw std::string("wrong type in right argument of binary expression");

  // in XPL, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


inline void xpl::type_checker::processBinaryMultDivExpression(cdk::binary_expression_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
    
    if(is_string(node->right()) || is_string(node->left())) {
        throw std::string("wrong type in argument of binary expression");
    }
    else if(is_pointer(node->right()) || is_pointer(node->left())) {
        throw std::string("wrong type in argument of binary expression");
    }
    else if(is_real(node->right()) || is_real(node->left())) {
        node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
    }
    else {
        node->type(new basic_type(4, basic_type::TYPE_INT));
    }
}

void xpl::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
    
    if(is_string(node->right()) || is_string(node->left())) {
        throw std::string("wrong type in argument of binary expression");
    }
    else if(is_pointer(node->right()) || is_pointer(node->left())) {
        if(is_real(node->right()) || is_real(node->left())) {
            throw std::string("wrong type in argument of binary expression");
        }
        else if(is_pointer(node->right()) && is_pointer(node->left())) {
            throw std::string("wrong type in argument of binary expression");
        }
        else {
            node->type(new basic_type(4, basic_type::TYPE_POINTER));
        }
    }
    else if(is_real(node->right()) || is_real(node->left())) {
        node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
    }
    else {
        node->type(new basic_type(4, basic_type::TYPE_INT));
    }
    
}
void xpl::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
    
    if(is_string(node->right()) || is_string(node->left())) {
        throw std::string("wrong type in argument of binary expression");
    }
    else if(is_pointer(node->right()) || is_pointer(node->left())) {
        if(is_real(node->right()) || is_real(node->left())) {
            throw std::string("wrong type in argument of binary expression");
        }
        else if(is_pointer(node->right()) && is_pointer(node->left())) { 
            if(node->left()->type()->name() == node->right()->type()->name()) {
                node->type(new basic_type(4, basic_type::TYPE_POINTER));
            }
            else {
                throw std::string("wrong type in argument of binary expression");
            }
        }
        else {
            node->type(new basic_type(4, basic_type::TYPE_POINTER));
        }
    }
    else if(is_real(node->right()) || is_real(node->left())) {
        node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
    }
    else {
        node->type(new basic_type(4, basic_type::TYPE_INT));
    }
}
void xpl::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
    processBinaryMultDivExpression(node,lvl);
}
void xpl::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
    processBinaryMultDivExpression(node,lvl);
}
void xpl::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
    if(!is_int(node->right()) || !is_int(node->left())) {
        throw std::string("wrong type in argument of binary expression");
    }
    node->type(new basic_type(4, basic_type::TYPE_INT));
}
void xpl::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryEqNEqExpression(node, lvl);
}
void xpl::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryEqNEqExpression(node, lvl);
}

void xpl::type_checker::do_and_node(cdk::and_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
    if(!is_int(node->right()) || !is_int(node->left())) {
        throw std::string("wrong type in argument of binary expression");
    }
    node->type(new basic_type(4, basic_type::TYPE_INT));
}

void xpl::type_checker::do_or_node(cdk::or_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
    if(!is_int(node->right()) || !is_int(node->left())) {
        throw std::string("wrong type in argument of binary expression");
    }
    node->type(new basic_type(4, basic_type::TYPE_INT));
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_func_definition_node(xpl::func_definition_node * const node, int lvl) {
    std::vector<basic_type*> args_type;
    std::string identifier;
    
    if(node->args() != NULL)
        for(size_t i = 0; i < node->args()->size(); i++) {
            xpl::var_declaration_node *arg = (xpl::var_declaration_node*) node->args()->node(i);
            args_type.push_back(arg->type());
        }
    
    if(node->literal() != NULL) {
        node->literal()->accept(this, lvl);
        if(!same_type(node->literal(),node->return_type()->name()))
            throw std::string("default return value type and function return type do not match");
    }
    
    if(node->identifier()->compare(std::string("xpl")) == 0)
        identifier = std::string("_main");
    else if(node->identifier()->compare(std::string("_main")) == 0)
        identifier = std::string("xpl");
    else 
        identifier = *(node->identifier());

    std::shared_ptr<xpl::symbol> symbol = _symtab.find_local(identifier);
    if(symbol != nullptr) {
        if(symbol->function_defined())
            throw *(node->identifier()) + " is already defined";
        
        if(symbol->function_arguments().size() != args_type.size())
            throw *(node->identifier()) + " is already declared with other types of arguments";
        
        if(symbol->type()->name() != node->return_type()->name())
            throw *(node->identifier()) + " is already declared with other return type";
        
        for(size_t i = 0; i < symbol->function_arguments().size() && i < args_type.size(); i++) { 
            if(symbol->function_arguments().at(i) != args_type.at(i))
                throw *(node->identifier()) + " is already declared with other types of arguments";
        }
        
        symbol->function_defined(true);
    }
    else {
        std::shared_ptr<xpl::symbol> s = std::make_shared<xpl::symbol>(node->return_type(), identifier, args_type, true, -1);
         
        s->offset(-1);
        _symtab.insert(identifier, s);
    }
}

void xpl::type_checker::do_func_declaration_node(xpl::func_declaration_node * const node, int lvl) {
    std::vector<basic_type*> args_type;
 
    if(node->args()!=NULL)
        for (size_t i = 0; i < node->args()->size(); i++) {
            xpl::var_declaration_node *arg = (xpl::var_declaration_node*) node->args()->node(i);
            args_type.push_back(arg->type());
            
        }
   
 
    if(node->identifier()->compare(std::string("xpl")) == 0) {
        if (!_symtab.find_local("_main"))
        _symtab.insert("_main", std::make_shared<xpl::symbol>(node->return_type(), "_main", args_type, false, -1)); // put in the symbol table
        else
            throw "xpl redeclared";
    }
    else if(node->identifier()->compare(std::string("_main")) == 0) {
        if (!_symtab.find_local("xpl"))
        _symtab.insert("xpl", std::make_shared<xpl::symbol>(node->return_type(), "xpl", args_type, false, -1)); // put in the symbol table
        else
            throw "_main redeclared";
    }
    else {
        const std::string &identifier = *(node->identifier());
        if (!_symtab.find_local(identifier)) {
            std::shared_ptr<xpl::symbol> s = std::make_shared<xpl::symbol>(node->return_type(), identifier, args_type, false, -1);
            s->offset(-1); 
            _symtab.insert(identifier, s); 
        }
        else
            throw identifier + " redeclared";
  }
}

void xpl::type_checker::do_func_invocation_node(xpl::func_invocation_node * const node, int lvl) {
    
    ASSERT_UNSPEC;
    
    const std::string &identifier = *(node->identifier());
    
    std::shared_ptr<xpl::symbol> s = _symtab.find(identifier);
    if(s != NULL && s->is_function()) {
        std::vector<basic_type*> args_type = s->function_arguments();
        cdk::expression_node *arg;
     
        if(node->args() != NULL) {
            if(args_type.size() != node->args()->size())
                throw identifier + ": wrong arguments";
                 
            for (size_t i = 0; i < args_type.size()  &&  i < node->args()->size(); i++) {
                
                arg = (cdk::expression_node*) node->args()->node(i);
         
                arg->accept(this, lvl);

        
                if (!same_type(arg, args_type.at(i)->name())) {
                    throw identifier + ": wrong argument types";
                }
            }
         
         
        }
    }
    else if(s != NULL && !(s->is_function()))
        throw identifier + " is not a function";
    else
        throw identifier + " is undeclared";
     
     
}

void xpl::type_checker::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = node->name();
  std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);

  if (symbol != nullptr) {
    node->type(symbol->type());
  }
  else {
    throw id;
  }
}

void xpl::type_checker::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_UNSPEC;
  try {
    node->lvalue()->accept(this, lvl);
    node->type(node->lvalue()->type());
  } catch (const std::string &id) {
    throw "undeclared variable '" + id + "'";
  }
}

void xpl::type_checker::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;

  
  node->lvalue()->accept(this, lvl);
  node->rvalue()->accept(this, lvl);
  
  if(is_int(node->lvalue()) && is_int(node->rvalue()))
      node->type(new basic_type(4, basic_type::TYPE_INT));
  else if(is_real(node->lvalue()) && is_int(node->rvalue()))
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));  
  else if(is_real(node->lvalue()) && is_real(node->rvalue()))
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  
  else if(is_string(node->lvalue()) && is_string(node->rvalue()))
      node->type(new basic_type(4, basic_type::TYPE_STRING));
  
  else if(is_pointer(node->lvalue()) && is_pointer(node->rvalue())) 
      node->type(new basic_type(4, basic_type::TYPE_POINTER));
  
  else
      throw std::string("wrong type in right argument of assignment expression");
}

void xpl::type_checker::do_var_declaration_node(xpl::var_declaration_node * const node, int lvl) {
    const std::string &identifier = *(node->identifier());
    
    if (!_symtab.find_local(identifier))
        _symtab.insert(identifier, std::make_shared<xpl::symbol>(node->type(), identifier, -1));
    else
        throw identifier + " was already declared!";
}

void xpl::type_checker::do_var_inicialization_node(xpl::var_inicialization_node * const node, int lvl) {
    const std::string &identifier = *(node->identifier());
    
    if (!_symtab.find_local(identifier))
        _symtab.insert(identifier, std::make_shared<xpl::symbol>(node->type(), identifier, -1));
    else
        throw identifier + " was already declared!";
   
   
    node->expression()->accept(this, lvl + 2);
    if(!same_type(node->expression(), node->type()->name()) && !((node->type()->name() & basic_type::TYPE_DOUBLE) != 0 && is_int(node->expression())))
        throw std::string("initialization expression type is incompatible with declared variable type");
     
}


void xpl::type_checker::do_index_node(xpl::index_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->pointer()->accept(this, lvl);
    if (!is_pointer(node->pointer()))
        throw std::string("wrong type in argument of index node");
   
   
    node->index()->accept(this, lvl);
   
    if (!is_int(node->index()))
        throw std::string("wrong type in argument of index node");
   
    
    node->type(new basic_type(4, basic_type::TYPE_INT));
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void xpl::type_checker::do_print_node(xpl::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_read_node(xpl::read_node * const node, int lvl) { 
  try {
    node->accept(this, lvl);
  } catch (const std::string &id) {
    throw "undeclared variable '" + id + "'";
  }
}

void xpl::type_checker::do_print_line_node(xpl::print_line_node * const node, int lvl) {
    node->argument()->accept(this, lvl + 2);
}

void xpl::type_checker::do_block_node(xpl::block_node * const node, int lvl) {//?????
    
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_while_node(xpl::while_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
  node->block()->accept(this, lvl + 4);
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_if_node(xpl::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
  node->block()->accept(this, lvl + 4);
}

void xpl::type_checker::do_if_else_node(xpl::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
  node->thenblock()->accept(this, lvl + 4);
  node->elseblock()->accept(this, lvl + 4);
}

void xpl::type_checker::do_next_node(xpl::next_node * const node, int lvl) {
    //??
}

void xpl::type_checker::do_stop_node(xpl::stop_node * const node, int lvl) {
    //??
}

void xpl::type_checker::do_return_node(xpl::return_node * const node, int lvl) {
    //??
}

void xpl::type_checker::do_sweep_up_node(xpl::sweep_up_node * const node, int lvl){ 
    node->lvalue()->accept(this, lvl);
    node->expression1()->accept(this, lvl);
    node->expression2()->accept(this, lvl);
    node->expression3()->accept(this, lvl);
    node->block()->accept(this, lvl);
}

void xpl::type_checker::do_sweep_down_node(xpl::sweep_down_node * const node, int lvl)  { 
    node->lvalue()->accept(this, lvl);
    node->expression1()->accept(this, lvl);
    node->expression2()->accept(this, lvl);
    node->expression3()->accept(this, lvl);
    node->block()->accept(this, lvl);
}
