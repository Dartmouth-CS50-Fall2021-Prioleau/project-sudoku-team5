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
 * For example,                                                                                                                                                
 *  #ifdef UNIT_TEST                                                                                                                                           
 *  #include "unittest.h"                                                                                                                                      
 *                                                                                                                                                             
 *  /////////////////////////////////////                                                                                                                      
 *  // create and validate an empty tree                                                                                                                       
 *  int test_newtree0()                                                                                                                                        
 *  {                                                                                                                                                          
 *    START_TEST_CASE("newtree0");                                                                                                                             
 *    tree_t *tree = tree_new();                                                                                                                               
 *    EXPECT(tree != NULL);                                                                                                                                    
 *    EXPECT(tree->root == NULL);                                                                                                                              
                                                                                                                                                               
 *    EXPECT(tree_find(tree, "hello") == NULL);                                                                                                                
 *                                                                                                                                                             
 *    tree_delete(tree);                                                                                                                                       
 *    EXPECT(nmalloc-nfree == 0);                                                                                                                              
 *                                                                                                                                                             
 *    END_TEST_CASE;                                                                                                                                           
 *    return TEST_RESULT;                                                                                                                                      
 *  }                                                                                                                                                          
 *                                                                                                                                                             
 *  ////////////////////////////////////////////                                                                                                               
 *  int                                                                                                                                                        
 *  main(const int argc, const char *argv[])                                                                                                                   
 *  {                                                                                                                                                          
 *    int failed = 0;                                                                                                                                          
 *                                                                                                                                                             
 *    failed += test_newtree0();                                                                                                                               
 *    failed += test_newtree1();                                                                                                                               
 *    failed += test_treeleft();                                                                                                                               
 *    failed += test_treefind();                                                                                                                               
 *                                                                                                                                                             
 *    if (failed) {                                                                                                                                            
 *      printf("FAIL %d test cases\n", failed);                                                                                                                
 *      return failed;                                                                                                                                         
 *    } else {                                                                                                                                                 
 *      printf("PASS all test cases\n");                                                                                                                       
 *      return 0;                                                                                                                                              
 *    }                                                                                                                                                        
 *  }                                                                                                                                                          
 *                                                                                                                                                             
 *  #endif // UNIT_TEST                                                                                                                                        
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
#define EXPECT(x)                                               \
  if (!(x)) {                                                   \
    _failures++;                                                \
    printf("Fail %s Line %d: [%s]\n", _testname, __LINE__, #x); \
  }

// return the result count at the end of a test                                                                                                                
#define END_TEST_CASE                                                   \
  if (_failures == 0) {                                                 \
    printf("PASSED test %s\n\n", _testname);                              \
  } else {                                                              \
    printf("FAILED test %s with %d errors\n\n", _testname, _failures);    \
  }

#define TEST_RESULT (_failures)

#endif // _UNITTEST_H 


