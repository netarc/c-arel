/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_node_h
#define include_c_arel_node_h

namespace c_arel {
  namespace nodes {
    class Not;
    class Grouping;
    class And;
    
    class Node : virtual  public Derived {
    public:
      nodes::Not Not(void);
      nodes::Grouping Or(variant right);
      nodes::And And(variant right);
      
      const char * to_sql(void);

      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}

#endif
