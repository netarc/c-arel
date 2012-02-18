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
    })
  })
})