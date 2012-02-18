#include "test_lib.h"

using namespace c_arel;

TEST_SUITE(table, "table", {
  DESCRIBE("skip", {
    IT("should add an offset", {
      Table relation = c_arel::Table("users");
      SelectManager sm = relation.skip(2);
      assert_equal(sm.to_sql(), "SELECT FROM users OFFSET 2");
    })
  })

  DESCRIBE("having", {
    IT("adds a having caluse", {
      Table relation = c_arel::Table("users");
      SelectManager sm = relation.having(relation["id"].equal(10));
      assert_equal(sm.to_sql(), "SELECT FROM users HAVING users.id = 10");
    })
  })

  DESCRIBE("backwards compat", {
    IT("join noops on null", {
      Table relation = c_arel::Table("users");
      SelectManager sm = relation.join(NULL);
      assert_equal(sm.to_sql(), "SELECT FROM users");
    })

    IT("takes a second argument for join type", {
      Table relation = c_arel::Table("users");
      nodes::TableAlias right = relation.alias();
      nodes::Equality predicate = relation["id"].equal(right["id"]);
      SelectManager mgr = relation.join<nodes::OuterJoin>(right).on(predicate);
      assert_equal(mgr.to_sql(), "SELECT FROM users LEFT OUTER JOIN users users_2 ON users.id = users_2.id");
    })
  })

  DESCRIBE("group", {
    IT("should create a group", {
      Table relation = c_arel::Table("users");
      SelectManager mgr = relation.group(relation["id"]);
      assert_equal(mgr.to_sql(), "SELECT FROM users GROUP BY users.id");
    })
  })

  DESCRIBE("order", {
    IT("should take an order", {
      Table relation = c_arel::Table("users");
      SelectManager mgr = relation.order("foo");
      assert_equal(mgr.to_sql(), "SELECT FROM users ORDER BY \"foo\"");
    })
  })

  DESCRIBE("take", {
    IT("should add a limit", {
      Table relation = c_arel::Table("users");
      SelectManager mgr = relation.take(1).project("*");
      assert_equal(mgr.to_sql(), "SELECT * FROM users LIMIT 1");
    })
  })

  DESCRIBE("project", {
    IT("can project", {
      Table relation = c_arel::Table("users");
      SelectManager mgr = relation.project(nodes::SqlLiteral("*"));
      assert_equal(mgr.to_sql(), "SELECT * FROM users");
    })

    IT("takes an array of parameters", {
      Table relation = c_arel::Table("users");
      std::vector<variant> list;
      list.push_back(nodes::SqlLiteral("*"));
      list.push_back(nodes::SqlLiteral("*"));
      SelectManager mgr = relation.project(list);
      assert_equal(mgr.to_sql(), "SELECT *, * FROM users");
    })
  })

  DESCRIBE("where", {
    IT("returns a tree manager", {
      Table relation = c_arel::Table("users");
      SelectManager mgr = relation.where(relation["id"].equal(1));
      mgr.project(relation["id"]);
      assert_equal(mgr.to_sql(), "SELECT users.id FROM users WHERE users.id = 1");
    })
  })

  IT("should have a name", {
    Table relation = c_arel::Table("users");
    assert_equal(relation.name.c_str(), "users");
  })
})
