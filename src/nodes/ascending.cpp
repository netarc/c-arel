/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  namespace nodes {
    Ascending::Ascending(variant expr) : Ordering(expr) {
    }

    const char * Ascending::classname(void) {
      return "Arel::Nodes::Ascending";
    }
  }
}