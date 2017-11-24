#ifndef TOKEN_H
#define TOKEN_H 1

#include "states-machine.h"

static const int MAX_TOKEN_VALUE = 64;

static const int NUMBER_OF_RESERVER_WORDS = 11; // OMG I am sorry for that
static const char* RESERVED_WORDS[] = {
  "IF",
  "BEGIN",
  "END",
  "WHILE",
  "PROGRAM",
  "FUNCTION",
  "VAR",
  "CALL",
  "OUTPUT",
  "INPUT",
  "LOOP"
};

typedef enum {
  IDENTIFIER,
  NUMBER,
  SEMICOLON,
  LOGICAL_COMPARER,
  ATTRIBUTION,
  ARITHMETIC_OPERATOR,
  RESERVED_WORD
} TokenType;

typedef struct {
  TokenType type;
  char *value;
} Token;

char *getTokenTypeDescription(TokenType type);
Token *finalizeToken(char *value, State state);

#endif
