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
