//Bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

//Parâmetros

#define N 3

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
    int array[9] = {0,1,2,3,4,5,6,7,8};
    srand(time(NULL));
    for(int i = 0; i < N - 1; i++)
    {
        size_t j = rand() / (RAND_MAX / (N - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

void quebraArray(int array[9], int mp[N][N])
{
    int cont = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            m[i][j] = array[cont];
            cont++;
        }
    }
}

//Protótipo/Esqueleto do 8 - Puzzle manual
void povoarM(char m[N][N])
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
}


void imprimirM(char m[N][N])
{
    printf("-------------\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
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
    //char tabu[N][N]; int v[9];
    int v[9] = {-2,-2,-2,-2,-2,-2,-2,-2,-2};

    
    //{{'1','2','3'},{'4','5','6'},{'7','8','.'}};
    //povoarM(tabu);
    //imprimirM(tabu);
    
    shuffle(v);     
    for(int i = 0; i < 9; i++)
    {
        printf("%d",v[i]);
    }

    return 0;
}
