/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_predications_h
#define include_c_arel_predications_h

namespace c_arel {
  class Predications : virtual  public Derived {
  public:
    nodes::NotEqual not_equal(variant other);
    nodes::Grouping not_equal_any(std::vector<variant> others);
    nodes::Grouping not_equal_all(std::vector<variant> others);
    nodes::Equality equal(variant other);
    nodes::Grouping equal_any(std::vector<variant> others);    
    nodes::Grouping equal_all(std::vector<variant> others);
    nodes::In in(SelectManager & other);
    nodes::In in(variant other);
    nodes::Grouping in_any(std::vector<variant> others);
    nodes::Grouping in_all(std::vector<variant> others);
    nodes::NotIn not_in(SelectManager & other);
    nodes::NotIn not_in(variant other);
    nodes::Grouping not_in_any(std::vector<variant> others);
    nodes::Grouping not_in_all(std::vector<variant> others);
    nodes::Matches matches(variant other);
    nodes::Grouping matches_any(std::vector<variant> others);
    nodes::Grouping matches_all(std::vector<variant> others);
    nodes::DoesNotMatch does_not_match(variant other);
    nodes::Grouping does_not_match_any(std::vector<variant> others);
    nodes::Grouping does_not_match_all(std::vector<variant> others);
    nodes::GreaterThanOrEqual gteq(variant right);
    nodes::Grouping gteq_any(std::vector<variant> others);
    nodes::Grouping gteq_all(std::vector<variant> others);
    nodes::GreaterThan gt(variant right);
    nodes::Grouping gt_any(std::vector<variant> others);
    nodes::Grouping gt_all(std::vector<variant> others);
    nodes::LessThan lt(variant right);
    nodes::Grouping lt_any(std::vector<variant> others);
    nodes::Grouping lt_all(std::vector<variant> others);
    nodes::LessThanOrEqual lteq(variant right);
    nodes::Grouping lteq_any(std::vector<variant> others);
    nodes::Grouping lteq_all(std::vector<variant> others);
    nodes::Between between(std::vector<variant> expr);
    nodes::Between between(variant left, variant right);
    nodes::Grouping between_any(std::vector<variant> others);
    nodes::Grouping between_all(std::vector<variant> others);
  };
}

#endif