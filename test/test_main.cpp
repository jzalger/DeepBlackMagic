#include "unity.h"
#include <main.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_function(void) {
  // test stuff
}


int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_function);
  return UNITY_END();
}

void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);
  runUnityTests();
}
