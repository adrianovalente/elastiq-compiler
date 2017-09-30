#include <stdio.h>

#include "colors.h"
#include "lexical-analyser.h"

int main() {
  printf(ANSI_COLOR_BLUE "\n  LEXICAL ANALYSER\n" ANSI_COLOR_RESET);
  getTokens();
  printf("\n");
  return 0;
}
