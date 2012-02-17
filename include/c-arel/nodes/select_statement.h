/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_select_statement_h
#define include_c_arel_select_statement_h

namespace c_arel {
  namespace nodes {
    class SelectStatement : public Node {
    public:
      explicit SelectStatement(void);

      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
      
      std::vector<variant> cores;
      std::vector<variant> orders;
      variant             with;
      variant             limit;
      variant             offset;      
    };
  }
}

#endif
