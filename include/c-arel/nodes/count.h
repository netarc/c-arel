/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_count_h
#define include_c_arel_count_h

namespace c_arel {
  namespace nodes {
    class Count : public Function {
    public:
      explicit Count(std::vector<variant> expr);
      explicit Count(std::vector<variant> expr, bool distinct);
      explicit Count(std::vector<variant> expr, bool distinct, const char * alias);
      
      Count & as(const char *alias);
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
