/* Descricao das funcoes declaradas me Grafos - busca.h */
#include <stdio.h>
#include <stdlib.h>
#include "Grafos_Busca.h"
#include "heap.h"
//#include "Grafos - Matriz adjacencia.h"

#define INF 2500000
/*
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

  /*Falta o TAD de fila para continuar

}

*/

int Floydinho(tgrafo *grafo){
   int V = grafo->num_vertices;
   int dist[V][V];
   int i,j, k;
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
        p = grafo->vet[i]->prox;
        while(p != NULL){
            if(i != p->id && p->peso != INF){
                dist[i][p->id] = p->peso;
            }
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
            if(dist[j][i] != INF && maior < dist[j][i])
                maior = dist[j][i];
        }
        exc[i] = maior;
        maior = 0;
   }

   tapontador_vertice v;

   for(i = 0; i < V; i++){
        for(j = 0; j < V; j++){
            v = grafo->vet[i];
            dist[i][j] = dist[i][j]*v->egressos;
        }
   }

   maior = exc[0];
   int verticecentral = 0;

   /*Escolhe o vértice central */
   for(i = 1; i < V; i++){
        if(exc[i] < maior){
            maior = exc[i];
            verticecentral = i;
        }
   }

    return verticecentral;
}

void Dijkstra(tgrafo *grafo, int verticev){
    int numv = grafo->num_vertices;
    int dist[numv], ant[numv];
    int i;

    tapontador p;

    minHeap h;
    h = initMinHeap(numv);
    for(i = 0; i < numv; i++){
        if(i == verticev){
            dist[i] = 0;
        }
        else{
            dist[i] = INF;
        }
        ant[i] = -1;
        insertNode(&h,p->id,p->peso);
    }


    node u;
    tapontador v;
    int alt;
    while(!isEmpty(&h)){
        u = retirar_Min(&h);
        v = grafo->vet[u.idvertice]->prox;
        while(v != NULL){
            if(dist[u.idvertice] == INF){
                alt = v->peso;
            }
            else{
                alt = dist[u.idvertice] + v->peso;
            }
            if(alt < dist[v->id]){
                dist[v->id] = alt;
                ant[v->id] = u.idvertice;
            }
            v = v->prox;
        }
    }
    printf("\nMenores distancias:");
    for(i = 0; i < numv; i++){
        printf(" %d", dist[i]);
    }

    printf("\nAntecessores (caminho):");
    for(i = 0; i < numv; i++){
        printf(" %d", ant[i]);
    }

}

/*        while Q is not empty:                  // The main loop
          u := vertex in Q with min dist[u]  // Source node in first case
          remove u from Q

          for each neighbor v of u:           // where v has not yet been removed from Q.
              alt := dist[u] + length(u, v)
              if alt < dist[v]:               // A shorter path to v has been found
                  dist[v]  := alt
                  previous[v]  := u
              end if
          end for
      end while
      return dist[], previous[]
  end function*/
