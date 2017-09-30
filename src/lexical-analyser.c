#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "boolean.h"
#include "token.h"
#include "colors.h"

void addCharToString(char *str, char a) {
  int len = strlen(str);
  if (len + 1 == MAX_TOKEN_VALUE) {
    printf(ANSI_COLOR_RED "Token has reached max length: %s" ANSI_COLOR_RESET, str);
    exit(EXIT_FAILURE);
  }
  str[len] = a;
  str[len + 1] = '\0';
}

bool isSpacer(char a) {
  return (bool)(a == '\n' || a == ' ');
}

void getTokens(char *path, void (*cb)(Token *token)) {
  FILE *fp = fopen(path, "r");
  char currentChar;
  State currentState;

  if (fp == NULL) {
    printf(ANSI_COLOR_RED  "Did not find file!" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  char *tokenValue = malloc(MAX_TOKEN_VALUE * sizeof(char));
  currentChar = fgetc(fp);

  while (currentChar != EOF) {

    if (isSpacer(currentChar)) {
      if (strlen(tokenValue) > 0) {
       cb(finalizeToken(tokenValue, currentState));

       // reseting the token value
       tokenValue = malloc(MAX_TOKEN_VALUE * sizeof(char));
       resetStateMachine();

      }
    } else {

      processChar(currentChar);

      /*
       * when the machine returns to the initial state, it means
       * that the token is finished and we need to start another one
       */
      if (getCurrentState() == INITIAL_STATE) {

        cb(finalizeToken(tokenValue, currentState));

        // reseting the token value
        tokenValue = malloc(MAX_TOKEN_VALUE * sizeof(char));

        // coming back one char so we will read it again
        fseek(fp, -1 * sizeof(char), SEEK_CUR); 

      } else {
        addCharToString(tokenValue, currentChar);
        currentState = getCurrentState();
      }
    
    }
    
    currentChar = fgetc(fp);
  }

  fclose(fp);

}
