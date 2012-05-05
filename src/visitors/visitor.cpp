/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {

  class ClassMap {
  public:

    template<typename T>
    static void declare(void) {
      _classes.push_back(typeid(T).name());
      _classes.push_back(typeid(T*).name());
    }

    static bool is_recognized_classname(const char *cname) {
      return std::find(_classes.begin(), _classes.end(), cname) != _classes.end();
    }

  protected:
    static std::vector<const char *> _classes;
  };

  std::vector<const char *> ClassMap::_classes;

  static bool model_map = false;
  static void create_model_map(void) {
    if (model_map) return;
    model_map = true;

    ClassMap::declare<Derived>();
    ClassMap::declare<Attribute>();
    ClassMap::declare<Table>();
    ClassMap::declare<TreeManager>();
    // Terminal Nodes
    ClassMap::declare<nodes::Distinct>();
    // Binary Nodes
    ClassMap::declare<nodes::Binary>();
    ClassMap::declare<nodes::As>();
    ClassMap::declare<nodes::Assignment>();
    ClassMap::declare<nodes::Between>();
    ClassMap::declare<nodes::DoesNotMatch>();
    ClassMap::declare<nodes::GreaterThan>();
    ClassMap::declare<nodes::GreaterThanOrEqual>();
    ClassMap::declare<nodes::Join>();
    ClassMap::declare<nodes::LessThan>();
    ClassMap::declare<nodes::LessThanOrEqual>();
    ClassMap::declare<nodes::Matches>();
    ClassMap::declare<nodes::NotEqual>();
    ClassMap::declare<nodes::NotIn>();
    ClassMap::declare<nodes::Or>();
    ClassMap::declare<nodes::Union>();
    ClassMap::declare<nodes::UnionAll>();
    ClassMap::declare<nodes::Intersect>();
    ClassMap::declare<nodes::Except>();
    ClassMap::declare<nodes::Values>();
    // Unary Nodes
    ClassMap::declare<nodes::Unary>();
    ClassMap::declare<nodes::Bin>();
    ClassMap::declare<nodes::Group>();
    ClassMap::declare<nodes::Grouping>();
    ClassMap::declare<nodes::Having>();
    ClassMap::declare<nodes::Limit>();
    ClassMap::declare<nodes::Not>();
    ClassMap::declare<nodes::Offset>();
    ClassMap::declare<nodes::On>();
    ClassMap::declare<nodes::Ordering>();
    ClassMap::declare<nodes::Top>();
    ClassMap::declare<nodes::Lock>();
    ClassMap::declare<nodes::DistinctOn>();
    ClassMap::declare<nodes::Ascending>();
    ClassMap::declare<nodes::Descending>();
    ClassMap::declare<nodes::TableAlias>();
    ClassMap::declare<nodes::With>();
    ClassMap::declare<nodes::WithRecursive>();
    ClassMap::declare<nodes::UnqualifiedColumn>();
    // Nodes
    ClassMap::declare<nodes::And>();
    ClassMap::declare<nodes::Equality>();
    ClassMap::declare<nodes::In>();
    ClassMap::declare<nodes::JoinSource>();
    ClassMap::declare<nodes::Node>();
    ClassMap::declare<nodes::SelectCore>();
    ClassMap::declare<nodes::SelectStatement>();
    ClassMap::declare<nodes::SqlLiteral>();
    ClassMap::declare<nodes::InnerJoin>();
    ClassMap::declare<nodes::StringJoin>();
    ClassMap::declare<nodes::OuterJoin>();
    ClassMap::declare<nodes::DeleteStatement>();
    ClassMap::declare<nodes::InsertStatement>();
    ClassMap::declare<nodes::UpdateStatement>();
    // Function Nodes
    ClassMap::declare<nodes::Function>();
    ClassMap::declare<nodes::Sum>();
    ClassMap::declare<nodes::Exists>();
    ClassMap::declare<nodes::Max>();
    ClassMap::declare<nodes::Min>();
    ClassMap::declare<nodes::Avg>();
    ClassMap::declare<nodes::Count>();
    ClassMap::declare<nodes::NamedFunction>();
    // INFIX Nodes
    ClassMap::declare<nodes::Multiplication>();
    ClassMap::declare<nodes::Division>();
    ClassMap::declare<nodes::Addition>();
    ClassMap::declare<nodes::Subtraction>();
  }

//  template<typename T> std::vector<base_field*> model<T>::fields_;

  // TODO: lame method lookup - probably could be cleaned up...
  method_dict_map_t Visitor::_visitor_method_lookup;
  method_dict_map_t & Visitor::method_dictionary(void) {
    if (_visitor_method_lookup.empty()) {

    }
    return _visitor_method_lookup;
  }


  std::string Visitor::accept(variant & object) {
    return visit(object);
  }

  std::string Visitor::visit(variant & object) {
    create_model_map();

    Derived *base = (Derived *)*object;
    std::string classname;

    if (!object) {
      printf("visit was empty!\n");
      return "";
    }

    if (ClassMap::is_recognized_classname(object.type().name())) {
      classname = base->classname();
    } else {
      if (object.isString())
        classname = "String";
      else if (object.type() == typeid(std::vector<variant>))
        classname = "Array";
      else
        classname = "literal";
    }

    method_dict_map_t method_dict_map = method_dictionary();
    if (method_dict_map[classname]) {
      return (this->*method_dict_map[classname])(object);
    }
    else {
      printf("Visitor::visit failed to find method: %s(%s)\n", classname.c_str(), object.type().name());
      return "";
    }
  }
}