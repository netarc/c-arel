/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_select_manager_h
#define include_c_arel_select_manager_h
namespace c_arel {
  class Table;
  namespace nodes {
    class Exists;
  }

  class SelectManager : public TreeManager {
  public:
    explicit SelectManager(Connection *connection=NULL);
    explicit SelectManager(Connection *connection, Table &table);

    SelectManager & where(variant expression);

    SelectManager & with(std::vector<variant> subqueries);
    SelectManager & with(variant subquery);
    SelectManager & with_recursive(std::vector<variant> subqueries);
    SelectManager & with_recursive(variant subquery);

    int offset(void);
    int skip(void);
    int take(void);
    SelectManager & offset(int amount);
    SelectManager & skip(int amount);
    SelectManager & take(int limit);
    nodes::TableAlias as(const char *other);
    SelectManager & on(variant exprs);
    SelectManager & group(std::vector<variant> columns);
    SelectManager & group(variant column);
    SelectManager & having(variant exprs);
    SelectManager & project(variant projection);
    SelectManager & distinct(bool value);
    SelectManager & order(variant exprs);

    SelectManager & from(variant table);

    SelectManager & join(variant relation);
    template<typename T>
    SelectManager & join(variant relation) {
      if (!relation)
        return *this;

      nodes::SelectCore *select_core = static_cast<nodes::SelectCore *>(*this->ctx);
      nodes::JoinSource *join_source = static_cast<nodes::JoinSource *>(*select_core->source);
      std::vector<variant> *join_source_right = static_cast<std::vector<variant> *>(*join_source->right);

      if (relation.isString()) {
        join_source_right->push_back(nodes::StringJoin(relation, nullptr));
      }
      else if (relation.isType<nodes::SqlLiteral>()) {
        join_source_right->push_back(nodes::StringJoin(relation, nullptr));
      }
      else {
        join_source_right->push_back(T(relation, nullptr));
      }
      return *this;
    }

    nodes::Except minus(SelectManager other);
    nodes::Except except(SelectManager other);
    nodes::Intersect intersect(SelectManager other);
    nodes::Union union_with(SelectManager other);
    nodes::UnionAll union_all(SelectManager other);

    nodes::Exists exists(void);

    // inheritance/rtii support
    virtual variant self(void) { return *this; }
  private:
    variant collapse(variant exprs);
    variant collapse(variant exprs, variant existing);
  };
}
#endif
