/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  nodes::Ascending OrderPredications::asc(void) {
    return nodes::Ascending(self());
  }
  
  nodes::Descending OrderPredications::desc(void) {
    return nodes::Descending(self());
  }
}