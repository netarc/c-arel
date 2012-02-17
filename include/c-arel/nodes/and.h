/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_and_h
#define include_c_arel_and_h

namespace c_arel {
  namespace nodes {
    class And : public Node {
    public:
      explicit And(variant children);
      explicit And(variant children, variant right);
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
      
      std::vector<variant> children;
    };
  }
}

#endif
