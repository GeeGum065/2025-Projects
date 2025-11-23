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
#define MAX 5

//Números Aleatórios
static inline int rand_int(int a, int b) {
    return a + rand() % (b - a + 1);
}

static inline double rand_unit() {
    return (double)rand() / (double)(RAND_MAX);
}
typedef struct no
{
    struct info;
    struct no *prox;
}No;

typedef struct pilha
{
   No *Topo;
}Pilha;

int vaziaPilha(Pilha *p)
{
    if (p->Topo==NULL)
    {
        return 1; //pilha vazia
    }
    return 0;
}

Pilha* CriaPilha (void)
{
     Pilha *p;
     p=(Pilha*)malloc(sizeof(Pilha));
     p->Topo = NULL;
   return p;
}

No* ins_ini (No* t, state a)
{
    No* aux = (No*) malloc(sizeof(No));
    aux->info = a;
    aux->prox = t;
    return aux;
}

void push (Pilha* p, state v)
{
    p->Topo = ins_ini(p->Topo,v);
}

No* ret_ini (No* aux)
{
    No* p = aux->prox;
    free(aux);
    return p;
}

state pop (Pilha *p)
{
    int v;
    if (vaziaPilha(p))
    {
        printf("\n\n\t==> Pilha VAZIA, IMPOSSIVEL CONTINUAR.\b\n");
        exit(1); /* aborta programa */
    }
    v = p->Topo->info;
    p->Topo = ret_ini(p->Topo);
    return v;
}

Pilha* liberaPilha (Pilha *p) //APAGA TODA PILHA
{
    No *q = p->Topo;
    while (q!=NULL)
    {
        No* t = q->prox;
        free(q);
        q = t;
    }
    free(p);
    return(NULL);
}

/* FUNÇÕES DE MANIPULAÇÃO DE PFILA

Fila* CriaFila()  CRIA A FILA

int VaziaFila (Fila* f) VERIFICA SE A FILA ESTÁ VAIZA

void InsereFila (Fila* f, int v) INSERÇÃO

int RetiraFila (Fila* f) REMOÇÃO

Fila* liberaFila (Fila* f) LIBERA A FILA

void imprimeFila (Fila* f)IMPRIME A FILA
*/
typedef struct nos
{
    state info;
    struct nos *prox;
}Nos;

typedef struct fila
{
    Nos * ini;
    Nos * fim;
} Fila;

int VaziaFila (Fila* f)
{
    if (f->ini==NULL) return 1;
    return 0;

}


Fila* CriaFila ()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

Nos* ins_fim (Nos *fim, state A)
{
    Nos *p = (Nos*)malloc(sizeof(Nos));
    p->info = A;
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista não estava vazia */
    fim->prox = p;
    return p;
}

void InsereFila (Fila* f, state v)
{
    f->fim = ins_fim(f->fim,v);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

Nos* retira_ini (Nos* ini)
{
    Nos* p = ini->prox;
    free(ini);
    return p;
}

int RetiraFila (Fila* f)
{
    int v;
    if (VaziaFila(f))
    {
        printf("Fila vazia.\n");
        exit(0); /* aborta programa */
    }
    v = f->ini->info;
    f->ini = retira_ini(f->ini);
    if (f->ini == NULL) /* fila ficou vazia? */
    f->fim = NULL;
    return v;
}

void imprimeFila (Fila* f)
{
    Nos* q;
    printf("\n\t\t");
    for (q=f->ini; q!=NULL; q=q->prox)
    {
        printf("%d - ",q->info);
    }
    printf("\n");
}


Fila* liberaFila (Fila* f)
{
    Nos* q = f->ini;
    while (q!=NULL)
    {
        Nos* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}


//Jogo
typedef struct state{
    int tabu[TAM][TAM];
    int moviveis[4];
    int posmoviveis[4][2];
    int prof=0;
}state;
typedef struct {
    state** states;
    int qtd;
    int maximo ;
}statesVisitados;
void randArray(int array[])
{
    for(int i = N - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

void criaTabu(int mp[TAM][TAM])
{
    int v[N] = {-1,1,2,3,4,5,6,7,8};
    randArray(v);
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

void acharVazio(int matrix[TAM][TAM],int pontoVazio[2]){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            if(matrix[i][j] == -1){
                pontoVazio[0] = i;
                pontoVazio[1] = j;
            }
        }
    }
}

//(inversões pares)
bool verificaSolucao(int array[9]){
    int aux[8];
    int k = 0;
    
    for(int i = 0; i < 9; i++){
        if(array[i] != -1){
            aux[k] = array[i];
            k++;
        }
    }
    
    int cont = 0;
    for(int i = 0; i < 8; i++){
        for(int j = i + 1; j < 8; j++){
            if(aux[i] > aux[j]){
                cont++;
            }
        }
    }
    
    return (cont % 2 == 0);
}


void achaMoviveis(int pos[4][2], int m[TAM][TAM], int pontoVazio[2], int moviveis[4]){
    acharVazio(m, pontoVazio);
    int linha = pontoVazio[0];
    int coluna = pontoVazio[1];
    
    // Inicializa todas as posições como inválidas
    for(int i = 0; i < 4; i++){
        pos[i][0] = -1;
        pos[i][1] = -1;
        moviveis[i] = -1;
    }
    
    // Baixo
    if(linha + 1 < TAM){
        pos[0][0] = linha + 1;
        pos[0][1] = coluna;
        moviveis[0] = m[linha + 1][coluna];
    }
    
    // Cima
    if(linha - 1 >= 0){
        pos[1][0] = linha - 1;
        pos[1][1] = coluna;
        moviveis[1] = m[linha - 1][coluna];
    }
    
    // Direita
    if(coluna + 1 < TAM){
        pos[2][0] = linha;
        pos[2][1] = coluna + 1;
        moviveis[2] = m[linha][coluna + 1];
    }
    
    // Esquerda
    if(coluna - 1 >= 0){
        pos[3][0] = linha;
        pos[3][1] = coluna - 1;
        moviveis[3] = m[linha][coluna - 1];
    }
}

void imprimirTabu(int m[TAM][TAM])
{
    printf("\n-------------\n");
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(m[i][j] == -1){
                printf("| . ");
            }
            else{
                printf("| %d ", m[i][j]);
            }
        }
        printf("|\n-------------\n");
    }
}

//Jogador:

void mostrarMoviveis(int moviveis[4]){
    printf("\nPeças que você pode mover: ");
    bool primeiro = true;
    for(int i = 0; i < 4; i++){
        if(moviveis[i] > 0){
            if(!primeiro) printf(", ");
            printf("%d", moviveis[i]);
            primeiro = false;
        }
    }
    printf("\n");
}

//Verifica se o número escolhido é válido
bool numeroValido(int num, int moviveis[4]){
    for(int i = 0; i < 4; i++){
        if(moviveis[i] == num){
            return true;
        }
    }
    return false;
}

//Movimenta a peça escolhida
void moverPeca(int m[TAM][TAM], int num, int moviveis[4], int pos[4][2], int pontoP[2]){
    for(int i = 0; i < 4; i++){
        if(moviveis[i] == num){
            // Troca a posição do -1 com o número escolhido
            m[pontoP[0]][pontoP[1]] = num;
            m[pos[i][0]][pos[i][1]] = -1;
            return;
        }
    }
}
int contamoviveis(state estado){
    cont=2;
    for(int i = 2; i<4;i++){
        if(estado->moviveis[i]<8&&estado->moviveis[i]>1){
            cont++;
        }
    }
}   return cont;
void bfs(state Estado){
    int pontop[2], posmoviveis[4][2];
    Fila *f=NULL;
    f=CriaFila();
    InsereFila(f,Estado);
    
    
}
void iddfs(state Estado){
    int pontop[2], posmoviveis[4][2];
    Pilha *p=NULL;
    p=CriaPilha();
    push(p,Estado);
    while(Estado->prof<MAX){
        
        acharVazio(Estado->tabu,pontop);
        achaMoviveis(posmoviveis,Estado->tabu,pontop,Estado->moviveis);
        for(int i =1;i<10;i++){
            if(numeroValido(i,Estado->moviveis)){
                
        }
        
        Estado->prof++;
    }
        
    }
    
}

//Verifica se o jogador venceu
bool verificaVitoria(int m[TAM][TAM]){
    int esperado[TAM][TAM] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, -1}
    };
    
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            if(m[i][j] != esperado[i][j]){
                return false;
            }
        }
    }
    return true;
}

//A*:

int main()
{
    srand(time(NULL));
    
    int cordenadaPO[2];
    int moviveis[4];
    int tabuleiro[TAM][TAM];
    int pos[4][2];
    int escolha;
    int movimentos = 0;
    int v[N];
    
    // Gera tabuleiro solucionável
    do {
        criaTabu(tabuleiro);
        int k = 0;
        for(int i = 0; i < TAM; i++){
            for(int j = 0; j < TAM; j++){
                v[k] = tabuleiro[i][j];
                k++;
            }
        }
    } while(!verificaSolucao(v));
    
    printf("=== 8-PUZZLE ===\n");
    printf("Objetivo: Organize os números de 1 a 8 em ordem.\n");
    printf("Configuração final:\n");
    printf("-------------\n");
    printf("| 1 | 2 | 3 |\n");
    printf("-------------\n");
    printf("| 4 | 5 | 6 |\n");
    printf("-------------\n");
    printf("| 7 | 8 | . |\n");
    printf("-------------\n\n");
    
    // Loop principal do jogo
    while(true){
        imprimirTabu(tabuleiro);
        
        // Verifica vitória
        if(verificaVitoria(tabuleiro)){
            printf("\nVocê venceu em %d movimentos!\n\n", movimentos);
            break;
        }
        
        // Encontra movimentos possíveis
        achaMoviveis(pos, tabuleiro, cordenadaPO, moviveis);
        mostrarMoviveis(moviveis);
        
        // Solicita jogada
        printf("\nDigite o número que deseja mover (0 para sair): ");
        if(scanf("%d", &escolha) != 1){
            printf("Entrada inválida!\n");
            while(getchar() != '\n');
            continue;
        }
        
        if(escolha == 0){
            printf("Jogo encerrado. Você fez %d movimentos.\n", movimentos);
            break;
        }
        
        // Valida e executa movimento
        if(numeroValido(escolha, moviveis)){
            moverPeca(tabuleiro, escolha, moviveis, pos, cordenadaPO);
            movimentos++;
        } else {
            printf("\nO número %d não pode ser movido!\n", escolha);
            sleep(2);
        }
        system("clear");
    }
    
    return 0;
}
