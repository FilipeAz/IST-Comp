#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

inline std::string translateType(basic_type *type) {
    switch(type->name()) {
        case basic_type::TYPE_INT:      
            return "int";
            break;
        case basic_type::TYPE_DOUBLE:
            return "real";
            break;
        case basic_type::TYPE_STRING:
            return "string";
            break;
        case basic_type::TYPE_VOID:
            return "procedure";
            break;
        case basic_type::TYPE_POINTER:
            return '[' + translateType(type->subtype()) + ']';
            break;
        default:
            return "unspec";
    }
}


//---------------------------------------------------------------------------


void xpl::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  process_literal(node, lvl);
}

void xpl::xml_writer::do_double_node(cdk::double_node * const node, int lvl) {
    process_literal(node, lvl);
}

void xpl::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  process_literal(node, lvl);
}

void xpl::xml_writer::do_null_node(xpl::null_node * const node, int lvl) {
    os() << std::string(lvl, ' ') << "<null_node/>" << std::endl;
}

//---------------------------------------------------------------------------

inline void xpl::xml_writer::do_unary_expression(cdk::unary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}

void xpl::xml_writer::do_not_node(cdk::not_node * const node, int lvl) {
    do_unary_expression(node, lvl);
}

void xpl::xml_writer::do_address_node(xpl::address_node * const node, int lvl) {
    do_unary_expression(node, lvl);
}

//---------------------------------------------------------------------------

inline void xpl::xml_writer::do_binary_expression(cdk::binary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

void xpl::xml_writer::do_and_node(cdk::and_node * const node, int lvl) {
    do_binary_expression(node, lvl);
}

void xpl::xml_writer::do_or_node(cdk::or_node * const node, int lvl) {
    do_binary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << "<" << node->label() << ">" << node->name() << "</" << node->label() << ">" << std::endl;
}

void xpl::xml_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);

  node->lvalue()->accept(this, lvl);
  reset_new_symbol();

  node->rvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_var_declaration_node(xpl::var_declaration_node * const node, int lvl) {
    //ASSERT_SAFE_EXPRESSIONS;
    
    if(node->isPublic())
        os() << std::string(lvl, ' ') << "<var_declaration_node identifier='" << *(node->identifier()) << "' qualifier='public'>" << std::endl;
    else if(node->hasUse())
        os() << std::string(lvl, ' ') << "<var_declaration_node identifier='" << *(node->identifier()) << "' qualifier='use'>" << std::endl;
    else
        os() << std::string(lvl, ' ') << "<var_declaration_node identifier='" << *(node->identifier()) << "'>" << std::endl;
    
    openTag("type", lvl + 2);
    os() << std::string(lvl + 4, ' ') << translateType(node->type()) << std::endl;
    closeTag("type", lvl + 2);
    
    closeTag(node, lvl);
}

void xpl::xml_writer::do_var_inicialization_node(xpl::var_inicialization_node * const node, int lvl) {
    //ASSERT_SAFE_EXPRESSIONS;
    
    if(node->isPublic())
        os() << std::string(lvl, ' ') << "<var_inicialization_node identifier='" << *(node->identifier()) << "' qualifier='public'>" << std::endl;
    else
        os() << std::string(lvl, ' ') << "<var_inicialization_node identifier='" << *(node->identifier()) << "'>" << std::endl;
    
    openTag("type", lvl + 2);
    os() << std::string(lvl + 4, ' ') << translateType(node->type()) << std::endl;
    closeTag("type", lvl + 2);
    
    openTag("expression", lvl + 2);
    node->expression()->accept(this, lvl + 4);
    closeTag("expression", lvl + 2);
    
    closeTag(node, lvl);
}

void xpl::xml_writer::do_mem_alloc_node(xpl::mem_alloc_node * const node, int lvl) {
    do_unary_expression(node, lvl);
}

void xpl::xml_writer::do_index_node(xpl::index_node * const node, int lvl) {
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    
    openTag("pointer", lvl + 2);
    node->pointer()->accept(this, lvl + 4);
    closeTag("pointer", lvl + 2);
    
    openTag("index", lvl + 2);
    node->index()->accept(this, lvl + 4);
    closeTag("index", lvl + 2);
    
    closeTag(node, lvl);
}

void xpl::xml_writer::do_identity_node(xpl::identity_node * const node, int lvl) {
    do_unary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_func_definition_node(xpl::func_definition_node * const node, int lvl) {
    //ASSERT_SAFE_EXPRESSIONS;
    
    if(node->isPublic())
        os() << std::string(lvl, ' ') << "<func_definition_node identifier='" << *(node->identifier()) << "' qualifier='public'>" << std::endl;
    else
        os() << std::string(lvl, ' ') << "<func_definition_node identifier='" << *(node->identifier()) << "'>" << std::endl;
    
    if(node->literal() != NULL) {
        os() << std::string(lvl + 2, ' ') << "<return type='" << translateType(node->return_type()) << "'>" << std::endl;
        
        openTag("default", lvl + 4);
        node->literal()->accept(this, lvl + 6);
        closeTag("default", lvl + 4);
        
        os() << std::string(lvl + 2, ' ') << "</return>" << std::endl;
    }
    else {
        os() << std::string(lvl + 2, ' ') << "<return type='" << translateType(node->return_type()) << "'/>" << std::endl;
    }
    
    _symtab.push();
    
    openTag("arguments", lvl + 2);
    if(node->args() != NULL)
        node->args()->accept(this, lvl + 4);
    closeTag("arguments", lvl + 2);
    
    openTag("statements", lvl + 2);
    if(node->statements() != NULL)
        node->statements()->accept(this, lvl + 4);
    closeTag("statements", lvl + 2);
    
    _symtab.pop();
    
    closeTag(node, lvl);
}

void xpl::xml_writer::do_func_declaration_node(xpl::func_declaration_node * const node, int lvl) {
    //ASSERT_SAFE_EXPRESSIONS;
    
    if(node->isPublic())
        os() << std::string(lvl, ' ') << "<func_declaration_node identifier='" << *(node->identifier()) << "' qualifier='public'>" << std::endl;
    else if(node->hasUse())
        os() << std::string(lvl, ' ') << "<func_declaration_node identifier='" << *(node->identifier()) << "' qualifier='use'>" << std::endl;
    else
        os() << std::string(lvl, ' ') << "<func_declaration_node identifier='" << *(node->identifier()) << "'>" << std::endl;
    

    os() << std::string(lvl + 2, ' ') << "<return type='" << translateType(node->return_type()) << "'/>" << std::endl;
    
    openTag("arguments", lvl + 2);
    if(node->args() != NULL)
        node->args()->accept(this, lvl + 4);
    closeTag("arguments", lvl + 2);
    
    closeTag(node, lvl);
}

void xpl::xml_writer::do_func_invocation_node(xpl::func_invocation_node * const node, int lvl) {
    //ASSERT_SAFE_EXPRESSIONS;
    
    os() << std::string(lvl, ' ') << "<func_invocation_node identifier='" << *(node->identifier()) << "'>" << std::endl;
    
    openTag("arguments", lvl + 2);
    if(node->args() != NULL)
        node->args()->accept(this, lvl + 4);
    closeTag("arguments", lvl + 2);
    
    closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_print_node(xpl::print_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_read_node(xpl::read_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << "<read_node/>" << std::endl;
}

void xpl::xml_writer::do_print_line_node(xpl::print_line_node * const node, int lvl) {
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    node->argument()->accept(this, lvl + 2);
    closeTag(node, lvl);
}

void xpl::xml_writer::do_block_node(xpl::block_node * const node, int lvl) {
    //ASSERT_SAFE_EXPRESSIONS;
  
    _symtab.push();
    
    openTag(node, lvl);
    
    openTag("varSequence", lvl + 2);
    if(node->varSequence() != NULL)
        node->varSequence()->accept(this, lvl + 4);
    closeTag("varSequence", lvl + 2);
    
    openTag("instrSequence", lvl + 2);
    if(node->instrSequence() != NULL)
        node->instrSequence()->accept(this, lvl + 4);
    closeTag("instrSequence", lvl + 2);
    
    closeTag(node, lvl);
    
    _symtab.pop();
    
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_while_node(xpl::while_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("block", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_if_node(xpl::if_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_if_else_node(xpl::if_else_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
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

void xpl::xml_writer::do_next_node(xpl::next_node * const node, int lvl) {
    //ASSERT_SAFE_EXPRESSIONS;
    os() << std::string(lvl, ' ') << "<next_node/>" << std::endl;
}

void xpl::xml_writer::do_stop_node(xpl::stop_node * const node, int lvl) {
    //ASSERT_SAFE_EXPRESSIONS;
    os() << std::string(lvl, ' ') << "<stop_node/>" << std::endl;
}

void xpl::xml_writer::do_return_node(xpl::return_node * const node, int lvl) {
    //ASSERT_SAFE_EXPRESSIONS;
    os() << std::string(lvl, ' ') << "<return_node/>" << std::endl;
}

void xpl::xml_writer::do_sweep_up_node(xpl::sweep_up_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    
    openTag(node, lvl);
    
    openTag("lvalue", lvl + 2);
    node->lvalue()->accept(this, lvl + 4);
    closeTag("lvalue", lvl + 2);
    
    openTag("first_expression", lvl + 2);
    node->expression1()->accept(this, lvl + 4);
    closeTag("first_expression", lvl + 2);
    
    openTag("second_expression", lvl + 2);
    node->expression2()->accept(this, lvl + 4);
    closeTag("second_expression", lvl + 2);
    
    openTag("increment", lvl + 2);
    node->expression3()->accept(this, lvl + 4);
    closeTag("increment", lvl + 2);
    
    openTag("block", lvl + 2);
    node->block()->accept(this, lvl + 4);
    closeTag("block", lvl + 2);
    
    closeTag(node, lvl);
}

void xpl::xml_writer::do_sweep_down_node(xpl::sweep_down_node * const node, int lvl)  {
    //ASSERT_SAFE_EXPRESSIONS;
    
    openTag(node, lvl);
    
    openTag("lvalue", lvl + 2);
    node->lvalue()->accept(this, lvl + 4);
    closeTag("lvalue", lvl + 2);
    
    openTag("first_expression", lvl + 2);
    node->expression1()->accept(this, lvl + 4);
    closeTag("first_expression", lvl + 2);
    
    openTag("second_expression", lvl + 2);
    node->expression2()->accept(this, lvl + 4);
    closeTag("second_expression", lvl + 2);
    
    openTag("decrement", lvl + 2);
    node->expression3()->accept(this, lvl + 4);
    closeTag("decrement", lvl + 2);
    
    openTag("block", lvl + 2);
    node->block()->accept(this, lvl + 4);
    closeTag("block", lvl + 2);
    
    closeTag(node, lvl);
}

void xpl::xml_writer::do_apply_function_node(xpl::apply_function_node * const node, int lvl) {
    
}


