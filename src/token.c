#include "token.h"

char *getTokenTypeDescription(Token *token) {
  switch (token->type) {
    case (IDENTIFIER)              : return "IDENTIDFIER";
    case (NUMBER)                  : return "NUMBER";
    case (ARITHMETIC_OPERATOR)     : return "ARITHMETIC_OPERATOR";
  }
}

