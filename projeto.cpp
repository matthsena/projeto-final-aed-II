#include "projeto.h"
#include <time.h>
#include <string.h>
#include <math.h>

Block * criar_novo_bloco(char *hash, Pendentes * transacoes, int nounce) {
    Block *novo_bloco = (Block *) malloc(sizeof(Block));

    novo_bloco->nounce = nounce;
    novo_bloco->hash = hash;
    novo_bloco->transacoes = transacoes;
    novo_bloco->timestamp = (int)time(NULL);

    return novo_bloco;
}

Block * adicionar_bloco(char *hash, Pendentes * transacoes, int nounce, Block * bloco) {
    if (bloco == NULL) {
      return criar_novo_bloco(hash, transacoes, nounce);
    }
        
    Block *fim = bloco;

    while (fim->prox != NULL) {
        fim = fim->prox;
    }

    fim->prox = criar_novo_bloco(hash, transacoes, nounce);

    return bloco;
}

Transacao iniciar_transacao(char *remetente, char *destinatario, float valor) {
  Transacao t;

  t.valor = valor;
  t.destinatario = destinatario;
  t.remetente = remetente;

  return t;
}

Pendentes* criar_no_transacao(Transacao t) {
    Pendentes *nova_transacao = (Pendentes *) malloc(sizeof(Pendentes));
    nova_transacao->transacao = t;
    nova_transacao->prox = NULL;
    return nova_transacao;
}


Pendentes* adicionar_transacao(char * remetente, char * destinatario, float valor, Pendentes * p) {
    Transacao t = iniciar_transacao(remetente, destinatario, valor);

    if (p == NULL) {
      return criar_no_transacao(t);
    }
        
    Pendentes *fim = p;

    while (fim->prox != NULL) {
        fim = fim->prox;
    }

    fim->prox = criar_no_transacao(t);

    return p;
}

void imprimir_lista(Pendentes *lista) {
    if (lista == NULL)
      return;

    Pendentes *atual = lista;
    while (atual != NULL)
    {
        printf("%f\n", atual->transacao.valor);
        atual = atual->prox;
    }
}
/*
void limpar_transacoes(Pendentes ** transacoes) {
    Pendentes *atual = * transacoes;
    Pendentes *prox;

    while (atual != NULL) {
      prox = atual->prox;
      free(atual);
      atual = prox;
    }

    * transacoes = NULL;

    printf("Limpo");
} */

int tamanho_numero(int n) {
  int len = 0;

  while (n != 0) {
    n = n / 10;
    ++len;
  }

  return len;
}

Block * minerar_novo_bloco(char * minerador, int timestamp, char *hash_anterior, int nounce, Pendentes * transacoes) {
  char str_timestamp[tamanho_numero(timestamp)];
  sprintf(str_timestamp, "%d", timestamp);

  char str_nounce[tamanho_numero(nounce)];
  sprintf(str_nounce, "%d", nounce);

  int len = strlen(hash_anterior) + strlen(str_timestamp) + strlen(str_nounce);
  char str_digest[len + 1];

  strcat(str_digest, str_timestamp);
  strcat(str_digest, hash_anterior);
  strcat(str_digest, str_nounce);

  char *resultado = sha256(str_digest);

  printf("\n%s\n", resultado);

  if (strncmp(resultado, "000", 3) != 0) {
    return minerar_novo_bloco(minerador, timestamp, hash_anterior, nounce + 1, transacoes);
  }

  // limpar_transacoes(&transacoes);


  printf("\nnounce: %d\n", nounce);
  // TODO
  // 1. Adicionar transação da rede para o minerador
  // 2. Fazer operações nas carteiras a partir de transações pendentes
  // 3. Liberar lista de transações pendentes

  return criar_novo_bloco(resultado, NULL, nounce);
}


void minerar_bloco(char * minerador, Block * b, Pendentes * transacoes) {
  while(b->prox != NULL) {
    b = b->prox;
  }

  char *hash_anterior =  b->hash;

  printf("%d\n", b->timestamp);

  char * valor = (char *) "meetexto";

  Block *tmp = minerar_novo_bloco(minerador, b->timestamp, valor, 0, transacoes);

  printf("%d\n", tmp->timestamp);

}
