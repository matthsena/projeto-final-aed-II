#include <iostream>
#include "projeto.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Apenas um exemplo. Alterei, inclua e implemente todas as funcoes necessarias.
Transacao iniciar_transacao(const char *fromAddress, const char *toAddress, float amount) {
  Transacao t;

  t.amount = amount;
  t.toAddress = toAddress;
  t.fromAddress = fromAddress;

  return t;
}

T_Pendente* criar_no_transacao(Transacao t) {
    T_Pendente *nova_transacao = (T_Pendente *) malloc(sizeof(T_Pendente));
    nova_transacao->transacao = t;
    nova_transacao->prox = NULL;
    return nova_transacao;
}

Block * criar_novo_bloco(char *hash_anterior, T_Pendente * transacoes, int nounce) {
    Block *novo_bloco = (Block *) malloc(sizeof(Block));

    novo_bloco->nounce = nounce;
    novo_bloco->hash_anterior = hash_anterior;
    novo_bloco->transacoes = transacoes;
    novo_bloco->timestamp = (int)time(NULL);

    return novo_bloco;
}

T_Pendente* adicionar_transacao(const char * fromAddress, const char * toAddress, float amount, T_Pendente * p) {

    Transacao t = iniciar_transacao(fromAddress, toAddress, amount);

    if (p == NULL) {
      return criar_no_transacao(t);
    }
        
    T_Pendente *fim = p;

    while (fim->prox != NULL) {
        fim = fim->prox;
    }

    fim->prox = criar_no_transacao(t);

    return p;
}

void imprimir_lista(T_Pendente *lista)
{
    T_Pendente *atual = lista;
    while (atual != NULL)
    {
        printf("%f\n", atual->transacao.amount);
        atual = atual->prox;
    }
}

void liberar_lista(T_Pendente *lista)
{
    T_Pendente *atual = lista, *alvo;
    while (atual != NULL)
    {
        alvo = atual;
        atual = atual->prox;
        free(alvo);
    }
}
