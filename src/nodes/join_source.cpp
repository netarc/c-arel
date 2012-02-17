/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"


namespace c_arel {
  namespace nodes {
    JoinSource::JoinSource(Table *single_source) : Binary(single_source, std::vector<variant>()) {
    }
    
    JoinSource::JoinSource(Table *single_source, variant joinop) : Binary(single_source, joinop) {
    }
    
    const char * JoinSource::classname(void) {
      return "Arel::Nodes::JoinSource";
    }
    
    bool JoinSource::isEmpty(void) {
      std::vector<variant> rlist = right;
      return !left && rlist.empty();
    }
  }
}