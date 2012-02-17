/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"


namespace c_arel {
  namespace nodes {
    TableAlias::TableAlias(variant left, variant right) : Binary(left, right) {
    }
    
    Attribute TableAlias::operator[] (const char *name) {
      return Attribute(self(), name);
    }
    
    variant & TableAlias::name(void) {
      return right;
    }
    
    variant & TableAlias::relation(void) {
      return left;
    }
    
    variant & TableAlias::table_alias(void) {
      return name();
    }
    
    const char * TableAlias::classname(void) {
      return "Arel::Nodes::TableAlias";
    }
  }
}