/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */
 
#ifndef include_c_arel_values_h
#define include_c_arel_values_h

namespace c_arel {
  namespace nodes {
    class Values : public Binary {
    public:
      explicit Values(std::vector<variant> exprs);
      explicit Values(std::vector<variant> exprs, std::vector<variant> columns);

      std::vector<variant> & expressions(void);
      std::vector<variant> & columns(void);

      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
