/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_table_h
#define include_c_arel_table_h
namespace c_arel {
  class Table : virtual  public Derived {
  public:
    Table(const char *name, Connection *connection=NULL);

    SelectManager from(Table &table);

    nodes::TableAlias alias();
    nodes::TableAlias alias(std::string name);

    SelectManager join(variant relation);
    template<typename T>
    SelectManager join(variant relation) {
      return from(*this).join<T>(relation);
    }

    SelectManager group(std::vector<variant> columns);
    SelectManager group(variant column);
    SelectManager order(variant exprs);
    SelectManager where(variant condition);
    SelectManager project(variant condition);

    SelectManager take(int amount);
    SelectManager skip(int amount);

    SelectManager having(variant expr);

    Attribute operator[] (const char *name);

    // -- non AREL helper methods --
    DeleteManager delete_from(void);
    virtual variant self(void) { return *this; }
    virtual const char *classname(void);

    variant               table_alias;
    std::vector<variant>  aliases;

    Connection *connection;
    std::string name;
  };
}
#endif