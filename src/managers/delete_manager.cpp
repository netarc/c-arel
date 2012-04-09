/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  DeleteManager::DeleteManager(Connection *connection) : TreeManager(connection) {
    this->ast = nodes::DeleteStatement();
    this->ctx = this->ast;
  }

  DeleteManager::DeleteManager(Connection *connection, Table &table) : TreeManager(connection) {
    this->ast = nodes::DeleteStatement();
    this->ctx = this->ast;
    this->from(table);
  }

  DeleteManager & DeleteManager::from(variant relation) {
    nodes::DeleteStatement *delete_statement = static_cast<nodes::DeleteStatement *>(*this->ast);
    delete_statement->left = relation;
    return *this;
  }

  DeleteManager & DeleteManager::where(variant expression) {
    if (expression.isType<TreeManager *>() || expression.isType<TreeManager>())
      expression = ((TreeManager *)expression)->ast;

    nodes::DeleteStatement *node = (nodes::DeleteStatement *)*this->ctx;
    node->wheres().push_back(expression);

    return *this;
  }
}