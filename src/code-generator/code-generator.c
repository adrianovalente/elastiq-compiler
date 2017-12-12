#include <stdio.h>
#include "../../lib/utarray.h"

#include "../utils/colors.h"
#include "../utils/strings.h"

#include "./code-generator.h"
#include "./temp-vars.h"
#include "./code-repository.h"
#include "./expression-evaluator.h"

UT_array *varsBeingDeclared, *loops, *conditionals = NULL;
char *s, *varBeingAssigned = NULL;
bool waitingForIdentifierToAssign = false;
int ifsCounter = 0;

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
    addToDataArea("MAIN JP INICIO");
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
         s = stringWithText(*p); strcat(s, " K /0000"); addToDataArea(s);
      }

      utarray_free(varsBeingDeclared); varsBeingDeclared = NULL;

    }

    return; // better being safe, huh?
  }

  if (strcmp(submachine, "atribuicao") == 0) {
    if (state == 0) {
      waitingForIdentifierToAssign = true;
    } else if (state == 2) {
      startExpression();
    } else if (state == 4) {
      char *exp = finishExpression();
      char *s = stringWithText("LD "); strcat(s, exp); strcat(s, " ; Result of Anonymous Expression"); addToCodeArea(s);
      s = stringWithText("MM "); strcat(s, varBeingAssigned); strcat(s, " ; Assignment"); addToCodeArea(s);
      varBeingAssigned = NULL;
    }
  }

  if (strcmp(submachine, "id") == 0 && state == 999) {
    if (varsBeingDeclared != NULL) {
      utarray_push_back(varsBeingDeclared, &value);
      // TODO add to symbols table

      return; // better safe than sorry haha
    }

    if (waitingForIdentifierToAssign) {
      varBeingAssigned = value;
      waitingForIdentifierToAssign = false;
    }

    if (isEvaluatingExpression()) {
      addOperand(transition->token);
      return;
    }

    return;
  }

  if (strcmp(submachine, "condicional") == 0) {

    if (state == 1) {

      printf("Starting a conditional.\n");

      // init a new stack to store all loops if it's not defined yet.
      if (loops == NULL) {
        utarray_new(conditionals, &ut_str_icd);
      }

      char *condition = startExpression();
      utarray_push_back(conditionals, &condition);
    }

    if (state == 3) {
      finishExpression();
      char **condition = (char **)utarray_back(conditionals);

      printf("Condition is stored here %s\n", *condition);
      char *s = stringWithText("LD "); strcat(s, *condition); strcat(s, " ; Condition is here!");

      addToCodeArea(s);
      char *counter = intToString(ifsCounter);
      s = stringWithText("JZ "); strcat(s, counter); strcat(s, "endif ; Evaluating Conditional");
      addToCodeArea(s);

    }

    if (state == 7) {
      printf("End if \n");
      char *s = intToString(ifsCounter); strcat(s, "endif LD ZERO"); addToCodeArea(s);
      ifsCounter++;
    }
  }

  if (strcmp(submachine, "iterativo") == 0) {
    if (state == 1) {
      printf("Starting a loop.\n");

      if (loops == NULL) {
        utarray_new(loops, &ut_str_icd);
      }

      char *condition = startExpression();
      utarray_push_back(loops, &condition);

      char *s = stringWithText(condition); strcat(s, "startLoop LD ZERO ; Beginning of a loop "); addToCodeArea(s);
    }

    if (state == 3) {
      finishExpression();
      char **condition = (char **)utarray_back(loops);
      char *s = stringWithText("LD "); strcat(s, *condition); strcat(s, " ; Verifying loop condition"); addToCodeArea(s);
      s = stringWithText("JZ "); strcat(s, *condition); strcat(s, "endLoop"); addToCodeArea(s);
    }

    if (state == 5) {
      printf("Finishing loop.\n");
      char **condition = (char **)utarray_back(loops);
      char *s = stringWithText("JP "); strcat(s, *condition); strcat(s, "startLoop ; Loop"); addToCodeArea(s);
      s = stringWithText(*condition); strcat(s, "endLoop LD ZERO"); addToCodeArea(s);

      utarray_pop_back(loops);
    }
  }

  if (strcmp(submachine, "numero") == 0 && state == 999) {
    if (isEvaluatingExpression()) {
      addOperand(transition->token);
      return;
    }
  }

  if (strcmp(submachine, "operador_aritmetico") == 0 && state == 1) {
    if (isEvaluatingExpression()) {
      addOperator(transition->token);
      return;
    }
  }

  if (strcmp(submachine, "operador_comparacao") == 0 && state == 1) {
    if (isEvaluatingExpression()) {
      addOperator(transition->token);
      return;
    }
  }

}

/**
 * Inits this module, initializing arrays and setting initial vars.
 */
void initCodeGenerator() {
  initCode();
}
