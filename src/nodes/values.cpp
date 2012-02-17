/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  namespace nodes {
    Values::Values(std::vector<variant> exprs) : Binary(exprs, std::vector<variant>()) {
    }

    Values::Values(std::vector<variant> exprs, std::vector<variant> columns) : Binary(exprs, columns) {
    }
    
    std::vector<variant> & Values::expressions(void) {
      std::vector<variant> *a = static_cast<std::vector<variant> *>(*left);
      return *a;
    }
    
    std::vector<variant> & Values::columns(void) {
      std::vector<variant> *a = static_cast<std::vector<variant> *>(*right);
      return *a;
    }
    
    const char * Values::classname(void) {
      return "Arel::Nodes::Values";
    }
  }
}