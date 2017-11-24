#ifndef SYNTATIC_ANALYSER_H
#define SYNTATIC_ANALYSER_H 1

#include "utils/boolean.h"
#include "token.h"
#include "ape.h"
#include "create_ape.h"

bool processToken(Token *token);
bool automataIsValid();

#endif
