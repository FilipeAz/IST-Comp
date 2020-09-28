#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "targets/locals_visitor.h"
#include "ast/all.h"  // all.h is automatically generated

//---------------------------------------------------------------------------

inline bool xpl::postfix_writer::is_int(cdk::expression_node * const node) {
    return (node->type()->name() & basic_type::TYPE_INT) != 0; 
}

inline bool xpl::postfix_writer::is_real(cdk::expression_node * const node) {
    return (node->type()->name() & basic_type::TYPE_DOUBLE) != 0; 
}

inline bool xpl::postfix_writer::is_string(cdk::expression_node * const node) {
    return (node->type()->name() & basic_type::TYPE_STRING) != 0; 
}

inline bool xpl::postfix_writer::is_pointer(cdk::expression_node * const node) {
    return (node->type()->name() & basic_type::TYPE_POINTER) != 0; 
}

inline bool xpl::postfix_writer::same_type(cdk::expression_node * const node, unsigned long int type) {
    return (node->type()->name() & type) != 0; 
}


//---------------------------------------------------------------------------

void xpl::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
      
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
    
    if (current_function() != NULL) 
        _pf.INT(node->value()); 
    
    else                            
    {
        _pf.DATA();
        _pf.ALIGN();
        _pf.LABEL(_current_id_init);
        _pf.CONST(node->value()); // push an integer
    }
  
}

void xpl::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
    int label1;
    
    if (current_function() != NULL) {                
        _pf.DATA(); 
        _pf.ALIGN();
        _pf.LABEL(mklbl(label1 = ++_lbl));
        _pf.DOUBLE(node->value());
        _pf.TEXT();
        _pf.ALIGN();
        _pf.ADDR(mklbl(label1));
        _pf.DLOAD();
    }
    
    else                           
    {
        _pf.DATA();
        _pf.ALIGN();
        _pf.LABEL(_current_id_init);
        _pf.DOUBLE(node->value());
    }
}

void xpl::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) { 
    int lbl1;

    /* generate the string */
    _pf.RODATA(); // strings are DATA readonly
    _pf.ALIGN(); // make sure we are aligned
    _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
    _pf.STR(node->value()); // output string characters

    /* leave the address on the stack */
    if (current_function() != NULL) {                            
        _pf.TEXT(); // return to the TEXT segment
        _pf.ADDR(mklbl(lbl1)); // the string to be printed
    }
    else {                                                        
        _pf.DATA(); 
        _pf.ALIGN();
        _pf.LABEL(_current_id_init); 
        _pf.ID(mklbl(lbl1));
    }
}


void xpl::postfix_writer::do_null_node(xpl::null_node * const node, int lvl) { 
    if (current_function() != NULL)                   
        _pf.INT(0);
    else                                              
    {
        _pf.DATA();
        _pf.ALIGN();
        _pf.LABEL(_current_id_init);
        _pf.CONST(0);                                               
    }
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS
  node->argument()->accept(this, lvl); // determine the value
  _pf.NEG(); // 2-complement
}

void xpl::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    node->argument()->accept(this, lvl); // determine the value
    _pf.NOT();
}

void xpl::postfix_writer::do_address_node(xpl::address_node * const node, int lvl) {
    node->argument()->accept(this, lvl);
}

//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void xpl::postfix_writer::processComparingBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    int ltReal = 0;  //flag to see if its between reals
    
    node->left()->accept(this, lvl);
    
    if(is_int(node->left()) && is_real(node->right())) {
        _pf.I2D();
        ltReal = 1;
    }
    
    node->right()->accept(this, lvl);
    
    if(is_int(node->right()) && is_real(node->left())) {
        _pf.I2D();
        ltReal = 1;
    }
    
    if(ltReal == 1 || is_real(node)) {
        _pf.DCMP();
        _pf.INT(0);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void xpl::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) { 
    ASSERT_SAFE_EXPRESSIONS
  
    node->left()->accept(this, lvl); 
    
    if(is_int(node->left()) && is_real(node))
        _pf.I2D(); //Integer to real
        
    else if(is_int(node->left()) && is_pointer(node))
    {
        _pf.INT(4); 
        _pf.MUL(); 
        _pf.ADD();
    }
     
    node->right()->accept(this, lvl); 
    
    if(is_int(node->right()) && is_real(node))
        _pf.I2D(); //Integer to real
        
    else if(is_int(node->right()) && is_pointer(node))
    {
        _pf.INT(4); 
        _pf.MUL(); 
        _pf.ADD();
    }
    
    if(is_int(node) || is_pointer(node))
        _pf.ADD(); 
    else
        _pf.DADD(); 
  
}


void xpl::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
  
    node->left()->accept(this, lvl); 
    
    if(is_int(node->left()) && is_real(node))
        _pf.I2D(); //Integer to real
        
    else if(is_int(node->left()) && is_pointer(node)) {
        _pf.INT(4); 
        _pf.MUL(); 
        _pf.ADD();
    }
     
    node->right()->accept(this, lvl); 
    
    if(is_int(node->right()) && is_real(node))
        _pf.I2D(); //Integer to real
        
    else if(is_int(node->right()) && is_pointer(node)) {
        _pf.INT(4);
        _pf.MUL(); 
        _pf.ADD();
    } 
  
    if(is_int(node) || is_pointer(node)) {
        _pf.SUB(); 
        
        if(is_pointer(node->left()) && is_pointer(node->right())) { 
            _pf.INT(4);    
            _pf.DIV();     
        }
    }
    else
    _pf.DSUB(); 
}

void xpl::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    node->left()->accept(this, lvl);
    
    if(is_int(node->left()) && is_real(node))
        _pf.I2D(); //Integer to real
        
    node->right()->accept(this, lvl);
    
    if(is_int(node->right()) && is_real(node))
        _pf.I2D(); //Integer to real
        
        
    if(is_int(node))
        _pf.MUL();
    else
        _pf.DMUL(); 
}
void xpl::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS
    node->left()->accept(this, lvl);
    
    if(is_int(node->left()) && is_real(node))
        _pf.I2D(); //Integer to real
        
    node->right()->accept(this, lvl);
    
    if(is_int(node->right()) && is_real(node))
        _pf.I2D(); //Integer to real
        
        
    if(is_int(node))
        _pf.DIV();
    else
        _pf.DDIV(); 
}
void xpl::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
    _pf.MOD();
}
void xpl::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
    processComparingBinaryExpression(node,lvl);
    _pf.LT();
}
void xpl::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
    processComparingBinaryExpression(node,lvl);
    _pf.LE();
}
void xpl::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
    processComparingBinaryExpression(node,lvl);
    _pf.GE();
}
void xpl::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
    processComparingBinaryExpression(node,lvl);
    _pf.GT();
}
void xpl::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
    processComparingBinaryExpression(node,lvl);
    _pf.NE();
}
void xpl::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
    processComparingBinaryExpression(node,lvl);
    _pf.EQ();
}

void xpl::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {
    int label;
    ASSERT_SAFE_EXPRESSIONS
    
    node->left()->accept(this, lvl);
    _pf.DUP();
    _pf.JZ(mklbl(label = ++_lbl));
    
    node->right()->accept(this, lvl);
    _pf.AND();
    
    _pf.LABEL(mklbl(label));
}

void xpl::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
    int label;
    ASSERT_SAFE_EXPRESSIONS
    
    node->left()->accept(this, lvl);
    _pf.DUP();
    _pf.JNZ(mklbl(label = ++_lbl));
    
    node->right()->accept(this, lvl);
    _pf.OR();
    
    _pf.LABEL(mklbl(label));
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    
    std::shared_ptr<xpl::symbol> symbol = _symtab.find(node->name());
    
    if(symbol->offset() < 0 || symbol->offset() >= 8) {
        _pf.LOCAL(symbol->offset());
    }
    else {
        _pf.ADDR(node->name());
    }
    
}

void xpl::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS
  node->lvalue()->accept(this, lvl);
  
  if(is_real(node))
      _pf.DLOAD();
  else 
      _pf.LOAD();
}

void xpl::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) { 
    ASSERT_SAFE_EXPRESSIONS
    node->rvalue()->accept(this, lvl); 
    if(!is_real(node->rvalue()) && !is_real(node->lvalue())) 
        _pf.DUP();
    else if(!is_real(node->rvalue()) && is_real(node->lvalue())) {
        _pf.I2D();
        _pf.DDUP();
    }
    else
        _pf.DDUP();
        
    node->lvalue()->accept(this, lvl); 

    if(!is_real(node->lvalue())) 
        _pf.STORE(); 
    else
        _pf.DSTORE();
    
}

void xpl::postfix_writer::do_var_declaration_node(xpl::var_declaration_node * const node, int lvl) { 
    ASSERT_SAFE_EXPRESSIONS
    
    std::string identifier = *(node->identifier());
    std::shared_ptr<xpl::symbol> symbol = _symtab.find(identifier);
      
     
    if(current_function() != NULL) {
        if(node->isPublic() || node->hasUse()) 
            throw std::string("Cannot use the qualifiers 'public' or 'use' inside the body of a function or when declaring a function's argument");
             
        if(_current_offset >= 8) { 
            symbol->offset(_current_offset);
            _current_offset += node->type()->size();
        }
        else if(_current_offset <= 0) { 
            _current_offset -= node->type()->size();  
            symbol->offset(_current_offset);
        }
        else
            throw std::string("This offset cannot exist!!");   
    
    
    }
    else {   
        
        if(node->hasUse()) {
            _pf.EXTERN(identifier);
        }
        else {
            if(identifier == std::string("_main")) 
                identifier = std::string("xpl");
                
            if (!(node->isPublic()))
                _pf.GLOBAL(identifier, _pf.OBJ());
                    
            _pf.BSS(); 
            _pf.ALIGN();        
                    
            _pf.LABEL(identifier);     
                    
            _pf.BYTE(node->type()->size()); 
            _pf.TEXT(); // return to the TEXT segment
            _pf.ALIGN();
        }          
             
         
    }
    
}

void xpl::postfix_writer::do_var_inicialization_node(xpl::var_inicialization_node * const node, int lvl) { 
    ASSERT_SAFE_EXPRESSIONS
    
    std::string &identifier = *(node->identifier());
    std::shared_ptr<xpl::symbol> symbol = _symtab.find(identifier);
      
     
    if(current_function() != NULL) { 
        if(node->isPublic()) 
            throw std::string("Cannot use the qualifier 'public' inside the body of a function");
             
        if(_current_offset >= 8) {
            throw std::string("Cannot initialize a function's argument");           
        }
        else if(_current_offset <= 0) {
            _current_offset -= node->type()->size();   
            symbol->offset(_current_offset);  
            
            node->expression()->accept(this, lvl); 
                     
            if(is_int(node->expression()) && (node->type()->name() & basic_type::TYPE_DOUBLE) != 0)
                _pf.I2D();
                
            _pf.LOCAL(symbol->offset());
                
            if((node->type()->name() & basic_type::TYPE_INT) != 0 || (node->type()->name() & basic_type::TYPE_STRING) != 0 || (node->type()->name() & basic_type::TYPE_POINTER) != 0)
                _pf.STORE();                    
            else
                _pf.DSTORE();
        }
        else
            throw std::string("This offset cannot exist!!");   
    
    
    }
    else {  
        
        if(node->expression()->label() != "integer_node" && node->expression()->label() != "double_node" && node->expression()->label() != "string_node" && node->expression()->label() != "null_node")
                throw std::string("Can only initialize variables at global scope with literals");
             
        else {
            if(identifier == std::string("_main"))
                identifier = std::string("xpl");
                
            if(node->expression()->label() == "string_node")
                _pf.RODATA();
            
            else
                _pf.DATA();
            
            _pf.ALIGN();
            
            if (node->isPublic())
                _pf.GLOBAL(identifier, _pf.OBJ());
            
            
            _current_id_init = identifier;
            node->expression()->accept(this, lvl);
           
            
            _pf.TEXT(); // return to the TEXT segment
            _pf.ALIGN();
        }          
             
         
    }
}

void xpl::postfix_writer::do_mem_alloc_node(xpl::mem_alloc_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    
    _pf.INT(4);
    _pf.DUP();
    node->argument()->accept(this, lvl);
    _pf.MUL();
    _pf.ALLOC();
    _pf.SP();
}

void xpl::postfix_writer::do_index_node(xpl::index_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    node->pointer()->accept(this, lvl);
    _pf.LOAD();
    node->index()->accept(this, lvl);
    _pf.INT(4);
    _pf.MUL();
    _pf.ADD();
}

void xpl::postfix_writer::do_identity_node(xpl::identity_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    node->argument()->accept(this, lvl);
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_func_definition_node(xpl::func_definition_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    int label = ++_lbl;
    std::string identifier;
    
    _current_function_end_label = label;
 
    _pf.TEXT();
    _pf.ALIGN();
    
    if(node->identifier()->compare(std::string("xpl")) == 0)
        identifier = std::string("_main");
    else if(node->identifier()->compare(std::string("_main")) == 0)
        identifier = std::string("xpl");
    else   
        identifier = *(node->identifier());
    
    _pf.GLOBAL(identifier, _pf.FUNC()); 
    
    _pf.LABEL(identifier);
    
    locals_visitor *lv = new locals_visitor(_compiler);
    
    node->accept(lv, lvl);
    
    int bytes = lv->get_num_bytes();
    
    delete lv;
    
    _pf.ENTER(bytes);
    
    current_function(_symtab.find_local(identifier));
    
    _symtab.push();
     
    if(node->args() != NULL) {
        _current_offset = 8;                                               
        node->args()->accept(this, lvl);
    }
    
    _current_offset = 0;                                       
    
   
    _current_offset -= current_function()->type()->size(); 
    
                
    
    
    std::shared_ptr<xpl::symbol> symbol = _symtab.find(identifier);
    if(node->literal() != NULL) {
        node->literal()->accept(this, lvl);
        if(is_int(node->literal()) || is_string(node->literal()) || is_pointer(node->literal())) {
        _pf.LOCAL(-4);
        _pf.STORE();
        }
        else if(is_real(node->literal())) {
        _pf.LOCAL(-8);
        _pf.DSTORE();
        }
    }
    else { 
        if(current_function()->type()->name() == basic_type::TYPE_INT || current_function()->type()->name() == basic_type::TYPE_POINTER || current_function()->type()->name() == basic_type::TYPE_STRING) { 
        _pf.INT(0);        
        _pf.LOCAL(-4);
        _pf.STORE();
        current_function()->offset(-4);
        }
        if(current_function()->type()->name() == basic_type::TYPE_DOUBLE) { 
        _pf.INT(0); 
        _pf.I2D();
        _pf.LOCAL(-8);
        _pf.DSTORE();
        current_function()->offset(-8);
        }
    }   
    
    node->statements()->accept(this, lvl);
    
    
     
    _pf.LABEL(mklbl(_current_function_end_label));
   
   
    if(current_function()->type()->name() == basic_type::TYPE_INT || current_function()->type()->name() == basic_type::TYPE_STRING || current_function()->type()->name() == basic_type::TYPE_POINTER) {
        _pf.LOCAL(-4);
        _pf.LOAD();
        _pf.POP();              
    }
    else if(current_function()->type()->name() == basic_type::TYPE_DOUBLE) {
        _pf.LOCAL(-8);
        _pf.DLOAD();
        _pf.DPOP();
    }
     
    _pf.LEAVE();
    _pf.RET();
    
    
    _symtab.pop();
    current_function(NULL);
    _pf.EXTERN("argc");
    _pf.EXTERN("argv");
    _pf.EXTERN("envp");
    _pf.EXTERN("readi");
    _pf.EXTERN("readd");
    _pf.EXTERN("reads");
    _pf.EXTERN("printi");
    _pf.EXTERN("printd");
    _pf.EXTERN("prints");
    _pf.EXTERN("println");
    
       
  
}

void xpl::postfix_writer::do_func_declaration_node(xpl::func_declaration_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    
    std::string identifier;
   
    if(node->identifier()->compare(std::string("xpl")) == 0)
        identifier = std::string("_main");
    else if(node->identifier()->compare(std::string("_main")) == 0)
        identifier = std::string("xpl");
    else   
        identifier = *(node->identifier());
        
        
    if(node->hasUse()) {
        _pf.EXTERN(identifier);
    }   
    
  
    
}

void xpl::postfix_writer::do_func_invocation_node(xpl::func_invocation_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    std::shared_ptr<xpl::symbol> s;
    std::string identifier;
    
    if(node->identifier()->compare(std::string("xpl"))==0)
        identifier = std::string("_main");
    else if(node->identifier()->compare(std::string("_main"))==0)
        identifier = std::string("xpl");
    else   
        identifier = *(node->identifier());
    
    s = _symtab.find(identifier);    
    int trash = 0;
    
    if(node->args() != NULL)
        for(int i = (node->args()->size()) - 1; i >= 0; i--) {
            cdk::expression_node * arg = (cdk::expression_node*) node->args()->node(i);
            arg->accept(this, lvl);
            trash += arg->type()->size();
        }
    
    _pf.CALL(identifier);
    if(trash > 0)               
        _pf.TRASH(trash);
        
        
    if( (s->type()->name() & basic_type::TYPE_INT) != 0 || (s->type()->name() & basic_type::TYPE_STRING) != 0 || (s->type()->name() & basic_type::TYPE_POINTER) != 0 )
        _pf.PUSH();             
    else if((s->type()->name() & basic_type::TYPE_DOUBLE) != 0)
        _pf.DPUSH();
    
    node->type(new basic_type(s->type()->size(), s->type()->name()));
    
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_evaluation_node(xpl::evaluation_node * const node, int lvl) { 
  ASSERT_SAFE_EXPRESSIONS
  node->argument()->accept(this, lvl); // determine the value
 
    if (node->argument()->type()->name() == basic_type::TYPE_INT) {
        _pf.TRASH(4); // delete the evaluated value
        
    } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
        _pf.TRASH(4); // delete the evaluated value's address
    } else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
        _pf.TRASH(8); // delete the printed value
    } else if (node->argument()->type()->name() == basic_type::TYPE_POINTER) {
        _pf.TRASH(4); // delete the printed value
    } else if (node->argument()->type()->name() == basic_type::TYPE_VOID) {
        // nothing
    } else {
        std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
        exit(1);
    }
    
}

void xpl::postfix_writer::do_print_node(xpl::print_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS
  
   
  node->argument()->accept(this, lvl); // determine the value to print
   
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value

  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value
    
  } else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.CALL("printd");
    _pf.TRASH(8); // delete the printed value
    
  } else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
  
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_read_node(xpl::read_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    if (node->type()->name() == basic_type::TYPE_INT) {
        _pf.CALL("readi");
        _pf.PUSH();
        
    } else if (node->type()->name() == basic_type::TYPE_STRING) {
        _pf.CALL("reads");
        _pf.PUSH();
        
    } else if (node->type()->name() == basic_type::TYPE_DOUBLE) {
        _pf.CALL("readd");
        _pf.DPUSH();
        
    }
    node->accept(this, lvl);
    _pf.STORE();
}

void xpl::postfix_writer::do_print_line_node(xpl::print_line_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    node->argument()->accept(this, lvl); // determine the value to print
    if (node->argument()->type()->name() == basic_type::TYPE_INT) {
        _pf.CALL("printi");
        _pf.TRASH(4); // delete the printed value
        
    } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
        _pf.CALL("prints");
        _pf.TRASH(4); // delete the printed value
        
    } else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
        _pf.CALL("printd");
        _pf.TRASH(8); // delete the printed value
        
    } else {
        std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
        exit(1);
    }
    
    _pf.CALL("println"); // print a newline
}

void xpl::postfix_writer::do_block_node(xpl::block_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    
    _symtab.push();
   
    if(node->varSequence() != NULL)
    {
        node->varSequence()->accept(this, lvl);
    }
    
    if(node->instrSequence() != NULL)
    {
        node->instrSequence()->accept(this, lvl);
    }
    
    _symtab.pop();
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_while_node(xpl::while_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS
  int whilecond = ++_lbl, whileend = ++_lbl;
  
  _cycles_stack_next.push_back(whilecond);
  _cycles_stack_stop.push_back(whileend);
  _pf.LABEL(mklbl(whilecond));
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(whileend));
  node->block()->accept(this, lvl);
  _pf.JMP(mklbl(whilecond));
  _pf.LABEL(mklbl(whileend));
  _cycles_stack_next.pop_back();
  _cycles_stack_stop.pop_back();
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_if_node(xpl::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_if_else_node(xpl::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}

void xpl::postfix_writer::do_next_node(xpl::next_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    if(_cycles_stack_next.size() > 0) {
        int lbl1 = _cycles_stack_next.back();
        _pf.JMP(mklbl(lbl1));
    }
    else
         throw std::string("next outside of a loop!!");
}

void xpl::postfix_writer::do_stop_node(xpl::stop_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    if(_cycles_stack_stop.size() > 0) {
        int lbl1 = _cycles_stack_stop.back();
        _pf.JMP(mklbl(lbl1));
    }
    else
        throw std::string("stop outside of a loop!!");
}

void xpl::postfix_writer::do_return_node(xpl::return_node * const node, int lvl) {
    _pf.JMP(mklbl(_current_function_end_label));
}

void xpl::postfix_writer::do_sweep_up_node(xpl::sweep_up_node * const node, int lvl){  
    ASSERT_SAFE_EXPRESSIONS
    
    
    
    cdk::le_node *le;
    cdk::add_node *add;
    cdk::assignment_node *ass;
    cdk::rvalue_node *rvalue;
    int sweepcond = ++_lbl, sweepinc = ++_lbl, sweepend = ++_lbl;
    
    ass = new cdk::assignment_node(node->lineno(), node->lvalue(), node->expression1());
    
    ass->accept(this, lvl);
    
    _cycles_stack_next.push_back(sweepinc); 
    _cycles_stack_stop.push_back(sweepend);
    _pf.LABEL(mklbl(sweepcond)); 
    
    rvalue = new cdk::rvalue_node(node->lineno(),node->lvalue());
    
    le = new cdk::le_node(node->lineno(), rvalue, node->expression2());
    
    le->accept(this,lvl);
    
    _pf.JZ(mklbl(sweepend));
    
    node->block()->accept(this, lvl);
    
    _pf.LABEL(mklbl(sweepinc));
    
    add = new cdk::add_node(node->lineno(), rvalue, node->expression3());
    
    add->accept(this,lvl);
    
    ass = new cdk::assignment_node(node->lineno(), node->lvalue(), add);
    
    ass->accept(this,lvl);
    
    _pf.JMP(mklbl(sweepcond));
    
    _pf.LABEL(mklbl(sweepend));
    
    _cycles_stack_next.pop_back();
    _cycles_stack_stop.pop_back();
    
}

void xpl::postfix_writer::do_sweep_down_node(xpl::sweep_down_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS
    
    
    cdk::ge_node *ge;
    cdk::sub_node *sub;
    cdk::assignment_node *ass;
    cdk::rvalue_node *rvalue;
    int sweepcond = ++_lbl, sweepinc = ++_lbl, sweepend = ++_lbl;
    
    ass = new cdk::assignment_node(node->lineno(), node->lvalue(), node->expression1());
    
    ass->accept(this, lvl);
    
    _cycles_stack_next.push_back(sweepinc); 
    _cycles_stack_stop.push_back(sweepend);
    _pf.LABEL(mklbl(sweepcond));
    
    rvalue = new cdk::rvalue_node(node->lineno(),node->lvalue());
    
    ge = new cdk::ge_node(node->lineno(), rvalue, node->expression2());
    
    ge->accept(this,lvl);
    
    _pf.JZ(mklbl(sweepend));
    
    node->block()->accept(this, lvl);
    
    _pf.LABEL(mklbl(sweepinc));
    
    sub = new cdk::sub_node(node->lineno(), rvalue, node->expression3());
    
    sub->accept(this,lvl);
    
    ass = new cdk::assignment_node(node->lineno(), node->lvalue(), sub);
    
    ass->accept(this,lvl);
    
    _pf.JMP(mklbl(sweepcond));
    
    _pf.LABEL(mklbl(sweepend));
    
    _cycles_stack_next.pop_back();
    _cycles_stack_stop.pop_back();
}
