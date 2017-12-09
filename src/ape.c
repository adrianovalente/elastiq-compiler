/**
 * This file is adapted from Roro's original APE that can be found on github
 * https://github.com/rogerioyuuki/poli-github/blob/master/compiladores/entrega3/syntax/ape.c
 *
 * #thanks @Roro
 */

#include "ape.h"
#include "utils/colors.h"
#include "../lib/utarray.h"
#include "../lib/uthash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void free_estados(Estado *estado) {
    Transicao *current, *tmp;

    HASH_ITER(hh, estado->transicoes, current, tmp) {
        HASH_DEL(estado->transicoes, current);
        free(current);
    }

    TransicaoChamada *current2, *tmp2;
    HASH_ITER(hh, estado->chamadas, current2, tmp2) {
        HASH_DEL(estado->chamadas, current2);
        free(current2);
    }

    free(estado);
}

void free_automato(Automato *automato) {
    Estado *current, *tmp;

    HASH_ITER(hh, automato->estadosTransicoes, current, tmp) {
        HASH_DEL(automato->estadosTransicoes, current);
        free_estados(current);
    }

    utarray_free(automato->estadosFinais);
    free(automato);
}

void free_ape(APE *ape) {
    Automato *current, *tmp;

    HASH_ITER(hh, ape->automatos, current, tmp) {
        HASH_DEL(ape->automatos, current);
        free_automato(current);
    }

    utarray_free(ape->pilha);
}


Transicao * busca_transicao_possivel(Automato *automato, Token *token) {
    /* Busca transicoes do estado atual */
    Estado *estado;
    HASH_FIND_INT(automato->estadosTransicoes, & (automato->estado), estado);
    if (estado != NULL) {
        /* Busca a transição pro token dado */
        Transicao *transicao;
        HASH_FIND_STR(estado->transicoes, token->value, transicao);

        return transicao;
    }

    return NULL;
}

TransicaoChamada * busca_submaquina_possivel(Automato *automato, Token *token) {
    /* Busca as transições de submáquina do automato atual */
    Estado *estado;
    HASH_FIND_INT(automato->estadosTransicoes, & (automato->estado), estado);
    if (estado != NULL) {
        TransicaoChamada *chamada;
        const char *chaveBusca;

        switch (token->type) {
            case IDENTIFIER:
                chaveBusca = "id";
                break;
            case NUMBER:
                chaveBusca = "numero";
                break;
            default:
                chaveBusca = token->value;
        }

        HASH_FIND_STR(estado->chamadas, chaveBusca, chamada);

        return chamada;
    }

    return NULL;
}

bool is_final(Automato *automato) {
    int *p;

    for (p = (int*)utarray_front(automato->estadosFinais);
         p != NULL;
         p = (int*)utarray_next(automato->estadosFinais, p))
    {
        if (automato->estado == *p) {
            return true;
        }
    }

    return false;
}

bool is_ape_valid(APE *ape) {
    Automato *atual, *p;

    atual = ape->automatoAtual;
    if (!is_final(atual)) {
        return false;
    }

    for (p = (Automato*)utarray_front(ape->pilha);
         p != NULL;
         p = (Automato*)utarray_next(ape->pilha, p))
    {
        if (!is_final(p)) {
            return false;
        }
    }

    return true;
}

void empilha_automato(APE *ape, Automato *novoAutomato) {

    utarray_push_back(ape->pilha, ape->automatoAtual);
    ape->automatoAtual = novoAutomato;

}

bool desempilha_automato(APE *ape) {

    if (utarray_len(ape->pilha) > 0) {
        Automato *automato = (Automato*)utarray_back(ape->pilha);
        utarray_pop_back(ape->pilha);

        ape->automatoAtual = automato;
        return true;
    }

    return false;
}

Automato *busca_novo_automato(APE *ape, const char *title) {
    Automato *automato, *novoAutomato;
    HASH_FIND_STR(ape->automatos, title, automato);

    novoAutomato = malloc(sizeof(Automato));
    novoAutomato->title = automato->title;
    novoAutomato->estado = automato->estado;

    novoAutomato->estadosTransicoes = automato->estadosTransicoes;
    novoAutomato->estadosFinais = automato->estadosFinais;

    return novoAutomato;
}

/**
 * Consumes a token from a stream.
 *
 * @param {APE} ape - the stack automata
 * @param {Token} token
 *
 * @returns NULL if there is a syntax error,
 *       or a CodeGeneratorTransition that describes the available transition.
 */
CodeGeneratorTransition *consome_token(APE *ape, Token *token) {
    Automato *automato = ape->automatoAtual;

    /* Tenta realizar transição */
    Transicao *transicao = busca_transicao_possivel(automato, token);
    if (transicao != NULL) {
        printf(ANSI_COLOR_YELLOW "[%s] Consuming token %s and going to state %d\n" ANSI_COLOR_RESET,
          automato->title, token->value, transicao->estadoResultado);
        /* Realiza a transição */
        automato->estado = transicao->estadoResultado;

        /*
         * TODO verify if casting static const* to const* is ok
         * https://stackoverflow.com/questions/21422903/passing-const-char-to-parameter-of-type-char-discards-qualifiers
         */
        return allocCodeGeneratorTransition(token, (char *)automato->title, transicao->estadoResultado);
    }

    /* Busca chamada de submáquina */
    TransicaoChamada *chamada = busca_submaquina_possivel(automato, token);
    if (chamada != NULL) {

        /* Guarda estado de retorno */
        automato->estado = chamada->estadoResultado;

        /* Empilha automato e consome token novamente */
        if (strcmp(chamada->submaquina, "id") != 0
            &&
            strcmp(chamada->submaquina, "numero") != 0) {

            printf(ANSI_COLOR_MAGENTA "[%s] Entering submachine %s\n" ANSI_COLOR_RESET,
              automato->title, chamada->submaquina);

            /* Não empilha identificador nem número, eles estao no lexico */
            empilha_automato(ape, busca_novo_automato(ape, chamada->submaquina));
            consome_token(ape, token);
        } else {
          printf(ANSI_COLOR_YELLOW "[%s] Consuming token %s with value %s \n" ANSI_COLOR_RESET,
            automato->title, chamada-> submaquina, token->value);
        }

        return allocCodeGeneratorTransition(token, (char *)chamada->submaquina, chamada->estadoResultado);
    }

    /* Se automato estiver em estado final, pode desempilhar e tentar */
    if (is_final(automato)) {
        if (!desempilha_automato(ape)) return NULL;
        return consome_token(ape, token);
    }

    /* Aí vc não ajuda... erro de sintaxe */
    return NULL;
}
