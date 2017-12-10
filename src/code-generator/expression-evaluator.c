#include "expression-evaluator.h"
#include "temp-vars.h"

#include <stdio.h>
#include "../../lib/utarray.h"
#include "../utils/colors.h"

char *label = NULL;
UT_array *operandsStack, *operatorsStack = NULL;

typedef enum {
  ExpressionStatePaused,
  ExpressionStateRunning
} ExpressionState;

ExpressionState state = ExpressionStatePaused;

/**
 * @returns {boolean} true if there is already one expression being evaluated
 */
bool isEvaluatingExpression() {
  return state == ExpressionStateRunning;
}


/**
 * Starts evaluating an expression.
 */
void startExpression() {
  if (isEvaluatingExpression()) {
    printf(ANSI_COLOR_RED "Semantic Error: Expression already being evaluated!\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  state = ExpressionStateRunning;
  label = getTempVar();
  utarray_new(operandsStack, &ut_str_icd);
  utarray_new(operatorsStack, &ut_str_icd);
}

/**
 * Finishes the current expression being evaluated.
 *
 * @returns {string} label to the memory address where it's stored.
 */
char *finishExpression() {
  if (!isEvaluatingExpression()) {
    printf(ANSI_COLOR_RED "Semantic Error: Tried to finish expression but is not evaluating anything!\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  state = ExpressionStatePaused;
  return label;
}
