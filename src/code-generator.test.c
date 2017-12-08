#include <stdio.h>
#include <stdlib.h>
#include "./code-generator.h"

int main() {
  printf("Hello tests!\n");
  consumeTransition(
    generateToken(RESERVED_WORD, "BEGIN"),
    "my submachine",
    "1"
  );

  return 0;
}



