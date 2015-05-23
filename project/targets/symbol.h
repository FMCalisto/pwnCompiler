// $Id: symbol.h,v 1.3 2015/05/20 00:39:55 ist169984 Exp $ -*- c++ -*-
#ifndef __PWN_SEMANTICS_SYMBOL_H__
#define __PWN_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>

namespace pwn {

    class symbol {
      basic_type *_type; // removed const to allow symbol copy (type getters are not declared as const)
      std::string _name;
      int _value;

    public:
      inline symbol(basic_type *type, const std::string &name, int value) :
          _type(type), _name(name), _value(value) {
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
      inline int value() const {
        return _value;
      }
      inline int value(int v) {
        return _value = v;
      }
    };

} // pwn

#endif
