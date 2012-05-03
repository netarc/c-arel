/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_h
#define include_c_arel_h

#include <stdio.h>
#include <vector>
#include <string>
#include <map>

#define nullptr ((void *)0)

#include "../deps/variant/variant.hpp"
#include "c-arel/util.h"
#include "c-arel/derived.h"
#include "c-arel/connection.h"

#include "c-arel/visitors/visitor.h"
#include "c-arel/visitors/to_sql.h"

//-- nodes
#include "c-arel/nodes/node.h"
#include "c-arel/nodes/select_core.h"
#include "c-arel/nodes/select_statement.h"
#include "c-arel/nodes/insert_statement.h"
#include "c-arel/nodes/update_statement.h"
// terminal
#include "c-arel/nodes/distinct.h"
// unary
#include "c-arel/nodes/unary.h"
#include "c-arel/nodes/ascending.h"
#include "c-arel/nodes/descending.h"
#include "c-arel/nodes/with.h"
// binary
#include "c-arel/nodes/binary.h"
#include "c-arel/nodes/equality.h"
#include "c-arel/nodes/in.h"
#include "c-arel/nodes/join_source.h"
#include "c-arel/nodes/table_alias.h"
#include "c-arel/nodes/infix_operation.h"
#include "c-arel/nodes/delete_statement.h"
#include "c-arel/nodes/values.h"
#include "c-arel/nodes/unqualified_column.h"
// nary
#include "c-arel/nodes/and.h"
// joins
#include "c-arel/nodes/inner_join.h"
#include "c-arel/nodes/outer_join.h"
#include "c-arel/nodes/string_join.h"

#include "c-arel/nodes/sql_literal.h"
//-- nodes

// managers
#include "c-arel/managers/tree_manager.h"
#include "c-arel/managers/select_manager.h"
#include "c-arel/managers/delete_manager.h"
#include "c-arel/managers/insert_manager.h"
#include "c-arel/managers/update_manager.h"

#include "c-arel/expessions.h"
#include "c-arel/predications.h"
#include "c-arel/order_predications.h"
#include "c-arel/alias_predication.h"
#include "c-arel/math.h"
#include "c-arel/attribute.h"
#include "c-arel/table.h"

// functions
#include "c-arel/nodes/function.h"
#include "c-arel/nodes/named_function.h"
#include "c-arel/nodes/count.h"

#endif