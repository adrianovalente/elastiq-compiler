#include <stdio.h>

#include "colors.h"
#include "lexical-analyser.h"

int main() {
  printf(ANSI_COLOR_BLUE "\n  LEXICAL ANALYSER\n" ANSI_COLOR_RESET);
  getTokens();
  printf("\n");
  return 0;
}

void checkIsSpacer() {
  isSpacer(' ');
}


void test(char *testDescription, void (*f)()) {
  (*f)();
  printf(ANSI_COLOR_GREEN "    ✓ " ANSI_COLOR_RESET "%s\n", testDescription);
}
