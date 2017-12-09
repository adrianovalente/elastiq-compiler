#include <stdio.h>
#include "syntatic-analyser.h"
#include "create_ape.h"

APE *_ape = NULL;
APE *getAutomata() {
  if (_ape == NULL) _ape = create_ape();

  return _ape;
}

CodeGeneratorTransition *processToken(Token *token, void (*cb)(CodeGeneratorTransition *transition)) {
  return consome_token(getAutomata(), token, cb);
}

bool automataIsValid() {
  return is_ape_valid(getAutomata());
}
