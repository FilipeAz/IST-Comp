#include <string>
#include <sstream>
#include "targets/locals_visitor.h"
#include "ast/all.h" 

//Funcoes auxiliares para descobrir o tipo
inline bool xpl::locals_visitor::is_int(xpl::func_definition_node * const node) {
    return (node->return_type()->name() & basic_type::TYPE_INT) != 0; 
}

inline bool xpl::locals_visitor::is_real(xpl::func_definition_node * const node) {
    return (node->return_type()->name() & basic_type::TYPE_DOUBLE) != 0; 
}

inline bool xpl::locals_visitor::is_string(xpl::func_definition_node * const node) {
    return (node->return_type()->name() & basic_type::TYPE_STRING) != 0; 
}

inline bool xpl::locals_visitor::is_pointer(xpl::func_definition_node * const node) {
    return (node->return_type()->name() & basic_type::TYPE_POINTER) != 0; 
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void xpl::locals_visitor::do_func_definition_node(xpl::func_definition_node * const node, int lvl) {
    /*if(is_int(node->return_type()) || is_string(node->return_type()) || is_pointer(node->return_type()))
        _num_bytes += 4;
    else if(is_real(node->return_type()))
        _num_bytes += 8;*/
    
    _num_bytes += node->return_type()->size(); //EM VEZ DISTO
     
    node->statements()->accept(this, lvl);
}

void xpl::locals_visitor::do_block_node(xpl::block_node * const node, int lvl) {
    if(node->varSequence() != NULL)
        node->varSequence()->accept(this, lvl);
    

}

void xpl::locals_visitor::do_var_declaration_node(xpl::var_declaration_node * const node, int lvl) {
    /*if(is_int(node->type()) || is_string(node->type()) || is_pointer(node->type()))
        _num_bytes += 4;
    else if(is_real(node->type()))
        _num_bytes += 8;*/
    
    _num_bytes += node->type()->size(); //EM VEZ DISTO
}

void xpl::locals_visitor::do_var_inicialization_node(xpl::var_inicialization_node * const node, int lvl) {
    /*if(is_int(node->type()) || is_string(node->type()) || is_pointer(node->type()))
        _num_bytes += 4;
    else if(is_real(node->type()))
        _num_bytes += 8;*/
    
    _num_bytes += node->type()->size(); //EM VEZ DISTO
}


void xpl::locals_visitor::do_sequence_node(cdk::sequence_node * const node, int lvl) {
    for(size_t i = 0; i < node->size(); i++) {
        node->node(i)->accept(this, lvl);
    }
}





