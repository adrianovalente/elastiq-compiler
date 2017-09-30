#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "colors.h"
#include "boolean.h"

char *getTokenTypeDescription(TokenType type) {
  switch (type) {
    case (IDENTIFIER)              : return "IDENTIFIER";
    case (NUMBER)                  : return "NUMBER";
    case (SEMICOLON)               : return "SEMICOLON";
    case (LOGICAL_COMPARER)        : return "LOGICAL_COMPARER";
    case (ATTRIBUTION)             : return "ATTRIBUTION";
    case (ARITHMETIC_OPERATOR)     : return "ARITHMETIC_OPERATOR";
    case (RESERVED_WORD)           : return "RESERVED_WORD";
  }
}

bool isReservedWord(char *str) {
  int i;
  for (i = 0; i < NUMBER_OF_RESERVER_WORDS; i++) {
    if (strcmp(RESERVED_WORDS[i], str) == 0) {
      return true;
    }
  }
  return false;
}


TokenType getTokenType(State state, char *tokenValue) {
  TokenType type;
  switch (state) {
    case STATE_Q1 : type = IDENTIFIER; break;
    case STATE_Q2 : type = NUMBER; break;
    case STATE_Q3 : type = SEMICOLON; break;
    case STATE_Q5 : type = LOGICAL_COMPARER; break;
    case STATE_Q7 : type = ATTRIBUTION;  break;
    case STATE_Q8 : type = ARITHMETIC_OPERATOR; break;

    default:
      printf(ANSI_COLOR_RED "Invalid Token \"%s\"\n" ANSI_COLOR_RESET, tokenValue);
      exit(EXIT_FAILURE);

  }

  // maybe it's a reserved word
  if (type == IDENTIFIER && isReservedWord(tokenValue)) {
    type = RESERVED_WORD;
  }

  return type;

}


Token *finalizeToken(char *value, State state) {
  Token *token = malloc(sizeof(Token));
  token->value = value;
  token->type = getTokenType(state, value);

  return token;

  // TODO implement interface with compiler main file
  printf(
    ANSI_COLOR_YELLOW "Got token with type: %s, value: \"%s\"\n" ANSI_COLOR_RESET,
    getTokenTypeDescription(token->type),
    token->value
  );
}
