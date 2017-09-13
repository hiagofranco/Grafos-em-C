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

int entraFila(Fila *F, elem *x, elem *prior)
{
  no *p;
  no *new = (no *) malloc(sizeof(no));
  if(!new) return 0;
  new->info = *x;
  new->prioridade = *prior;
  if(estaVazia(F) || *prior < F->ini->prioridade){
    new->prox = F->ini;
    F->ini = new;
  }
  else{
    p = F->ini;
  while(p->prox != NULL && p->prox->prioridade <= new->prioridade){
    p = p->prox;
    new->prox = p->prox;
    p->prox = new;
  }
  }
  F->qtd_elementos++;
  return 1;
}

int saiFila(Fila *F)
{
    no *del;
    int item;
    if(estaVazia(F)){
        return 0;
    }
    else{
        del = F->ini;
        item = del->info;
        F->ini = F->ini->prox;
        free(del);
    }
    F->qtd_elementos--;
    return item;
}

int estaVazia(Fila *F)
{
  if(F->ini == NULL) return 1;
  else return 0;
}
