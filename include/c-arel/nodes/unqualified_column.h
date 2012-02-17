/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_unqualified_column_h
#define include_c_arel_unqualified_column_h

namespace c_arel {
  namespace nodes {
    class UnqualifiedColumn : public Unary {
    public:
      explicit UnqualifiedColumn(variant expr);
      
      variant & name(void);

      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
