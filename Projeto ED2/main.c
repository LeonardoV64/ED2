//Leonardo Vanderlei da Silva GU3011348
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libf.h"
#include <time.h>

int main()
{
    clock_t t_a, t_d, res;
    Func *f, *vet, *r;
    int y = 0;
    arvAVL *raiz = cria_arvAVL();
    arvoreLLRB *raizr = cria_arvoreLLRB();

    vet = data();
    heapSort(vet, TAM);//16ms
    escreveArq(vet);

    while(y!=3){
    opcs();
    scanf("%d", &y);

        switch (y){
            case 1 :
            t_a = clock();
            f = data();
            insere_arvAVL(raiz, *f);
            t_d = clock();
            res = t_d - t_a;
            printf("Tempo em milissegundos para AVL Desordenada:%lf\n", (double)res);

            t_a = clock();
            f = data();
            insere_arvoreLLRB(raizr, *f);
            t_d = clock();
            res = t_d - t_a;
            printf("Tempo em milissegundos para RB Desordenada:%lf\n", (double)res);
            break;

            case 2 :

            t_a = clock();
            r = datao();
            insere_arvAVL(raiz, *r);
            t_d = clock();
            res = t_d - t_a;
            printf("Tempo em milissegundos para AVL Ordenada:%lf\n", (double)res);

            t_a = clock();
            r = datao();
            insere_arvoreLLRB(raizr, *r);
            t_d = clock();
            res = t_d - t_a;
            printf("Tempo em milissegundos para RB Ordenada:%lf\n", (double)res);
            break;

            case 3 :
            break;
        }
    }

    free(f);
    free(r);
    liberar_arvAVL(raiz);
    liberar_arvoreLLRB(raizr);
    return 0;
}
