#include "expression-evaluator.h"
#include "temp-vars.h"
#include "code-repository.h"
#include "../utils/strings.h"
#include "../utils/colors.h"

#include <stdio.h>
#include "../../lib/utarray.h"

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
 * @returns {boolean} true if the operator if of high
 * precedence (i.e., multiplication or division)
 */
bool isHighPrecedenceOperator(op) {
  return strcmp(op, "*") == 0 || strcmp(op, "/") == 0;
}

/**
 * If the operator has precedence greater than or equal to there
 * top of the operatorsStack, if can be pushed to the stack.
 */
bool shouldPushOperator(Token *token) {
  if (isHighPrecedenceOperator(token->value)) return true;


  char *stackTop = utarray_back(operatorsStack);
  printf("top of stack is %s", stackTop);

  return !isHighPrecedenceOperator(stackTop);
}

void addOperand(Token *token) {
  printf("Adding operand.\n");
  char *tmp, *s;
  switch(token->type) {
    case IDENTIFIER:
      utarray_push_back(operandsStack, &token->value);
      break;

    case NUMBER:
      tmp = getTempVar();
      s = malloc(strlen(tmp) + 1); strcpy(s, tmp);
      strcat(s, " K /");
      strcat(s, token->value);
      addToDataArea(s);
      utarray_push_back(operandsStack, &tmp);
      break;

    default:
      printf(ANSI_COLOR_RED "Invalid token type!\n" ANSI_COLOR_RED);
      exit(EXIT_FAILURE);
  }

}

void addOperator(Token *token) {

  return;

  if (utarray_len(operatorsStack) == 0) {
    printf("Printing operator because stack is empty.\n");
    utarray_push_back(operatorsStack, token->value);
  } else {

    if (shouldPushOperator(token)) {
      printf("Should push operator.\n");
    } else {
      printf("Should not push operator.\n");
    }
  }
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
  char *s = malloc(strlen(label) + 1); strcpy(s, label);
  strcat(s, " K /0000 ; Anonymous Expression"); addToDataArea(s);

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
