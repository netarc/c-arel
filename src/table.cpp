/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  Table::Table(const char *name) : name(name) {
  }
  
  Table::Table(const char *name, variant engine) : name(name), engine(engine) {
  }

  SelectManager Table::from(Table &table) {
    return SelectManager(this->engine, table);
  }
  
  nodes::TableAlias Table::alias(void) {
    return alias(format_string("%s_2", name.c_str()));
  }
  
  nodes::TableAlias Table::alias(std::string name) {
    nodes::TableAlias a = nodes::TableAlias(self(), name);
    aliases.push_back(a);
    return a;
  }
  
  SelectManager Table::join(variant relation) {
    return from(*this).join<nodes::InnerJoin>(relation);
  }

//  template<typename T>
//  SelectManager Table::join(variant relation) {
//    return from(this).join<T>(relation);
//  }
  
  SelectManager Table::group(std::vector<variant> columns) {
    return from(*this).group(columns);
  }
  
  SelectManager Table::group(variant column) {
    return from(*this).group(column);
  }
  
  SelectManager Table::order(variant exprs) {
    return from(*this).order(exprs);
  }

  SelectManager Table::where(variant condition) {
    TreeManager mgr = from(*this).where(condition);
    return *((SelectManager *)&mgr);
  }
  
  SelectManager Table::take(int amount) {
    return from(*this).take(amount);
  }
  
  SelectManager Table::skip(int amount) {
    return from(*this).skip(amount);
  }
  
  SelectManager Table::having(variant expr) {
    return from(*this).having(expr);
  }
  
  SelectManager Table::project(variant projection) {
    return from(*this).project(projection);
  }
  
  Attribute Table::operator[] (const char *name) {
    return Attribute(this, name);
  }
 
  // -- non AREL helper methods --
  
  DeleteManager Table::delete_from(void) {
    return DeleteManager(this->engine, *this);
  }

  const char * Table::classname(void) {
    return "Arel::Table";
  }
}