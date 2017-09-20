/* Descricao das funcoes declaradas me Grafos - busca.h */
#include <stdio.h>
#include <stdlib.h>
#include "GrafosBusca.h"
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
  Falta o TAD de fila para continuar
}
void dijkstra(struct tgrafo *grafo, tvertice v){
   int V = grafo->num_vertices;
   int dist[V];
   int i;
   for(i = 0; i < V; i++){
    dist[i] = INF;
   }
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
        v = grafo->vet[i];
        for(j = 0; j < V; j++){
            q = grafo->vet[j]->prox;

            entradas = 0;
            while(q != NULL){
                if(i != j && q->id == v->id){
                    entradas = 1;
                }
                q = q->prox;
            }
            if(entradas == 1 && exc[v->id] < maior){
                maior = exc[v->id];
                verticecentral = v->id;
            }
        }
   }

    return verticecentral;
}

void Dijkstra(tgrafo *grafo){
    /*Pega o numero de vertices
    cria um vetor para armazenar a distancia para cada vertice
    e outro vetor para armazenar os antecessores (menor caminho até todos) */
    int numv = grafo->num_vertices;
    float dist[numv][numv];
    int ant[numv][numv];
    int i, j, marcacao[numv][numv];
    tapontador arestaAtual;
    tapontador_vertice verticeAtual;


    /*Preenche o vetor de distâncias com infinito e 0 para a raiz inderida na funcao*/
    for (i = 0; i < numv; i++){
        for(j = 0; j < numv; j++){
            if(i == j){
            dist[i][j] = 0;
        }
        else{
            dist[i][j] = INF;
        }
        marcacao[i][j] = BRANCO;
        ant[i][j] = -1;
        }
    }

    float menor;
    //int menorVertice;
    int contadorMax, contadorVert;

    //for para passar por todos os vertices
    for(contadorVert = 0; contadorVert < numv; contadorVert++){
        verticeAtual = grafo->vet[contadorVert];
        arestaAtual = grafo->vet[contadorVert]->prox;

        //Dijkstra em si
        for(contadorMax = 0; contadorMax < numv; contadorMax++){
            while(arestaAtual != NULL){
                if((arestaAtual->peso + dist[contadorVert][verticeAtual->id] < dist[contadorVert][arestaAtual->id]) && (marcacao[contadorVert][arestaAtual->id] == BRANCO)){
                    dist[contadorVert][arestaAtual->id] = arestaAtual->peso + dist[contadorVert][verticeAtual->id];
                    ant[contadorVert][arestaAtual->id] = verticeAtual->id;
                }
                arestaAtual = arestaAtual->prox;
            }
            marcacao[contadorVert][verticeAtual->id] = PRETO;

            menor = INF;
            for (i = 0; i < numv; i++){
                if ((dist[contadorVert][i] < menor) && (marcacao[contadorVert][i] != PRETO)){
                    menor = dist[contadorVert][i];
                    //menorVertice = i;
                    verticeAtual = grafo->vet[i];
                    arestaAtual = verticeAtual->prox;
                }
            }

            if(menor == INF){
                break;
            }
        }


        /*Printa o vetor de menores distancias*/

        printf("\nVertice de origem : %d", contadorVert);
        printf("\nMenores distancias:");
        for(j = 0; j < numv; j++){
            if(dist[contadorVert][j] == INF){
                printf("  INF");
            }
            else
                printf(" %.2f", dist[contadorVert][j]);
            }
        printf("\n");


        /*Printa o vetor de menores caminhos (antecessores)*/
        printf("\nAntecessores (caminho):");
        for(j = 0; j < numv; j++){
            printf(" %d", ant[contadorVert][j]);
        }
        printf("\n\n");
    }

}
