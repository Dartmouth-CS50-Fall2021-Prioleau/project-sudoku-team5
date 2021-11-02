/* 
 * unittest.h - some useful MACROS for controlling unit tests.
 *
 * David Kotz, May 2016
 * CS 50
 *
 * This code, and the code that uses them, would likely be enclosed in
 *  #ifdef UNIT_TEST ... #endif
 * to compile in the unit-test code only when desired.
 * 
 */

#ifndef __UNITTEST_H
#define __UNITTEST_H

// each test should start by setting the result count to zero
#define START_TEST_CASE(name) int _failures=0; char *_testname = (name);

// Check a condition; if false, print warning message.
// e.g., EXPECT(dict->start == NULL).
// note: the preprocessor 
//   converts __LINE__ into line number where this macro was used, and
//   converts "#x" into a string constant for arg x.
#define EXPECT(x)						\
  if (!(x)) {							\
    _failures++;						\
    printf("Fail %s Line %d: [%s]\n", _testname, __LINE__, #x); \
  }

// return the result count at the end of a test
#define END_TEST_CASE							\
  if (_failures == 0) {							\
    printf("PASS test %s\n\n", _testname);				\
  } else {								\
    printf("FAIL test %s with %d errors\n\n", _testname, _failures);	\
  }

#define TEST_RESULT (_failures)

#endif // _UNITTEST_H
