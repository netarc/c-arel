/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_insert_manager_h
#define include_c_arel_insert_manager_h

namespace c_arel {
  class InsertManager : public TreeManager {
  public:
    explicit InsertManager(Connection *connection=NULL);
    explicit InsertManager(Connection *connection, Table &table);

    InsertManager & into(Table &table);
    InsertManager & insert(std::vector<variant> fields);
    nodes::Values create_values(std::vector<variant> values, std::vector<variant> columns);

    // inheritance/rtii support
    virtual variant self(void) { return *this; }
  };
}

#endif
