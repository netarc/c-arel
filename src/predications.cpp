/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  #define PREDICATION_ALL(method, name) \
    nodes::Grouping Predications::name(std::vector<variant> others) { \
      std::vector<variant> pieces; \
      for (std::vector<variant>::iterator wIt=others.begin(); wIt!=others.end(); ++wIt) \
        pieces.push_back(method(*wIt)); \
      return nodes::Grouping(nodes::And(pieces)); \
    }
  
  #define PREDICATION_ANY(method, name) \
    nodes::Grouping Predications::name(std::vector<variant> others) { \
      std::vector<variant>::iterator wIt; \
      variant node; \
      node = method(*(wIt=others.begin())); \
      for (++wIt; wIt!=others.end(); ++wIt) \
        node = nodes::Or(node, method(*wIt)); \
      return nodes::Grouping(node); \
    }
    
  nodes::NotEqual Predications::not_equal(variant other) {
    return nodes::NotEqual(self(), other);
  }

  PREDICATION_ANY(not_equal, not_equal_any);

  PREDICATION_ALL(not_equal, not_equal_all);

  nodes::Equality Predications::equal(variant other) {
    return nodes::Equality(self(), other);
  }

  PREDICATION_ANY(equal, equal_any);

  PREDICATION_ALL(equal, equal_all);
   
  nodes::In Predications::in(SelectManager & other) {
    return nodes::In(self(), other.ast);
  }

  nodes::In Predications::in(variant other) {
    return nodes::In(self(), other);
  }
  
  PREDICATION_ANY(in, in_any);
  
  PREDICATION_ALL(in, in_all);
   
  nodes::NotIn Predications::not_in(SelectManager & other) {
    return nodes::NotIn(self(), other.ast);
  }
  
  nodes::NotIn Predications::not_in(variant other) {
    return nodes::NotIn(self(), other);
  }

  PREDICATION_ANY(in, not_in_any);
  
  PREDICATION_ALL(in, not_in_all);

  nodes::Matches Predications::matches(variant other) {
    return nodes::Matches(self(), other);
  }
   
  PREDICATION_ANY(matches, matches_any);
  
  PREDICATION_ALL(matches, matches_all);

  nodes::DoesNotMatch Predications::does_not_match(variant other) {
    return nodes::DoesNotMatch(self(), other);
  }
  
  PREDICATION_ANY(does_not_match, does_not_match_any);

  PREDICATION_ALL(does_not_match, does_not_match_all);
  
  nodes::GreaterThanOrEqual Predications::gteq(variant right) {
    return nodes::GreaterThanOrEqual(self(), right);
  }

  PREDICATION_ANY(gteq, gteq_any);
  
  PREDICATION_ALL(gteq, gteq_all);

  nodes::GreaterThan Predications::gt(variant right) {
    return nodes::GreaterThan(self(), right);
  }

  PREDICATION_ANY(gt, gt_any);
  
  PREDICATION_ALL(gt, gt_all);

  nodes::LessThan Predications::lt(variant right) {
    return nodes::LessThan(self(), right);
  }

  PREDICATION_ANY(lt, lt_any);

  PREDICATION_ALL(lt, lt_all);

  nodes::LessThanOrEqual Predications::lteq(variant right) {
    return nodes::LessThanOrEqual(self(), right);
  }
   
  PREDICATION_ANY(lteq, lteq_any);

  PREDICATION_ALL(lteq, lteq_all);
  
  nodes::Between Predications::between(std::vector<variant> expr) {
    return between(expr.at(0), expr.at(1));
  }
  
  nodes::Between Predications::between(variant left, variant right) {
    return nodes::Between(self(), nodes::And(left, right));
  }

  PREDICATION_ANY(between, between_any);
  
  PREDICATION_ALL(between, between_all);
}