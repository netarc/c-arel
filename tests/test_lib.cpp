#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "test_lib.h"

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


/*-------------------------------------------------------------------------*
 * Public assert methods
 *-------------------------------------------------------------------------*/

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

void test__fail(test *tc, const char *file, int line, const char *message) {
  tc->asserts++;
  fail_test(tc, file, line, message);
}

void test__assert(test *tc, const char *file, int line, const char *message, int condition) {
  tc->asserts++;
  if (condition == 0)
    fail_test(tc, file, line, message);
}

void test__assert_pass(test *tc, const char *file, int line, const char *message, int ret_value) {
  tc->asserts++;
  if (ret_value < 0)
    fail_test(tc, file, line, message);
}

/*-------------------------------------------------------------------------*
 * Test Suite
 *-------------------------------------------------------------------------*/

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

