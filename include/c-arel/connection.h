/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_connection_h
#define include_c_arel_connection_h

namespace c_arel {
  class Connection {
  public:
    virtual std::string quote_table_name(std::string name);
    virtual std::string quote_column_name(std::string name);
    virtual std::string quote(std::string value, variant column=NULL);
    virtual std::string quote_string(std::string value);
  };
}

#endif