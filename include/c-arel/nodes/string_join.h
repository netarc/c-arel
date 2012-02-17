/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_string_join_h
#define include_c_arel_string_join_h

namespace c_arel {
  namespace nodes {
    class StringJoin : public Join {
    public:
      explicit StringJoin(variant left, variant right);
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
