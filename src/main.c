#include <stdio.h>

#include "token.h"
#include "utils/colors.h"
#include "lexical-analyser.h"
#include "syntatic-analyser.h"

/* void onGetToken(Token *token) { */
/*   if (!processToken(token)) { */
/*     printf(ANSI_COLOR_RED "Unexpected token %s\n" ANSI_COLOR_RESET, token->value); */
/*     exit(EXIT_FAILURE); */
/*   } */
/* } */

void printToken(Token *token) {
  printf(ANSI_COLOR_GREEN "Token received is %s\n" ANSI_COLOR_RESET, token->value);
}


int main(int argc, char *argv[]) {
  char *filePath = argv[1];
  if (!filePath) {
    printf(ANSI_COLOR_RED "Please provide a file to be analysed!" ANSI_COLOR_RESET);
  }

  /* getTokens(filePath, onGetToken); */
  getTokens(filePath, printToken);

  /* if (!automataIsValid()) { */
  /*   printf(ANSI_COLOR_RED "\nInvalid Program!\n" ANSI_COLOR_RESET); */
  /*   exit(EXIT_FAILURE); */
  /* } else { */
  /*   printf(ANSI_COLOR_GREEN "\n✓ " ANSI_COLOR_RESET "Program is valid!\n"); */
  /* } */
}
