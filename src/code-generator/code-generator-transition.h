#ifndef CODE_GENERATOR_TRANSITION_H
#define CODE_GENERATOR_TRANSITION_H 1

#include "../token.h"

/**
 * This is the object passed as callback when a transition is done.
 */
typedef struct {
  Token *token;
  char *submachine;
  int state;
} CodeGeneratorTransition;


CodeGeneratorTransition *allocCodeGeneratorTransition(Token *token, char *submachine, int state);

#endif
