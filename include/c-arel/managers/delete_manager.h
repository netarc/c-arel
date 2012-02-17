/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_delete_manager_h
#define include_c_arel_delete_manager_h

namespace c_arel {
  class DeleteManager : public TreeManager {
  public:
    explicit DeleteManager(variant engine);
    explicit DeleteManager(variant engine, Table &table);

    DeleteManager & from(variant relation);
    DeleteManager & where(variant expression);

    // inheritance/rtii support
    virtual variant self(void) { return *this; }
  };
}

#endif