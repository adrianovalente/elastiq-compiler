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

  s = stringWithText("LD "); strcat(s, *operand); addToCodeArea(s); // loading first operator

  utarray_pop_back(operandsStack); // pop first operand from stack
  operand = (char **)utarray_back(operandsStack);

  s = stringWithText(op); strcpy(s, op);
  strcat(s, " "); strcat(s, *operand); addToCodeArea(s); // loading first operator

  utarray_pop_back(operandsStack); // pop first operand from stack

  char *tmp = getTempVar();
  utarray_push_back(operandsStack, &tmp); // pushing value to tmp var
  s = stringWithText(tmp); strcat(s, " K /0000"); addToDataArea(s);
  s = stringWithText("MM "); strcat(s, tmp); addToCodeArea(s); // storing temp result

}

void consumeLogicOperator(char *op) {

  // getting second operand
  char **el = (char **)utarray_back(operandsStack);
  char *secondOperand = stringWithText(*el);
  utarray_pop_back(operandsStack);

  // getting first operand
  el = (char **)utarray_back(operandsStack);
  char *firstOperand = stringWithText(*el);
  utarray_pop_back(operandsStack);

  // pushing result
  char *tmp = getTempVar();
  utarray_push_back(operandsStack, &tmp); // pushing value to tmp var

  char *s = stringWithText("LD "); strcat(s, firstOperand); strcat(s, " ; First logical operator"); addToCodeArea(s);
  s = stringWithText("- "); strcat(s, secondOperand); strcat(s, " ; Second logical operator"); addToCodeArea(s);


  if (strcmp(op, "==") == 0) {

    s = stringWithText("JZ "); strcat(s, tmp); strcat(s, "salva1"); addToCodeArea(s);
    addToCodeArea("LD ZERO");
    s = stringWithText("MM "); strcat(s, tmp); addToCodeArea(s);
    s = stringWithText("JP "); strcat(s, tmp); strcat(s, "final"); addToCodeArea(s);
    s = stringWithText(tmp); strcat(s, "salva1 LD UM"); addToCodeArea(s);
    s = stringWithText("MM "); strcat(s, tmp); addToCodeArea(s);
    s = stringWithText(tmp); strcat(s, "final LD ZERO"); addToCodeArea(s);

    return;
  }

  if (strcmp(op, "!=") == 0) {

    s = stringWithText("JZ "); strcat(s, tmp); strcat(s, "salva0"); addToCodeArea(s);
    addToCodeArea("LD UM");
    s = stringWithText("MM "); strcat(s, tmp); addToCodeArea(s);
    s = stringWithText("JP "); strcat(s, tmp); strcat(s, "final"); addToCodeArea(s);
    s = stringWithText(tmp); strcat(s, "salva0 LD ZERO"); addToCodeArea(s);
    s = stringWithText("MM "); strcat(s, tmp); addToCodeArea(s);
    s = stringWithText(tmp); strcat(s, "final LD ZERO"); addToCodeArea(s);

    return;
  }

  if (strcmp(op, ">") == 0 || strcmp(op, ">=") == 0) {
    if (strcmp(op, ">") == 0) {
      addToCodeArea("- UM");
    }
    char *s = stringWithText("JN "); strcat(s, tmp); strcat(s, "salva0"); addToCodeArea(s);
    addToCodeArea("LD UM");
    s = stringWithText("MM "); strcat(s, tmp); addToCodeArea(s);
    s = stringWithText("JP "); strcat(s, tmp); strcat(s, "final"); addToCodeArea(s);
    s = stringWithText(tmp); strcat(s, "salva0 LD ZERO");
    s = stringWithText("MM "); strcat(s, tmp); addToCodeArea(s);
    s = stringWithText(tmp); strcat(s, "final LD ZERO"); addToCodeArea(s);

    return ;
  }

  if (strcmp(op, "<") == 0 || strcmp(op, "<=") == 0) {
    if (strcmp(op, ">") == 0) {
      addToCodeArea("+ UM");
    }
    char *s = stringWithText("JN "); strcat(s, tmp); strcat(s, "salva1"); addToCodeArea(s);
    addToCodeArea("LD ZERO");
    s = stringWithText("MM "); strcat(s, tmp); addToCodeArea(s);
    s = stringWithText("JP "); strcat(s, tmp); strcat(s, "final"); addToCodeArea(s);
    s = stringWithText(tmp); strcat(s, "salva1 LD UM");
    s = stringWithText("MM "); strcat(s, tmp); addToCodeArea(s);
    s = stringWithText(tmp); strcat(s, "final LD ZERO"); addToCodeArea(s);

    return ;
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
      s = stringWithText(tmp); strcpy(s, tmp);
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
 *
 * @returns {string} the temp register where the expression is stored.
 */
char *startExpression() {
  if (isEvaluatingExpression()) {
    printf(ANSI_COLOR_RED "Semantic Error: Expression already being evaluated!\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  state = ExpressionStateRunning;
  label = getTempVar();
  char *s = stringWithText(label); strcpy(s, label);
  strcat(s, " K /0000 ; Anonymous Expression"); addToDataArea(s);

  utarray_new(operandsStack, &ut_str_icd);
  utarray_new(operatorsStack, &ut_str_icd);

  printf(ANSI_COLOR_YELLOW "Started evaluation expression %s\n" ANSI_COLOR_RESET, label);
  return label;
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
  printf(ANSI_COLOR_YELLOW "Finishing expression %s\n" ANSI_COLOR_RESET, label);
  return label;
}
