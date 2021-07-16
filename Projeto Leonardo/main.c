#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libf.h"
#include <time.h>

int main()
{
    clock_t t_a, t_d, res;
    Func *f, *vet;
    int y =1;
    arvAVL *raiz = cria_arvAVL();
    arvoreLLRB *raizr = cria_arvoreLLRB();

    vet = data();
    heapSort(vet, TAM);
    escreveArq(vet);

    opcs();
    scanf("%d", &y);

        switch (y){
            case 1 :
            t_a = clock();
            f = data();
            insere_arvAVL(raiz, *f);
            t_d = clock();
            res = t_d - t_a;
            printf("%lf", (double)res);

            t_a = clock();
            f = data();
            insere_arvoreLLRB(raizr, *f);
            t_d = clock();
            res = t_d - t_a;
            printf("%lf", (double)res);
            break;

            case 2 :

            t_a = clock();
            insere_arvAVL(raiz, *vet);
            t_d = clock();
            res = t_d - t_a;
            printf("%lf", (double)res);

            t_a = clock();
            insere_arvoreLLRB(raizr, *vet);
            t_d = clock();
            res = t_d - t_a;
            printf("%lf", (double)res);
            break;

            case 3 :
            break;
        }


    free(f);
    free(vet);
    return 0;
}
