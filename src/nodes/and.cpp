/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  namespace nodes {
    And::And(variant children) {
      if (!children.isType<std::vector<variant> >()) {
        this->children = std::vector<variant>();
        this->children.push_back(children);
        this->children.push_back(nullptr);
      }
      else {
        this->children = children;
      }
    }

    And::And(variant children, variant right) {
      if (!children.isType<std::vector<variant> >()) {
        this->children = std::vector<variant>();
        this->children.push_back(children);
        this->children.push_back(right);
      }
      else {
        this->children = children;
      }
    }

    const char * And::classname(void) {
      return "Arel::Nodes::And";
    }
  }
}