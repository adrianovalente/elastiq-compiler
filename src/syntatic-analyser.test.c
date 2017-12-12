#include <stdio.h>
#include "utils/colors.h"
#include "token.h"
#include "syntatic-analyser.h"

void testToken(TokenType type, char *value, bool shouldBeValid) {
  Token *token = malloc(sizeof(Token));
  token->type = type;
  token->value = value;
  bool valid = processToken(token);
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
  testToken(IDENTIFIER, "a", true);
  testToken(PUSH, ">", true);
  testToken(NUMBER, "2", true);

  printf("\n\n");
  printf(
    ANSI_COLOR_GREEN "    ✓ " ANSI_COLOR_RESET "Should accept text syntatically correct\n"
  );

  testToken(PARENTHESES, ")", false);
  printf(
    ANSI_COLOR_GREEN "    ✓ " ANSI_COLOR_RESET "Should reject unexpected token\n"
  );

  printf("\n\n");

  return 0;
}
