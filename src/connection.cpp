/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  std::string Connection::quote_table_name(std::string name) {
    return quote_column_name(name);
  }

  std::string Connection::quote_column_name(std::string name) {
    return name;
  }

  std::string Connection::quote(std::string value, variant column) {
    return format_string("'%s'", quote_string(value).c_str());
  }

  std::string Connection::quote_string(std::string value) {
    return gsub_string(value, "'", "''");
  }

  Connection _base_connection;
}