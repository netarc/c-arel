/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_unary_h
#define include_c_arel_unary_h

namespace c_arel {
  namespace nodes {
    class Unary : public Node {
    public:
      explicit Unary(variant expr);
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
      
      variant expr;
    };
    
    #define UNARY_TABLE(name) \
      class name : public Unary { \
      public: \
      explicit name(variant expr); \
      virtual variant self(void) { return *this; } \
      virtual const char *classname(void); \
      }
    
    UNARY_TABLE(Bin);
    UNARY_TABLE(Group);
    UNARY_TABLE(Grouping);
    UNARY_TABLE(Having);
    UNARY_TABLE(Limit);
    UNARY_TABLE(Not);
    UNARY_TABLE(Offset);
    UNARY_TABLE(On);
    UNARY_TABLE(Ordering);
    UNARY_TABLE(Top);
    UNARY_TABLE(Lock);
    UNARY_TABLE(DistinctOn);
  }
}

#endif
