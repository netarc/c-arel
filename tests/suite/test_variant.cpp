#include "test_lib.h"

TEST_SUITE(variant, "variant", {
  IT("should correctly type cast", {
    variant v;
    v = (char)1;
    assert_true((char)v == (char)1);
    v = (unsigned char)1;
    assert_true((unsigned char)v == (unsigned char)1);
    v = (short)1;
    assert_true((short)v == (short)1);
    v = (unsigned short)1;
    assert_true((unsigned short)v == (unsigned short)1);
    v = (int)1;
    assert_true((int)v == (int)1);
    v = (unsigned int)1;
    assert_true((unsigned int)v == (unsigned int)1);
    v = (long)1;
    assert_true((long)v == (long)1);
    v = (unsigned long)1;
    assert_true((unsigned long)v == (unsigned long)1);
    v = (float)1.0f;
    assert_true((float)v == (float)1.0f);
    v = (double)1.0f;
    assert_true((double)v == (double)1.0f);

    v = (long)0;
    assert_true((long)v == (long)0);
    v = NULL;
    assert_true((long)v == (long)0);
  })
})
