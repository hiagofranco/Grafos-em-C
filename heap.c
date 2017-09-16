#include<stdio.h>
#include<stdlib.h>
#include"heap.h"

    void inicializarHeap(Heap *h, int tam_max)
    {
      h->tam_atual = 0;
      h->tam_max = tam_max;
    }
    int pai(int i)
    {
      return i/2;
    }

    int filhoEsquerda(int i)
    {
      return 2*i;
    }

    int filhoDireita(int i)
    {
      return 2*i + 1;
    }

    void destruirHeap(Heap * h)
    {
      free(h->prioridade);
      h->tam_max=0;
      h->tam_atual=0;
    }

    void minHeapify(Heap *h, int i)
    {
      int esq = filhoEsquerda(i);
      int dir = filhoDireita(i);
      int temp;
      int menor = i;
        if ((esq < h->tam_atual) && (h->prioridade[esq]<h->prioridade[i]))
        {
            menor = esq;
        }
        if ((dir < h->tam_atual) && (h->prioridade[dir]<h->prioridade[menor]))
        {
            menor = dir;
        }

        if (menor != i)
        {
            temp = h->prioridade[i];
            h->prioridade[i] = h->prioridade[menor];
            h->prioridade[menor] = temp;
            minHeapify(h,menor);
        }
    }

    void construirHeapMin(Heap *h)
    {
      int i;
      int metadeTamanho = h->tam_atual/2;
      for (i=metadeTamanho;i>0;i--)
      {
            minHeapify(h,i);
      }
    }

    int inserirForaDeOrdem(Heap * h, int valor)
    {
        if (h->tam_atual< h->tam_max)
        {
            h->prioridade[h->tam_atual] = valor;
            h->tam_atual = h->tam_atual+1;
            return 1;
        }
        return 0;
    }

    void imprimirArranjo(Heap h)
    {
      int tamanho = h.tam_atual;
      int i;
      for (i=0;i<tamanho;i++)
      {
          printf("%.2f\t",h.prioridade[i]);

      }
    }
    int inserirHeap(Heap *h, int chave)
    {
        int i, temp;
        if (h->tam_atual == h->tam_max)
        {
            return 0;
        }
        i = h->tam_atual;
        h->prioridade[i] = chave;
        h->tam_atual = h->tam_atual+1;
        while ((i>1) && (h->prioridade[pai(i)]<h->prioridade[i]))
        {
            temp = h->prioridade[i];
            h->prioridade[i] = h->prioridade[pai(i)];
            h->prioridade[pai(i)] = temp;
            i = pai(i);
        }
            return 1;
    }
    int Min_valor(Heap *h)
    {
        return h->prioridade[1];
    }
