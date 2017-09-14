#include<stdio.h>
#include"Grafos_Lista_adjacencia.h"

int main()
{
    int i;
    int id1,id2;
    int n_cidades;
    int qt_estrada;
    float estrada_tam;
    int egressos_cidade;
    tgrafo Grafo;

    scanf("%d %d",&n_cidades,&qt_estrada);
    //Inicialzia a matriz
    inicializaGrafo(&Grafo,n_cidades);

    for(i=0;i<n_cidades;i++)
    {
    //escaneia os egressos para cada cidade (n-1) vezes
        scanf("%d",&egressos_cidade);
        insere_egressos(&Grafo,i,egressos_cidade);
    }
    for(i=0;i<qt_estrada;i++)
    {
        //estrada de tamanho d que liga Id1 a Id2
        scanf("%d %d %f", &id1,&id2,&estrada_tam);
        insere_aresta(&Grafo,id1,id2,estrada_tam);
    }

    printaGrafo(&Grafo, n_cidades);

    printf("\nCidade Central: %d", Floydinho(&Grafo));
    return 0;
}
