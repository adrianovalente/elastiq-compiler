#include <stdio.h>

#include "token.h"
#include "utils/colors.h"
#include "lexical-analyser.h"
#include "syntatic-analyser.h"
#include "code-generator/code-generator.h"
#include "code-generator/code-generator-transition.h"
#include "code-generator/code-repository.h"

void onGetTransition(CodeGeneratorTransition *transition) {
  consumeTransition(transition);
}

void onGetToken(Token *token) {
  if (!processToken(token, onGetTransition)) {
    printf(ANSI_COLOR_RED "Unexpected token %s\n" ANSI_COLOR_RESET, token->value);
    exit(EXIT_FAILURE);
  }
}


int main(int argc, char *argv[]) {
  char *filePath = argv[1];
  char *outputPath = argv[2];
  if (!filePath || strlen(filePath) == 0) {
    printf(ANSI_COLOR_RED "Please provide a file to be analysed!" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  if (!outputPath || strlen(outputPath) == 0) {
    printf(ANSI_COLOR_RED "Please provide an output path!" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  initCodeGenerator();
  getTokens(filePath, onGetToken);

  if (!automataIsValid()) {
    printf(ANSI_COLOR_RED "\nInvalid Program!\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  } else {
    printf(ANSI_COLOR_GREEN "\n✓ " ANSI_COLOR_RESET "Program is valid!\n");
  }

  saveCodeToFile(outputPath);
}
