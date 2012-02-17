/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"


namespace c_arel {
  TreeManager::TreeManager(variant engine) {
    this->engine = engine;
    this->ast = NULL;
    this->ctx = NULL;
  }
  
  TreeManager::~TreeManager(void) {
  }
  
  Visitor *TreeManager::visitor(void) {
//    engine.connection.visitor
    return new ToSql(NULL);
  }
  
  const char * TreeManager::to_sql(void) {
    return visitor()->accept(this->ast).c_str();
  }
  
  TreeManager & TreeManager::where(variant expr) {
    return *this;
  }
}