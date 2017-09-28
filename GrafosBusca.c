/* Descricao das funcoes declaradas me GrafosBusca.h */
#include <stdio.h>
#include <stdlib.h>
#include "GrafosBusca.h"

#define INF 2500000

void vertice_central(tgrafo *grafo)
{
    int numv = quantidadeDeVertices(grafo);
    /*Cria uma matriz para as menores distancias e uma outra para os caminhos percorridos
    as cidades estão da seguinte maneira:
        -Linhas: cidade de origem
        -Colunas: cidade de destino*/
    float dist[numv][numv];
    int ant[numv][numv];

    /*i e j, variaveis auxiliares para percorrer a matriz
    a matriz marcacao serve para marcar os vertices já analisados durante a execucao do algoritmo de Dijkstra*/
    int i, j, marcacao[numv][numv];

    /*Preenche a matriz de distancias com infinito e 0 para a diagonal principal
    inicialmente marca todos os vertices como brancos (nao analisados)*/
    for (i = 0; i < numv; i++)
    {
        for(j = 0; j < numv; j++)
        {
            if(i == j)
            {
                dist[i][j] = 0;
            }
            else
            {
                dist[i][j] = INF;
            }
            marcacao[i][j] = BRANCO;
            ant[i][j] = -1;
        }
    }

    /*menor é utilizada para pegar a menor distancia durante a execução do Dijkstra
    contadorMax serve para analisar no maximo a quantidade de vertices no grafo
    cidadeAtual é a cidade de origem  */
    float menor;
    int contadorMax, cidadeAtual;

    //ponteiros para aresta e vertice, respectivamente
    tapontador arestaAtual;
    tapontador_vertice verticeAtual;

    //for para o Dijkstra ter origem em todos os vertices
    for(cidadeAtual = 0; cidadeAtual < numv; cidadeAtual++)
    {
        //verticeAtual aponta para o vertice que está sendo analisado
        verticeAtual = grafo->vet[cidadeAtual];
        //arestaAtual aponta para a aresta que está sendo analisada
        arestaAtual = grafo->vet[cidadeAtual]->prox;

        //Dijkstra em si para um vertice
        for(contadorMax = 0; contadorMax < numv; contadorMax++)
        {
            while(arestaAtual != NULL)      //verifica todos as arestas de um vertice
            {
                // if verifica se o vertice já foi analisado e se a distância encontrada nessa iteração é menor do que a encontrada nas anteriores
                if((arestaAtual->peso + dist[cidadeAtual][verticeAtual->id] < dist[cidadeAtual][arestaAtual->id]) && (marcacao[cidadeAtual][arestaAtual->id] == BRANCO))
                {
                    dist[cidadeAtual][arestaAtual->id] = arestaAtual->peso + dist[cidadeAtual][verticeAtual->id];
                    ant[cidadeAtual][arestaAtual->id] = verticeAtual->id;
                }
                arestaAtual = arestaAtual->prox;
            }
            marcacao[cidadeAtual][verticeAtual->id] = PRETO;        //terminou de analisar o vertice, marca-o como PRETO

            menor = INF;
             //aqui pegamos a menor das distâncias na linha da matriz correspondente a cidade de origem
            for (i = 0; i < numv; i++)
            {
                if ((dist[cidadeAtual][i] < menor) && (marcacao[cidadeAtual][i] != PRETO)) //deve-se verificar se o vértice já foi analisado
                {
                    menor = dist[cidadeAtual][i];
                    verticeAtual = grafo->vet[i];
                    arestaAtual = verticeAtual->prox;
                }
            }

            /*se a menor distância for infinito, significa que não há caminho entre a cidade de origem
            e as que ainda não foram analisadas, portanto podemos parar a execução do Dijkstra*/
            if(menor == INF)
            {
                break;
            }
        }
    }

    printf("\nMatriz de distancias: \n");
    for(i = 0; i < numv; i++){
        for(j = 0; j < numv; j++){
            printf("%.2f  ", dist[i][j]);
        }
        printf("\n");
    }

    printf("\nMatriz de caminhos: \n");
    for(i = 0; i < numv; i++){
        for(j = 0; j < numv; j++){
            printf("%d  ", ant[i][j]);
        }
        printf("\n");
    }


     /*Aqui multiplicamos cada linha da matriz de distancias pelo numero de egressos de seus respectivos vertices
    Com isso, conseguimos uma forma de analisar a distancia total percorrida, considerando o numero de pessoas */
    for(i = 0; i < numv; i++)
    {
        verticeAtual = grafo->vet[i];
        for(j = 0; j < numv; j++)
        {
            if(dist[i][j] != INF)
            {
                dist[i][j] = dist[i][j]*verticeAtual->egressos;
            }
        }
    }

    float vet_desloc[numv];
    /*O vetor vet_desloc ira guardar o deslocamento total para chegar a um determinado vertice
    Para isso, fazemos a soma dos elementos de cada coluna
    A soma nos dará o deslocamento total de pessoas para chegar a essa determinada cidade */
    for(i = 0; i < numv; i++)
    {
        vet_desloc[i] = 0;
    }
    for(i = 0; i < numv; i++)
    {
        for(j = 0; j < numv; j++)
        {
            if(dist[j][i] != INF)
            {
                vet_desloc[i] = vet_desloc[i] + dist[j][i];
            }
        }
    }

    /*Aqui, percorremos o vetor que contem os deslocamentos, escolhendo o menor deles
    ou seja, o vertice qual tera o menor deslocamento total de pessoas para ser alcançado
    Ao encontrarmos o menor deslocamento, atribuimos o indice do vertice com o menor deslocamento
    total à variável cidade central. */
    menor = vet_desloc[0];
    int cc_crit_1 = 0;
    for(i = 1; i < numv; i++)
    {
        if(menor > vet_desloc[i])
        {
            menor = vet_desloc[i];
            cc_crit_1 = i;
        }
    }
    /*Printamos o indice do vertice central, que será a cidade a ser escolhida que satisfaz
    o Criterio 1 */
    printf("%d\n", cc_crit_1);


}

void betwenness(tgrafo *grafo)
{
    int numv = quantidadeDeVertices(grafo);
    /*Cria uma matriz para as menores distancias e uma outra para os caminhos percorridos
    as cidades estão da seguinte maneira:
        -Linhas: cidade de origem
        -Colunas: cidade de destino*/
    float dist[numv][numv];
    int ant[numv][numv];

    /*i e j, variaveis auxiliares para percorrer a matriz
    a matriz marcacao serve para marcar os vertices já analisados durante a execucao do algoritmo de Dijkstra*/
    int i, j, marcacao[numv][numv];

    /*Preenche a matriz de distancias com infinito e 0 para a diagonal principal
    inicialmente marca todos os vertices como brancos (nao analisados)*/
    for (i = 0; i < numv; i++)
    {
        for(j = 0; j < numv; j++)
        {
            if(i == j)
            {
                dist[i][j] = 0;
            }
            else
            {
                dist[i][j] = INF;
            }
            marcacao[i][j] = BRANCO;
            ant[i][j] = -1;
        }
    }

    /*menor é utilizada para pegar a menor distancia durante a execução do Dijkstra
    contadorMax serve para analisar no maximo a quantidade de vertices no grafo
    cidadeAtual é a cidade de origem  */
    float menor;
    int contadorMax, cidadeAtual;

    //ponteiros para aresta e vertice, respectivamente
    tapontador arestaAtual;
    tapontador_vertice verticeAtual;

    //for para o Dijkstra ter origem em todos os vertices
    for(cidadeAtual = 0; cidadeAtual < numv; cidadeAtual++)
    {
        //verticeAtual aponta para o vertice que está sendo analisado
        verticeAtual = grafo->vet[cidadeAtual];
        //arestaAtual aponta para a aresta que está sendo analisada
        arestaAtual = grafo->vet[cidadeAtual]->prox;

        //Dijkstra em si para um vertice
        for(contadorMax = 0; contadorMax < numv; contadorMax++)
        {
            while(arestaAtual != NULL)      //verifica todos as arestas de um vertice
            {
                // if verifica se o vertice já foi analisado e se a distância encontrada nessa iteração é menor do que a encontrada nas anteriores
                if((arestaAtual->peso + dist[cidadeAtual][verticeAtual->id] < dist[cidadeAtual][arestaAtual->id]) && (marcacao[cidadeAtual][arestaAtual->id] == BRANCO))
                {
                    dist[cidadeAtual][arestaAtual->id] = arestaAtual->peso + dist[cidadeAtual][verticeAtual->id];
                    ant[cidadeAtual][arestaAtual->id] = verticeAtual->id;
                }
                arestaAtual = arestaAtual->prox;
            }
            marcacao[cidadeAtual][verticeAtual->id] = PRETO;        //terminou de analisar o vertice, marca-o como PRETO

            menor = INF;
             //aqui pegamos a menor das distâncias na linha da matriz correspondente a cidade de origem
            for (i = 0; i < numv; i++)
            {
                if ((dist[cidadeAtual][i] < menor) && (marcacao[cidadeAtual][i] != PRETO)) //deve-se verificar se o vértice já foi analisado
                {
                    menor = dist[cidadeAtual][i];
                    verticeAtual = grafo->vet[i];
                    arestaAtual = verticeAtual->prox;
                }
            }

            /*se a menor distância for infinito, significa que não há caminho entre a cidade de origem
            e as que ainda não foram analisadas, portanto podemos parar a execução do Dijkstra*/
            if(menor == INF)
            {
                break;
            }
        }
    }

    int maior = 0;
    int valorBetweenness[numv];      //cada lugar do vetor armazena o valor de betweenness para cada vertice
    int seguidorDeCaminho;           //a funcao dessa variavel esta explicada abaixo

    for (j = 0; j < numv; j++)
    {
        valorBetweenness[j] = 0;                        //iniciliza o vetor nulo
    }

    for(cidadeAtual = 0; cidadeAtual < numv; cidadeAtual++)         // cidade em que está sendo calculado o betweenness
    {
        for(i = 0; i < numv; i++)                                   //linha da matriz: cidade de origem
        {
            if(i != cidadeAtual)                                    //a cidade que estamos analisando não pode ser origem
            {
                for(j = 0; j < numv; j++)                           //coluna da matriz: cidade de destino
                {
                    if(j > i && j != cidadeAtual)                   /*a primeira comparação serve como otimização para grafos não
                                                                    orientados (para ida e volta, o menor caminho é o mesmo) e a
                                                                    segunda determina que a cidade analisada não pode ser destino*/
                    {
                        seguidorDeCaminho = ant[i][j];           /*seguidorDeCaminho serve para armazenar os vértices antecessores
                                                                permitindo assim "caminhar" pelo vetor do destino até a origem*/

                        while(seguidorDeCaminho != -1)         //se o seguidorDeCaminho for -1, quer dizer que retornamos a origem
                        {
                            if(seguidorDeCaminho == cidadeAtual)        /*se o seguidorDeCaminho for igual a cidade analisada
                                                                        ela está no meio de um dos menores caminhos no grafo,
                                                                        então temos que incrementar o valor de betweenness da cidade
                                                                        atual e já podemos analisar outros caminhos*/
                            {
                                valorBetweenness[cidadeAtual]++;
                                seguidorDeCaminho = -1;
                            }
                            else
                            {
                                seguidorDeCaminho = ant[i][seguidorDeCaminho];  /*se não encontrar a cidade que queremos,
                                                                                continua percorrendo o caminho*/
                            }
                        }
                    }
                }
            }
        }
    }

    //encontra o maior valor de betweenness e printa a cidade com esse valor
    for(i=0;i<numv-1;i++)
    {
        if(valorBetweenness[i]<valorBetweenness[i+1])
        {
            maior = i+1;
        }
    }
    printf("%d  %d",maior, valorBetweenness[maior]);

}

