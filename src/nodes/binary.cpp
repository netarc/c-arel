/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  namespace nodes {
    Binary::Binary(variant left, variant right) : left(left), right(right) {

    }
    
    const char * Binary::classname(void) {
      return "Arel::Nodes::Binary";
    }
    
    #define BINARY_TABLE_CLASS(name) \
      name::name(variant left, variant right) : Binary(left, right) {} \
      const char * name::classname(void) { \
        std::string nspace = "Arel::Nodes::"; \
        return (nspace + #name).c_str(); \
      }
    
    BINARY_TABLE_CLASS(As);
    BINARY_TABLE_CLASS(Assignment);
    BINARY_TABLE_CLASS(Between);
    BINARY_TABLE_CLASS(DoesNotMatch);
    BINARY_TABLE_CLASS(GreaterThan);
    BINARY_TABLE_CLASS(GreaterThanOrEqual);
    BINARY_TABLE_CLASS(Join);
    BINARY_TABLE_CLASS(LessThan);
    BINARY_TABLE_CLASS(LessThanOrEqual);
    BINARY_TABLE_CLASS(Matches);
    BINARY_TABLE_CLASS(NotEqual);
    BINARY_TABLE_CLASS(NotIn);
    BINARY_TABLE_CLASS(Or);
    BINARY_TABLE_CLASS(Union);
    BINARY_TABLE_CLASS(UnionAll);
    BINARY_TABLE_CLASS(Intersect);
    BINARY_TABLE_CLASS(Except);
  }
}