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

  // var hello, world;
  processToken(generateToken(RESERVED_WORD, "VAR"), onTransition);
  processToken(generateToken(IDENTIFIER, "hello"), onTransition);
  processToken(generateToken(RESERVED_WORD, ","), onTransition);
  processToken(generateToken(IDENTIFIER, "world"), onTransition);
  processToken(generateToken(SEMICOLON, ";"), onTransition);

  // hello := 5;
  processToken(generateToken(IDENTIFIER, "hello"), onTransition);
  processToken(generateToken(ATTRIBUTION, ":="), onTransition);
  processToken(generateToken(NUMBER, "5"), onTransition);
  processToken(generateToken(SEMICOLON, ";"), onTransition);

  /**
   * FIXME
   * Do jeito que a linguagem foi definida, ela precisa de
   * dois pontos-e-vírgula para terminar uma sentença!
   */
  processToken(generateToken(SEMICOLON, ";"), onTransition);

  // world = hello * 3 + 2;
  processToken(generateToken(IDENTIFIER, "world"), onTransition);
  processToken(generateToken(ATTRIBUTION, ":="), onTransition);
  processToken(generateToken(IDENTIFIER, "hello"), onTransition);
  processToken(generateToken(ARITHMETIC_OPERATOR, "*"), onTransition);
  processToken(generateToken(NUMBER, "3"), onTransition);
  processToken(generateToken(ARITHMETIC_OPERATOR, "+"), onTransition);
  processToken(generateToken(NUMBER, "2"), onTransition);
  processToken(generateToken(SEMICOLON, ";"), onTransition);

  processToken(generateToken(SEMICOLON, ";"), onTransition);  // sorry

  processToken(generateToken(RESERVED_WORD, "WHILE"), onTransition);
  processToken(generateToken(IDENTIFIER, "hello"), onTransition);
  processToken(generateToken(LOGICAL_COMPARER, "=="), onTransition);
  processToken(generateToken(NUMBER, "5"), onTransition);
  processToken(generateToken(RESERVED_WORD, "LOOP"), onTransition);

  processToken(generateToken(IDENTIFIER, "world"), onTransition);
  processToken(generateToken(ATTRIBUTION, ":="), onTransition);
  processToken(generateToken(NUMBER, "2"), onTransition);
  processToken(generateToken(SEMICOLON, ";"), onTransition);

  processToken(generateToken(RESERVED_WORD, "END"), onTransition);
  processToken(generateToken(RESERVED_WORD, "LOOP"), onTransition);
  processToken(generateToken(SEMICOLON, ";"), onTransition);


  printCode();

  printf("\n\nBye! õ/ \n");
  return 0;
}
