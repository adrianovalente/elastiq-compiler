#include <stdlib.h>
#include "./code-generator-transition.h"

/**
 * A simple CodeGeneratorTransition constructor.
 *
 * @param {Token *} token
 * @param {char *} submachine
 * @param {char *} state
 *
 * @returns {CodeGeneratorTransition *}
 */
CodeGeneratorTransition *allocCodeGeneratorTransition(Token *token, char *submachine, int state) {
  CodeGeneratorTransition *transition = malloc(sizeof(CodeGeneratorTransition));
  transition->token = token;
  transition->submachine = submachine;
  transition->state = state;

  return transition;
}
