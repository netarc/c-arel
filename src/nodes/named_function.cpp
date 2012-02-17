/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"


namespace c_arel {
  namespace nodes{
    NamedFunction::NamedFunction(variant name, variant expr) : Function(expr) {
    }

    NamedFunction::NamedFunction(variant name, variant expr, variant aliaz) : Function(expr, aliaz) {
    }
    
    const char * NamedFunction::classname(void) {
      return "Arel::Nodes::NamedFunction";
    }
  }
}