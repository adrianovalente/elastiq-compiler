#include <stdio.h>
#include "utils/colors.h"
#include "token.h"
#include "syntatic-analyser.h"

void noop() {}

void testToken(TokenType type, char *value, bool shouldBeValid) {
  Token *token = malloc(sizeof(Token));
  token->type = type;
  token->value = value;
  bool valid = processToken(token, noop);
  if (shouldBeValid != valid) {
    printf(
      ANSI_COLOR_RED "Assertion Error: Expected APE to be %svalid\n" ANSI_COLOR_RESET,
      shouldBeValid ? "" : "NOT "
    );
    exit(EXIT_FAILURE);
  }
}

int main() {
  printf(ANSI_COLOR_BLUE "\n  SYNTATIC ANALYSER\n" ANSI_COLOR_RESET);
  testToken(RESERVED_WORD, "PROGRAM", true);
  testToken(RESERVED_WORD, "VAR", true);
  testToken(IDENTIFIER, "hello", true);
  testToken(SEMICOLON, ";", true);
  testToken(IDENTIFIER, "hello", true);
  testToken(ATTRIBUTION, ":=", true);
  testToken(NUMBER, "5", true);
  testToken(SEMICOLON, ";", true);
  testToken(RESERVED_WORD, "END", true);

  printf("\n\n");
  printf(
    ANSI_COLOR_GREEN "    ✓ " ANSI_COLOR_RESET "Should accept text syntatically correct\n"
  );

  testToken(IDENTIFIER, "hello", false);
  printf(
    ANSI_COLOR_GREEN "    ✓ " ANSI_COLOR_RESET "Should reject unexpected token\n"
  );

  printf("\n\n");

  return 0;
}
