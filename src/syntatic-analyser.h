#ifndef SYNTATIC_ANALYSER_H
#define SYNTATIC_ANALYSER_H 1

#include "utils/boolean.h"
#include "token.h"
#include "ape.h"
#include "create_ape.h"
#include "code-generator/code-generator-transition.h"

CodeGeneratorTransition *processToken(Token *token, void (*cb)(CodeGeneratorTransition *transition));
bool automataIsValid();

#endif
