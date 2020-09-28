#ifndef __XPL_SEMANTICS_SYMBOL_H__
#define __XPL_SEMANTICS_SYMBOL_H__

#include <string>
#include <vector>
#include <cdk/basic_type.h>

namespace xpl {

    class symbol {
      basic_type *_type;
      std::string _name;
      
      //Functions
      std::vector<basic_type*> _function_arguments;
      
      bool _function_defined;       //If true, the function was already defined 
      bool _is_function = false;            //If false, this symbol is a variable
       
      //Local Variables:
      int _offset = 0;      
             
      long _value; // hack!

    public:
        //Variable
      inline symbol(basic_type *type, const std::string &name, long value) :
          _type(type), _name(name), _value(value) {
      }
        //Function
      inline symbol(basic_type *type, const std::string &name, std::vector<basic_type*> function_arguments, bool function_defined, long value) :
          _type(type), _name(name), _function_arguments(function_arguments), _function_defined(function_defined), _is_function(true), _value(value) {
      }
      
      virtual ~symbol() {
        delete _type;
      }

      inline basic_type *type() const {
        return _type;
      }
      inline const std::string &name() const {
        return _name;
      }
      inline long value() const {
        return _value;
      }
      inline long value(long v) {
        return _value = v;
      }
      inline std::vector<basic_type*> function_arguments() {
        return _function_arguments;
      }
      inline bool function_defined() {
        return _function_defined;
      }
      inline void function_defined(bool defined) {
         _function_defined = defined;
      }
      inline bool is_function() {
        return _is_function;
      }
      inline void is_function(bool value) {
         _is_function = value;
      }
      inline int offset() {
        return _offset;
      }
      inline void offset(int of) {
        _offset = of;
      }
    };

} // xpl

#endif
