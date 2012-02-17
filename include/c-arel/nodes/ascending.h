/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_ordering_h
#define include_c_arel_ordering_h

namespace c_arel {
  namespace nodes {
    class Ascending : public Ordering {
    public:
      explicit Ascending(variant expr);
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
