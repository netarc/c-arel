/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  SelectManager::SelectManager(variant engine) : TreeManager(engine) {
    this->ast = nodes::SelectStatement();
    this->ctx = ((nodes::SelectStatement)this->ast).cores.back();
  }

  SelectManager::SelectManager(variant engine, Table &table) : TreeManager(engine) {
    this->ast = nodes::SelectStatement();
    this->ctx = ((nodes::SelectStatement)this->ast).cores.back();
    this->from(table);
  }
  
  SelectManager & SelectManager::where(variant expression) {
    if (expression.isType<TreeManager *>() || expression.isType<TreeManager>())
      expression = ((TreeManager *)expression)->ast;
    
    nodes::SelectCore *node = (nodes::SelectCore *)*this->ctx;
    node->wheres.push_back(expression);
    
    return *this;
  }
  
  SelectManager & SelectManager::with(std::vector<variant> subqueries) {
    nodes::SelectStatement *select_statement = (nodes::SelectStatement *)*this->ast;
    select_statement->with = nodes::With(subqueries);
    return *this;
  }
  
  SelectManager & SelectManager::with(variant subquery) {
    nodes::SelectStatement *select_statement = (nodes::SelectStatement *)*this->ast;
    std::vector<variant> a;
    a.push_back(subquery);
    select_statement->with = nodes::With(a);
    return *this;
  }
  
  SelectManager & SelectManager::with_recursive(std::vector<variant> subqueries) {
    nodes::SelectStatement *select_statement = (nodes::SelectStatement *)*this->ast;
    select_statement->with = nodes::WithRecursive(subqueries);
    return *this;
  }
  
  SelectManager & SelectManager::with_recursive(variant subquery) {
    nodes::SelectStatement *select_statement = (nodes::SelectStatement *)*this->ast;
    std::vector<variant> a;
    a.push_back(subquery);
    select_statement->with = nodes::WithRecursive(a);
    return *this;
  }
  
  SelectManager & SelectManager::skip(int amount) {
    nodes::SelectStatement *select_statement = (nodes::SelectStatement *)*this->ast;
    if (amount)
      select_statement->offset = nodes::Offset(amount);
    else
      select_statement->offset = NULL;
    return *this;
  }

  SelectManager & SelectManager::take(int limit) {
    nodes::SelectStatement *select_statement = (nodes::SelectStatement *)*this->ast;
    nodes::SelectCore *select_core = (nodes::SelectCore *)*this->ctx;
    if (limit) {
      select_statement->limit = nodes::Limit(limit);
      select_core->top = nodes::Top(limit);
    }
    else {
      select_statement->limit = NULL;
      select_core->top = NULL;
    }
    return *this;
  }
  
  nodes::TableAlias SelectManager::as(const char *other) {
    return nodes::TableAlias(nodes::Grouping(this->ast), nodes::SqlLiteral(other));
  }

  SelectManager & SelectManager::on(variant exprs) {
    nodes::SelectCore *select_core = static_cast<nodes::SelectCore *>(*this->ctx);
    nodes::JoinSource *join_source = static_cast<nodes::JoinSource *>(*select_core->source);
    std::vector<variant> *join_source_right = static_cast<std::vector<variant> *>(*join_source->right);
    nodes::Binary *last_binary = static_cast<nodes::Binary *>(*join_source_right->back());
    last_binary->right = nodes::On(collapse(exprs));
    return *this;
  }

  SelectManager & SelectManager::group(std::vector<variant> columns) {
    for (std::vector<variant>::iterator wIt=columns.begin(); wIt!=columns.end(); ++wIt)
      group(*wIt);
    return *this;
  }

  SelectManager & SelectManager::group(variant column) {
    nodes::SelectCore *select_core = (nodes::SelectCore *)*this->ctx;

    if (column.isString())
      column = nodes::SqlLiteral(column.toString());

    select_core->groups.push_back(nodes::Group(column));
    return *this;
  }

  SelectManager& SelectManager::having(variant exprs) {
    nodes::SelectCore *select_core = static_cast<nodes::SelectCore *>(*this->ctx);
    select_core->having = nodes::Having(collapse(exprs, select_core->having));
    return *this;
  }
  
  SelectManager& SelectManager::project(variant projection) {
  //# FIXME: converting these to SQLLiterals is probably not good, but
  //# rails tests require it.
    nodes::SelectCore *select_core = (nodes::SelectCore *)*this->ctx;
    if (projection.isString()) {
      select_core->projections.push_back(nodes::SqlLiteral(projection.toString()));
    }
    else {
      select_core->projections.push_back(projection);
    }
    return *this;
  }
  
  SelectManager& SelectManager::distinct(bool value) {
    nodes::SelectCore *select_core = (nodes::SelectCore *)*this->ctx;
    if (value)
      select_core->set_quantifier = nodes::Distinct();
    else
      select_core->set_quantifier = NULL;
    return *this;
  }
  
  SelectManager& SelectManager::order(variant exprs) {
    if (!exprs.isType<std::vector<variant> >()) {
      std::vector<variant> a;
      a.push_back(exprs);
      exprs = a;
    }

    std::vector<variant> a = exprs;
    nodes::SelectStatement *select_statement = (nodes::SelectStatement *)*this->ast;
    
    select_statement->orders.insert(select_statement->orders.end(), a.begin(), a.end());
    return *this;
  }
  
  SelectManager& SelectManager::from(variant table) {
    if (table.isString())
      table = nodes::SqlLiteral(table.toString());
    
    nodes::SelectCore *select_core = (nodes::SelectCore *)*this->ctx;
    nodes::Binary *node_binary = (nodes::Binary *)*select_core->source;

    if (table.isType<nodes::Join>() ||
        table.isType<nodes::InnerJoin>() ||
        table.isType<nodes::OuterJoin>() ||
        table.isType<nodes::StringJoin>()) {
      std::vector<variant> *a = static_cast<std::vector<variant> *>(*node_binary->right);
      a->push_back(table);
    } else {
      node_binary->left = table;
    }
    
    return *this;
  }
  
  SelectManager& SelectManager::join(variant relation) {
    return join<nodes::InnerJoin>(relation);
  }
  
  //  template<typename T>
  //  SelectManager& SelectManager::join(variant relation) {
  //    if (!relation)
  //      return *this;
  //
  //    nodes::SelectCore *select_core = static_cast<nodes::SelectCore *>(*this->ctx);
  //    nodes::JoinSource *join_source = static_cast<nodes::JoinSource *>(*select_core->source);
  //    std::vector<variant> *join_source_right = static_cast<std::vector<variant> *>(*join_source->right);
  //    
  //    if (relation.isString()) {
  //      join_source_right->push_back(nodes::StringJoin(relation, NULL));
  //    }
  //    else if (relation.isType<nodes::SqlLiteral>()) {
  //      join_source_right->push_back(nodes::StringJoin(relation, NULL));
  //    }
  //    else {
  //      join_source_right->push_back(T(relation, NULL));
  //    }
  //    return *this;
  //  }
  
  nodes::Except SelectManager::minus(SelectManager other) {
    return except(other);
  }

  nodes::Except SelectManager::except(SelectManager other) {
    return nodes::Except(ast, other.ast);
  }
  
  nodes::Intersect SelectManager::intersect(SelectManager other) {
    return nodes::Intersect(ast, other.ast);
  }
  
  nodes::Union SelectManager::union_with(SelectManager other) {
    return nodes::Union(ast, other.ast);
  }
  
  nodes::UnionAll SelectManager::union_all(SelectManager other) {
    return nodes::UnionAll(ast, other.ast);
  }
  
  // Private
  variant SelectManager::collapse(variant exprs) {
    return collapse(exprs, NULL);
  }
  
  variant SelectManager::collapse(variant exprs, variant existing) {
    if (!exprs.isType<std::vector<variant> >()) {
      std::vector<variant> a;
      a.push_back(exprs);
      exprs = a;
    }
    
    std::vector<variant> a = exprs;
    if (!!existing) {
      std::vector<variant> new_a;
      new_a.push_back(existing);
      new_a.insert(new_a.end(), a.begin(), a.end());
      a = new_a;
    }

    if (a.size() == 1)
      return a.front();
    else
      return nodes::And(a);
  }
  
  nodes::Exists SelectManager::exists(void) {
    return nodes::Exists(ast);
  }
}