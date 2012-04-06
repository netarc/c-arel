/* Copyright (c) 2012 Joshua Hollenbeck
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */
 
#ifndef variant_h
#define variant_h

#include <string>
#include <memory>
#include <typeinfo>

class variant {
public: // structors
  variant()
    : _type_container(NULL) {
  }

  template<typename T>
  variant(T val)
    : _type_container(NULL) {
    set_val<T>(val);
  }
  
  template<typename T>
  variant(T *val)
    : _type_container(NULL) {
    set_val<T>(val);
  }
  
  variant(const variant &val)
    : _type_container(NULL) {
    set_type_container(val._type_container);
  }
  
  ~variant() {
    reset();
  }

public: // assignemnt
  template<typename T>
  variant & operator =(T val) {
    set_val<T>(val);
    return *this;
  }
  
  template<typename T>
  variant & operator =(T *val) {
    set_val<T>(val);
    return *this;
  }
  
  variant & operator=(const variant &val) {
    set_type_container(val._type_container);
    return *this;
  }
  
public: // conversion
  template<typename T>
  operator T(void) {
    type_container<T> *result = dynamic_cast<type_container<T> *>(_type_container);
    if (!result)
      throw std::bad_cast();
    return result->_value;
  }
  
  void * operator *(void) {
    return _type_container ? _type_container->_ptrvalue : NULL;
  }
  
  const char * toString(void) {
    if (isType<char *>())
      return (char *)**this;
    else if (isType<const char *>())
      return (const char *)**this;
    else if (isType<std::string>())
      return (*((std::string *)**this)).c_str();
    else
      return NULL;
  }
      
public: // queries

  bool operator !(void) {
    return !**this;
  }

  const std::type_info & type() const {
    return _type_container ? _type_container->type() : typeid(NULL);
  }
  
  bool isString(void) {
    return toString() != NULL;
  }
  
  template<class T>
  bool isType(void) {
    return typeid(T) == type();
  }
  
protected: // internal
  
  class base_type_container {
  public: // structors
    explicit base_type_container()
      : _ptrvalue(NULL), _refcnt(0) {}
    virtual ~base_type_container() {}

  public: // queries
    virtual const std::type_info & type() const = 0;
    
  public: // representation
    void *_ptrvalue;
    int   _refcnt;
  };
  
  template<typename T>
  class type_container : public base_type_container {
  public: // structors
    explicit type_container(const T & val)
      : _value(val), base_type_container() { 
      _ptrvalue = &_value;
    }
    
    explicit type_container(T* val)
      : _value(*val), base_type_container() {
      _ptrvalue = (void *)_value;
    }
    
  public: // queries
    virtual const std::type_info & type() const {
      return typeid(T);
    }
    
  public: // representation
    T _value;
    
  private: // intentionally left unimplemented
    type_container & operator=(const type_container &);
  };

  template<class T>
  void set_val(T val) {
    if (typeid(val) == typeid(NULL))
      set_type_container(NULL);
    else
      set_type_container(new type_container<T>(val));
  }
  
  template<class T>
  void set_val(T* val) {
    if (val == NULL)
      set_type_container(NULL);
    else
      set_type_container(new type_container<T*>(&val));
  }
  
  virtual void set_type_container(base_type_container * container) {
    reset();

    _type_container = container;
    if (_type_container)
      _type_container->_refcnt++;
  }
  
  void reset(void) {
    if (!_type_container)
      return;

    if (--_type_container->_refcnt <= 0)
      delete _type_container;
    _type_container = NULL;
  }
  
  base_type_container *_type_container;
};

typedef variant var;

#endif