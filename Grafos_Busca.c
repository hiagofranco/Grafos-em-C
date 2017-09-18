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
                if(i != j && j != k){
                    if(dist[j][i] + dist[i][k] < dist[j][k])
                    dist[j][k] = dist[j][i] + dist[i][k];
                }
            }
        }
   }

   tapontador_vertice v;

   /*Multiplica a matriz pelo numero de egressos
   para levarmos em conta o menor deslocamento de pessoas
   (pessoas * deslocamento)*/
   for(i = 0; i < V; i++){
        for(j = 0; j < V; j++){
            v = grafo->vet[i];
            dist[i][j] = dist[i][j]*v->egressos;
        }
   }

   /* Cria um vetor de excentricidades*/
   int exc[V];
   /*Encontra o custo máximo de cada coluna da matriz*/
   int maior = 0;
   for(i = 0; i < V; i++){
        for(j = 0; j < V; j++){
            if(i != j && dist[j][i] != INF && maior < dist[j][i])
                maior = dist[j][i];
        }
        exc[i] = maior;
        maior = 0;
   }

   maior = exc[0];
   int verticecentral = 0;
   int entradas;
   tapontador q;

   /*Escolhe o vértice central
   O de menos excentricidade entre as maiores */
   for(i = 0; i < V; i++){
        p = grafo->vet[i];
        for(j = 0; j < V; j++){
            q = grafo->vet[j];
            q = q->prox;
            entradas = 0;
            while(q != NULL){
                if(i != j && q->id == p->id){
                    entradas = 1;
                }
                q = q->prox;
            }
            if(entradas == 1 && exc[p->id] < maior){
                maior = exc[p->id];
                verticecentral = p->id;
            }
        }
   }

    return verticecentral;
}

void Dijkstra(tgrafo *grafo, int verticev){
    /*Pega o numero de vertices
    cria um vetor para armazenar a distancia para cada vertice
    e outro vetor para armazenar os antecessores (menor caminho até todos) */
    int numv = grafo->num_vertices;
    int dist[numv], ant[numv];
    int i;

    /*Preenche o vetor de distâncias com infinito e 0 para a raiz inderida na funcao*/
    for(i = 0; i < numv; i++){
        if(i == verticev){
            dist[i] = 0;
        }
        else{
            dist[i] = INF;
        }
        ant[i] = -1;
    }
    /*Inicializa a árvore*/
    minHeap h;
    h = initMinHeap(numv);

    /*Inicializa um ponteiro para o vertice raiz
    aponta para o proximo
    armazenando na arvore os ids dos vertice ao qual a raiz está ligada
    mais a distancia de ligação entre eles */
    tapontador p;
    p = grafo->vet[verticev];
    p = p->prox;
    while(p != NULL){
        insertNode(&h,&p);
        p = p->prox;
    }

    tapontador u,v;
    int alt;

    /*Aqui, a ideia é retirar os nos da heap, que esta ordenada com os menores caminhos na raiz
    e com isso ir atualizando os valores do vetor de distancia e de antecessores */
    while(!isEmpty(&h)){
        *u = retirar_Min(&h);
        v = grafo->vet[u->id]->prox;
        while(v != NULL){
            if(dist[u->id] == INF){
                alt = v->peso;
            }
            else{
                alt = dist[u->id] + v->peso;
            }
            if(alt < dist[v->id]){
                dist[v->id] = alt;
                ant[v->id] = u->id;
            }
            v = v->prox;
        }
    }

    /*Printa o vetor de menores distancias*/
    printf("\nMenores distancias:");
    for(i = 0; i < numv; i++){
        printf(" %d", dist[i]);
    }
    /*Printa o vetor de menores caminhos (antecessores)*/
    printf("\nAntecessores (caminho):");
    for(i = 0; i < numv; i++){
        printf(" %d", ant[i]);
    }

}

/*  PSEUDOCÓDIGO QUE USEI PARA GERAR ESSE LINDO ALGORITMO
    function Dijkstra(Graph, source):
       dist[source]  := 0                     // Distance from source to source
       for each vertex v in Graph:            // Initializations
           if v ≠ source
               dist[v]  := infinity           // Unknown distance function from source to v
               previous[v]  := undefined      // Previous node in optimal path from source
           end if
           add v to Q                         // All nodes initially in Q
       end for

      while Q is not empty:                  // The main loop
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
  end function */
