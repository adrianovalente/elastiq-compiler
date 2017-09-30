#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "boolean.h"
#include "states-machine.h"
#include "token.h"
#include "colors.h"

void getTokens() {
  FILE *fp = fopen("/Users/drico/Desktop/hello.el", "r");
  char currentChar;
  char nextChar;
  bool _finished = false;

  if (fp == NULL) {
    printf(ANSI_COLOR_RED  "Did not find file!" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  while (!_finished) {
    nextChar = fgetc(fp);
    printf("next char is %c\n", nextChar);

    if (nextChar == EOF) _finished = true;
  }


}

void onGetToken(Token *token) {
  printf(
    "Got token with type: %s, value: %s",
    getTokenTypeDescription(token),
    token->value
  );
}

