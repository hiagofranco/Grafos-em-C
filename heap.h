#include<stdio.h>

#define TAM_MAX 1000

typedef int parentesco;

    typedef struct
    {
        int tam_max;
        int tam_atual;
        float prioridade[TAM_MAX];
    }Heap;

 void inicializarHeap(Heap *h, int tam_max);
 parentesco pai(int i);
 parentesco filhoEsquerda(int i);
 parentesco filhoDireita(int i);
 void destruirHeap(Heap * h);
 void maxHeapify(Heap *h, int i);
 void construirHeapMaximo(Heap *h);
 int inserirForaDeOrdem(Heap * h, int valor);
 void imprimirArranjo(Heap h);
 int inserirHeap(Heap * h, int chave);
 int Max_valor(Heap *h);
