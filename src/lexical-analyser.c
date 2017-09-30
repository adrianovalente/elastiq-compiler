#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "boolean.h"
#include "states-machine.h"
#include "token.h"
#include "colors.h"

TokenType getTokenType(State state) {
  return (TokenType)0;
}

void onGetToken(Token *token) {
  printf(
    ANSI_COLOR_YELLOW "\n\nGot token with type: %s, value: %s\n\n" ANSI_COLOR_RESET,
    getTokenTypeDescription(token),
    token->value
  );
}

void addCharToToken(char *str, char a) {
  int len = strlen(str);
  str[len] = a;
  str[len + 1] = '\0';
}

void getTokens() {
  FILE *fp = fopen("/Users/drico/Desktop/hello.el", "r");
  char currentChar;
  char nextChar;
  bool _finished = false;

  if (fp == NULL) {
    printf(ANSI_COLOR_RED  "Did not find file!" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  char tokenValue[] = "";

  while (!_finished) {
    nextChar = fgetc(fp);
    printf("next char is %c\n", nextChar);

    processChar(nextChar);

    /*
     * when the machine returns to the initial state, it means
     * that the token is finished and we need to start another one
     */
    if (getCurrentState() == INITIAL_STATE) {
      Token *token = malloc(sizeof(Token));
      token->value = tokenValue;
      token->type = getTokenType(getCurrentState());
      onGetToken(token);
    } else {
      addCharToToken(tokenValue, nextChar);
        printf("%s\n", tokenValue);
    }

    if (nextChar == EOF) _finished = true;
  }


}
