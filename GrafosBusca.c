/* Descricao das funcoes declaradas me Grafos - busca.h */
#include <stdio.h>
#include <stdlib.h>
#include "GrafosBusca.h"

//#include "Grafos - Matriz adjacencia.h"

#define INF 2500000

int quantidadeDeVertices(tgrafo *grafo)
{
    return grafo->num_vertices;
}
void guardar(int tam,int matriz_guardada[][tam],int i, int j,int valor)
{
    matriz_guardada[i][j] = valor;
}

void Operacao_Dijkstra(tgrafo *grafo,int numv,int matriz[][numv],int escolha)
{
    /*Pega o numero de vertices
    cria um vetor para armazenar a distancia para cada vertice
    e outro vetor para armazenar os antecessores (menor caminho at� todos) */
    float dist[numv][numv];
    int ant[numv][numv];
    int i, j, marcacao[numv][numv];
    tapontador arestaAtual;
    tapontador_vertice verticeAtual;

    /*Preenche o vetor de dist�ncias com infinito e 0 para a raiz inderida na funcao*/
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

    float menor;
    int contadorMax, cidadeAtual;

    //for para passar por todos os vertices
    for(cidadeAtual = 0; cidadeAtual < numv; cidadeAtual++)
    {
        verticeAtual = grafo->vet[cidadeAtual];
        arestaAtual = grafo->vet[cidadeAtual]->prox;

        //Dijkstra em si
        for(contadorMax = 0; contadorMax < numv; contadorMax++)
        {
            while(arestaAtual != NULL)
            {
                if((arestaAtual->peso + dist[cidadeAtual][verticeAtual->id] < dist[cidadeAtual][arestaAtual->id]) && (marcacao[cidadeAtual][arestaAtual->id] == BRANCO))
                {
                    dist[cidadeAtual][arestaAtual->id] = arestaAtual->peso + dist[cidadeAtual][verticeAtual->id];
                    ant[cidadeAtual][arestaAtual->id] = verticeAtual->id;
                }
                arestaAtual = arestaAtual->prox;
            }
            marcacao[cidadeAtual][verticeAtual->id] = PRETO;

            menor = INF;
            for (i = 0; i < numv; i++)
            {
                if ((dist[cidadeAtual][i] < menor) && (marcacao[cidadeAtual][i] != PRETO))
                {
                    menor = dist[cidadeAtual][i];
                    verticeAtual = grafo->vet[i];
                    arestaAtual = verticeAtual->prox;
                }
            }

            if(menor == INF)
            {
                break;
            }
        }

        if(escolha==1)
        {
            for(i = 0;i<numv;i++)
            {
                for(j = 0;j<numv;j++)
                {
                    guardar(numv,matriz,i,j,ant[i][j]);
                }
            }
        }
        else
        {
            if(escolha==2)
            {
                for(i = 0;i<numv;i++)
                {
                    for(j = 0;j<numv;j++)
                    {
                        guardar(numv,matriz,i,j,dist[i][j]);
                    }
                }
            }
        }
    }

}

//Fun��o que encontra o vertice central de acordo com o Criterio 1
void vertice_central(tgrafo *grafo)
{
    /*Declara��o das constantes e da matriz de distancias
    que ira conter as menores dist�ncias para os v�rtices a partir de cada um dos v�rtices do grafo */
    int i,j;
    int numv = grafo->num_vertices;
    int dist[numv][numv];
    Operacao_Dijkstra(grafo,numv,dist,2); //Chama o Dijkstra para preencher a matriz de distancias

    tapontador_vertice v;

    /*Aqui multiplicamos cada linha da matriz de distancias pelo numero de egressos de seus respectivos vertices
    Com isso, conseguimos uma forma de analisar a distancia total percorrida, considerando o numero de pessoas */
    for(i = 0; i < numv; i++)
    {
        v = grafo->vet[i];
        for(j = 0; j < numv; j++)
        {
            if(dist[i][j] != INF)
            {
                dist[i][j] = dist[i][j]*v->egressos;
            }
        }
    }

    float vet_desloc[numv];
    /*O vetor vet_desloc ira guardar o deslocamento total para chegar a um determinado vertice
    Para isso, fazemos a soma dos elementos de cada coluna
    A soma nos dar� o deslocamento total de pessoas para chegar a essa determinada cidade */
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
    ou seja, o vertice qual tera o menor deslocamento total de pessoas para ser alcan�ado
    Ao encontrarmos o menor deslocamento, atribuimos o indice do vertice com o menor deslocamento
    total � vari�vel cidade central. */
    float menor = vet_desloc[0];
    int cc_crit_1 = 0;
    for(i = 1; i < numv; i++)
    {
        if(menor > vet_desloc[i])
        {
            menor = vet_desloc[i];
            cc_crit_1 = i;
        }
    }
    /*Printamos o indice do vertice central, que ser� a cidade a ser escolhida que satisfaz
    o Criterio 1 */
    printf("%d\n", cc_crit_1);
}

void Dijkstra(tgrafo *grafo)
{
    int numv = grafo->num_vertices;
    int matriz_antecessores[numv][numv];
    Operacao_Dijkstra(grafo,numv,matriz_antecessores,1);
}

void betwenness(tgrafo *grafo)
{
    int numv = grafo->num_vertices;
    int matriz_antecessores[numv][numv];
    Operacao_Dijkstra(grafo,numv,matriz_antecessores,1);
    operacao_betweenness(numv,matriz_antecessores);
}

void operacao_betweenness(int numv,int ant[][numv])
{
    int maior = 0;
    int cidadeAtual, i, j;
    int valorBetweenness[numv];      //cada lugar do vetor armazena o valor de betweenness para cada vertice
    int seguidorDeCaminho;           //a funcao dessa variavel esta explicada abaixo

    for (j = 0; j < numv; j++)
    {
        valorBetweenness[j] = 0;                        //iniciliza o vetor nulo
    }

    for(cidadeAtual = 0; cidadeAtual < numv; cidadeAtual++)
    {  // cidade em que est� sendo calculado o betweenness
        for(i = 0; i < numv; i++)
        {                            //linha da matriz: cidade de origem
            if(i != cidadeAtual)
            {                             //a cidade que estamos analisando n�o pode ser origem
                for(j = 0; j < numv; j++)
                {                    //cidade de destino
                    if(j > i && j != cidadeAtual)
                    {            /*a primeira compara��o serve como otimiza��o para grafos n�o
                                                              orientados (para ida e volta, o menor caminho � o mesmo) e a
                                                              segunda determina que a cidade analisada n�o pode ser destino*/
                        seguidorDeCaminho = ant[i][j];           /*seguidorDeCaminho serve para armazenar os v�rtices antecessores
                                                                permitindo assim "caminhar" pelo vetor do destino at� a origem*/
                        while(seguidorDeCaminho != -1)
                        {
                            if(seguidorDeCaminho == cidadeAtual)
                            {       /*se o seguidorDeCaminho for igual a cidade analisada
                                                                        ela est� no meio de um dos menores caminhos no grafo,
                                                                        ent�o temos que incrementar o valor de betweenness da cidade
                                                                        e j� podemos analisar outros caminhos*/
                                valorBetweenness[cidadeAtual]++;
                                seguidorDeCaminho = -1;
                            }
                            else
                            {
                                seguidorDeCaminho = ant[i][seguidorDeCaminho];  //se n�o encontrar a cidade que queremos, volta no caminho
                            }
                        }
                    }
                }
            }
        }
    }
    for(i=0;i<numv-1;i++)
    {
        if(valorBetweenness[i]<valorBetweenness[i+1])
        {
            maior = i+1;
        }
    }
    printf("%d",maior);
}




