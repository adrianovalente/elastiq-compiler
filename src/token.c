#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "utils/colors.h"
#include "utils/boolean.h"

/**
 * Returns the description (as a string) for a given token type.
 *
 * @param {TokenType} type
 * @returns {string}
 */
char *getTokenTypeDescription(TokenType type) {
  switch (type) {
    case (IDENTIFIER)              : return "IDENTIFIER";
    case (NUMBER)                  : return "NUMBER";
    case (PUSH)                    : return "PUSH";
    case (ADD)                     : return "ADD";
    case (SUB)                     : return "SUB";
    case (CLEAR)                   : return "CLEAR";
    case (SEPARATOR)               : return "SEPARATOR";
    case (COMMENT)                 : return "COMMENT";
  }
}

/**
 * Returns true if a string is a reserved word.
 *
 * @param {string} str
 * @returns {bool}
 */
/* bool isReservedWord(char *str) { */
/*   int i; */
/*   for (i = 0; i < NUMBER_OF_RESERVER_WORDS; i++) { */
/*     if (strcmp(RESERVED_WORDS[i], str) == 0) { */
/*       return true; */
/*     } */
/*   } */
/*   return false; */
/* } */


/**
 * Returns the token type of a given word, according to
 * the final state of the recognizer machine.
 *
 * @param {State} state - the machine state when the execution finished
 * @param {string} tokenValue - the token value
 * @returns {TokenType}
 */
TokenType getTokenType(State state, char *tokenValue) {
  TokenType type;
  switch (state) {
    case STATE_Q1 : type = IDENTIFIER; break;
    case STATE_Q2 : type = NUMBER; break;
    case STATE_Q3 : type = PUSH; break;
    case STATE_Q4 : type = ADD; break;
    case STATE_Q5 : type = SUB; break;
    case STATE_Q6 : type = CLEAR;  break;
    case STATE_Q7 : type = SEPARATOR; break;
    case STATE_Q8 : type = COMMENT; break;

    default:
      printf(ANSI_COLOR_RED "Invalid Token \"%s\"\n" ANSI_COLOR_RESET, tokenValue);
      exit(EXIT_FAILURE);

  }

  // maybe it's a reserved word
  /* if (type == IDENTIFIER && isReservedWord(tokenValue)) { */
  /*   type = RESERVED_WORD; */
  /* } */

  return type;

}


Token *finalizeToken(char *value, State state) {
  Token *token = malloc(sizeof(Token));
  token->value = value;
  token->type = getTokenType(state, value);

  return token;
}
