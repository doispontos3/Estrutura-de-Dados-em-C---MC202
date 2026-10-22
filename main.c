#include <stdio.h>
int main() {
    int testes, i, j, k, p, q, M, N;
    scanf("%d",&testes);
    int aparicoes[testes];
    for (i=0; i<testes; i++){
        scanf("%d %d", &M, &N);
        int MATRIZ[M][N];
        for (j=0; j<M; j++) {
            for (k=0; k<N; k++){
                scanf("%d", &MATRIZ[j][k]);
            }
        }
        int X, Y;
        scanf("%d %d", &X, &Y);
        int P[X][Y];
        for (j=0; j<X; j++) {
            for (k=0; k<Y; k++){
                scanf("%d",&P[j][k]);
            }
        }
        int booleano;
        aparicoes[i]=0;
        for(j=0; j <=(M-X);j++) {
            for (k=0; k<=(N-Y); k++){
                booleano = 1;
                for(p=0; p<X && booleano==1;p++) {
                    for(q=0; q<Y && booleano==1;q++) {
                        if(P[p][q]!=MATRIZ[j+p][k+q]){
                            booleano = 0;
                 
                        }   
                    }
                }
                if (booleano==1){
                    aparicoes[i]++;        
                }
            }
        }
    }
    for (i=0; i<testes;i++){
        printf("%d\n", aparicoes[i]);
    }
    return 0;
}