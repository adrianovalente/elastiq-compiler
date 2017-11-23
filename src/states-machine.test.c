#include <stdio.h>
#include <stdlib.h>
#include "states-machine.h"
#include "utils/colors.h"

/*
 * Resets the machine state before each test.
 */
void beforeAll() {
  resetStateMachine();
}

/**
 * Asserts that actual state is equal to the expected.
 */
void assert(State actual, State expected) {
  if (actual != expected) {
    printf(
      ANSI_COLOR_RED "Assertion Error: Expected %s to be %s\n",
      getStateDescription(actual),
      getStateDescription(expected)
    );
    exit(EXIT_FAILURE);
  }
}

void test(char *testDescription, void (*f)()) {
  beforeAll();
  (*f)();
  printf(ANSI_COLOR_GREEN "    ✓ " ANSI_COLOR_RESET "%s\n", testDescription);
}

void checkIdentifier() {
  processChar('h');
  processChar('e');
  processChar('l');
  processChar('l');
  processChar('o');
  assert(getCurrentState(), STATE_Q1);
}

void checkInteger() {
  processChar('1');
  processChar('2');
  assert(getCurrentState(), STATE_Q2);
}

void checkSemicolon() {
  processChar(';');
  assert(getCurrentState(), STATE_Q3);
}

void checkEqualComparator() {
  processChar('=');
  processChar('=');
  assert(getCurrentState(), STATE_Q5);
}

void checkIdentifierWithComparator() {
  processChar('a');
  processChar('b');
  processChar('=');
  assert(getCurrentState(), INITIAL_STATE);
}


int main() {

  printf(ANSI_COLOR_BLUE "\n  STATES MACHINE\n" ANSI_COLOR_RESET);

  test("Should end execution of string string \"hello\" in STATE_Q1", checkIdentifier);
  test("Should end execution of string \"12\" in STATE_Q2", checkInteger);
  test("Should end execution of string \";\" in STATE_Q3", checkSemicolon);
  test("Should end execution of string \"==\" ins STATE_Q5", checkEqualComparator);
  test("Should reset state after finding first \"=\"", checkIdentifierWithComparator);

  printf("\n");
  return(0);
}
