#include <stdio.h>

#include "colors.h"
#include "lexical-analyser.h"

int main(int argc, char *argv[]) {
  char *filePath = argv[1];
  printf(ANSI_COLOR_BLUE "\n  LEXICAL ANALYSER\n" ANSI_COLOR_RESET);
  getTokens(filePath);
  printf("\n");
  return 0;
}

void test(char *testDescription, void (*f)()) {
  (*f)();
  printf(ANSI_COLOR_GREEN "    ✓ " ANSI_COLOR_RESET "%s\n", testDescription);
}
