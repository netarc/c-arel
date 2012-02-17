/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_math_h
#define include_c_arel_math_h

namespace c_arel {
  class Math : virtual  public Derived {
  public:
    nodes::Multiplication operator *(variant other);
    nodes::Division operator /(variant other);
    nodes::Grouping operator +(variant other);
    nodes::Grouping operator -(variant other);
  };
}

#endif