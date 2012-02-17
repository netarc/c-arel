/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"


namespace c_arel {
  namespace nodes {
    InfixOperation::InfixOperation(std::string op, variant left, variant right) : Binary(left, right), op(op) {
    }
    
    const char * InfixOperation::classname(void) {
      return "Arel::Nodes::InfixOperation";
    }
    
    #define INFIX_TABLE_CLASS(name, op) \
      name::name(variant left, variant right) : InfixOperation(op, left, right) {} \
      const char * name::classname(void) { \
        std::string nspace = "Arel::Nodes::"; \
        return (nspace + #name).c_str(); \
      }
    
    INFIX_TABLE_CLASS(Multiplication, "*");
    INFIX_TABLE_CLASS(Division, "/");
    INFIX_TABLE_CLASS(Addition, "+");
    INFIX_TABLE_CLASS(Subtraction, "-");
  }
}