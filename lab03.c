// Nome: Felipe de Freitas Percinoto RA: 275170
#include <stdio.h>
// O struct nesse contexto é como trazer uma bomba atômica numa luta de boxe, mas como foi requisitado nós iremos computar a matriz e referir as suas linhas e colunas usando registro.
typedef struct{
    int linha;
    int coluna;
    int valor;
} posicao;
// conta_caminho() vai ser nossa função recursiva, enquanto a main() estará responsável por computar a matriz com o struct e chamar a função recursiva e printar seu resultado.
int conta_caminho(int M, int N, posicao matriz[M][N], int linha, int coluna){
 // Os três casos base são os 3 cenários possíveis dada uma posição, se sair da matriz ou chegar numa barreira retorna 0, se chegar no final retorna 1.   
    if(linha>=M || coluna>=N){
        return 0;
    }
    if(matriz[linha][coluna].valor==0){
        return 0;
    }
    if(linha==M-1 && coluna==N-1){
        return 1;
    }
// O caso recursivo vai ser simplesmente quando estivermos em uma posição normal e vamos fazer duas chamadas recursivas andando pra baixo e pra direita.
    return conta_caminho(M, N, matriz, linha, coluna + 1) + conta_caminho(M, N, matriz, linha + 1, coluna);
}
// A gente utiliza o struct para computar a matriz, apesar disso o struct não precisa ser ativamente utilizado na solução recursiva.
int main(){
    int testes, M, N, teste, i, j;
    scanf("%d ", &testes);
    for(teste=0; teste<testes; teste++){
        scanf("%d %d", &M, &N);
        posicao matriz[M][N];
        for(i=0; i<M; i++){
            for(j=0; j<N; j++){
                matriz[i][j].linha= i;
                matriz[i][j].coluna= j;
                scanf("%d", &matriz[i][j].valor);
            }
        }
    int caminhos = conta_caminho(M, N, matriz, 0, 0);
    printf("%d\n", caminhos);
    }
}

