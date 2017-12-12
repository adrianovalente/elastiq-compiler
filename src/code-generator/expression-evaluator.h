#include "../token.h"
#include "../utils/boolean.h"

bool isEvaluatingExpression();
char *startExpression();
char *finishExpression();

void addOperator(Token *token);
void addOperand(Token *token);
