#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

/* Definicoes das funcoes do TAD lista */

void criaFila(Fila *F)
{
  F->qtd_elementos = 0;
  F->ini = NULL;
  F->fim = NULL;
}

int entraFila(Fila *F, elem *x)
{
  no *new = (no *) malloc(sizeof(no));
  if(!new) return 0;
  new->info = *x;
  new->prox = NULL;
  if(estaVazia(F))
    F->ini = new;
  F->fim->prox = new;
  F->fim = new;
  F->qtd_elementos++;
  return 1;
}

int saiFila(Fila *F, elem *x)
{
  if(estaVazia(F)) return 0;
  no *aux = F->ini;
  *x = F->ini->info;
  F->ini = F->ini->prox;
  if(F->qtd_elementos == 1) F->fim = NULL;
  F->qtd_elementos--;
  free(aux);
  return 1;
}

int estaVazia(Fila *F)
{
  if(F->ini == NULL) return 1;
  else return 0;
}
