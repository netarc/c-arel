/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_sql_literal_h
#define include_c_arel_sql_literal_h

namespace c_arel {
  namespace nodes {
    class SqlLiteral : virtual  public Derived {
    public:
      SqlLiteral(const char *value);
      
      variant value;
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
