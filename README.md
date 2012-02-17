# C-Arel

* http://github.com/netarc/c-arel

## DESCRIPTION

C-Arel is a SQL AST manager that is a C++ port of [Arel](http://github.com/rails/arel)

## Building C-Arel - Using CMake

The C-Arel library is built using CMake 2.6+ (<http://www.cmake.org>) on all platforms.

On most systems you can build the library using the following commands

	$ mkdir build && cd build
	$ cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
	$ cmake --build .

## A Gentle Introduction

Generating a query with ARel is simple. For example, in order to produce

    SELECT * FROM users

you construct a table relation and convert it to sql:

    using namespace c_arel;
    Table users = Table("users");
    SelectManager query = users.project("*");
    query.to_sql();

### More Sophisticated Queries

Here is a whirlwind tour through the most common relational operators. These will probably cover 80% of all interaction with the database.

First is the 'restriction' operator, `where`:

    users.where(users["name"].equal("amy"));
    # => SELECT * FROM users WHERE users.name = 'amy'

What would, in SQL, be part of the `SELECT` clause is called in Arel a `projection`:

    users.project(users["id"]);
    # => SELECT users.id FROM users

Joins resemble SQL strongly:

    users.join(photos).on(users["id"].equal(photos["user_id"]));
    # => SELECT * FROM users INNER JOIN photos ON users.id = photos.user_id

What are called `LIMIT` and `OFFSET` in SQL are called `take` and `skip` in Arel:

    users.take(5); # => SELECT * FROM users LIMIT 5
    users.skip(4); # => SELECT * FROM users OFFSET 4

`GROUP BY` is called `group`:

    users.group(users["name"]);
    # => SELECT * FROM users GROUP BY name

The best property of the Relational Algebra is its "composability", or closure under all operations. For example, to restrict AND project, just "chain" the method invocations:

    users                                 \
      .where(users["name"].equal("amy"))  \
      .project(users["id"])               \
    # => SELECT users.id FROM users WHERE users.name = 'amy'

All operators are chainable in this way, and they are chainable any number of times, in any order.

    users.where(users["name"].equal("bob")).where(users["age"].lt(25));

The `OR` operator works like this:

    users.where(users["name"].equal("bob").or(users["age"].lt(25)));

The `AND` operator behaves similarly.
