#include "test_lib.h"

using namespace c_arel;

BEGIN_TEST(skip_should_add_an_offset, "skip should add an offset")
  Table relation = c_arel::Table("users");
  SelectManager sm = relation.skip(2);
  must_be_like(sm.to_sql(), "SELECT FROM users OFFSET 2");
END_TEST

BEGIN_TEST(having_adds_a_having_clause, "having adds a having clause")
  Table relation = c_arel::Table("users");
  SelectManager sm = relation.having(relation["id"].equal(10));
  must_be_like(sm.to_sql(), "SELECT FROM users HAVING users.id = 10");
END_TEST

BEGIN_TEST(backwards_compat_join_noops_on_null, "backwards compat join noops on null")
  Table relation = c_arel::Table("users");
  SelectManager sm = relation.join(NULL);
  must_be_like(sm.to_sql(), "SELECT FROM users");
END_TEST

BEGIN_TEST(backwards_compat_takes_a_second_argument_for_join_type, "takes a second argument for join type")
  Table relation = c_arel::Table("users");
  nodes::TableAlias right = relation.alias();
  nodes::Equality predicate = relation["id"].equal(right["id"]);
  SelectManager mgr = relation.join<nodes::OuterJoin>(right).on(predicate);
  must_be_like(mgr.to_sql(), "SELECT FROM users LEFT OUTER JOIN users users_2 ON users.id = users_2.id");
END_TEST

BEGIN_TEST(group_should_create_a_group, "group should create a group")
  Table relation = c_arel::Table("users");
  SelectManager mgr = relation.group(relation["id"]);
  must_be_like(mgr.to_sql(), "SELECT FROM users GROUP BY users.id");
END_TEST

BEGIN_TEST(order_should_take_an_order, "order should take an order")
  Table relation = c_arel::Table("users");
  SelectManager mgr = relation.order("foo");
  must_be_like(mgr.to_sql(), "SELECT FROM users ORDER BY \"foo\"");
END_TEST

BEGIN_TEST(take_should_add_a_limit, "take should add a limit")
  Table relation = c_arel::Table("users");
  SelectManager mgr = relation.take(1).project("*");
  must_be_like(mgr.to_sql(), "SELECT * FROM users LIMIT 1");
END_TEST

BEGIN_TEST(project_can_project, "project can project")
  Table relation = c_arel::Table("users");
  SelectManager mgr = relation.project(nodes::SqlLiteral("*"));
  must_be_like(mgr.to_sql(), "SELECT * FROM users");
END_TEST

BEGIN_TEST(project_takes_an_array_of_parameters, "project takes an array of parameters")
  Table relation = c_arel::Table("users");
  std::vector<variant> list;
  list.push_back(nodes::SqlLiteral("*"));
  list.push_back(nodes::SqlLiteral("*"));
  SelectManager mgr = relation.project(list);
  must_be_like(mgr.to_sql(), "SELECT *, * FROM users");
END_TEST

BEGIN_TEST(where_returns_a_tree_manager, "where returns a tree manager")
  Table relation = c_arel::Table("users");
  SelectManager mgr = relation.where(relation["id"].equal(1));
  mgr.project(relation["id"]);
  must_be_like(mgr.to_sql(), "SELECT users.id FROM users WHERE users.id = 1");
END_TEST

BEGIN_TEST(table_should_have_a_name, "table should have a name")
  Table relation = c_arel::Table("users");
  must_be_like(relation.name.c_str(), "users");
END_TEST

BEGIN_SUITE(table)
  ADD_TEST(skip_should_add_an_offset);
  ADD_TEST(having_adds_a_having_clause);
  ADD_TEST(backwards_compat_join_noops_on_null);
  ADD_TEST(backwards_compat_takes_a_second_argument_for_join_type);
  ADD_TEST(group_should_create_a_group);
  ADD_TEST(order_should_take_an_order);
  ADD_TEST(take_should_add_a_limit);
  ADD_TEST(project_can_project);
  ADD_TEST(project_takes_an_array_of_parameters);
  ADD_TEST(where_returns_a_tree_manager);
  ADD_TEST(table_should_have_a_name);
END_SUITE
