// Nome: Felipe de Freitas Percinoto RA: 275170
#include <stdio.h>
#include <stdlib.h>
// Vamos comecar definindo o struct básico das notas normais e substutivas com nó do nosso codigo (por "nosso" subentende-se "meu" pois sou apenas uma pessoa usando linguajar de livro de matematica);
typedef struct Notas {
    int RA;
    double P1;
    double P2;
    double P3;
    double Media;
    struct Notas *prox;
} Notas;
typedef struct Subs {
    int RA;
    double N_Subs;
    struct Subs *prox;
} Subs;
// Uma função de inserção que vai computar nossos dados e vai percorrer a nossa lista usando nós;
void insercao(Notas **inicio, Subs **inicio_s) {
    int alunos, alunos_s, i;
    Notas *final = NULL;
    Subs *final_s = NULL;
    scanf("%d", &alunos);
    for(i=0; i<alunos; i++) {
        Notas *nota = (Notas*)malloc(sizeof(Notas));
        scanf("%d %lf %lf %lf", &nota->RA, &nota->P1, &nota->P2, &nota->P3);
        nota->prox = NULL;
        if(*inicio == NULL) {
            *inicio = nota;
            final = nota;
        } else {
            final->prox = nota;
            final = nota;
        }
    }
    scanf("%d", &alunos_s);
    for(i=0; i<alunos_s; i++) {
        Subs *sub = (Subs*)malloc(sizeof(Subs));
        scanf("%d %lf", &sub->RA, &sub->N_Subs);
        sub->prox = NULL; 
        if(*inicio_s == NULL) {
            *inicio_s = sub;
            final_s = sub;
        } else {
            final_s->prox = sub;
            final_s = sub;
        }
    }
}
// Feito a computação dos dados, iremos verificar se a nota da substutiva será utilizada no lugar da menor nota e, logo em seguida, calcularemos a média;
void substitutiva(Notas *notas, Subs *subs){
    Notas *nota;
    Subs *sub;
    for(sub = subs; sub != NULL; sub= sub->prox){
        for(nota= notas; nota!= NULL; nota= nota->prox){
            if(nota->RA == sub->RA){
                double menor_nota = nota->P1;
                int posicao = 1;
                if(menor_nota > nota->P2){
                    menor_nota = nota->P2;
                    posicao = 2;
                } else if(menor_nota> nota->P3){
                    menor_nota = nota->P3;
                    posicao = 3;
                }
                if(posicao == 1){
                    nota->P1 = sub->N_Subs;
                } else if(posicao == 2){
                    nota->P2 = sub->N_Subs;
                } else if(posicao == 3){
                    nota->P3 = sub->N_Subs;
                }
                break;
            } 
        }
    }
    for(nota= notas; nota!= NULL; nota= nota->prox){
        nota->Media =(nota->P1 + nota->P2 + nota->P3)/3.0; 
    }
}
// Feita a substituição e o calculo de média, iremos realizar a ordenação utilizando inserction sort e em seguida a impressão final.
void ordenacao(Notas **notas){
    Notas *ordenado = NULL;
    Notas *nota_atual = *notas;
    while(nota_atual != NULL){
        Notas *proximo = nota_atual->prox;
        if(ordenado== NULL || nota_atual->Media >ordenado->Media || (nota_atual->Media == ordenado->Media && nota_atual->RA < ordenado->RA)){
            nota_atual->prox = ordenado;
            ordenado = nota_atual;
        } else {
            Notas *aux = ordenado;
            while(aux->prox != NULL && (aux->prox->Media >nota_atual->Media || (aux->prox->Media == nota_atual->Media && aux->prox->RA <nota_atual->RA))) {
                aux = aux->prox;
            }
            nota_atual->prox = aux->prox;
            aux->prox = nota_atual;
        }
        nota_atual = proximo;
    }
    *notas = ordenado;
}
void impressao(Notas *notas){
    Notas *nota;
    for(nota= notas; nota!=NULL; nota= nota->prox){
        printf("%d %.1f\n", nota->RA, nota->Media);
    }
}
// Na função main faremos a chamada das funções de substituição & ordenação, as inserções e a impressão final. Nela, também definimos os ponteiros dos structs a serem preenchidos e processados pelas demais funções.
int main(){
    Notas *notas = NULL;
    Subs *subs = NULL;
    insercao(&notas, &subs);
    substitutiva(notas, subs);
    ordenacao(&notas);
    impressao(notas);
    return 0;
}