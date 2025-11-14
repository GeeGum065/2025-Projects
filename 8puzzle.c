//Bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

//Parâmetros

#define N 9
#define TAM 3


typedef struct numeros{
    int pos[2];
    int info;
    char direc;
} possivel;

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


void achaM(int pos[4][2],int m[TAM][TAM],int pontoP[2],int moviveis[4], possivel p[4]){
    acharP(m,pontoP);
    int linha = pontoP[0];
    int coluna = pontoP[1];
    
    if(linha + 1 < 3){
        p[0].pos[0] = linha + 1;
        p[0].pos[1] = coluna;
    }
    if(linha - 1 >= 0){
        p[1].pos[0] = linha - 1;
        p[1].pos[1] = coluna;
    }
    if(coluna + 1 < 3){
        p[2].pos[1] = coluna + 1;
        p[2].pos[0] = linha;
    }
    if(coluna - 1 >= 0){
        p[3].pos[1] = coluna - 1;
        p[3].pos[0] = linha;
    }
    
    for(int i = 0; i < 4; i++)
    {
        if(p[i].pos[0] > 2 || p[i].pos[0] < 0 && p[i].pos[1] > 2 || p[i].pos[1] < 0){
            moviveis[i] = -1;
        } else{
            moviveis[i] = m[p[i].pos[0]][p[i].pos[1]];
        }
    }
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

void mostrarM(int moviveis[4]){
    printf("\nAs posições possíveis são:");
    for(int i = 0; i < 4; i++){
        if(moviveis[i] > 0){
            printf("\n%d",moviveis[i]);
        }
    }
}
/*
void andarJ(int moviveis[4], matrizz[TAM][TAM){
    
    switch(num)
    {
        case moviveis[0]:
        v[0] -= 1;
        break;
        
        case moviveis[1]:
        v[0] += 1;
        break;
        
        case moviveis[2]:
        if()
        break;
        
        case moviveis[3]:
        v[1] -= 1;
        break;
        
        default :
        break;
    }
}
}
*/
 
// Protótipo/Esqueleto do 8 - Puzzle 
int main()
{
    
    int cordenadaPO[2];
    int moviveis[4];
    int tabu[TAM][TAM];
    int pos[4][2];
    possivel p[4];
    
    quebraArray(tabu);
    
    imprimirM(tabu);
    
    acharP(tabu,cordenadaPO);
    achaM(pos, tabu, cordenadaPO, moviveis, p);

     for(int i =0;i<2;i++){
        printf("%d ",cordenadaPO[i]);
    }
    printf("\n");
    for(int i =0;i<4;i++){
        for(int j =0;j<2;j++){
    
            printf("%d ",p[i].pos[j]);
        }
    }
    mostrarM(moviveis);
    
    
    printf("\n");
    //sleep(10);
    //system("clear");
    return 0;
}
