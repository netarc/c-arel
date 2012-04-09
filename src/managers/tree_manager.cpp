/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"


namespace c_arel {
  TreeManager::TreeManager(Connection *connection) {
    this->connection = connection;
    this->ast = NULL;
    this->ctx = NULL;
  }

  TreeManager::~TreeManager(void) {
  }

  Visitor *TreeManager::visitor(void) {
    return new ToSql(connection);
  }

  const char * TreeManager::to_sql(void) {
    return ToSql(NULL).accept(this->ast).c_str();
  }

  TreeManager & TreeManager::where(variant expr) {
    return *this;
  }
}