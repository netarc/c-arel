/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"


namespace c_arel {
  namespace nodes {
    DeleteStatement::DeleteStatement(void) : Binary(nullptr, std::vector<variant>()) {
    }

    DeleteStatement::DeleteStatement(variant relation) : Binary(relation, std::vector<variant>()) {
    }

    DeleteStatement::DeleteStatement(variant relation, std::vector<variant> wheres) : Binary(relation, wheres) {
    }

    variant & DeleteStatement::relation(void) {
      return left;
    }

    std::vector<variant> & DeleteStatement::wheres(void) {
      std::vector<variant> *w = static_cast<std::vector<variant> *>(*right);
      return *w;
    }

    const char * DeleteStatement::classname(void) {
      return "Arel::Nodes::DeleteStatement";
    }
  }
}