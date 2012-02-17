/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {

  nodes::Multiplication Math::operator *(variant other) {
    return nodes::Multiplication(self(), other);
  }
  
  nodes::Division Math::operator /(variant other) {
    return nodes::Division(self(), other);
  }
  
  nodes::Grouping Math::operator +(variant other) {
    return nodes::Grouping(nodes::Addition(self(), other));
  }
  
  nodes::Grouping Math::operator -(variant other) {
    return nodes::Grouping(nodes::Subtraction(self(), other));
  }
}