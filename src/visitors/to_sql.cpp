/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  extern Connection _base_connection;

  // TODO: lame method lookup/rtii - probably could be cleaned up...
  method_dict_map_t ToSql::_to_sql_method_lookup;
  method_dict_map_t & ToSql::method_dictionary(void) {
    if (_to_sql_method_lookup.empty()) {
      method_dict_map_t parent_method_dictionary = Visitor::method_dictionary();
      _to_sql_method_lookup = method_dict_map_t(parent_method_dictionary.begin(), parent_method_dictionary.end());
      // overrides
      _to_sql_method_lookup["Arel::Nodes::DeleteStatement"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_DeleteStatement;
      _to_sql_method_lookup["Arel::Nodes::UpdateStatement"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_UpdateStatement;
      _to_sql_method_lookup["Arel::Nodes::InsertStatement"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_InsertStatement;
      _to_sql_method_lookup["Arel::Nodes::SelectStatement"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_SelectStatement;
      _to_sql_method_lookup["Arel::Nodes::SelectCore"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_SelectCore;
      _to_sql_method_lookup["Arel::Nodes::Exists"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Exists;
      _to_sql_method_lookup["Arel::Nodes::Values"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Values;
      _to_sql_method_lookup["Arel::Nodes::Bin"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Bin;
      _to_sql_method_lookup["Arel::Nodes::Distinct"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Distinct;
      _to_sql_method_lookup["Arel::Nodes::With"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_With;
      _to_sql_method_lookup["Arel::Nodes::WithRecursive"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_WithRecursive;
      _to_sql_method_lookup["Arel::Nodes::Union"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Union;
      _to_sql_method_lookup["Arel::Nodes::UnionAll"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_UnionAll;
      _to_sql_method_lookup["Arel::Nodes::Intersect"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Intersect;
      _to_sql_method_lookup["Arel::Nodes::Except"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Except;
      _to_sql_method_lookup["Arel::Nodes::Having"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Having;
      _to_sql_method_lookup["Arel::Nodes::Offset"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Offset;
      _to_sql_method_lookup["Arel::Nodes::Limit"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Limit;
      _to_sql_method_lookup["Arel::Nodes::Top"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Top;
      _to_sql_method_lookup["Arel::Nodes::Ascending"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Ascending;
      _to_sql_method_lookup["Arel::Nodes::Descending"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Descending;
      _to_sql_method_lookup["Arel::Nodes::Grouping"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Grouping;
      _to_sql_method_lookup["Arel::Nodes::Group"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Group;
      _to_sql_method_lookup["Arel::Nodes::Count"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Count;
      _to_sql_method_lookup["Arel::Nodes::Sum"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Sum;
      _to_sql_method_lookup["Arel::Nodes::Max"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Max;
      _to_sql_method_lookup["Arel::Nodes::Min"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Min;
      _to_sql_method_lookup["Arel::Nodes::Avg"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Avg;
      _to_sql_method_lookup["Arel::Nodes::JoinSource"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_JoinSource;
      _to_sql_method_lookup["Arel::Table"] = (visitor_method_t)&ToSql::visit_Arel_Table;
      _to_sql_method_lookup["Arel::Nodes::In"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_In;
      _to_sql_method_lookup["Arel::Nodes::NotIn"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_NotIn;
      _to_sql_method_lookup["Arel::Nodes::StringJoin"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_StringJoin;
      _to_sql_method_lookup["Arel::Nodes::OuterJoin"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_OuterJoin;
      _to_sql_method_lookup["Arel::Nodes::InnerJoin"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_InnerJoin;
      _to_sql_method_lookup["Arel::Nodes::On"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_On;
      _to_sql_method_lookup["Arel::Nodes::Not"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Not;
      _to_sql_method_lookup["Arel::Nodes::And"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_And;
      _to_sql_method_lookup["Arel::Nodes::Or"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Or;
      _to_sql_method_lookup["Arel::Nodes::Assignment"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Assignment;
      _to_sql_method_lookup["Arel::Nodes::Equality"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Equality;
      _to_sql_method_lookup["Arel::Nodes::NotEqual"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_NotEqual;
      _to_sql_method_lookup["Arel::Nodes::As"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_As;
      _to_sql_method_lookup["Arel::Nodes::TableAlias"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_TableAlias;
      _to_sql_method_lookup["Arel::Nodes::Between"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Between;
      _to_sql_method_lookup["Arel::Nodes::GreaterThanOrEqual"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_GreaterThanOrEqual;
      _to_sql_method_lookup["Arel::Nodes::GreaterThan"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_GreaterThan;
      _to_sql_method_lookup["Arel::Nodes::LessThanOrEqual"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_LessThanOrEqual;
      _to_sql_method_lookup["Arel::Nodes::LessThan"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_LessThan;
      _to_sql_method_lookup["Arel::Nodes::Matches"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_Matches;
      _to_sql_method_lookup["Arel::Nodes::DoesNotMatch"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_DoesNotMatch;
      _to_sql_method_lookup["Arel::Nodes::UnqualifiedColumn"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_UnqualifiedColumn;
      _to_sql_method_lookup["Arel::Attribute"] = (visitor_method_t)&ToSql::visit_Arel_Attribute;
      _to_sql_method_lookup["Arel::Nodes::SqlLiteral"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_SqlLiteral;
      _to_sql_method_lookup["Arel::Nodes::InfixOperation"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_InfixOperation;
      _to_sql_method_lookup["Arel::Nodes::Addition"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_InfixOperation;
      _to_sql_method_lookup["Arel::Nodes::Subtraction"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_InfixOperation;
      _to_sql_method_lookup["Arel::Nodes::Multiplication"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_InfixOperation;
      _to_sql_method_lookup["Arel::Nodes::Division"] = (visitor_method_t)&ToSql::visit_Arel_Nodes_InfixOperation;
      _to_sql_method_lookup["Array"] = (visitor_method_t)&ToSql::array;
      _to_sql_method_lookup["String"] = (visitor_method_t)&ToSql::quoted;
      _to_sql_method_lookup["literal"] = (visitor_method_t)&ToSql::literal;

//      casted_visitor_method<nodes::SelectStatement *>((casted_visitor_method<nodes::SelectStatement *>::method_t)&ToSql::_visit_Arel_Nodes_SelectStatement);
    }
    return _to_sql_method_lookup;
  }

  ToSql::ToSql(Connection *connection) {
    this->connection = connection ? connection : &_base_connection;
    this->last_column = "";
  }

  std::string ToSql::accept(variant & object) {
    this->last_column = "";
    return Visitor::accept(object);
  }

  std::string ToSql::visit_Arel_Nodes_DeleteStatement(variant & o) {
    nodes::DeleteStatement *node = static_cast<nodes::DeleteStatement *>(*o);

    std::vector<std::string> pieces;
    pieces.push_back("DELETE FROM");
    pieces.push_back(visit(node->relation()));
    if (!node->wheres().empty()) pieces.push_back(format_string("WHERE %s", join_vector(visit_Array(node->wheres()), " AND ").c_str()));

    return join_vector(pieces, " ");
  }

  /*
   # FIXME: we should probably have a 2-pass visitor for this
   def build_subselect key, o
     stmt             = Nodes::SelectStatement.new
     core             = stmt.cores.first
     core.froms       = o.relation
     core.wheres      = o.wheres
     core.projections = [key]
     stmt.limit       = o.limit
     stmt.orders      = o.orders
     stmt
   end
   */
  nodes::SelectStatement ToSql::build_subselect(variant key, variant o) {
    nodes::UpdateStatement *node = static_cast<nodes::UpdateStatement *>(*o);
    nodes::SelectStatement stmt;
    nodes::SelectCore *core = static_cast<nodes::SelectCore *>(*stmt.cores.front());
    core->set_from(node->relation);
    core->wheres = node->wheres;
    std::vector<variant> p;
    p.push_back(key);
    core->projections = p;
    stmt.limit = node->limit;
    stmt.orders = node->orders;
    return stmt;
  }

  std::string ToSql::visit_Arel_Nodes_UpdateStatement(variant & o) {
    nodes::UpdateStatement *node = static_cast<nodes::UpdateStatement *>(*o);

    std::vector<variant> wheres;
    if (node->orders.empty() && !node->limit)
      wheres = node->wheres;
    else {
      std::vector<variant> sub;
      sub.push_back(build_subselect(node->key, o));
      wheres.push_back(nodes::In(node->key, sub));
    }

    std::vector<std::string> pieces;
    pieces.push_back("UPDATE");
    pieces.push_back(visit(node->relation));
    if (!node->values.empty()) pieces.push_back(format_string("SET %s", join_vector(visit_Array(node->values), ", ").c_str()));
    if (!wheres.empty()) pieces.push_back(format_string("WHERE %s", join_vector(visit_Array(wheres), " AND ").c_str()));

    return join_vector(pieces, " ");
  }


  std::string ToSql::visit_Arel_Nodes_InsertStatement(variant & o) {
    nodes::InsertStatement *node = static_cast<nodes::InsertStatement *>(*o);

    std::vector<std::string> pieces;
    pieces.push_back("INSERT INTO");
    pieces.push_back(visit(node->relation));
    if (!node->columns.empty()) {
      std::vector<std::string> column_names;
      for (std::vector<variant>::iterator it=node->columns.begin(); it!=node->columns.end(); ++it)
        column_names.push_back(quote_column_name(static_cast<Attribute *>(**it)->name));
      pieces.push_back(format_string("(%s)", join_vector(column_names, ", ").c_str()));
    }
    if (!!node->values)
      pieces.push_back(visit(node->values));

    return join_vector(pieces, " ");
  }

  std::string ToSql::visit_Arel_Nodes_Exists(variant & o) {
    nodes::Exists *node = static_cast<nodes::Exists *>(*o);
    std::string alias = !!node->alias ? format_string(" AS %s", visit(node->alias).c_str()) : "";
    return format_string("EXISTS (%s)%s", visit(node->expressions).c_str(), alias.c_str());
  }

  std::string ToSql::visit_Arel_Nodes_SelectStatement(variant & o) {
    nodes::SelectStatement *node = static_cast<nodes::SelectStatement *>(*o);

    std::vector<std::string> pieces;

    //     (visit(o.with) if o.with),
    if (!!node->with) pieces.push_back(visit(node->with));
    //     o.cores.map { |x| visit_Arel_Nodes_SelectCore x }.join,
    std::vector<variant>::iterator it;
    for (it=node->cores.begin(); it!=node->cores.end(); ++it) {
      pieces.push_back(visit_Arel_Nodes_SelectCore(*it));
    }
//    ("ORDER BY #{o.orders.map { |x| visit x }.join(', ')}" unless o.orders.empty?),
    if (!node->orders.empty()) pieces.push_back(format_string("ORDER BY %s", join_vector(visit_Array(node->orders), ", ").c_str()));
    //     (visit(o.limit) if o.limit),
    if (!!node->limit) pieces.push_back(visit(node->limit));
    //     (visit(o.offset) if o.offset),
    if (!!node->offset) pieces.push_back(visit(node->offset));
    //     (visit(o.lock) if o.lock),

    return join_vector(pieces, " ");
  }

  std::string ToSql::visit_Arel_Nodes_SelectCore(variant & o) {
    nodes::SelectCore *node = static_cast<nodes::SelectCore *>(*o);

    std::vector<std::string> pieces;
    std::vector<variant>::iterator wIt;

    pieces.push_back("SELECT");
    if (!!node->top) pieces.push_back(visit(node->top));
    if (!!node->set_quantifier) pieces.push_back(visit(node->set_quantifier));
    if (!node->projections.empty()) pieces.push_back(join_vector(visit_Array(node->projections), ", "));

    if (!!node->source) {
      nodes::JoinSource *nodeSource = static_cast<nodes::JoinSource *>(*node->source);
      if (!nodeSource->isEmpty())
        pieces.push_back(format_string("FROM %s", visit(node->source).c_str()));
    }

    if (!node->wheres.empty()) pieces.push_back(format_string("WHERE %s", join_vector(visit_Array(node->wheres), " AND ").c_str()));
    if (!node->groups.empty()) pieces.push_back(format_string("GROUP BY %s", join_vector(visit_Array(node->groups), ", ").c_str()));
    if (!!node->having) pieces.push_back(visit(node->having));

    return join_vector(pieces, " ");
  }

  std::string ToSql::visit_Arel_Nodes_Values(variant & o) {
    nodes::Values *node = static_cast<nodes::Values *>(*o);
    std::vector<variant> zipped = zip_vector(node->expressions(), node->columns());
    std::vector<std::string> vals;
    for (std::vector<variant>::iterator it=zipped.begin(); it!=zipped.end(); ++it) {
      std::vector<variant> *v = static_cast<std::vector<variant> *>(**it);
      variant value = v->at(0);
      variant attr = v->at(1);
      if (value.isType<nodes::SqlLiteral>())
        vals.push_back(visit_Arel_Nodes_SqlLiteral(value));
      else
        vals.push_back(quote(value, !!attr ? column_for(attr) : NULL));
    }
    return format_string("VALUES (%s)", join_vector(vals, ", ").c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Bin(variant & o) {
    nodes::Bin *node = static_cast<nodes::Bin *>(*o);
    return visit(node->expr);
  }

  std::string ToSql::visit_Arel_Nodes_Distinct(variant & o) {
    return "DISTINCT";
  }

  std::string ToSql::visit_Arel_Nodes_With(variant & o) {
    nodes::With *node = static_cast<nodes::With *>(*o);
    return format_string("WITH %s", join_vector(visit_Array(node->children()), ", ").c_str());
  }

  std::string ToSql::visit_Arel_Nodes_WithRecursive(variant & o) {
    nodes::WithRecursive *node = static_cast<nodes::WithRecursive *>(*o);
    return format_string("WITH RECURSIVE %s", join_vector(visit_Array(node->children()), ", ").c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Union(variant & o) {
    nodes::Union *node = (nodes::Union *)*o;
    return format_string("(%s UNION %s)", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_UnionAll(variant & o) {
    nodes::UnionAll *node = (nodes::UnionAll *)*o;
    return format_string("(%s UNION ALL %s)", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Intersect(variant & o) {
    nodes::Intersect *node = (nodes::Intersect *)*o;
    return format_string("(%s INTERSECT %s)", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Except(variant & o) {
    nodes::Except *node = (nodes::Except *)*o;
    return format_string("(%s EXCEPT %s)", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Having(variant & o) {
    nodes::Having *node = (nodes::Having *)*o;
    return format_string("HAVING %s", visit(node->expr).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Offset(variant & o) {
    nodes::Offset *node = (nodes::Offset *)*o;
    return format_string("OFFSET %s", visit(node->expr).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Limit(variant & o) {
    nodes::Limit *node = (nodes::Limit *)*o;
    return format_string("LIMIT %s", visit(node->expr).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Top(variant & o) {
    return "";
  }

  std::string ToSql::visit_Arel_Nodes_Ascending(variant & o) {
    nodes::Ascending *node = (nodes::Ascending *)*o;
    return format_string("%s ASC", visit(node->expr).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Descending(variant & o) {
    nodes::Descending *node = (nodes::Descending *)*o;
    return format_string("%s DESC", visit(node->expr).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Grouping(variant & o) {
    nodes::Grouping *node = (nodes::Grouping *)*o;
    return format_string("(%s)", visit(node->expr).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Group(variant & o) {
    nodes::Group *node = (nodes::Group *)*o;
    return visit(node->expr);
  }

  std::string ToSql::visit_Arel_Nodes_NamedFunction(variant & o) {
    nodes::NamedFunction *node = (nodes::NamedFunction *)*o;
    std::vector<variant> *e = static_cast<std::vector<variant> *>(*node->expressions);
    std::string exprs = join_vector(visit_Array(*e), ", ");
    std::string alias = !!node->alias ? format_string(" AS %s", visit(node->alias).c_str()) : "";
    return format_string("%s(%s%s)%s", node->name.toString(), !!node->distinct ? "DISTINCT " : "", exprs.c_str(), alias.c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Count(variant & o) {
    nodes::Count *node = (nodes::Count *)*o;
    std::vector<variant> *a = static_cast<std::vector<variant> *>(*node->expressions);
    std::string exprs = join_vector(visit_Array(*a), ", ");
    std::string alias = !!node->alias ? format_string(" AS %s", visit(node->alias).c_str()) : "";
    return format_string("COUNT(%s%s)%s", node->distinct ? "DISTINCT " : "", exprs.c_str(), alias.c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Sum(variant & o) {
    nodes::Sum *node = (nodes::Sum *)*o;
    std::vector<variant> *a = static_cast<std::vector<variant> *>(*node->expressions);
    std::string exprs = join_vector(visit_Array(*a), ", ");
    std::string alias = !!node->alias ? format_string(" AS %s", visit(node->alias).c_str()) : "";
    return format_string("SUM(%s)%s", exprs.c_str(), alias.c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Max(variant & o) {
    nodes::Max *node = (nodes::Max *)*o;
    std::vector<variant> *a = static_cast<std::vector<variant> *>(*node->expressions);
    std::string exprs = join_vector(visit_Array(*a), ", ");
    std::string alias = !!node->alias ? format_string(" AS %s", visit(node->alias).c_str()) : "";
    return format_string("MAX(%s)%s", exprs.c_str(), alias.c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Min(variant & o) {
    nodes::Min *node = (nodes::Min *)*o;
    std::vector<variant> *a = static_cast<std::vector<variant> *>(*node->expressions);
    std::string exprs = join_vector(visit_Array(*a), ", ");
    std::string alias = !!node->alias ? format_string(" AS %s", visit(node->alias).c_str()) : "";
    return format_string("MIN(%s)%s", exprs.c_str(), alias.c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Avg(variant & o) {
    nodes::Avg *node = (nodes::Avg *)*o;
    std::vector<variant> *a = static_cast<std::vector<variant> *>(*node->expressions);
    std::string exprs = join_vector(visit_Array(*a), ", ");
    std::string alias = !!node->alias ? format_string(" AS %s", visit(node->alias).c_str()) : "";
    return format_string("AVG(%s)%s", exprs.c_str(), alias.c_str());
  }

  std::string ToSql::visit_Arel_Nodes_TableAlias(variant & o) {
    nodes::TableAlias *node = (nodes::TableAlias *)*o;
    std::string relation = visit(node->relation());
    std::string table_name = quote_table_name(node->name());
    return format_string("%s %s", relation.c_str(), table_name.c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Between(variant & o) {
    nodes::Between *node = (nodes::Between *)*o;
    return format_string("%s BETWEEN %s", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_GreaterThanOrEqual(variant & o) {
    nodes::GreaterThanOrEqual *node = (nodes::GreaterThanOrEqual *)*o;
    return format_string("%s >= %s", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_GreaterThan(variant & o) {
    nodes::GreaterThan *node = (nodes::GreaterThan *)*o;
    return format_string("%s > %s", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_LessThanOrEqual(variant & o) {
    nodes::LessThanOrEqual *node = (nodes::LessThanOrEqual *)*o;
    return format_string("%s <= %s", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_LessThan(variant & o) {
    nodes::LessThan *node = (nodes::LessThan *)*o;
    return format_string("%s < %s", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Matches(variant & o) {
    nodes::Matches *node = (nodes::Matches *)*o;
    return format_string("%s LIKE %s", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_DoesNotMatch(variant & o) {
    nodes::DoesNotMatch *node = (nodes::DoesNotMatch *)*o;
    return format_string("%s NOT LIKE %s", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_JoinSource(variant & o) {
    nodes::JoinSource *node = static_cast<nodes::JoinSource *>(*o);

    std::vector<std::string> pieces;
    if (!!node->left)
      pieces.push_back(visit(node->left));
    std::vector<variant> right_nodes = node->right;
    for (std::vector<variant>::iterator it=right_nodes.begin(); it!=right_nodes.end(); ++it)
      pieces.push_back(visit(*it));
    return join_vector(pieces, " ");
  }

  std::string ToSql::visit_Arel_Nodes_StringJoin(variant & o) {
    nodes::StringJoin *node = static_cast<nodes::StringJoin *>(*o);
    return visit(node->left);
  }

  std::string ToSql::visit_Arel_Nodes_OuterJoin(variant & o) {
    nodes::OuterJoin *node = static_cast<nodes::OuterJoin *>(*o);
    return format_string("LEFT OUTER JOIN %s %s", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_InnerJoin(variant & o) {
    nodes::InnerJoin *node = static_cast<nodes::InnerJoin *>(*o);
    return format_string("INNER JOIN %s %s", visit(node->left).c_str(), !!node->right ? visit(node->right).c_str() : "");
  }

  std::string ToSql::visit_Arel_Nodes_On(variant & o) {
    nodes::On *node = static_cast<nodes::On *>(*o);
    return format_string("ON %s", visit(node->expr).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Not(variant & o) {
    nodes::Not *node = static_cast<nodes::Not *>(*o);
    return format_string("NOT (%s)", visit(node->expr).c_str());
  }

  std::string ToSql::visit_Arel_Table(variant & o) {
    Table *table = static_cast<Table *>(*o);
    return !!table->table_alias ? format_string("%s %s", quote_table_name(table->name).c_str(), quote_table_name(table->table_alias).c_str()) : quote_table_name(table->name);
  }

  std::string ToSql::visit_Arel_Nodes_In(variant & o) {
    nodes::In *node = static_cast<nodes::In *>(*o);
    return format_string("%s IN (%s)", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_NotIn(variant & o) {
    nodes::In *node = static_cast<nodes::In *>(*o);
    return format_string("%s NOT IN (%s)", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_And(variant & o) {
    nodes::And *node = static_cast<nodes::And *>(*o);
    std::vector<std::string> pieces;
    for (std::vector<variant>::iterator wIt=node->children.begin(); wIt!=node->children.end(); ++wIt) {
      pieces.push_back(visit(*wIt));
    }
    return join_vector(pieces, " AND ");
  }

  std::string ToSql::visit_Arel_Nodes_Or(variant & o) {
    nodes::Or *node = static_cast<nodes::Or *>(*o);
    return format_string("%s OR %s", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Assignment(variant & o) {
    nodes::Assignment *node = static_cast<nodes::Assignment *>(*o);
    return format_string("%s = %s", visit(node->left).c_str(), quote(node->right, column_for(node->left)).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_Equality(variant & o) {
    nodes::Equality *node = static_cast<nodes::Equality *>(*o);

    std::string left = visit(node->left);

    if (!node->right)
      return left + " IS NULL";
    else
      return format_string("%s = %s", left.c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_NotEqual(variant & o) {
    nodes::NotEqual *node = static_cast<nodes::NotEqual *>(*o);

    if (!node->right)
      return format_string("%s IS NULL", visit(node->left).c_str());
    else
      return format_string("%s != %s", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_As(variant & o) {
    nodes::As *node = static_cast<nodes::As *>(*o);
    return format_string("%s AS %s", visit(node->left).c_str(), visit(node->right).c_str());
  }

  std::string ToSql::visit_Arel_Nodes_UnqualifiedColumn(variant & o) {
    nodes::UnqualifiedColumn *node = static_cast<nodes::UnqualifiedColumn *>(*o);
    return quote_column_name(node->name());
  }

  std::string ToSql::visit_Arel_Attribute(variant & o) {
    Attribute *attribute = (Attribute *)*o;

    last_column = column_for(o);
    std::string join_name;

    if (attribute->relation.isType<nodes::TableAlias>())
      join_name = ((nodes::TableAlias *)*attribute->relation)->table_alias().toString();
    else
      join_name = ((Table *)*attribute->relation)->name;

    return format_string("%s.%s", quote_table_name(join_name).c_str(), quote_column_name(attribute->name).c_str());
  }
//  alias :visit_Arel_Attributes_Integer :visit_Arel_Attributes_Attribute
//  alias :visit_Arel_Attributes_Float :visit_Arel_Attributes_Attribute
//  alias :visit_Arel_Attributes_Decimal :visit_Arel_Attributes_Attribute
//  alias :visit_Arel_Attributes_String :visit_Arel_Attributes_Attribute
//  alias :visit_Arel_Attributes_Time :visit_Arel_Attributes_Attribute
//  alias :visit_Arel_Attributes_Boolean :visit_Arel_Attributes_Attribute

  std::string ToSql::visit_Arel_Nodes_SqlLiteral(variant & o) {
    nodes::SqlLiteral *l = (nodes::SqlLiteral *)*o;
    return literal(l->value);
  }

  std::string ToSql::literal(variant & o) {
    if (o.isString()) {
      return o.toString();
    }
    else {
      // TODO: Better way to convert from numbers?
      std::string as_number = number_variant_to_string(o);
      if (as_number.size() != 0)
        return as_number;

      if (o.isType<bool>()) {
        if ((bool)o)
          return "TRUE";
        else
          return "FALSE";
      }
      else {
        printf("unsupported type: %s\n", o.type().name());
        throw std::bad_cast();
      }
    }
  }
  /*
   alias :visit_Arel_Nodes_SqlLiteral :literal
   alias :visit_Arel_SqlLiteral       :literal # This is deprecated
   alias :visit_Bignum                :literal
   alias :visit_Fixnum                :literal
   */

  std::string ToSql::quoted(variant o) {
    return quote(o, last_column);
  }

//  alias :visit_ActiveSupport_Multibyte_Chars :quoted
//  alias :visit_ActiveSupport_StringInquirer  :quoted
//  alias :visit_BigDecimal                    :quoted
//  alias :visit_Class                         :quoted
//  alias :visit_Date                          :quoted
//  alias :visit_DateTime                      :quoted
//  alias :visit_FalseClass                    :quoted
//  alias :visit_Float                         :quoted
//  alias :visit_Hash                          :quoted
//  alias :visit_NilClass                      :quoted
//  alias :visit_String                        :quoted
//  alias :visit_Symbol                        :quoted
//  alias :visit_Time                          :quoted
//  alias :visit_TrueClass                     :quoted


  std::string ToSql::visit_Arel_Nodes_InfixOperation(variant & o) {
    nodes::InfixOperation *node = static_cast<nodes::InfixOperation *>(*o);
    return format_string("%s %s %s", visit(node->left).c_str(), node->op.c_str(), visit(node->right).c_str());
  }

  std::vector<std::string> ToSql::visit_Array(std::vector<variant> & o) {
    std::vector<variant> a = o;
    std::vector<std::string> pieces;
    for (std::vector<variant>::iterator wIt=a.begin(); wIt!=a.end(); ++wIt) {
      pieces.push_back(visit(*wIt));
    }
    return pieces;
  }

  std::string ToSql::array(variant & o) {
    std::vector<variant> a = o;
    std::vector<std::string> pieces = visit_Array(a);
    return pieces.empty() ? "NULL" : join_vector(pieces, ", ");
  }

  bool ToSql::table_exists(const char *name) {
    return true;
  }

  std::string ToSql::column_for(variant o) {
    // TODO
    //name    = attr.name.to_s
    //table   = attr.relation.table_name
    //
    //return nil unless table_exists? table
    //
    //column_cache[table][name]
//    def column_cache
//    @schema_cache.columns_hash
//    end
    return "";
  }


  std::string ToSql::quote(variant value) {
    return quote(value, last_column);
  }

  std::string ToSql::quote(variant value, variant column) {
    // TODO: most/all this logic should move to the connection?

    if (!value) {
      return "NULL";
    }

    // TODO: Better way to convert from numbers?
    std::string as_number = number_variant_to_string(value);
    if (as_number.size() != 0)
      return as_number;

    if (value.isType<bool>()) {
      if ((bool)value)
        return "TRUE";
      else
        return "FALSE";
    }
    if (value.isType<nodes::SqlLiteral>())
      value = static_cast<nodes::SqlLiteral *>(*value)->value;

    return connection->quote(value.toString());
  }

  std::string ToSql::quote_table_name(variant name) {
    if (name.isType<nodes::SqlLiteral>())
      return static_cast<nodes::SqlLiteral *>(*name)->value.toString();

    return connection->quote_table_name(name.toString());
  }

  std::string ToSql::quote_column_name(variant name) {
    if (name.isType<nodes::SqlLiteral>())
      name = static_cast<nodes::SqlLiteral *>(*name)->value;

    return connection->quote_column_name(name.toString());
  }
}