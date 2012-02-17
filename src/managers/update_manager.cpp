/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  UpdateManager::UpdateManager(variant engine) : TreeManager(engine) {
    this->ast = nodes::UpdateStatement();
    this->ctx = this->ast;
  }
  
  UpdateManager::UpdateManager(variant engine, Table &table) : TreeManager(engine) {
    this->ast = nodes::UpdateStatement();
    this->ctx = this->ast;
    this->table(table);
  }
  
  UpdateManager & UpdateManager::table(Table &table) {
    nodes::UpdateStatement *update_statement = static_cast<nodes::UpdateStatement *>(*this->ast);
    update_statement->relation = table;
    return *this;
  }
  
  UpdateManager & UpdateManager::set(variant values) {
    nodes::UpdateStatement *update_statement = static_cast<nodes::UpdateStatement *>(*this->ast);

    std::vector<variant> vals;
    if (values.isType<nodes::SqlLiteral>()) {
      vals.push_back(values);
      update_statement->values = vals;
    }
    else if (values.isType<std::vector<variant> >()) {
      std::vector<variant> *_values = static_cast<std::vector<variant> *>(*values);
      for (std::vector<variant>::iterator it=_values->begin(); it!=_values->end(); ++it) {
        std::vector<variant> *v = static_cast<std::vector<variant> *>(**it);
        variant column = v->at(0);
        variant value = v->at(1);
        vals.push_back(nodes::Assignment(nodes::UnqualifiedColumn(column), value));
      }
      update_statement->values = vals;
    }
    
    return *this;
  }
  
  UpdateManager & UpdateManager::set_where(std::vector<variant> exprs) {
    nodes::UpdateStatement *update_statement = static_cast<nodes::UpdateStatement *>(*this->ast);
    update_statement->wheres = exprs;
    return *this;
  }
  
  UpdateManager & UpdateManager::where(variant expr) {
    nodes::UpdateStatement *update_statement = static_cast<nodes::UpdateStatement *>(*this->ast);
    update_statement->wheres.push_back(expr);
    return *this;
  }
  
  UpdateManager & UpdateManager::take(variant limit) {
    nodes::UpdateStatement *update_statement = static_cast<nodes::UpdateStatement *>(*this->ast);
    if (!!limit)
      update_statement->limit = nodes::Limit(limit);
    return *this;
  }
  
  Attribute & UpdateManager::key(void) {
    nodes::UpdateStatement *update_statement = static_cast<nodes::UpdateStatement *>(*this->ast);
    return *static_cast<Attribute *>(*update_statement->key);
  }
  
  UpdateManager & UpdateManager::key(Attribute key) {
    nodes::UpdateStatement *update_statement = static_cast<nodes::UpdateStatement *>(*this->ast);
    update_statement->key = key;
    return *this;
  }
  
  UpdateManager & UpdateManager::order(std::vector<variant> expr) {
    nodes::UpdateStatement *update_statement = static_cast<nodes::UpdateStatement *>(*this->ast);
    update_statement->orders = expr;
    return *this;
  }
}