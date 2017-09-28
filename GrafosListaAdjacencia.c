#include <stdio.h>
#include <stdlib.h>
#include "GrafosListaAdjacencia.h"

/* Descricao das funcoes utilizadas */
void inicializaGrafo(tgrafo *grafo, int num_vertices)
{
    int i;
	if(num_vertices > MAXNUMVERTICES)
	{
		printf("Erro: numero de vertices supera o maximo!\n");
		return;
	}
	else
	{
		grafo->num_vertices = num_vertices;

		for (i = 0; i < num_vertices; i++)
		{

			grafo->vet[i] = (tvertice*)malloc(sizeof(tvertice));                    //controi o vetor de vertices com suas informacoes

			if(!grafo->vet[i])
			{
				printf("Erro: espaco insuficiente na memoria!\n");
				return;
			}
			else
			{
				//Vertices com inicio em 0
				grafo->vet[i]->id= i;
				grafo->vet[i]->prox = NULO;
			}
		}
	}
}

void insere_aresta(tgrafo *grafo, svertice v, svertice u, tpeso peso)
{
	taresta* new1 = (taresta*)malloc(sizeof(taresta));
	taresta* new2 = (taresta*)malloc(sizeof(taresta));

	if(new1 == NULO || new2 == NULO)
	{
		printf("Erro: Espaco insuficiente!\n");
		return;
	}

	else
	{
	    tapontador aux;
	    //Insercao dos elementos no bloco novo
		aux = grafo->vet[v]->prox;
		new1->peso = peso;
		new1->id = u;
		new1->prox = aux;
		grafo->vet[v]->prox = new1;

        aux = grafo->vet[u]->prox;
		new2->peso = peso;
		new2->id = v;
		new2->prox = aux;
		grafo->vet[u]->prox = new2;


	}
}


void insere_egressos(tgrafo *grafo, svertice v,int egressos)
{
    grafo->vet[v]->egressos = egressos;
}

void printaGrafo(tgrafo *grafo,int num_vertices)
{
    int i;
    tapontador aux;
    tapontador_vertice aux2;
    for(i = 0; i < num_vertices; i++)
    {
            aux2 = grafo->vet[i];
            printf(" Cidades conectadas com %d de %d habitantes: ", aux2->id, aux2->egressos);
            aux = aux2->prox;
            while(aux != NULL)
            {
                    printf("(Peso: %.2f  Cidade: %d   )  ", aux->peso, aux->id);
                    aux = aux->prox;
            }
            printf("\n");
    }
}

int quantidadeDeVertices(tgrafo *grafo)
{
    return grafo->num_vertices;
}
