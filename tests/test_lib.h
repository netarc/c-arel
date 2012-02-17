#ifndef include_test_lib_h
#define include_test_lib_h

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <c-arel.h>

#ifdef __cplusplus
# define __UNUSED(x)
#else
# ifdef __GNUC__
#   define __UNUSED(x) x __attribute__ ((__unused__))
# else
#   define __UNUSED(x) x
# endif
#endif

#if defined(_MSC_VER)
#define __UNUSED_ARG(x) ((void)(x)); /* note trailing ; */
#else
#define __UNUSED_ARG(x)
#endif

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

#define DECLARE_SUITE(SNAME) extern testsuite *test_suite_##SNAME(void)
#define SUITE_NAME(SNAME) test_suite_##SNAME

#define BEGIN_SUITE(SNAME) \
  testsuite *test_suite_##SNAME(void);\
  testsuite *test_suite_##SNAME(void) {\
    testsuite *_gitsuite = testsuite_new(#SNAME);

#define ADD_TEST(TNAME) \
  testsuite_add(_gitsuite, _gittest__##TNAME);

#define END_SUITE \
    return _gitsuite;\
  }

#define BEGIN_TEST(TNAME, DESC) \
  static void _gittest__##TNAME(test *_gittest) { \
    test__init(_gittest, #TNAME, DESC); \
    {\

#define END_TEST }}

typedef struct test test;
typedef struct testsuite testsuite;
typedef void (*testfunc)(test *);
typedef testsuite *(*test_suite)(void);

void test__init(test *t, const char *name, const char *description);
void test__fail(test *tc, const char *file, int line, const char *message);
void test__assert(test *tc, const char *file, int line, const char *message, int condition);
void test__assert_pass(test *tc, const char *file, int line, const char *message, int ret_value);

#define must_pass(expr) test__assert_pass(_gittest, __FILE__, __LINE__, "Method failed: " #expr, (expr))
#define must_fail(expr) test__assert(_gittest, __FILE__, __LINE__, "Expected method to fail: " #expr, (expr) < 0)
#define must_be_true(expr) test__assert(_gittest, __FILE__, __LINE__, "Expression is not true: " #expr, !!(expr))
#define must_be_like(expr, expected) test__assert(_gittest, __FILE__, __LINE__, "Expected string to be like: " #expected, strcmp(expr, expected) == 0)

testsuite *testsuite_new(const char *name);
void testsuite_add(testsuite *ts, testfunc test);
int testsuite_run(testsuite *ts);

#endif

