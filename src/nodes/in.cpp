/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  namespace nodes {
    In::In(variant operand1, variant operand2) : Equality(operand1, operand2) {
    }
    
    const char * In::classname(void) {
      return "Arel::Nodes::In";
    }
  }
}
