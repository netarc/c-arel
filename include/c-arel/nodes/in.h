/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_in_h
#define include_c_arel_in_h

namespace c_arel {
  namespace nodes {
    class In : public Equality {
    public:
      In(variant operand1, variant operand2);

      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
