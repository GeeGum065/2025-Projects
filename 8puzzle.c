//Bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

//Parâmetros

#define N 9
#define TAM 3


int possiveis = 0;

//Números Aleatórios
static inline int rand_int(int a, int b) {
    /* inteiro uniforme em [a,b] (assume a <= b) */
    return a + rand() % (b - a + 1);
}

static inline double rand_unit() {
    /* real uniforme em [0,1) */
    return (double)rand() / (double)(RAND_MAX);
}

//Arrumar essa função, usar vetor[8/N*N-1] = {1,2,3,4,5,6,7,8}; para randomizar posições e povoar e a matriz aleatoriamente.
void shuffle(int array[])
{
    srand(time(NULL));
    for(int i = 0; i < N - 1; i++)
    {
        size_t j = rand() / (RAND_MAX / (N - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

void quebraArray(int mp[TAM][TAM])
{
    int v[N] = {-1,1,2,3,4,5,6,7,8};
    shuffle(v);
    int cont = 0;
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            mp[i][j] = v[cont];
            cont++;
        }
    }
}


//Protótipo/Esqueleto do 8 - Puzzle manual

void acharP(int matrix[TAM][TAM],int pontoP[2]){
    for(int i =0;i<TAM;i++){
        for(int j =0;j<TAM;j++){
            if(matrix[i][j] == -1){
                pontoP[0]=i;
                pontoP[1]=j;
            }
        }

    }

}

void verificaMoviveis(){
    
}


void achaM(int pos[possiveis][2],int m[TAM][TAM],int pontoP[2]){
    acharP(m,pontoP);
    //if(pontoP[0] + 1 < 3){
        pos[0][0] = pontoP[0] + 1;
        pos[0][1] = pontoP[1];
    //}
    //if(pontoP[0] - 1 >= 0){
        pos[1][0] = pontoP[0] - 1;
        pos[1][1] = pontoP[1];
    //}
    //if(pontoP[1] + 1 < 3){
        pos[2][1] = pontoP[1] + 1;
        pos[2][0] = pontoP[0];
    //}
    //if(pontoP[1] - 1 >= 0){
        pos[3][1] = pontoP[1] - 1;
        pos[3][0] = pontoP[0];
    //}
}

void imprimirM(int m[TAM][TAM])
{
    printf("-------------\n");
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(m[i][j] == -1){
                printf("| . ");

            }
            else{
                printf("| %d ",m[i][j]);
            }
        }
        printf("|\n-------------\n");
    }
}

void andarJ(int cord[2]);


// Protótipo/Esqueleto do 8 - Puzzle 
int main()
{
    /*
    int cordenadaPO[2];
    int moviveis[4] = {-1,-1,-1,-1};
    int tabu[TAM][TAM];
    int pos[4][2];
    
    quebraArray(tabu);
    
    imprimirM(tabu);
    
    acharP(tabu,cordenadaPO);
    achaM(pos, tabu, cordenadaPO);
    for(int i =0;i<2;i++){
        printf("%d ",cordenadaPO[i]);
    }
    printf("\n");
    for(int i =0;i<4;i++){
        for(int j =0;j<2;j++){
    
            printf("%d ",pos[j][i]);
        }
    }
    */
    printf("%d", possiveis);
    return 0;
}
