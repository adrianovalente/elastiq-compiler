#include <stdio.h>

#include "utils/colors.h"
#include "token.h"
#include "lexical-analyser.h"

void onGetToken(Token *token) {
  printf(
    ANSI_COLOR_YELLOW "Got token with type: %s, value: \"%s\"\n" ANSI_COLOR_RESET,
    getTokenTypeDescription(token->type),
    token->value
  );
}


int main(int argc, char *argv[]) {
  char *filePath = argv[1];
  if (!filePath) {
    printf(ANSI_COLOR_RED "Please provide a file to be analysed!" ANSI_COLOR_RESET);
  }

  getTokens(filePath, onGetToken);
}
