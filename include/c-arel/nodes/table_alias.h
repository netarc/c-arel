/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_table_alias_h
#define include_c_arel_table_alias_h

namespace c_arel {
  class Attribute;

  namespace nodes {
    class TableAlias : public Binary {
    public:
      explicit TableAlias(variant left, variant right);
      
      Attribute operator[] (const char *name);
      variant & name(void);
      variant & relation(void);
      variant & table_alias(void);

      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
