/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_to_sql_h
#define include_c_arel_to_sql_h
namespace c_arel {
  namespace nodes {
    class SelectStatement;
  }
  
  class ToSql : public Visitor {
  public:
    ToSql(variant connection);
    
    virtual std::string accept(variant & object);
    
  protected:

    virtual std::string visit_Arel_Nodes_DeleteStatement(variant & o);
    virtual nodes::SelectStatement build_subselect(variant key, variant o);
    virtual std::string visit_Arel_Nodes_UpdateStatement(variant & o);
    virtual std::string visit_Arel_Nodes_InsertStatement(variant & o);
    virtual std::string visit_Arel_Nodes_Exists(variant & o);
    virtual std::string visit_Arel_Nodes_SelectStatement(variant & o);
    virtual std::string visit_Arel_Nodes_SelectCore(variant & o);
    virtual std::string visit_Arel_Nodes_Values(variant & o);
    virtual std::string visit_Arel_Nodes_Bin(variant & o);
    virtual std::string visit_Arel_Nodes_Distinct(variant & o);
     
    /*
     def visit_Arel_Nodes_DistinctOn o
       raise NotImplementedError, 'DISTINCT ON not implemented for this db'
     end
     */
    virtual std::string visit_Arel_Nodes_With(variant & o);
    virtual std::string visit_Arel_Nodes_WithRecursive(variant & o);
    
    virtual std::string visit_Arel_Nodes_Union(variant & o);
    virtual std::string visit_Arel_Nodes_UnionAll(variant & o);
    virtual std::string visit_Arel_Nodes_Intersect(variant & o);
    virtual std::string visit_Arel_Nodes_Except(variant & o);
    
    virtual std::string visit_Arel_Nodes_Having(variant & o);
    virtual std::string visit_Arel_Nodes_Offset(variant & o);
    virtual std::string visit_Arel_Nodes_Limit(variant & o);
    virtual std::string visit_Arel_Nodes_Top(variant & o);

    /*
     def visit_Arel_Nodes_Lock o
     visit o.expr
     end
     */
    
    virtual std::string visit_Arel_Nodes_Ascending(variant & o);
    virtual std::string visit_Arel_Nodes_Descending(variant & o);
    virtual std::string visit_Arel_Nodes_Grouping(variant & o);
    virtual std::string visit_Arel_Nodes_Group(variant & o);
    virtual std::string visit_Arel_Nodes_NamedFunction(variant & o);
    virtual std::string visit_Arel_Nodes_Count(variant & o);
    virtual std::string visit_Arel_Nodes_Sum(variant & o);
    virtual std::string visit_Arel_Nodes_Max(variant & o);
    virtual std::string visit_Arel_Nodes_Min(variant & o);
    virtual std::string visit_Arel_Nodes_Avg(variant & o);
    virtual std::string visit_Arel_Nodes_TableAlias(variant & o);
    virtual std::string visit_Arel_Nodes_Between(variant & o);
    virtual std::string visit_Arel_Nodes_GreaterThanOrEqual(variant & o);
    virtual std::string visit_Arel_Nodes_GreaterThan(variant & o);
    virtual std::string visit_Arel_Nodes_LessThanOrEqual(variant & o);
    virtual std::string visit_Arel_Nodes_LessThan(variant & o);
    virtual std::string visit_Arel_Nodes_Matches(variant & o);
    virtual std::string visit_Arel_Nodes_DoesNotMatch(variant & o);
    virtual std::string visit_Arel_Nodes_JoinSource(variant & o);
    virtual std::string visit_Arel_Nodes_StringJoin(variant & o);
    virtual std::string visit_Arel_Nodes_OuterJoin(variant & o);
    virtual std::string visit_Arel_Nodes_InnerJoin(variant & o);
    virtual std::string visit_Arel_Nodes_On(variant & o);
    virtual std::string visit_Arel_Nodes_Not(variant & o);
    virtual std::string visit_Arel_Table(variant & o);
    virtual std::string visit_Arel_Nodes_In(variant & o);
    virtual std::string visit_Arel_Nodes_NotIn(variant & o);
    virtual std::string visit_Arel_Nodes_And(variant & o);     
    virtual std::string visit_Arel_Nodes_Or(variant & o);
    virtual std::string visit_Arel_Nodes_Assignment(variant & o);
    virtual std::string visit_Arel_Nodes_Equality(variant & o);
    virtual std::string visit_Arel_Nodes_NotEqual(variant & o);
    virtual std::string visit_Arel_Nodes_As(variant & o);
    virtual std::string visit_Arel_Nodes_UnqualifiedColumn(variant & o);
    virtual std::string visit_Arel_Attribute(variant & o);
    virtual std::string visit_Arel_Nodes_SqlLiteral(variant & o);
    virtual std::string literal(variant & o);
    virtual std::string visit_Arel_Nodes_InfixOperation(variant & o);
    virtual std::vector<std::string> visit_Array(std::vector<variant> & o);
    virtual std::string array(variant & o);

    virtual bool table_exists(const char *name);
    virtual std::string column_for(variant o);
    virtual std::string quoted(variant o);
    virtual std::string quote(variant value);
    virtual std::string quote(variant value, variant column);
    virtual std::string quote_table_name(variant name);
    virtual std::string quote_column_name(variant name);

    std::string last_column;

    // TODO: lame method lookup - probably could be cleaned up...
  public:
    method_dict_map_t & method_dictionary(void);
    static method_dict_map_t _to_sql_method_lookup;
  };
}
#endif
