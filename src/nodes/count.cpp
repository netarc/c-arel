/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  namespace nodes {
    Count::Count(std::vector<variant> expr) : Function(expr) {
    }
    
    Count::Count(std::vector<variant> expr, bool distinct) : Function(expr) {
      this->distinct = distinct;
    }
    
    Count::Count(std::vector<variant> expr, bool distinct, const char * alias) : Function(expr, alias) {
      this->distinct = distinct;
    }
    
    Count & Count::as(const char *alias) {
      Function::as(alias);
      return *this;
    }
    
    const char * Count::classname(void) {
      return "Arel::Nodes::Count";
    }
  }
}