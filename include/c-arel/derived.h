/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_base_h
#define include_c_arel_base_h

namespace c_arel {
  class Derived {
  public:
    // inheritance/rtii support
    virtual variant self(void) { return *this; }
    virtual const char *classname(void) { return ""; }
  };
}

#endif