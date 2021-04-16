#ifndef SHA256_H
#define SHA256_H

#include <stddef.h>

#include <ctime>
#include <iostream>

#define SHA256_BLOCK_SIZE 32
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

typedef unsigned char BYTE;
typedef unsigned int WORD;

typedef struct
{
  BYTE data[64];
  WORD datalen;
  unsigned long long bitlen;
  WORD state[8];
} SHA256_CTX;

typedef struct
{
  const char * fromAddress;
  const char * toAddress;
  float amount;
} Transacao;

typedef struct pendente
{
  Transacao transacao;
  struct pendente * prox;
} T_Pendente;

typedef struct Block
{
  int timestamp;
  char *hash;
  T_Pendente * transacoes;
  int nounce;
  struct Block * prox;
} Block;


Transacao iniciar_transacao(const char * fromAddress, const char * toAddress, float amount);

T_Pendente * adicionar_transacao(const char * fromAddress, const char * toAddress, float amount, T_Pendente * p);

void imprimir_lista(T_Pendente * p);

Block * adicionar_novo_bloco(char *hash_anterior, T_Pendente * transacoes, int nounce, Block * b);

void minerar_transacoes(const char * address, Block *b);



void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len);
void sha256_final(SHA256_CTX *ctx, int hash[]);
char *sha256(const char *data);

#endif