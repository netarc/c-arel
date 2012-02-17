/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_visitor_h
#define include_c_arel_visitor_h
namespace c_arel {
  class Visitor;
  
  class visitor_method {
  public:
    explicit visitor_method() {}
    virtual std::string invoke(Visitor *visitor, variant & v) { return ""; }
  };
  
  template<typename T>
  class casted_visitor_method : visitor_method {
  public:
    typedef std::string (Visitor::*method_t)(T);
    explicit casted_visitor_method(method_t m) : method(m) {}

    virtual std::string invoke(Visitor *visitor, variant & v) {
      return (visitor->*method)((T)*v);
    }
  private:
    method_t method;
  };
  
  typedef std::string (Visitor::*visitor_method_t)(variant &);
  typedef std::map<std::string, visitor_method_t> method_dict_map_t;
  
  class Visitor {
  public:
    virtual std::string accept(variant & object);
    
  protected:
    std::string visit(variant & object);

    // TODO: lame method lookup - probably could be cleaned up...
  public:
    virtual method_dict_map_t & method_dictionary(void);
    static method_dict_map_t _visitor_method_lookup;
  };
}
#endif
