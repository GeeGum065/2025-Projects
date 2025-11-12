//Bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

//Parâmetros

#define N 9
#define TAM 3
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
void shuffle(char array[])
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

void quebraArray(char array[9], char mp[TAM][TAM])
{
    int cont = 0;
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            mp[i][j] = array[cont];
            cont++;
        }
    }
}


//Protótipo/Esqueleto do 8 - Puzzle manual
/*void povoarM(char m[N][N])
{
    int aux[9] = {0,1,2,3,4,5,6,7,8};
    int mp[N][N];
    shuffle(aux);
    quebraArray(aux,m);
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; i++)
        {
            
        }
    }
}*/
void acharP(char matrix[TAM][TAM],int pontoP[2]){
    for(int i =0;i<TAM;i++){
        for(int j =0;j<TAM;j++){
            if(matrix[i][j]=='.'){
                pontoP[0]=i;
                pontoP[1]=j;
            }
        }

    }

}
void achaM(int pos[4][2],char m[TAM][TAM],int pontoP[2]){
    acharP(m,pontoP);
    int aux[2];
    for(int i = 0; i < 3; i++){
        if(pontoP[0] + 1 != 3){
            pos[i][0] = pontoP[0] + 1;
        }
        if(pontoP[0] - 1 >= 0){
            pos[i][0] = pontoP[0] - 1;
        }
        if(pontoP[1] + 1 != 3){
            pos[i][1] = pontoP[0] + 1;
        }
        if(pontoP[1] - 1 >= 0){
            pos[i][1] = pontoP[0] - 1;
        }
    }
}
void imprimirM(char m[TAM][TAM])
{
    printf("-------------\n");
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            printf("| %c ",m[i][j]);
        }
        printf("|\n-------------\n");
    }
}

void andarJ(int cord[2]);


// Protótipo/Esqueleto do 8 - Puzzle 
int main()
{
    int cordenadaPO[2];
    char moviveis[4] = {' ',' ',' ',' '};
    char tabu[TAM][TAM];
    char v[N] = {'.','1','2','3','4','5','6','7','8'};
    
    
    shuffle(v);
    quebraArray(v,tabu);
    for(int i =0;i<TAM;i++){
        for(int j =0;j<TAM;j++){
        printf("%c",tabu[i][j]);
        }
        printf("\n");
    }
    imprimirM(tabu);
    acharP(tabu,cordenadaPO);
    for(int i =0;i<2;i++){
        printf("%d",cordenadaPO[i]);
    }
    return 0;
}
