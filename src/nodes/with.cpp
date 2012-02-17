/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  namespace nodes {
    With::With(variant expr) : Unary(expr) {
    }
    
    std::vector<variant> & With::children(void) {
      std::vector<variant> *a = static_cast<std::vector<variant> *>(*expr);
      return *a;
    }

    const char * With::classname(void) {
      return "Arel::Nodes::With";
    }
    
    WithRecursive::WithRecursive(variant expr) : With(expr) {
    }
    
    const char * WithRecursive::classname(void) {
      return "Arel::Nodes::WithRecursive";
    }
  }
}