/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_tree_manager_h
#define include_c_arel_tree_manager_h

namespace c_arel {
  class TreeManager {
  public:
    explicit TreeManager(variant engine);
    ~TreeManager();

    Visitor *visitor(void);
    const char * to_sql(void);

    virtual TreeManager & where(variant expression);
    
    // inheritance/rtii support
    virtual variant self(void) { return *this; }

  public:
    variant     engine;
    variant     ast;
  protected:
    variant     ctx;
  };
}

#endif
