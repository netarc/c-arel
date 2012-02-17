/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_insert_statement_h
#define include_c_arel_insert_statement_h

namespace c_arel {
  namespace nodes {
    class InsertStatement : public Node {
    public:
      explicit InsertStatement(void);

      variant relation;
      std::vector<variant> columns;
      variant values;
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
