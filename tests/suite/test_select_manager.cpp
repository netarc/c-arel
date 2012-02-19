#include "test_lib.h"

using namespace c_arel;

TEST_SUITE(select_manager, "select manager", {
  DESCRIBE("backwards compatibility", {
    DESCRIBE("as", {
      IT("makes an AS node by grouping the AST", {
        SelectManager sm = SelectManager(NULL);
        nodes::TableAlias as = sm.as("foo");
        assert_true(as.left.isType<nodes::Grouping>());
        assert_true(sm.ast.type() == static_cast<nodes::Grouping *>(*as.left)->expr.type());
        assert_equal("foo", static_cast<nodes::SqlLiteral *>(*as.right)->value);
      })

      IT("converts right to SqlLiteral if a string", {
        SelectManager sm = SelectManager(NULL);
        nodes::TableAlias as = sm.as("foo");
        assert_true(as.right.isType<nodes::SqlLiteral>());
      })

      IT("can make a subselect", {
        SelectManager sm = SelectManager(NULL);
        sm.project("*");
        sm.from("zomg");
        nodes::TableAlias as = sm.as("foo");
        
        sm = SelectManager(NULL);
        sm.project("name");
        sm.from(as);
        assert_equal("SELECT name FROM (SELECT * FROM zomg) foo", sm.to_sql());
      })
    }) // as

    DESCRIBE("from", {
      IT("ignores strings when table of same name exists", {
        Table table = c_arel::Table("users");
        SelectManager sm = SelectManager(NULL);

        sm.from(table);
        sm.from("users");
        sm.project(table["id"]);

        assert_equal("SELECT users.id FROM users", sm.to_sql());
      })

      IT("should support any ast", {
        Table table = c_arel::Table("users");
        SelectManager manager1 = SelectManager(NULL);

        SelectManager manager2 = SelectManager(NULL);
        manager2.project("*");
        manager2.from(table);

        manager1.project("lol");
        nodes::TableAlias as = manager2.as("omg");
        manager1.from(as);

        assert_equal("SELECT lol FROM (SELECT * FROM users) omg", manager1.to_sql());
      })
    })

    DESCRIBE("having", {
      IT("does not convert strings to SQLLiterals", {
        Table table = c_arel::Table("users");
        SelectManager manager = table.from(table);
        manager.having("foo");
        assert_equal("SELECT FROM users HAVING \"foo\"", manager.to_sql());
      })

      IT("can have multiple items specified separately", {
        Table table = c_arel::Table("users");
        SelectManager manager = table.from(table);
        manager.having("foo");
        manager.having("bar");
        assert_equal("SELECT FROM users HAVING \"foo\" AND \"bar\"", manager.to_sql());
      })

      IT("can have an array of items specified", {
        Table table = c_arel::Table("users");
        SelectManager manager = table.from(table);
        std::vector<variant> haves;
        haves.push_back("foo");
        haves.push_back("bar");
        manager.having(haves);
        assert_equal("SELECT FROM users HAVING \"foo\" AND \"bar\"", manager.to_sql());
      })
    })

    DESCRIBE("on", {
      IT("does not convert string to SQLLiterals", {
        Table table = c_arel::Table("users");
        nodes::TableAlias right = table.alias();
        SelectManager manager = table.from(table);
        manager.join(right).on("omg");
        assert_equal("SELECT FROM users INNER JOIN users users_2 ON \"omg\"", manager.to_sql());
      })

      IT("does not convert strings to SQLLiterals", {
        Table table = c_arel::Table("users");
        nodes::TableAlias right = table.alias();
        SelectManager manager = table.from(table);
        std::vector<variant> ons;
        ons.push_back("foo");
        ons.push_back("bar");
        manager.join(right).on(ons);
        assert_equal("SELECT FROM users INNER JOIN users users_2 ON \"foo\" AND \"bar\"", manager.to_sql());
      })
    })

    DESCRIBE("skip", {
      IT("should add an offset", {
        Table table = c_arel::Table("users");
        SelectManager manager = table.from(table);
        manager.skip(10);
        assert_equal("SELECT FROM users OFFSET 10", manager.to_sql());
      })

      IT("should chain", {
        Table table = c_arel::Table("users");
        assert_equal("SELECT FROM users OFFSET 10", table.from(table).skip(10).to_sql());
      })
    })

    DESCRIBE("offset", {
      IT("should add an offset", {
        Table table = c_arel::Table("users");
        SelectManager manager = table.from(table);
        manager.offset(10);
        assert_equal("SELECT FROM users OFFSET 10", manager.to_sql());
      })

      IT("should remove an offset", {
        Table table = c_arel::Table("users");
        SelectManager manager = table.from(table);
        manager.offset(10);
        assert_equal("SELECT FROM users OFFSET 10", manager.to_sql());

        manager.offset(NULL);
        assert_equal("SELECT FROM users", manager.to_sql());
      })

      IT("should return the offset", {
        Table table = c_arel::Table("users");
        SelectManager manager = table.from(table);
        manager.offset(10);
        assert_equal(10, manager.offset());
      })
    })

    DESCRIBE("exists", {
      
    })

  }) // backwards compatibility
}) // select manager