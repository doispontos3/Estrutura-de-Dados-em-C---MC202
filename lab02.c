#include <stdio.h>
// Aluno : Felipe de Freitas Percinoto RA: 275170 Turma G
void suavizador(int M, int S[M], int *c){ // A função suavizador() é responsavel por receber as amostras, suaviza-las e contar o número de anomalias.
    int i, aux[M];
    for(i=0;i<M;i++){
        scanf("%d", &S[i]);
    }
    for(i=0;i<M;i++){
        aux[i]=S[i];
    }
    for(i=0;i<M;i++){
        if(i==0){
            S[i] = (aux[i]+aux[i+1])/2;
        } else if(i<M-1){
            S[i] = (aux[i-1]+aux[i]+aux[i+1])/3;
        } else{
            S[i] = (aux[i-1]+aux[i])/2;
        } 
        if(S[i]>120){
            (*c)++;
        }
    }
}
int main(){ // A main() está responsável por receber os valores N, M e definir o inteiro c que atua como nosso ponteiro contador de anomalias. 
    int N, teste;
    scanf("%d", &N);
    for(teste=0;teste<N;teste++){
        int M, i;
        scanf("%d", &M);
        int S[M];
        int c=0;
        suavizador(M, S, &c);
        for (i=0; i<M;i++){
            printf("%d ", S[i]);
        }
        printf("\n%d\n", c);
    }
    return 0;
}