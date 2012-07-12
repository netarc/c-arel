/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  namespace nodes {
    nodes::Not Node::Not(void) {
      return nodes::Not(self());
    }

    nodes::Grouping Node::Or(variant right) {
      return nodes::Grouping(nodes::Or(self(), right));
    }

    nodes::And Node::And(variant right) {
      std::vector<variant> children;
      children.push_back(self());
      children.push_back(right);
      return nodes::And(children);
    }

    std::string Node::to_sql(void) {
      variant s = self();
      return ToSql(NULL).accept(s);
    }

    const char * Node::classname(void) {
      return "Arel::Nodes::Node";
    }
  }
}