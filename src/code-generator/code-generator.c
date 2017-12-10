#include <stdio.h>
#include "../../lib/utarray.h"

#include "../utils/colors.h"
#include "./code-generator.h"
#include "./temp-vars.h"
#include "./code-repository.h"
#include "./expression-evaluator.h"

UT_array *varsBeingDeclared = NULL;
char *s, *expressionBeingEvaludated, *varBeingAssigned = NULL;

void consumeTransition(CodeGeneratorTransition *transition) {
  if (transition == NULL) {
    printf(ANSI_COLOR_RED "SYNTAX ERROR! 🤷‍♀️\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  char *submachine = transition->submachine;
  char *value = transition->token == NULL ? "---" : transition->token->value;
  int state = transition->state;

  printf(ANSI_COLOR_CYAN "Consuming transition: %s %d, Token: %s\n" ANSI_COLOR_RESET, submachine, state, value);

  if (strcmp(submachine, "PROGRAMA") == 0) {
    addToDataArea("@ /0000");
    addToDataArea("ZERO K /0000");
    addToCodeArea("INICIO LD ZERO");

  }

  if (strcmp(submachine, "declaracoes") == 0) {

    if (state == 0) {
      printf("Starting a declaration!\n");
      utarray_new(varsBeingDeclared, &ut_str_icd);
    } else if (state == 3) {
      printf("Declaration is finished.\n");
      char **p = NULL;
      while ((p=(char**)utarray_next(varsBeingDeclared, p))) {

        /*
         * Allocating memory as a local array
         * https://stackoverflow.com/questions/8716714/bus-error-10-error
         */
         s = malloc(strlen(*p) + 1);
         strcpy(s, *p); strcat(s, " K /0000"); addToDataArea(s);
      }

      utarray_free(varsBeingDeclared); varsBeingDeclared = NULL;

    }

    return; // better being safe, huh?
  }

  if (strcmp(submachine, "atribuicao") == 0) {
    if (state == 2) {
      startExpression();
    } else if (state == 4) {
      finishExpression();
    }
  }

  if (strcmp(submachine, "id") == 0 && state == 999) {
    if (varsBeingDeclared != NULL) {
      utarray_push_back(varsBeingDeclared, &value);
      // TODO add to symbols table

      return; // better safe than sorry haha
    }

    if (isEvaluatingExpression()) {
      addOperand(transition->token);
      return;
    }

    return;
  }

  if (strcmp(submachine, "numero") == 0 && state == 999) {
    if (isEvaluatingExpression()) {
      addOperand(transition->token);
      return;
    }
  }

  if (strcmp(submachine, "expressao") == 0) {
  }

}

/**
 * Inits this module, initializing arrays and setting initial vars.
 */
void initCodeGenerator() {
  initCode();
}
