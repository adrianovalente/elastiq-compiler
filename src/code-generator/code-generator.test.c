#include <stdio.h>
#include <stdlib.h>
#include "./code-generator.h"
#include "../syntatic-analyser.h"

int main() {
  printf("Hello tests!\n");
  initCodeGenerator();

  consumeTransition(processToken(generateToken(RESERVED_WORD, "PROGRAM")));

  return 0;
}



