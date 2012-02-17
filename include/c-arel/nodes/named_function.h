/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_named_function_h
#define include_c_arel_named_function_h

namespace c_arel {
  namespace nodes {
    class NamedFunction : public Function {
    public:
      explicit NamedFunction(variant name, variant expr);
      explicit NamedFunction(variant name, variant expr, variant aliaz);
      
      variant name;
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
