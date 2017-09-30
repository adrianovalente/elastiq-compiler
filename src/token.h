typedef enum {
  IDENTIFIER,
  NUMBER,
  ARITHMETIC_OPERATOR
} TokenType;

typedef struct {
  TokenType type;
  char *value;
} Token;

char *getTokenTypeDescription(Token *token);
