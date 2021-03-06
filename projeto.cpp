#include "projeto.h"
#include <time.h>

pthread_mutex_t lock;

int found_nounce = 0;

Block * criar_novo_bloco(char *hash, Pendentes * transacoes, int nounce) {
    Block *novo_bloco = (Block *) malloc(sizeof(Block));

    novo_bloco->nounce = nounce;
    novo_bloco->hash = hash ? hash : sha256((const char *) "genesis block");
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
        printf("%s tem a receber $ %f UFABC Coins de: %s\n\n", 
        atual->transacao.destinatario,  atual->transacao.valor,
        atual->transacao.remetente? atual->transacao.remetente : "REDE BLOCKCHAIN (Prêmio de mineração)");
        
        atual = atual->prox;
    }
}

hashTable * realizar_transacao_carteira(hashTable * ht, char c[STR_SIZE], float valor) {

  if (c == NULL) {
    return ht;
  }

  int idx = hash(c, ht->tamanho);
    
  listaEncadeada *lista;
  lista = ht->tabela.encadeada[idx].primeiro;

  while(lista != NULL) {
      if (strcmp(lista->chave, c) == 0) {
          lista->valor.saldo = lista->valor.saldo + valor;
          break;
      }

      lista = lista->proximo;
  }

  return ht;
}

void realizar_transacoes(Pendentes *lista, hashTable * ht) {
    if (lista == NULL)
      return;

    Pendentes *atual = lista;
    Pendentes *prox;

    while (atual != NULL) {
        ht = realizar_transacao_carteira(ht, atual->transacao.remetente, atual->transacao.valor * - 1);
        ht = realizar_transacao_carteira(ht, atual->transacao.destinatario, atual->transacao.valor);

        prox = atual->prox;
        free(atual);

        atual = prox;
    }

    lista = NULL;
}

int tamanho_numero(int n) {
  int len = 0;

  while (n != 0) {
    n = n / 10;
    ++len;
  }

  return len;
}

MineracaoRetorno * minerar_novo_bloco(char * minerador, int timestamp, char *hash_anterior, int nounce, Pendentes * transacoes, hashTable * ht ) {

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

  if (found_nounce == 1) {
    pthread_exit(NULL);  
  }

  if (found_nounce == 0 && strncmp(resultado, "000", 3) != 0) {
    return minerar_novo_bloco(minerador, timestamp, hash_anterior, nounce + 1, transacoes, ht);
  }

  pthread_mutex_lock(&lock);

  if (found_nounce >= 1) {
    pthread_exit(NULL);  
  }

  found_nounce = 1;

  realizar_transacoes(transacoes, ht); 
  
  transacoes = NULL;
  transacoes = adicionar_transacao(NULL, minerador, 25.0, transacoes);

  MineracaoRetorno * retorno = (MineracaoRetorno *) malloc(sizeof(MineracaoRetorno));

  retorno->minerador = minerador; 
  retorno->nounce = nounce;
  retorno->transacoes = transacoes;

  pthread_mutex_unlock(&lock);

  return retorno;
}

void * minerar_bloco(void * args) {
  MineracaoParams * mx = (MineracaoParams *) args;

  while(mx->b->prox != NULL) {
    mx->b = mx->b->prox;
  }

  char *hash_anterior =  mx->b->hash;
  
  MineracaoRetorno *tmp = minerar_novo_bloco(mx->minerador, mx->b->timestamp, hash_anterior, mx->valor_inicial, mx->transacoes, mx->t);

  mx->b = adicionar_bloco(hash_anterior, tmp->transacoes, tmp->nounce, mx->b);

  found_nounce = 0;


  pthread_exit(NULL);
}


int hash(const char chave[STR_SIZE], int tamanho, int tentativa) {
    int h = chave[0];
    for (int i = 1; chave[i] != '\0'; i++)
        h = (h * 251 * chave[i]) % tamanho;
    return (h + tentativa) % tamanho;
}

hashTable criar_hash_table(int t) {
    hashTable h;
    h.tamanho = t;
    
    h.tabela.encadeada = (hashEncadeada*) malloc(sizeof(hashEncadeada) * t);
    for (int i = 0; i < t; i++)
        h.tabela.encadeada[i].primeiro = NULL;
    
    return h;
}

void destruirListaEncadeada(listaEncadeada *lista) {
    listaEncadeada *atual = lista;
    listaEncadeada *proximo = nullptr;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    lista = NULL;
}

void destruir_hash_table(hashTable h) {
      for (int i = 0; i < h.tamanho; i++)
          destruirListaEncadeada(h.tabela.encadeada[i].primeiro);

      free(h.tabela.encadeada);
      h.tabela.encadeada = NULL;
}

listaEncadeada *novoItemHashing(char c[STR_SIZE], Carteira v) {
    listaEncadeada *item;
    item = (listaEncadeada *) malloc(sizeof(listaEncadeada));
    strcpy(item->chave, c);
    item->valor = v;
    item->proximo = NULL;
    
    return item;
}

void inserir_hash_table(hashTable h, char c[STR_SIZE], Carteira v) {
    int idx = hash(c, h.tamanho);
    
    if (h.tabela.encadeada[idx].primeiro == NULL) {
        h.tabela.encadeada[idx].primeiro = novoItemHashing(c, v);
    } else {
        listaEncadeada *lista;
        lista = h.tabela.encadeada[idx].primeiro;
        
        while(lista->proximo != NULL) {
            lista = lista->proximo;
        }       
        lista->proximo = novoItemHashing(c, v);
    }
}

void retornar_saldo(hashTable h, char c[STR_SIZE]) {
    int idx = hash(c, h.tamanho);
    
    listaEncadeada *lista;
    lista = h.tabela.encadeada[idx].primeiro;

    char * nome;
    float saldo;

    while(lista != NULL) {
        if (strcmp(lista->chave, c) == 0) {
            
            nome = lista->valor.nome;
            saldo = lista->valor.saldo;
            break;
        }
        lista = lista->proximo;
    }

    printf("Nome: %s \nSaldo: $ %.5f UFABC Coins\n\n", c, saldo);
}