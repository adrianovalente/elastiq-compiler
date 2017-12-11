#include "expression-evaluator.h"
#include "temp-vars.h"
#include "code-repository.h"
#include "../utils/strings.h"
#include "../utils/colors.h"

#include <stdio.h>
#include "../../lib/utarray.h"

int logicalOperatorsCounter = 0;
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
bool isHighPrecedenceOperator(char *op) {
  return strcmp(op, "*") == 0 || strcmp(op, "/") == 0 ||
    strcmp(op, "AND") == 0 || strcmp(op, "!=") == 0 || strcmp(op, "==") == 0;
}

bool isArithmeticOperastor(char *op) {
  return strcmp(op, "*") == 0 || strcmp(op, "+") == 0 || strcmp(op, "/") == 0 || strcmp(op, "-") == 0;
}

void consumeArithmeticOperator(char *op) {
  char **operand, *s;
  operand = (char **)utarray_back(operandsStack);

  s = malloc(4); strcpy(s, "LD "); strcat(s, *operand); addToCodeArea(s); // loading first operator

  utarray_pop_back(operandsStack); // pop first operand from stack
  operand = (char **)utarray_back(operandsStack);

  s = malloc(strlen(op)+ 1); strcpy(s, op);
  strcat(s, " "); strcat(s, *operand); addToCodeArea(s); // loading first operator

  utarray_pop_back(operandsStack); // pop first operand from stack

  char *tmp = getTempVar();
  utarray_push_back(operandsStack, &tmp); // pushing value to tmp var
  s = malloc(strlen(tmp) + 1); strcpy(s, tmp); strcat(s, " K /0000"); addToDataArea(s);
  s = malloc(4); strcpy(s, "MM "); strcat(s, tmp); addToCodeArea(s); // storing temp result

}

char *stringWithText(char *a) {
  char *str = malloc((strlen(a) + 1) * sizeof(char));
  strcpy(str, a);
  return str;
}

void consumeLogicOperator(char *op) {

  if (strcmp(op, "==") == 0) {
    printf("== feels good man\n");

    char **firstOperand = (char **)utarray_back(operandsStack);
    char *s = malloc(4); strcpy(s, "LD "); strcat(s, *firstOperand); strcat(s, " ; First logical operator"); addToCodeArea(s);
    utarray_pop_back(operandsStack);

    char **secondOperand = (char **)utarray_back(operandsStack);
    s = malloc(3); strcpy(s, "- "); strcat(s, *secondOperand); strcat(s, " ; Second logical operator"); addToCodeArea(s);

    utarray_pop_back(operandsStack);
    char *tmp = getTempVar();
    utarray_push_back(operandsStack, &tmp); // pushing value to tmp var

    s = stringWithText("JZ "); strcat(s, tmp); strcat(s, "salva1"); addToCodeArea(s);
    addToCodeArea("LD ZERO");
    s = stringWithText("MM "); strcat(s, tmp); addToCodeArea(s);
    s = stringWithText("JP "); strcat(s, tmp); strcat(s, "final"); addToCodeArea(s);

    s = stringWithText(tmp); strcat(s, "salva1 LD UM"); addToCodeArea(s);
    s = stringWithText("MM "); strcat(s, tmp); addToCodeArea(s);

    s = stringWithText(tmp); strcat(s, "final LD ZERO"); addToCodeArea(s);

    return;
  }

  printf(ANSI_COLOR_RED "Unknown logic operator: %s\n" ANSI_COLOR_RESET, op);
  exit(EXIT_FAILURE);
}

/**
 * Consumes an operator by popping two elements from
 * the operands stack. The result is stored in a new
 * temp var, which is pushed again to the operands stack.
 *
 * @param {string} op - the operator
 */
void consumeOperator(char *op) {
  if (isArithmeticOperastor(op)) return consumeArithmeticOperator(op);
  else return consumeLogicOperator(op);
}


/**
 * If the operator has precedence greater than or equal to there
 * top of the operatorsStack, if can be pushed to the stack.
 */
bool shouldPushOperator(Token *token) {
  if (isHighPrecedenceOperator(token->value)) return true;

  char **stackTop = (char **)utarray_back(operatorsStack);
  return !isHighPrecedenceOperator(*stackTop);
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
      strcat(s, " K =");
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

  if (utarray_len(operatorsStack) == 0) {
    printf("Adding operator because stack is empty: %s\n", token->value);
    utarray_push_back(operatorsStack, &token->value);
  } else {

    if (shouldPushOperator(token)) {
      utarray_push_back(operatorsStack, &token->value);
      printf("Pushed operator to the stack: %s\n", token->value);
    } else {
      printf("Should pop from stack before bushing operator: %s\n", token->value);

      char **operatorFromStack = (char **)utarray_back(operatorsStack);
      consumeOperator(*operatorFromStack);
      utarray_pop_back(operatorsStack); // pop last operator.

      utarray_push_back(operatorsStack, &token->value);
      printf("Now pushing operator to the stack: %s\n", token->value);
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

  printf(ANSI_COLOR_YELLOW "Finishing expression %s\n" ANSI_COLOR_RESET, label);
  while (utarray_len(operatorsStack) > 0) {
    char **op = (char **)utarray_back(operatorsStack);
    consumeOperator(*op);
    utarray_pop_back(operatorsStack);
  }

  printf(ANSI_COLOR_YELLOW "Operators stack is empty.\n" ANSI_COLOR_RESET);
  if (utarray_len(operandsStack) != 1) {
    printf(ANSI_COLOR_RED "Semantic Error: Operands Stack length is != 1 but there are not operators!\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  char **val = (char **)utarray_back(operandsStack);
  char *s = stringWithText("LD "); strcat(s, *val); addToCodeArea(s);
  s = stringWithText("MM "); strcat(s, label); addToCodeArea(s);


  state = ExpressionStatePaused;
  return label;
}
