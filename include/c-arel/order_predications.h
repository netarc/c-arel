/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_order_predications_h
#define include_c_arel_order_predications_h

namespace c_arel {
  class OrderPredications : virtual  public Derived {
  public:
    nodes::Ascending asc(void);
    nodes::Descending desc(void);
  };
}

#endif