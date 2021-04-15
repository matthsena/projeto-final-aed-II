#include <iostream>
#include "projeto.h"
#include <stdlib.h>
#include <stdio.h>

// Apenas um exemplo. Alterei, inclua e implemente todas as funcoes necessarias.
Transacao criar_transacao(const char *fromAddress, const char *toAddress, float amount) {
  Transacao t;

  t.amount = amount;
  t.toAddress = toAddress;
  t.fromAddress = fromAddress;

  return t;
}
