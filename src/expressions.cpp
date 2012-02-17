/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"


namespace c_arel {
  nodes::Count Expressions::count(bool distinct) {
    std::vector<variant> a;
    a.push_back(self());
    return nodes::Count(a, distinct);
  }
  
  nodes::Sum Expressions::sum(void) {
    std::vector<variant> a;
    a.push_back(self());
    return nodes::Sum(a, nodes::SqlLiteral("sum_id"));
  }
  
  nodes::Max Expressions::maximum(void) {
    std::vector<variant> a;
    a.push_back(self());
    return nodes::Max(a, nodes::SqlLiteral("max_id"));
  }
  
  nodes::Min Expressions::minimum(void) {
    std::vector<variant> a;
    a.push_back(self());
    return nodes::Min(a, nodes::SqlLiteral("min_id"));
  }
  
  nodes::Avg Expressions::average(void) {
    std::vector<variant> a;
    a.push_back(self());
    return nodes::Avg(a, nodes::SqlLiteral("avg_id"));
  }
}