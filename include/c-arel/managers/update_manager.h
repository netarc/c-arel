/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_update_manager_h
#define include_c_arel_update_manager_h

namespace c_arel {
  class UpdateManager : public TreeManager {
  public:
    explicit UpdateManager(variant engine);
    explicit UpdateManager(variant engine, Table &table);
    
    UpdateManager & table(Table &table);
    UpdateManager & set(variant values);
    UpdateManager & take(variant limit);

    UpdateManager & set_where(std::vector<variant> exprs);
    UpdateManager & where(variant expr);

    Attribute & key(void);
    UpdateManager & key(Attribute key);

    UpdateManager & order(std::vector<variant> expr);

    // inheritance/rtii support
    virtual variant self(void) { return *this; }
  };
}

#endif
