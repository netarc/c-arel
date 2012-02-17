/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"


namespace c_arel {
  namespace nodes {
    Function::Function(variant expr) : expressions(expr), distinct(false) {
    }

    Function::Function(variant expr, variant alias) : expressions(expr), distinct(false)  {
      if (alias.isString())
        this->alias = nodes::SqlLiteral(alias.toString());
      else
        this->alias = alias;
    }
    
    Function & Function::as(const char *alias) {
      this->alias = nodes::SqlLiteral(alias);
      return *this;
    }
    
    const char * Function::classname(void) {
      return "Arel::Nodes::Function";
    }
    
    #define FUNCTION_NODE_BODY(name) \
      name::name(variant expr) : Function(expr) {} \
      name::name(variant expr, variant alias) : Function(expr, alias) {} \
      name & name::as(const char *alias) { \
        Function::as(alias); \
        return *this; \
      } \
      const char * name::classname(void) { \
        std::string nspace = "Arel::Nodes::"; \
        return (nspace + #name).c_str(); \
      }
    
    FUNCTION_NODE_BODY(Sum);
    FUNCTION_NODE_BODY(Exists);
    FUNCTION_NODE_BODY(Max);
    FUNCTION_NODE_BODY(Min);
    FUNCTION_NODE_BODY(Avg);
  }
}