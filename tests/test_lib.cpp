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
  // printf("%s\n", buf);
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