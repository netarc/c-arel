/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_with_h
#define include_c_arel_with_h

namespace c_arel {
  namespace nodes {
    class With : public Unary {
    public:
      explicit With(variant expr);
      
      std::vector<variant> & children(void);
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
    
    class WithRecursive : public With {
    public:
      explicit WithRecursive(variant expr);
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
