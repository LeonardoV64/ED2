#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libf.h"

#define RED 1
#define BLACK 0

struct NO{
    Func info;
    struct NO *esq;
    struct NO *dir;
    int cor, alt;
};

void opcs(){
    printf("\nEscolha um Metodo:\n");
    printf("1 Ordenado\n");
    printf("2 Desordenado\n");
    printf("3 Encerrar Execucao\n");
}

void heapSort(Func *vet, int tam) {
   int i = tam / 2, pai, filho;
   Func aux;
   while(1){
        if (i > 0) {
            i--;
            aux = vet[i];
        } else {
            tam--;
            if (tam <= 0) return;
            aux = vet[tam];
            vet[tam] = vet[0];
        }
        pai = i;
        filho = i * 2 + 1;

        while (filho < tam) {
            if ((filho + 1 < tam)  &&  (vet[filho + 1].id > vet[filho].id)){
                filho++;
            }
            if (vet[filho].id > aux.id) {
                vet[pai] = vet[filho];
                pai = filho;
                filho = pai * 2 + 1;
            } else {
                break;
            }
        }
        vet[pai] = aux;
    }
};

Func *data(){//função somente gera o arquivo ordenado
    Func *func = (Func*) malloc(TAM * sizeof(Func));
    int i = 0;
    char texto[300];
    FILE *file;
    if((file = fopen("massaDados.csv","r")) == NULL){
            printf ("Erro na abertura do arquivo.\n");
        }else{
            printf("Arquivo aberto com sucesso.\n");
        }
    /**< como só gera o ordenado, não precisa usar esse if
    if(x==2){
        if((file = fopen("massaDados.csv","r")) == NULL){
            printf ("Erro na abertura do arquivo.");
        }else{
            printf("Arquivo aberto com sucesso.");
        }
    }else{
        if((file = fopen("Resultado.csv","r")) == NULL){
            printf ("Erro na abertura do arquivo.");
        }else{
            printf("Arquivo aberto com sucesso.");
        }
    }
     */
    while(fgets(texto, 300, file)){
        func[i].id = atoi(strtok(texto,";"));
        strcpy(func[i].nome, strtok(NULL, ";"));
        func[i].idade = atoi(strtok(NULL, ";"));
        strcpy(func[i].empresa, strtok(NULL, ";"));
        strcpy(func[i].dpt, strtok(NULL, ";"));
        func[i].sal = atof(strtok(NULL, "\n"));
        i++;
        //note que vc não havia incluido o dado "empresa"
    }
    printf("Gerou o vetor\n");
    fclose(file);

    return func;
}

void escreveArq(Func *vet){
    int i = 0;

    FILE *file = fopen("Resultado.csv","w");
    if(file == NULL){
        printf("\nErro na criação do arquivo!");
        exit(1);
    }else{
        printf("\n\n\nArquivo criado com sucesso!");
    }

    i = 0;
    for(i = 0; i < TAM; i++){
        fprintf( file,"%d;%s;%d;%s;%s;%.2f\n",vet[i].id, vet[i].nome, vet[i].idade, vet[i].empresa, vet[i].dpt, vet[i].sal);
    }

    fclose(file);
}


//Arvore RB

arvoreLLRB *cria_arvoreLLRB(){
    arvoreLLRB *raiz = (arvoreLLRB*) malloc(sizeof(arvoreLLRB));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

void libera_NO(struct NO *no){
    if(no == NULL){
        return;
    }
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void liberar_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    libera_NO(*raiz);
    free(raiz);
}

int vazia_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return 1;
    }
    if(*raiz == NULL){
        return 1;
    }
    return 0;
}


int cor(struct NO *H){
    if(H == NULL){
        return BLACK;
    }else{
        return H->cor;
    }
}

void trocaCor(struct NO *H){
    H->cor = !H->cor;
    if(H->esq != NULL){
        H->esq->cor = !H->esq->cor;
    }
    if(H->dir != NULL){
        H->dir->cor = !H->dir->cor;
    }
}

struct NO *rotacionaEsquerda(struct NO *A){
    struct NO *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NO *rotacionaDireita(struct NO *A){
    struct NO *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NO *move2EsqRED(struct NO *H){
    trocaCor(H);
    if(cor(H->dir->esq) == RED){
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
}

struct NO *move2DirRED(struct NO *H){
    trocaCor(H);
    if(cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
}

struct NO *balancear(struct NO *H){
    if(cor(H->dir) == RED){
        H = rotacionaEsquerda(H);
    }
    if(H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }
    return H;
}


struct NO *insereNO(struct NO *H, Func dados, int *resp){
    if(H == NULL){
        struct NO *novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL){
            *resp = 0;
            return NULL;
        }
        novo->info = dados;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }
    if(dados.id == H->info.id){
        *resp = 0;
    }else{
        if(dados.id < H->info.id){
            H->esq = insereNO(H->esq, dados, resp);
        }else{
            H->dir = insereNO(H->dir, dados, resp);
        }
    }
    if(cor(H->dir) == RED && cor(H->esq) == BLACK){
        H = rotacionaEsquerda(H);
    }
    if(cor(H->esq) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }
    return H;
}

int insere_arvoreLLRB(arvoreLLRB *raiz, Func dados){
    int resp;

    *raiz = insereNO(*raiz, dados, &resp);
    if((*raiz) != NULL){
        (*raiz)->cor = BLACK;
    }
    return resp;
}

//Arvore AVl

arvAVL *cria_arvAVL(){
    arvAVL *raiz = (arvAVL*) malloc(sizeof(arvAVL));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}


void liberar_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    libera_NO(*raiz);
    free(raiz);
}

int vazia_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return 1;
    }
    if(*raiz == NULL){
        return 1;
    }
    return 0;
}


int alt_no(struct NO *no){
    if(no == NULL){
        return -1;
    }else{
        return no->alt;
    }

}

int fatorBalanceamento_NO(struct NO *no){
    return labs(alt_no(no->esq) - alt_no(no->dir));
}

int maior(int x, int y){
    if(x>y){
        return(x);
    }else{
        return(y);
    }
}

void rotacaoLL(arvAVL *raiz){
    struct NO *no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->esq), (*raiz)->alt) + 1;
    *raiz = no;
}

void rotacaoRR(arvAVL *raiz){
    struct NO *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = *raiz;
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->dir), (*raiz)->alt) + 1;
    *raiz = no;
}

void rotacaoLR(arvAVL *raiz){
    rotacaoRR(&(*raiz)->esq);
    rotacaoLL(raiz);
}

void rotacaoRL(arvAVL *raiz){
    rotacaoLL(&(*raiz)->dir);
    rotacaoRR(raiz);
}


int insere_arvAVL(arvAVL *raiz, Func dados){
    int res;
    if(*raiz == NULL){
        struct NO *novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL){
            return 0;
        }
        novo->info = dados;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }
    struct NO *atual = *raiz;
    if(dados.id < atual->info.id){
        if((res = insere_arvAVL(&(atual->esq), dados)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(dados.id < (*raiz)->esq->info.id){
                    rotacaoLL(raiz);
                }else{
                    rotacaoLR(raiz);
                }
            }
        }
    }else{
        if(dados.id > atual->info.id){
            if((res = insere_arvAVL(&(atual->dir), dados)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->info.id < dados.id){
                        rotacaoRR(raiz);
                    }else{
                        rotacaoRL(raiz);
                    }
                }
            }
            }else{
                printf("dados duplicado!\n");
                return 0;
            }
        }
        atual->alt = maior(alt_no(atual->esq), alt_no(atual->dir)) + 1;
        return res;
    }












