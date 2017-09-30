#include <stdio.h>

#include "colors.h"
#include "token.h"
#include "lexical-analyser.h"

Token *tokens[16] = { NULL };
int tokensLength = 0;

void onToken(Token *token) {
  tokens[tokensLength] = token;
  tokensLength++;
  printf("got a token!\n");
}

int main(int argc, char *argv[]) {
  char *filePath = argv[1];
  printf(ANSI_COLOR_BLUE "\n  LEXICAL ANALYSER\n" ANSI_COLOR_RESET);
  getTokens(filePath, onToken);
  printf("\n");
  return 0;
}

void test(char *testDescription, void (*f)()) {
  (*f)();
  printf(ANSI_COLOR_GREEN "    ✓ " ANSI_COLOR_RESET "%s\n", testDescription);
}
