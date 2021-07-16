#define TAM 15000

typedef struct NO *arvoreLLRB;

typedef struct NO *arvoreLLRB;

typedef struct funcionario{
    int id;
    char nome[70];
    int idade;
    char empresa[60];
    char dpt[80];
    float sal;
} Func;

void opcs();

void heapSort(Func *vet, int tam);

Func *data();

void escreveArq(Func * vet);

//Arvore RB

arvoreLLRB *cria_arvoreLLRB();

void liberar_arvoreLLRB(arvoreLLRB *raiz);

int vazia_arvoreLLRB(arvoreLLRB *raiz);

int insere_arvoreLLRB(arvoreLLRB *raiz, Func dados);

//Arvore AVL

typedef struct NO *arvAVL;

void opcs();

arvAVL *cria_arvAVL();

void liberar_arvAVL(arvAVL *raiz);

int vazia_arvAVL(arvAVL *raiz);

int fatorBalanceamento_NO(struct NO *no);

int maior(int x, int y);

void rotacaoLL(arvAVL *raiz);

void rotacaoRR(arvAVL *raiz);

void rotacaoLR(arvAVL *raiz);

void rotacaoRL(arvAVL *raiz);

int totalNO_arvAVL(arvAVL *raiz);

int insere_arvAVL(arvAVL *raiz, Func dados);



