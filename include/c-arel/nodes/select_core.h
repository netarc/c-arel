/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_select_core_h
#define include_c_arel_select_core_h
namespace c_arel {
  namespace nodes {
    class SelectCore : public nodes::Node {
    public:
      explicit SelectCore(void);
      
      variant & from(void);
      void set_from(variant value);

      variant               source;
      std::vector<variant>  wheres;
      std::vector<variant>  projections;
      std::vector<variant>  groups;
      variant               top;
      variant               set_quantifier;
      variant               having;

      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}
#endif
