/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_delete_statement_h
#define include_c_arel_delete_statement_h

namespace c_arel {
  namespace nodes {
    class DeleteStatement : public Binary {
    public:
      explicit DeleteStatement(void);
      explicit DeleteStatement(variant relation);
      explicit DeleteStatement(variant relation, std::vector<variant> wheres);
      
      variant & relation(void);
      std::vector<variant> & wheres(void);
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
