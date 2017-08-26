/* Descricao das funcoes declaradas me Grafos - busca.h */
#include <stdio.h>
#include <stdlib.h>
#include "Grafos - Busca.h"
//#include "Grafos - Matriz adjacencia.h"

void busca_profundidade(tgrafo *grafo)
{
  tvertice v;
  int cor[MAXNUMVERTICES];

  for(v = 0; v < grafo->num_vertices; v++)
    cor[v] = BRANCO;
  for(v = 0; v < grafo->num_vertices; v++)
    if(cor[v] == BRANCO)
      visita_dfs(v, cor, grafo);
}

void visita_dfs(tvertice v, int cor[], tgrafo *grafo)
{
  tvertice w;
  tapontador p;
  tpeso peso;

  cor[v] = CINZA;
  p = primeiro_adj(grafo, v);
  while(p != NULO) {
    recupera_adj(v, p, &w, &peso, grafo);
    if(cor[w] == BRANCO)
      visita_dfs(w, cor, grafo);
    p = prox_adj(grafo, v);
  }
  cor[v] = PRETO;
}

void busca_largura(tgrafo *grafo)
{
  tvertice v;
  int cor[MAXNUMVERTICES];

  for(v = 0; v < grafo->num_vertices; v++)
    cor[v] = BRANCO;
  for(v = 0; v < grafo->num_vertices; v++)
    if(cor[v] == BRANCO)
      visita_bfs(v, cor, grafo);
}

void visita_bfs(tvertice v, int cor[], tgrafo *grafo)
{
  tvertice w;
  tapontador p;
  tpeso peso;

  /*Falta o TAD de fila para continuar */

}
