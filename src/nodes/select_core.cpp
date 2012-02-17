/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"


namespace c_arel {
  namespace nodes {
    SelectCore::SelectCore(void) {
      source = JoinSource(NULL);
    }
    
    variant & SelectCore::from(void) {
      return static_cast<JoinSource *>(*source)->left;
    }
    
    void SelectCore::set_from(variant value) {
      static_cast<JoinSource *>(*source)->left = value;
    }
    
    const char * SelectCore::classname(void) {
      return "Arel::Nodes::SelectCore";
    }
  }
}