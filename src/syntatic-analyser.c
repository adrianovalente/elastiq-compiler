#include <stdio.h>
#include "syntatic-analyser.h"
#include "create_ape.h"

APE *_ape = NULL;
APE *getAutomata() {
  if (_ape == NULL) _ape = create_ape();

  return _ape;
}

CodeGeneratorTransition *processToken(Token *token) {
  return consome_token(getAutomata(), token);
}

bool automataIsValid() {
  return is_ape_valid(getAutomata());
}
