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
  }) // backwards compatibility


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
    IT("should create an exists clause", {
      Table table = c_arel::Table("users");
      SelectManager manager = table.from(table);
      manager.project("*");
      SelectManager m2 = SelectManager(NULL);
      m2.project(manager.exists());

      char tmp[1024];
      sprintf(tmp, "SELECT EXISTS (%s)", manager.to_sql());
      assert_equal(tmp, m2.to_sql());
    })

    IT("can be aliased", {
      Table table = c_arel::Table("users");
      SelectManager manager = table.from(table);
      manager.project("*");
      SelectManager m2 = SelectManager(NULL);
      m2.project(manager.exists().as("foo"));

      char tmp[1024];
      sprintf(tmp, "SELECT EXISTS (%s) AS foo", manager.to_sql());
      assert_equal(tmp, m2.to_sql());
    })
  })

  DESCRIBE("union", {
    IT("should union two managers", {
      Table table = c_arel::Table("users");
      SelectManager m1 = table.from(table);
      m1.project("*");
      m1.where(table["age"].lt(18));
      SelectManager m2 = table.from(table);
      m2.project("*");
      m2.where(table["age"].gt(99));
      nodes::Union node = m1.union_with(m2);
      assert_equal("(SELECT * FROM users WHERE users.age < 18 UNION SELECT * FROM users WHERE users.age > 99)", node.to_sql());
    })

    IT("should union all", {
      Table table = c_arel::Table("users");
      SelectManager m1 = table.from(table);
      m1.project("*");
      m1.where(table["age"].lt(18));
      SelectManager m2 = table.from(table);
      m2.project("*");
      m2.where(table["age"].gt(99));
      nodes::UnionAll node = m1.union_all(m2);
      assert_equal("(SELECT * FROM users WHERE users.age < 18 UNION ALL SELECT * FROM users WHERE users.age > 99)", node.to_sql());
    })
  })

  DESCRIBE("intersect", {
    IT("should intersect two managers", {
      Table table = c_arel::Table("users");
      SelectManager m1 = table.from(table);
      m1.project("*");
      m1.where(table["age"].gt(18));
      SelectManager m2 = table.from(table);
      m2.project("*");
      m2.where(table["age"].lt(99));
      nodes::Intersect node = m1.intersect(m2);
      assert_equal("(SELECT * FROM users WHERE users.age > 18 INTERSECT SELECT * FROM users WHERE users.age < 99)", node.to_sql());
    })
  })

  DESCRIBE("except", {
    IT("should intersect two managers", {
      Table table = c_arel::Table("users");
      SelectManager m1 = table.from(table);
      m1.project("*");
      m1.where(table["age"].between(18, 60));
      SelectManager m2 = table.from(table);
      m2.project("*");
      m2.where(table["age"].between(40, 99));
      nodes::Except node = m1.except(m2);
      assert_equal("(SELECT * FROM users WHERE users.age BETWEEN 18 AND 60 EXCEPT SELECT * FROM users WHERE users.age BETWEEN 40 AND 99)", node.to_sql());
    })
  })

  DESCRIBE("with", {
    IT("should support WITH RECURSIVE", {
      Table comments = c_arel::Table("comments");
      Attribute comments_id = comments["id"];
      Attribute comments_parent_id = comments["parent_id"];

      Table replies = c_arel::Table("replies");
      Attribute replies_id = replies["id"];

      SelectManager recursive_term = SelectManager(NULL);
      /*
      recursive_term.from(comments).project(comments_id, comments_parent_id).where(comments_id.eq 42)

        non_recursive_term = Arel::SelectManager.new Table.engine
        non_recursive_term.from(comments).project(comments_id, comments_parent_id).join(replies).on(comments_parent_id.eq replies_id)

        union = recursive_term.union(non_recursive_term)

        as_statement = Arel::Nodes::As.new replies, union

        manager = Arel::SelectManager.new Table.engine
        manager.with(:recursive, as_statement).from(replies).project(Arel.star)

        sql = manager.to_sql
        sql.must_be_like %{
          WITH RECURSIVE "replies" AS (
              SELECT "comments"."id", "comments"."parent_id" FROM "comments" WHERE "comments"."id" = 42
            UNION
              SELECT "comments"."id", "comments"."parent_id" FROM "comments" INNER JOIN "replies" ON "comments"."parent_id" = "replies"."id"
          )
          SELECT * FROM "replies"
        }
        */
    })
  })
}) // select manager