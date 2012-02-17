/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  namespace nodes {
    Unary::Unary(variant expr) : expr(expr) {
      
    }
    
    const char * Unary::classname(void) {
      return "Arel::Nodes::Unary";
    }
    
#define UNARY_TABLE_CLASS(name) \
name::name(variant expr) : Unary(expr) {} \
const char * name::classname(void) { \
std::string nspace = "Arel::Nodes::"; \
return (nspace + #name).c_str(); \
}
    
    UNARY_TABLE_CLASS(Bin);
    UNARY_TABLE_CLASS(Group);
    UNARY_TABLE_CLASS(Grouping);
    UNARY_TABLE_CLASS(Having);
    UNARY_TABLE_CLASS(Limit);
    UNARY_TABLE_CLASS(Not);
    UNARY_TABLE_CLASS(Offset);
    UNARY_TABLE_CLASS(On);
    UNARY_TABLE_CLASS(Ordering);
    UNARY_TABLE_CLASS(Top);
    UNARY_TABLE_CLASS(Lock);
    UNARY_TABLE_CLASS(DistinctOn);
  }
}