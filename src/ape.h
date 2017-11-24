#ifndef APE_H
#define APE_H 1

#include "utils/boolean.h"
#include "token.h"

#include "../lib/utarray.h"
#include "../lib/uthash.h"

typedef struct {

	const char *token;
	int estadoResultado;

	UT_hash_handle hh;

} Transicao;

typedef struct {

	const char *token;
	const char *submaquina;
	int estadoResultado;

	UT_hash_handle hh;

} TransicaoChamada;


typedef struct {

	int estado;

	Transicao *transicoes;
	TransicaoChamada *chamadas;

	UT_hash_handle hh;

} Estado;


typedef struct {

	const char *title;

	int estado;

	Estado *estadosTransicoes;
	UT_array *estadosFinais;

	UT_hash_handle hh;

} Automato;


typedef struct {

	Automato *automatos;

	Automato *automatoAtual;

	UT_array *pilha;

} APE;

APE *create_ape();
void free_ape(APE *ape);
bool consome_token(APE *ape, Token *token);
bool is_ape_valid(APE *ape);

#endif
