/* Descricao das funcoes declaradas me Grafos - busca.h */
#include <stdio.h>
#include <stdlib.h>
#include "Grafos - Busca.h"
#include "Fila.h"
//#include "Grafos - Matriz adjacencia.h"

#define INF 2500000

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

void dijkstra(struct tgrafo *grafo, tvertice v){
   int V = grafo->num_vertices;
   int dist[V];
   int i;
   for(i = 0; i < V; i++){
    dist[i] = INF;
   }

}

int Floydinho(tgrafo *grafo){
    int V = grafo->num_vertices;
   int dist[V][V];
   int i,j k;
    /* Preenche a matriz com infinito*/
   for(i = 0; i < V; i++){
        for(j = 0; j < V; j++){
            dist[i][j] = INF;
        }
   }
   /* Preenche a diagonal principal com 0's*/
   for(i = 0; i < V; i++){
        for(j = 0; j < V; j++){
            if(i == j){
                dist[i][j] = 0;
            }
        }
   }

   tapontador p;

    /*Coloca os pesos iniciais na matriz*/
   for(i = 0; i < V; i++){
        p = grafo->vet[i];
        p = p->prox;
        while(p != NULL){
            if(i == p->id){
                break;
            }
            dist[i][p->id] = p->peso;
            p = p->prox;
        }
   }
   /*Atualiza os menores caminhos*/
   for(i = 0; i < V; i++){
        for(j = 0; j < V; j++){
            for(k = 0; k < V; k++){
                if(dist[j][i] + dist[i][k] < dist[j][k])
                dist[j][k] = dist[j][i] + dist[i][k];
            }
        }
   }

   /* Cria um vetor de excentricidades*/
   int exc[V];
   /*Encontra o custo máximo de cada coluna da matriz*/
   int maior = 0;
   for(i = 0; i < V; i++){
        for(j = 0; j < V; j++){
            if(maior < dist[j][i] && dist[j][i] != INF)
                maior = dist[j][i];
        }
        exc[i] = maior;
        maior = 0;
   }

   maior = exc[0];
   int verticecentral = 0;

   /*Escolhe o vértice central */
   for(i = 1; i < V; i++){
        if(exc[i] > maior){
            maior = exc[i];
            verticecentral = i;
        }
   }

    return verticecentral;
}
