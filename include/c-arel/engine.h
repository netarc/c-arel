/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_engine_h
#define include_c_arel_engine_h

namespace c_arel {
  class Engine {
  public:
    virtual variant connection(void);
  };
}

#endif