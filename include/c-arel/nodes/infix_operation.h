/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_infix_operation_h
#define include_c_arel_infix_operation_h

namespace c_arel {
  namespace nodes {
    class InfixOperation : public Binary {
    public:
      explicit InfixOperation(std::string op, variant left, variant right);

      std::string op;

      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
    
    #define INFIX_NODE(name) \
      class name : public InfixOperation { \
        public: \
        explicit name(variant left, variant right); \
        virtual variant self(void) { return *this; } \
        virtual const char *classname(void); \
      }
    
    INFIX_NODE(Multiplication);
    INFIX_NODE(Division);
    INFIX_NODE(Addition);
    INFIX_NODE(Subtraction);
  }
}

#endif
