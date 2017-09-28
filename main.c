#include<stdio.h>
#include"GrafosListaAdjacencia.h"
#include"GrafosBusca.h"
#define TRUE 1
#define FALSE 0


int main()
{
    int i;
    int aux;
    int id1,id2;
    int n_cidades;
    int qt_estrada;
    float estrada_tam;
    int egressos_cidade;
    tgrafo Grafo;

    do
    {
        aux = TRUE;
        printf("Digite o numero de cidades e o numero de estradas em ordem\n");
        //Inicialzia a matriz
        scanf("%d %d",&n_cidades,&qt_estrada);
        if(n_cidades<2 || n_cidades>50)
        {
            printf("Erro: Numero de cidades e incompativel\n");
            aux = FALSE;
        }
        if(qt_estrada<1 || qt_estrada>(n_cidades*n_cidades))
        {
            printf("Erro: Numero de arestas e incompativel\n");
            aux = FALSE;
        }
        if(aux==FALSE)
        {
            system("pause");
            system("cls");
        }
    }while(aux==FALSE);
    inicializaGrafo(&Grafo,n_cidades);

    for(i=0;i<n_cidades;i++)
    {
    //escaneia os egressos para cada cidade (n-1) vezes
        do
        {
            aux = TRUE;
            printf("Digite o numero de egressos da cidade de %d\n",i);
            scanf("%d",&egressos_cidade);
            if(egressos_cidade<0 || egressos_cidade>50)
            {
                printf("Erro: Numero de egressos incompativel\n");
                aux = FALSE;
            }
            if(aux==FALSE)
            {
                system("pause");
                system("cls");
            }
        }while(aux==FALSE);
        insere_egressos(&Grafo,i,egressos_cidade);
    }
    for(i=0;i<qt_estrada;i++)
    {
        printf("\nDigite a cidade de origem, a de destino e distancia entre elas nessa ordem, separando-as por espaco\n");
        //estrada de tamanho d que liga Id1 a Id2
        do
        {
            aux = TRUE;
            scanf("%d",&id1);
            if(id1<0 || id1>=n_cidades)
            {
                printf("Erro: O ID da cidade de origem e incompativel\n");
                aux = FALSE;
            }
            scanf("%d",&id2);
            if(id2<0 || id2>=n_cidades)
            {
                printf("Erro: O ID da cidade de destino e incompativel\n");
                aux = FALSE;
            }
            scanf("%f", &estrada_tam);
            if(estrada_tam<=0 || estrada_tam>100)
            {
                printf("Erro: A distancia entre as estradas e incompativel\n");
                aux = FALSE;
            }
            if(aux==FALSE)
            {
                system("pause");
                system("cls");
                printf("Redigite as cidades e distancia novamente\n");
            }
        }while(aux==FALSE);

        insere_aresta(&Grafo,id1,id2,estrada_tam);
    }
    vertice_central(&Grafo);
    betwenness(&Grafo);
    return 0;
}
