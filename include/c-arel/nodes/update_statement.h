/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_update_statement_h
#define include_c_arel_update_statement_h

namespace c_arel {
  namespace nodes {
    class UpdateStatement : public Node {
    public:
      explicit UpdateStatement(void);
      
      variant              relation;
      variant              limit;
      variant              key;
      
      std::vector<variant> values;
      std::vector<variant> wheres;
      std::vector<variant> orders;
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
