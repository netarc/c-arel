/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_binary_h
#define include_c_arel_binary_h

namespace c_arel {
  namespace nodes {
    class Table;
    
    class Binary : public Node {
    public:
      explicit Binary(variant left, variant right);

      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);

      variant left;
      variant right;
    };
    
    #define BINARY_NODE(name) \
      class name : public Binary { \
        public: \
        explicit name(variant left, variant right); \
        virtual variant self(void) { return *this; } \
        virtual const char *classname(void); \
      }
    
    BINARY_NODE(As);
    BINARY_NODE(Assignment);
    BINARY_NODE(Between);
    BINARY_NODE(DoesNotMatch);
    BINARY_NODE(GreaterThan);
    BINARY_NODE(GreaterThanOrEqual);
    BINARY_NODE(Join);
    BINARY_NODE(LessThan);
    BINARY_NODE(LessThanOrEqual);
    BINARY_NODE(Matches);
    BINARY_NODE(NotEqual);
    BINARY_NODE(NotIn);
    BINARY_NODE(Or);
    BINARY_NODE(Union);
    BINARY_NODE(UnionAll);
    BINARY_NODE(Intersect);
    BINARY_NODE(Except);
  }
}

#endif
