/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  InsertManager::InsertManager(variant engine) : TreeManager(engine) {
    this->ast = nodes::InsertStatement();
  }
  
  InsertManager::InsertManager(variant engine, Table &table) : TreeManager(engine) {
    this->ast = nodes::InsertStatement();
    this->into(table);
  }
  
  InsertManager & InsertManager::into(Table &table) {
    nodes::InsertStatement *insert_statement = (nodes::InsertStatement *)*this->ast;
    insert_statement->relation = table;
    return *this;
  }
  
  InsertManager & InsertManager::insert(std::vector<variant> fields) {
    if (fields.empty())
      return *this;

    nodes::InsertStatement *insert_statement = (nodes::InsertStatement *)*this->ast;

    if (!insert_statement->relation) {
      // TODO: should we error out?
      variant f = fields.front();
      if (!f.isType<std::vector<variant> >())
        return *this;
      // TODO: should we error out?
      f = static_cast<std::vector<variant> *>(*f)->front();
      if (!f.isType<Attribute>())
        return *this;

      insert_statement->relation = static_cast<Attribute *>(*f)->relation;
    }
    
    std::vector<variant> values;
    for (std::vector<variant>::iterator it=fields.begin(); it!=fields.end(); ++it) {
      std::vector<variant> *v = static_cast<std::vector<variant> *>(**it);
      insert_statement->columns.push_back(v->at(0));
      values.push_back(v->at(1));
    }
    
    insert_statement->values = create_values(values, insert_statement->columns);
    
    return *this;
  }
  
  nodes::Values InsertManager::create_values(std::vector<variant> values, std::vector<variant> columns) {
    return nodes::Values(values, columns);
  }
}