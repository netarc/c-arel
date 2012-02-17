/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_expessions_h
#define include_c_arel_expessions_h

namespace c_arel {
  namespace nodes {
    class Count;
    class Sum;
    class Max;
    class Min;
    class Avg;
  }

  class Expressions : virtual  public Derived {
  public:
    nodes::Count count(bool distinct=false);
    nodes::Sum sum(void);
    nodes::Max maximum(void);
    nodes::Min minimum(void);
    nodes::Avg average(void);
  };
}

#endif