#include <stdio.h>
#include <stdlib.h>
#include "./code-generator.h"
#include "../syntatic-analyser.h"

void onTransition(CodeGeneratorTransition *transition) {
  consumeTransition(transition);
}

int main() {
  printf("Hello tests!\n");
  initCodeGenerator();

  processToken(generateToken(RESERVED_WORD, "PROGRAM"), onTransition);
  processToken(generateToken(RESERVED_WORD, "VAR"), onTransition);
  processToken(generateToken(IDENTIFIER, "hello"), onTransition);

  processToken(generateToken(RESERVED_WORD, ","), onTransition);
  processToken(generateToken(IDENTIFIER, "world"), onTransition);
  processToken(generateToken(SEMICOLON, ";"), onTransition);

  processToken(generateToken(IDENTIFIER, "hello"), onTransition);
  processToken(generateToken(ATTRIBUTION, ":="), onTransition);
  processToken(generateToken(NUMBER, "5"), onTransition);
  processToken(generateToken(SEMICOLON, ";"), onTransition);

  printCode();

  printf("\n\nBye! õ/ \n");
  return 0;
}



