/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_util_h
#define include_c_arel_util_h

namespace c_arel {
  namespace nodes {
    class SqlLiteral;
  }

  extern std::vector<variant> zip_vector(std::vector<variant> src, std::vector<variant> target);
  extern std::string join_vector(std::vector<std::string> v);
  extern std::string join_vector(std::vector<std::string> v, const char *delimiter);
  extern std::string format_string(const std::string &fmt, ...);
  extern std::string gsub_string(const std::string &sData, const std::string &sFrom, const std::string &sTo);
  extern nodes::SqlLiteral raw_sql(const char *sql);
  extern std::string number_variant_to_string(variant &value);
}

#endif
