#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils/colors.h"
#include "token.h"
#include "lexical-analyser.h"

static const int EXPECTED_TOKENS_LENGTH = 8;

Token *tokens[16] = { NULL };
int tokensLength = 0;

/*
 * Storing the tokens in an array so we can test them after
 */
void onToken(Token *token) {
  tokens[tokensLength] = token;
  tokensLength++;
}

/**
 * Gets the ordinal number to a given integer.
 * Used to prettify the tests output.
 *
 * @param {int} n
 * @returns {string}
 */
char *getOrdinalNumber(int n) {
  if (n == 0) return "1st";
  if (n == 1) return "2nd";
  if (n == 2) return "3rd";

  char *ordinal = malloc(3 * sizeof(char));
  sprintf(ordinal, "%dth", n + 1);
  return ordinal;
}

void test(char *testDescription, void (*f)()) {
  (*f)();
  printf(ANSI_COLOR_GREEN "    ✓ " ANSI_COLOR_RESET "%s\n", testDescription);
}

void assertTokensLength() {
  if (tokensLength != EXPECTED_TOKENS_LENGTH) {
    printf(
      ANSI_COLOR_RED "Assertion Error: Expected %d tokens but got %d\n" ANSI_COLOR_RESET,
      EXPECTED_TOKENS_LENGTH,
      tokensLength
    );
  }
}

void assertTokenContents(int position, TokenType type, char *value) {
  Token *token = tokens[position];
  if (token->type != type) {
    printf(
      ANSI_COLOR_RED "Assertion Error: Expected %s token to be a %s but is a %s\n" ANSI_COLOR_RESET,
      getOrdinalNumber(position),
      getTokenTypeDescription(type),
      getTokenTypeDescription(token->type)
    );
    exit(EXIT_FAILURE);
  }

  if (strcmp(token->value, value) != 0) {
    printf(
      ANSI_COLOR_RED "Assertion Error: Expected %s token to have value %s but is has  %s\n" ANSI_COLOR_RESET,
      getOrdinalNumber(position),
      value,
      token->value
    );
    exit(EXIT_FAILURE);
  }

  printf(
    ANSI_COLOR_GREEN "    ✓ " ANSI_COLOR_RESET "%s token should be a %s with value \"%s\"\n",
    getOrdinalNumber(position),
    getTokenTypeDescription(type),
    value
  );

}

/**
 * This is the main test function.
 * Path to the fixture file (hello.el) is passed
 * as a param when `make test` calls it.
 */
int main(int argc, char *argv[]) {
  char *filePath = argv[1];
  printf(ANSI_COLOR_BLUE "\n  LEXICAL ANALYSER\n" ANSI_COLOR_RESET);
  getTokens(filePath, onToken);
  test("Should get expected number of tokens", assertTokensLength);

  assertTokenContents(0, NUMBER, "2");
  assertTokenContents(1, PUSH, ">");
  assertTokenContents(2, IDENTIFIER, "n");
  assertTokenContents(3, PARENTHESES, "(");
  assertTokenContents(4, IDENTIFIER, "a");
  assertTokenContents(5, PUSH, ">");
  assertTokenContents(6, IDENTIFIER, "b");
  assertTokenContents(7, PARENTHESES, ")");
  printf("\n");
  return 0;
}
