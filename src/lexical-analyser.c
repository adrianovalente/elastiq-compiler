#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "boolean.h"
#include "states-machine.h"
#include "token.h"
#include "colors.h"

static const int MAX_TOKEN_VALUE = 64;

TokenType getTokenType(State state) {
  return (TokenType)0; // TODO IMPLEMENT
}

void finalizeToken(char *value, State state) {
  Token *token = malloc(sizeof(Token));
  token->value = value;
  token->type = getTokenType(state);
  
  // TODO implement interface with compiler main file
  printf(
    ANSI_COLOR_YELLOW "\n\nGot token with type: %s, value: %s\n\n" ANSI_COLOR_RESET,
    getTokenTypeDescription(token),
    token->value
  );
}


void addCharToString(char *str, char a) {
  int len = strlen(str);
  if (len + 1 == MAX_TOKEN_VALUE) {
    printf(ANSI_COLOR_RED "Token has reached max length: %s" ANSI_COLOR_RESET, str) ;
    exit(EXIT_FAILURE);
  }
  str[len] = a;
  str[len + 1] = '\0';
}

bool isSpacer(char a) {
  return (bool)(a == '\n' || a == ' ');
}

void getTokens() {
  FILE *fp = fopen("/Users/drico/Desktop/hello.el", "r");
  char currentChar;
  State currentState;

  if (fp == NULL) {
    printf(ANSI_COLOR_RED  "Did not find file!" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  char *tokenValue = malloc(MAX_TOKEN_VALUE * sizeof(char));
  currentChar = fgetc(fp);

  while (currentChar != EOF) {

    printf("next char is %d\n", currentChar);

    if (isSpacer(currentChar)) {
      printf(ANSI_COLOR_MAGENTA "\n\nSPACER DETECTED!\n\n" ANSI_COLOR_RESET);
      if (strlen(tokenValue) > 0) {
       finalizeToken(tokenValue, currentState);

       // reseting the token value
       tokenValue = malloc(MAX_TOKEN_VALUE * sizeof(char));

      }
    } else {

      processChar(currentChar);

      /*
       * when the machine returns to the initial state, it means
       * that the token is finished and we need to start another one
       */
      if (getCurrentState() == INITIAL_STATE) {

        finalizeToken(tokenValue, currentState);

        // reseting the token value
        tokenValue = malloc(MAX_TOKEN_VALUE * sizeof(char));

        // coming back one char so we will read it again
        fseek(fp, -1 * sizeof(char), SEEK_CUR); 

      } else {
        addCharToString(tokenValue, currentChar);
        currentState = getCurrentState();
        printf("%s\n", tokenValue);
      }

    
    }

    
    currentChar = fgetc(fp);
  }

}
