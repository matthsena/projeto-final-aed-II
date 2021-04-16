#include <iostream>
#include "projeto.h"
#include <stdlib.h>
#include <stdio.h>

// Apenas um exemplo. Alterei, inclua e implemente todas as funcoes necessarias.
Transacao iniciar_transacao(const char *fromAddress, const char *toAddress, float amount) {
  Transacao t;

  t.amount = amount;
  t.toAddress = toAddress;
  t.fromAddress = fromAddress;

  return t;
}
/**
void adicionar_transacao(Transacao t, TransacaoPendente * p) {
  TransacaoPendente *nova_transacao;

  nova_transacao = (TransacaoPendente *) malloc(sizeof(TransacaoPendente));
  nova_transacao->transacao = t;
  nova_transacao->prox = p->prox;
  p->prox = nova_transacao;
} **/



TransacaoPendente* criar_no_transacao(Transacao t) {
    TransacaoPendente *nova_transacao = (TransacaoPendente *) malloc(sizeof(TransacaoPendente));
    nova_transacao->transacao = t;
    nova_transacao->prox = NULL;
    return nova_transacao;
}

TransacaoPendente* adicionar_transacao(Transacao t, TransacaoPendente * p) {
    if (p == NULL) {
      return criar_no_transacao(t);
    }
        
    TransacaoPendente *fim = p;

    while (fim->prox != NULL) {
        fim = fim->prox;
    }

    fim->prox = criar_no_transacao(t);

    return p;
}

void imprimir_lista(TransacaoPendente *lista)
{
    TransacaoPendente *atual = lista;
    while (atual != NULL)
    {
        printf("%f\n", atual->transacao.amount);
        atual = atual->prox;
    }
}

void liberar_lista(TransacaoPendente *lista)
{
    TransacaoPendente *atual = lista, *alvo;
    while (atual != NULL)
    {
        alvo = atual;
        atual = atual->prox;
        free(alvo);
    }
}
