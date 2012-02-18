#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "test_lib.h"

static char TMP_BUFFER[2048];

unsigned int assertions = 0;
std::vector<_test_case *> __tests;
std::vector<_test_case *> __failed_tests;

_test_case *current_test_case(void) {
  return __tests.back();  
}

void free_test_case(_test_case *tc) {
  if (tc) {
    free(tc->name);
    if (tc->message)
      free(tc->message);
    if (tc->failed_pos)
      free(tc->failed_pos);
    free(tc);
  }
}

static char DESCRIP_BUFFER[2048];
const char * describe_stack(std::vector<const char *> &stack) {
  strcpy(DESCRIP_BUFFER, "");
  for (int i=0, iLen=stack.size(); i<iLen; ++i) {
    if (i > 0)
      strcat(DESCRIP_BUFFER, " ");
    strcat(DESCRIP_BUFFER, stack.at(i));
  }
// .back()->description
  return DESCRIP_BUFFER;
}


_test_case * __run_test(const char *description, std::vector<const char *> &stack) {
  _test_case *tc = (_test_case *)malloc(sizeof(_test_case));
  memset(tc, 0, sizeof(_test_case));

  char buf[1024];
  sprintf(buf, "\"%s %s\"", describe_stack(stack), description);
  tc->name = strdup(buf);

  __tests.push_back(tc);
  return tc;
}

void __end_test() {
  printf("%c", __tests.back()->failed ? 'F' : '.');
}

int run_test_suite(test_suite *suite_methods, int suite_count) {
  for (unsigned int i=0; i<suite_count; ++i)
    suite_methods[i]();

  printf("\n");
  for (std::vector<_test_case *>::iterator it=__failed_tests.begin(); it!=__failed_tests.end(); ++it) {
    printf("\n%s\n%s\n%s\n", (*it)->name, (*it)->message, (*it)->failed_pos);
  }

  printf("\n%u tests, %u assertions, %u failures\n", (unsigned int)__tests.size(), assertions, (unsigned int)__failed_tests.size());

  while (!__tests.empty()) {
    free_test_case(__tests.back());
    __tests.pop_back();
  }

  return __failed_tests.size() > 0 ? -1 : 0;
}

static void fail_test(const char *file, int line, const char *message) {
  _test_case *tc = current_test_case();
  char buf[1024];
  const char *last_error = NULL;

  snprintf(buf, 1024, "%s:%d", file, line);

  tc->failed = 1;
  tc->message = strdup(message);
  tc->failed_pos = strdup(buf);

  __failed_tests.push_back(tc);

  longjmp(tc->jump, 0);
}

void __test_assert_true(const char *file, int line, bool value, const char *message) {
  ++assertions;
  if (!value) {
    if (!message) {
      message = &TMP_BUFFER[0];
      sprintf(TMP_BUFFER, "expected: TRUE");
    }
    fail_test(file, line, message);
  }
}

void __test_assert_equal(const char *file, int line, int expected, int value, const char *message) {
  ++assertions;
  if (expected != value) {
    if (!message) {
      message = &TMP_BUFFER[0];
      sprintf(TMP_BUFFER, "expected: %i but was %i", expected, value);
    }
    fail_test(file, line, message);
  }
}

void __test_assert_equal(const char *file, int line, const char *expected, const char *value, const char *message) {
  ++assertions;
  if (strcmp(expected, value) != 0) {
    if (!message) {
      message = &TMP_BUFFER[0];
      sprintf(TMP_BUFFER, "expected: '%s' but was '%s'", expected, value);
    }
    fail_test(file, line, message);
  }
}



/*
void __run_test_suite() {
  printf("\n");
  std::vector<const char *> context_stack;
  _test_case *current_test_case;

  // describe("backwards compat")
  context_stack.push_back("backwards compat");

  // describe("join")
  context_stack.push_back("join");

  // it("noops on nil")
  current_test_case = __run_test("noops on nil", context_stack);
  if (setjmp(current_test_case->jump) == 0) {
    current_test_case->failed = 1;
    longjmp(current_test_case->jump, 0);

    // Table relation = c_arel::Table("users");
    // SelectManager sm = relation.skip(2);
    // assert_equal(sm.to_sql(), "SELECT FROM users OFFSET 2", "DESCRP");
  }
  __end_test();

  context_stack.pop_back();

  // it("noops on nil")
  current_test_case = __run_test("noops on nil", context_stack);
  if (setjmp(current_test_case->jump) == 0) {
    longjmp(current_test_case->jump, 0);

    // Table relation = c_arel::Table("users");
    // SelectManager sm = relation.skip(2);
    // assert_equal(sm.to_sql(), "SELECT FROM users OFFSET 2", "DESCRP");
  }
  __end_test();



  printf("\n%u tests, %u assertions, %u failures\n", (unsigned int)__tests.size(), 0, 0);

  while (!__tests.empty()) {
    free_test_case(__tests.back());
    __tests.pop_back();
  }
}
*/


/*
#define DO_ALLOC(TYPE) ((TYPE*) malloc(sizeof(TYPE)))
#define GIT_MAX_TEST_CASES 64

struct test {
  char *name;
  char *message;
  char *failed_pos;
  char *description;
  char *error_message;
  unsigned char asserts;

  testfunc function;
  unsigned failed:1, ran:1;
  jmp_buf *jump;
};

struct testsuite {
  char *name;
  int count, fail_count;
  int asserts;
  test *list[GIT_MAX_TEST_CASES];
};


static void test_free(test *t) {
  if (t) {
    free(t->name);
    free(t->description);
    free(t->failed_pos);
    free(t->message);
    free(t->error_message);
    free(t);
  }
}

static void test_run(test *tc) {
  jmp_buf buf;
  tc->jump = &buf;

  if (setjmp(buf) == 0) {
    tc->ran = 1;
    (tc->function)(tc);
  }

  tc->jump = 0;
}

static test *create_test(testfunc function) {
  test *t = DO_ALLOC(test);

  memset(t, 0x0, sizeof(test));
  t->function = function;

  return t;
}

void test__init(test *t, const char *name, const char *description) {
  t->name = strdup(name);
  t->description = strdup(description);
}




static void fail_test(test *tc, const char *file, int line, const char *message) {
  char buf[1024];
  const char *last_error = NULL;

  snprintf(buf, 1024, "%s:%d", file, line);

  tc->failed = 1;
  tc->message = strdup(message);
  tc->failed_pos = strdup(buf);

  if (last_error)
    tc->error_message = strdup(last_error);

  if (tc->jump != 0)
    longjmp(*(tc->jump), 0);
}

void __test_assert_true(test *tc, const char *file, int line, bool value, const char *message) {
  tc->asserts++;
  if (!value) {
    if (!message) {
      message = &TMP_BUFFER[0];
      sprintf(TMP_BUFFER, "expected: TRUE\n");
    }
    fail_test(tc, file, line, message);
  }
}

// void __test_assert_equal(test *tc, const char *file, int line, const char *expected, const char *value, const char *message) {
void __test_assert_equal(_test_case *tc, const char *file, int line, const char *expected, const char *value, const char *message) {
  // tc->asserts++;
  if (strcmp(expected, value) != 0) {
    if (!message) {
      message = &TMP_BUFFER[0];
      sprintf(TMP_BUFFER, "expected: '%s' but was '%s'", expected, value);
    }
    // fail_test(tc, file, line, message);
  }
}

void __test_assert_equal(test *tc, const char *file, int line, int expected, int value, const char *message) {
  tc->asserts++;
  if (expected != value) {
    if (!message) {
      message = &TMP_BUFFER[0];
      sprintf(TMP_BUFFER, "expected: %i but was %i\n", expected, value);
    }
    fail_test(tc, file, line, message);
  }
}


static void testsuite_init(testsuite *ts) {
  ts->count = 0;
  ts->fail_count = 0;
  ts->asserts = 0;
  memset(ts->list, 0, sizeof(ts->list));
}

testsuite *testsuite_new(const char *name) {
  testsuite *ts = DO_ALLOC(testsuite);
  testsuite_init(ts);
  ts->name = strdup(name);
  return ts;
}

static void free_suite(testsuite *ts) {
  unsigned int n;

  for (n = 0; n < GIT_MAX_TEST_CASES; n++)
    if (ts->list[n])
      test_free(ts->list[n]);

  free(ts->name);
  free(ts);
}

void testsuite_add(testsuite *ts, testfunc test) {
  assert(ts->count < GIT_MAX_TEST_CASES);
  ts->list[ts->count++] = create_test(test);
}

static void print_details(testsuite *ts) {
  int i;
  int failCount = 0;

  if (ts->fail_count == 0) {
    const char *testWord = ts->count == 1 ? "test" : "tests";
    printf("OK (%d %s - %d assertions)\n", ts->count, testWord, ts->asserts);
  } else {
    printf("Failed (%d failures):\n", ts->fail_count);

    for (i = 0 ; i < ts->count ; ++i) {
      test *tc = ts->list[i];
      if (tc->failed) {
        failCount++;
        printf("  %d) \"%s\" [test %s @ %s]\n\t%s\n",
          failCount, tc->description, tc->name, tc->failed_pos, tc->message);
        if (tc->error_message)
          printf("\tError: %s\n", tc->error_message);
      }
    }
  }
}

int testsuite_run(testsuite *ts) {
  int i, fail_count;

  printf("Suite \"%s\": ", ts->name);

  for (i = 0 ; i < ts->count ; ++i) {
    test *tc = ts->list[i];

    test_run(tc);
    ts->asserts += tc->asserts;

    if (tc->failed) {
      ts->fail_count++;
      putchar('F');
    } else
      putchar('.');

    fflush(stdout);
  }
  printf("\n  ");
  print_details(ts);
  fail_count = ts->fail_count;

  free_suite(ts);
  return fail_count;
}
*/
