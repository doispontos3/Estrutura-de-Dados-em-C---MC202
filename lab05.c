// Nome: Felipe de Freitas Percinoto RA: 275170
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Vamos definir as estruturas de fila e pilha com struct pra definir o topo e base das estruturas e nós de lista ligada pra armazenar os dados dentro desse struct.
// Também iremos definir a nossa ABB. Nesse trabalho até da pra usar um vetor no lugar da ABB e depois compensar por nossa decisão burra lá nas funções que exigem busca, mas como 
// nas instruções fala de como lidar com ABB, subtende-se que realmente devemos usar ABB, portanto escreverei 100 linhas de struct e operação de vetores a mais em troca de funções de busca triviais.
typedef struct no_fila{
    int indice;
    struct no_fila *prox;
} no_fila;
typedef struct fila_encomendas{
    int num;
    no_fila *inicio;
    no_fila *fim;
} fila_encomendas;
typedef struct no_pilha{
    int indice;
    struct no_pilha *prox;
} no_pilha;
typedef struct pilha_descartes{
    int num;
    no_pilha *topo;
} pilha_descartes;
typedef struct ABB {
    int valor;
    struct ABB *esq;  
    struct ABB *dir; 
} ABB;
// Para definir nossa função usar(), devemos primeiro definir outras mini-funções que removam o valor X da nossa árvore e a reconstruam logo em seguida, se não todas ramificações que partem de X terão seus valores perdidos.
// Para maior parte das funções é interessante utilizar o void já que não precisamos de valores retornados, porém é mais comodo reconstruir a árvore com return após utilizar a função usar().
ABB* menor_no(ABB *raiz) {
    ABB *atual = raiz;
    while(atual && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}
ABB* remover_no(ABB *raiz, int indice, int *removido, int *valor_removido) {
    if(raiz== NULL) {
        *removido = 0;
        return NULL;
    }
    if(indice< raiz->valor) {
        raiz->esq = remover_no(raiz->esq, indice, removido, valor_removido);
    } else if(indice > raiz->valor) {
        raiz->dir = remover_no(raiz->dir, indice, removido, valor_removido);
    } else {
        *removido = 1;
        *valor_removido = raiz->valor;
        if(raiz->esq== NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        } else if(raiz->esq== NULL) {
            ABB *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if(raiz->dir== NULL) {
            ABB *temp = raiz->esq;
            free(raiz);
            return temp;
        } else {
            ABB *sucessor = menor_no(raiz->dir);
            int indice_sucessor = sucessor->valor;
            raiz->dir = remover_no(raiz->dir, indice_sucessor, removido, valor_removido);
            raiz->valor = indice_sucessor;
            *valor_removido = indice; 
        }
    }
    return raiz;
}
// Depois de definir as funções auxiliares que reconstroem os nós da ABB, vamos definir as funções auxiliares que iniciam e colocam ou removem os indices das pilhas e das filas.
void inicializar_fila(fila_encomendas *fila) {
    fila->inicio = NULL;
    fila->fim= NULL;
    fila->num = 0;
}
void inicializar_pilha(pilha_descartes *pilha) {
    pilha->topo = NULL;
    pilha->num = 0;
}
int desenfileirar(fila_encomendas *fila) {
    if(fila->inicio== NULL) {
        printf("FILA_VAZIA\n");
        return 0;
    }
    no_fila *temp = fila->inicio;
    int valor = temp->indice;
    fila->inicio = fila->inicio->prox;
    if(fila->inicio== NULL) {
        fila->fim = NULL;
    }
    fila->num--;
    return valor;
}
void empilhar(pilha_descartes *pilha, int indice) {
    no_pilha *novo =(no_pilha*)malloc(sizeof(no_pilha));
    novo->indice = indice;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->num++;
}
int desempilhar(pilha_descartes *pilha) {
    if(pilha->topo== NULL) {
        printf("PILHA_VAZIA\n");
        return 0;
    }
    no_pilha *temp = pilha->topo;
    int valor = temp->indice;
    pilha->topo = pilha->topo->prox;
    pilha->num--;
    return valor;
}
// Para cada instrução, vamos definir uma função void e executa-la logo após computa-la na main.
void inserir(ABB **raiz, int indice){
    if(*raiz== NULL){
        *raiz = (ABB*)malloc(sizeof(ABB));
        (*raiz)->valor = indice;
        (*raiz)->esq = (*raiz)->dir = NULL;
        return;
    }
    if(indice <(*raiz)->valor)
        inserir(&(*raiz)->esq, indice);
    else if(indice >(*raiz)->valor)
        inserir(&(*raiz)->dir, indice);
}
// Definidas as sub-funções recursivas que reestruturam a árvore, podemos chamar a função usar() de fato.
void usar(ABB **raiz, pilha_descartes *pilha, int indice) {
    int removido = 0;
    int valor_removido = 0;
    *raiz = remover_no(*raiz, indice, &removido, &valor_removido);
    if(removido){
        empilhar(pilha, valor_removido);
    }
}
void recuperar(ABB **raiz, pilha_descartes *pilha) {
    int indice =desempilhar(pilha);
    if(indice){
    inserir(raiz, indice); 
    }
}
void encomendar(fila_encomendas *fila, int indice) {
    no_fila *novo =(no_fila*)malloc(sizeof(no_fila));
    novo->indice = indice;
    novo->prox = NULL;
    if(fila->fim== NULL) {
        fila->inicio= novo;
        fila->fim= novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->num++;
}
void receber(ABB **raiz, fila_encomendas *fila) {
    int indice= desenfileirar(fila);
    if(indice){
    inserir(raiz, indice);
    }
}
void verificar(ABB *raiz, int indice){
    if(raiz== NULL){
        printf("AUSENTE\n");
        return;
    }
    if(raiz->valor== indice){
        printf("PRESENTE\n");
        return;
    }
    if(raiz->valor< indice){
        verificar(raiz->dir, indice);
    }
    if(raiz->valor> indice){
        verificar(raiz->esq, indice);
    }
}
int maior_indice(ABB *raiz){
    if(raiz == NULL){
        printf("\n");
        return -1;
    }
    if(raiz->dir == NULL){
        return raiz->valor;
    }
    return maior_indice(raiz->dir);
}
void receita(ABB *raiz, int ultimo) {
    if(raiz== NULL) {
        return;
    }
    receita(raiz->esq, ultimo);
    if(raiz->valor == ultimo){
        printf("%d\n", raiz->valor);
    } else{
        printf("%d ", raiz->valor);
    }
    receita(raiz->dir, ultimo);
}
void essencia(ABB *raiz){
    if(raiz== NULL){
        printf("BOLSA_VAZIA\n");
        return;
    }
    if(raiz->esq== NULL){
        int essencia = raiz->valor;
        printf("%d\n", essencia);
        return;
    }
    essencia(raiz->esq);
}
// Definidas todas funções principais em void, a chamada delas será feita na main() juntamente com a computação das instruções e os índices.
int main(){
    int testes, linhas, teste, linha;
    scanf("%d", &testes);
    for(teste=0; teste<testes; teste++){
        scanf("%d", &linhas);
        char instrucao[11];
        int indice;
        pilha_descartes pilha;
        fila_encomendas fila;
        ABB *arvore= NULL;
        inicializar_pilha(&pilha);
        inicializar_fila(&fila);
        for(linha=0; linha<linhas; linha++){
            scanf("%s", instrucao);
            if(strcmp(instrucao, "RECEBER") != 0 && strcmp(instrucao, "ESSENCIA") != 0 && strcmp(instrucao, "RECUPERAR") != 0 && strcmp(instrucao, "RECEITA") != 0) {
                scanf("%d", &indice);
            } if(strcmp(instrucao, "INSERIR")== 0){
                inserir(&arvore, indice);
            } else if(strcmp(instrucao, "USAR") == 0){
                usar(&arvore, &pilha, indice);
            } else if(strcmp(instrucao, "RECUPERAR") == 0){
                recuperar(&arvore, &pilha);
            } else if(strcmp(instrucao, "ENCOMENDAR")== 0){
                encomendar(&fila, indice);
            } else if(strcmp(instrucao, "RECEBER") == 0){
                receber(&arvore, &fila);
            } else if(strcmp(instrucao, "VERIFICAR") == 0){
                verificar(arvore, indice);
            } else if(strcmp(instrucao, "RECEITA") == 0){
                int ultimo = maior_indice(arvore);
                receita(arvore, ultimo);
            } else{
                essencia(arvore);
            }
        }
    }            
}
