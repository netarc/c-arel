/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_alias_predication_h
#define include_c_arel_alias_predication_h

namespace c_arel {
  class AliasPredication : virtual  public Derived {
  public:
    nodes::As as(const char *other);
  };
}

#endif