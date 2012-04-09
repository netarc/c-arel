#ifndef include_test_lib_h
#define include_test_lib_h

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

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


struct _test_case {
  char *name;
  char *message;
  char *failed_pos;

  unsigned char asserts;

  unsigned failed:1;
  jmp_buf jump;
};

typedef void (*test_suite)(void);

int run_test_suite(test_suite *suite_methods, int suite_count);
_test_case * __run_test(const char *description, std::vector<const char *> &stack);
void __end_test(void);


#define TEST_SUITE(SNAME, DESCRIP, METHOD) \
  void test_suite_##SNAME(void) { \
    std::vector<const char *> context_stack; \
    context_stack.push_back(DESCRIP); \
    _test_case *_ctc; \
    METHOD \
  }

#define DESCRIBE(DESCRIP, METHOD) \
  context_stack.push_back(DESCRIP); \
  METHOD; \
  context_stack.pop_back();

// #define _end_describe \
//   context_stack.pop_back();

#define IT(DESCRIP, METHOD) \
  _ctc = __run_test(DESCRIP, context_stack); \
  if (setjmp(_ctc->jump) == 0) \
  METHOD \
  __end_test();

_test_case *current_test_case(void);


#define DECLARE_SUITE(SNAME) extern void test_suite_##SNAME(void)
#define SUITE_NAME(SNAME) test_suite_##SNAME


#define MACRO_ARG_MATCH(arg1, arg2, arg3, arg4, ...) arg4
// ASSERT_TRUE
void __test_assert_true(const char *file, int line, bool value, const char *message);
#define _test_assert_true(value)                        __test_assert_true(__FILE__, __LINE__, value, NULL)
#define _test_assert_true_with_message(value, message)  __test_assert_true(__FILE__, __LINE__, value, message)
#define _macro_assert_true(...) MACRO_ARG_MATCH(__VA_ARGS__, _test_assert_true_with_message, _test_assert_true, _test_assert_true, )
#define assert_true(...) _macro_assert_true(__VA_ARGS__)(__VA_ARGS__)

// ASSERT_EQUAL
void __test_assert_equal(const char *file, int line, int value, int expected, const char *message);
void __test_assert_equal(const char *file, int line, const char *value, const char *expected, const char *message);
#define test_assert_equal(expected, value)                        __test_assert_equal(__FILE__, __LINE__, expected, value, NULL)
#define test_assert_equal_with_message(expected, value, message)  __test_assert_equal(__FILE__, __LINE__, expected, value, message)
#define macro_assert_equal(...) MACRO_ARG_MATCH(__VA_ARGS__, test_assert_equal_with_message, test_assert_equal, test_assert_equal, )
#define assert_equal(...) macro_assert_equal(__VA_ARGS__)(__VA_ARGS__)

#endif

