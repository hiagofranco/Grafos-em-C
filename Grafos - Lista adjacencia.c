#include <stdio.h>
#include <stdlib.h>
#include "Grafos - Lista adjacencia.h"

/* Descricao das funcoes utilizadas */
void inicializaGrafo(tgrafo *grafo, int num_vertices)
{
	if(num_vertices > MAXNUMVERTICES)
	{
		printf("Erro: numero de vertices supera o maximo!\n");
		return;
	}
	else
	{
		grafo->num_vertices = num_vertices;

		for (int i = 0; i < num_vertices; i++)
		{
			grafo->vet[i] = (taresta*)malloc(sizeof(taresta));

			if(!grafo->vet[i])
			{
				printf("Erro: espaco insuficiente na memoria!\n");
				return;
			}
			else
			{
				/* Aqui decidi que os vertices comecariam em 0, nao em 1. Se isto
				 * for trocado, precisamos trocar todo o resto do codigo na parte
				 * de acesso */
				grafo->vet[i]->vertice = i;
				grafo->vet[i]->peso = 1;
				grafo->vet[i]->prox = NULO;
			}
		}
	}
}

void insere_aresta(tgrafo *grafo, tvertice v, tvertice u, tpeso peso)
{
	taresta* new = (taresta*)malloc(sizeof(taresta));

	if(new == NULO)
	{
		printf("Erro: Espaco insuficiente!\n");
		return;
	}
	else
	{
		tapontador aux = grafo->vet[v]->prox;
		new->peso = peso;
		new->vertice = u;
		new->prox = aux;
		grafo->vet[v]->prox = new;
	}
}

void retira_aresta(tgrafo *grafo, tvertice v, tvertice u)
{
	/* Aqui vou precisar de dois ponteiros para poder organizar os ponteiros da
	 * aresta quando exclui-la */
	tapontador aux = grafo->vet[v]->prox;
	tapontador aux2 = grafo->vet[v];

	while(aux != NULO)
	{
		if(aux->vertice == u)
			break;
		else
		{
			aux2 = aux;
			aux = aux->prox;
		}
	}

	if(!aux)
	{
		printf("Erro: vertice nao existe!\n");
		return;
	}

	else
	{
		aux2->prox = aux->prox;
		aux->prox = NULO;
		free(aux);
	}
}

int existe_aresta(tgrafo *grafo, tvertice v, tvertice u)
{
	tapontador aux = grafo->vet[v]->prox;

	while(aux->prox != NULO)
	{
		if(aux->vertice == u)
			return 1;
		else
			return 0;
	}
}

void libera_grafo(tgrafo *grafo)
{
	tapontador aux, aux2;
	for (int i = 0; i < grafo->num_vertices; i++)
	{
		aux = grafo->vet[i];
		aux2 = grafo->vet[i]->prox;
		while(aux2 != NULO)
		{
			free(aux);
			aux = aux2;
			aux2 = aux2->prox;
		}
	}
}

int existe_adj(tgrafo *grafo, tvertice v)
{
	if(!grafo->vet[v]->prox)
		return 1;
	else
		return 0;
}

tapontador primeiro_adj(tgrafo *grafo, tvertice v)
{
	if(existe_adj(grafo, v))
		return grafo->vet[v]->prox;
	else
		return NULO;
}

tapontador prox_adj(tgrafo *grafo, tvertice v)
{
	return grafo->vet[v]->prox;
}
