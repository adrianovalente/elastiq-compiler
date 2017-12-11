#include "../token.h"
#include "../utils/boolean.h"

bool isEvaluatingExpression();
void startExpression();
char *finishExpression();

void addOperator(Token *token);
void addOperand(Token *token);
