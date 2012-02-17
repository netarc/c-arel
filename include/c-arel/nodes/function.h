/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_function_h
#define include_c_arel_function_h

namespace c_arel {
  namespace nodes {
    class Function : 
      public OrderPredications, 
      public Predications {
    public:
      explicit Function(variant expr);
      explicit Function(variant, variant alias);
      
      Function & as(const char *alias);
        
      variant expressions;
      variant alias;
      variant distinct;
      
      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
    
    #define FUNCTION_NODE(name) \
      class name : public Function { \
      public: \
        explicit name(variant expr); \
        explicit name(variant expr, variant alias); \
        name & as(const char *alias); \
        virtual variant self(void) { return *this; } \
        virtual const char *classname(void); \
      }
    
    FUNCTION_NODE(Sum);
    FUNCTION_NODE(Exists);
    FUNCTION_NODE(Max);
    FUNCTION_NODE(Min);
    FUNCTION_NODE(Avg);
  }
}

#endif
