/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_attribute_h
#define include_c_arel_attribute_h

namespace c_arel {
  class Table;
  
  class Attribute : 
    virtual  public Derived, 
    public Expressions, 
    public Predications, 
    public AliasPredication, 
    public Math, 
    public OrderPredications {
  public:
    explicit Attribute(variant relation, const char *name);
    
    variant relation;
    variant name;
    
    // inheritance/rtii support
    virtual variant self(void) { return *this; }
    virtual const char *classname(void);
  };
}

#endif