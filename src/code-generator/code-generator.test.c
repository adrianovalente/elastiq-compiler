#include <stdio.h>
#include <stdlib.h>
#include "./code-generator.h"
#include "../syntatic-analyser.h"

int main() {
  printf("Hello tests!\n");
  initCodeGenerator();

  consumeTransition(processToken(generateToken(RESERVED_WORD, "PROGRAM")));
  consumeTransition(processToken(generateToken(RESERVED_WORD, "VAR")));
  consumeTransition(processToken(generateToken(IDENTIFIER, "hello")));
  consumeTransition(processToken(generateToken(RESERVED_WORD, ",")));
  consumeTransition(processToken(generateToken(IDENTIFIER, "world")));
  consumeTransition(processToken(generateToken(SEMICOLON, ";")));


  printCode();

  printf("\n\nBye! õ/ \n");
  return 0;
}



