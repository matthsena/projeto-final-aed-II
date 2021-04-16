#include "projeto.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h> 

// Apenas um exemplo. Alterei, inclua e implemente todas as funcoes necessarias.
Transacao iniciar_transacao(const char *fromAddress, const char *toAddress, float amount) {
  Transacao t;

  t.amount = amount;
  t.toAddress = toAddress;
  t.fromAddress = fromAddress;

  return t;
}


Block * criar_novo_bloco(char *hash, T_Pendente * transacoes, int nounce) {
    Block *novo_bloco = (Block *) malloc(sizeof(Block));

    novo_bloco->nounce = nounce;
    novo_bloco->hash = hash;
    novo_bloco->transacoes = transacoes;
    novo_bloco->timestamp = (int)time(NULL);

    return novo_bloco;
}

Block * adicionar_novo_bloco(char *hash, T_Pendente * transacoes, int nounce, Block * bloco) {
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



T_Pendente* criar_no_transacao(Transacao t) {
    T_Pendente *nova_transacao = (T_Pendente *) malloc(sizeof(T_Pendente));
    nova_transacao->transacao = t;
    nova_transacao->prox = NULL;
    return nova_transacao;
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

int tamanho_numero(int n) {
  int count = 0;

  while (n != 0) {
    n = n / 10;     // n = n/10
    ++count;
  }

  return count;
}

void minerar_novo_bloco(int timestamp, const char *hash_anterior, int nounce) {
  char str_timestamp[tamanho_numero(timestamp)];
  sprintf(str_timestamp, "%d", timestamp);

  char str_nounce[tamanho_numero(nounce)];
  sprintf(str_nounce, "%d", nounce);

  int len =  strlen(hash_anterior) + strlen(str_timestamp) + strlen(str_nounce);

  char str_digest[len + 1];

  strcat(str_digest, str_timestamp);
  strcat(str_digest, hash_anterior);
  strcat(str_digest, str_nounce);


  char *resultado = sha256(str_digest);
  printf("\n%s\n", resultado);

  if (resultado[0] != '0') {
    minerar_novo_bloco(timestamp, hash_anterior, nounce + 1);
  } else {
    printf("\nnounce: %d\n", nounce);
  }





  /*
   = sha256("abc");
  printf("%c", resultado[0]);

  while (resultado[0] != '0') {
    ++nounce;
  } */



  /*
   while (hash.substring(0, difficulty) !== Array(difficulty + 1).join('0')) {
      nonce += 1;
      hash = calculateHash();
    }

    debugBlock('👷 🚧 A new block has been mined: ', hash);

    return {
      timestamp,
      transactions,
      previusHash,
      nonce,
      hash
    }*/ 
}


void minerar_transacoes(const char * address, Block *b) {
  while(b->prox != NULL) {
    b = b->prox;
  }

  char *hash_anterior =  b->hash;
  // a partir daqui gerar bloco com mineracao

  //b = adicionar_novo_bloco(char *hash, T_Pendente * transacoes, int nounce, Block * bloco)



  printf("%d\n", b->timestamp);

  minerar_novo_bloco(b->timestamp, "meetexto", 0);
}
