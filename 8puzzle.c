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
typedef struct state{
    int tabu[TAM][TAM];
    int moviveis[4];
    int posmoviveis[4][2];
}state;
typedef struct {
    int maximo;
    state** states;
    int qtd;
}statesVisitados;
typedef struct no
{
    state* info;
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

No* ins_ini (No* t, state* a)
{
    No* aux = (No*) malloc(sizeof(No));
    aux->info = a;
    aux->prox = t;
    return aux;
}

void push (Pilha* p, state* v)
{
    p->Topo = ins_ini(p->Topo,v);
}

No* ret_ini (No* aux)
{
    No* p = aux->prox;
    free(aux);
    return p;
}

state* pop (Pilha *p)
{
    state* v;
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
    state* info;
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

Nos* ins_fim (Nos *fim, state* A)
{
    Nos *p = (Nos*)malloc(sizeof(Nos));
    p->info = A;
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista não estava vazia */
    fim->prox = p;
    return p;
}

void InsereFila (Fila* f, state* v)
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

state* RetiraFila (Fila* f)
{
    state* v;
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

statesVisitados* criarVisitados(){
    int max =500;
    statesVisitados* sv = (statesVisitados*)malloc(sizeof(statesVisitados));
    sv->states = (state**)malloc(sizeof(state*)*max);
    sv->maximo=max;
    sv->qtd=0;
    return sv;
}
void addstates(statesVisitados* sv, state* State){
    if(sv->qtd>=sv->maximo){
        int novomax = sv->maximo*2;
        state** novosstates = (state**)malloc(sizeof(state*)*novomax);
        for(int i =0;i<sv->qtd;i++){
            novosstates[i]=sv->states[i];
        }
        free(sv->states);
    
    sv->states = novosstates;
    sv->maximo = novomax;
    }
    sv->states[sv->qtd++]=State;
}
bool verificavisitado(statesVisitados* sv, state* State){
    for(int i = 0; i< sv->qtd; i++){
        state* atual = sv ->states[i];
        bool igual = true;
        for(int j = 0; j<TAM&&igual;j++){
            for(int k = 0;k<TAM;k++){
                if(State->tabu[j][k]!=atual->tabu[j][k]){
                    igual=false;
                    break;
                }
            }
        }
        if (igual) return true;
    }
    return false;
}
void dstrstatesvisitados(statesVisitados* sv){
    for(int i =0;i<sv->qtd;i++){
        free(sv->states[i]);
    }
    free(sv->states);
    free(sv);
}
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
int contamoviveis(state* estado){
    int cont=2;
    for(int i = 2; i<4;i++){
        if(estado->moviveis[i]<8&&estado->moviveis[i]>1){
            cont++;
        }
    }

    return cont;
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
void bfs(state* Estado){
    int pontop[2], posMoviveis[4][2], movimentaveis[4];
    Fila *f = CriaFila();
    statesVisitados* visitados = criarVisitados();

    InsereFila(f, Estado);
    addstates(visitados, Estado);

    while(!VaziaFila(f)){
        state* atual = RetiraFila(f);

        if(verificaVitoria(atual->tabu)){
            printf("\nAchei a solução!\nForam explorados %d estados.\n", visitados->qtd);
            imprimirTabu(atual->tabu);
            dstrstatesvisitados(visitados);
            liberaFila(f);
            return;
        }

        // Calcula movimentos possiveis do estado atual
        acharVazio(atual->tabu, pontop);
        achaMoviveis(atual->posmoviveis, atual->tabu, pontop, atual->moviveis);

        // Tenta cada um dos 4 movimentos
        for(int i = 0; i < 4; i++){
            if(atual->moviveis[i] == -1){ // movimento inexistente
                continue;
            }
            // Criar novo estado
            state* proximo = (state*)malloc(sizeof(state));

            // Copiar tabu atual para o novo
            for(int x = 0; x < TAM; x++){
                for(int y = 0; y < TAM; y++){
                    proximo->tabu[x][y] = atual->tabu[x][y];
                }
            }
            // Aplicar movimento
            moverPeca(proximo->tabu,atual->moviveis[i],atual->moviveis,atual->posmoviveis,pontop);

            // Calcular moviveis do novo estado
            acharVazio(proximo->tabu, pontop);
            achaMoviveis(proximo->posmoviveis, proximo->tabu, pontop, proximo->moviveis);

            // Se o estado ainda nao foi visitado, colocar na fila
            if(!verificavisitado(visitados, proximo)){
                addstates(visitados, proximo);
                InsereFila(f, proximo);
            
        }
    }
}
}
void iddfs(state Estado){
    int pontop[2], posmoviveis[4][2];
    Pilha *p=NULL;
    p=CriaPilha();
    
    
}



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
    int opcao;
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
    printf("0:Jogar normalmente\n1:resolver por bfs\n2:resolver por iddfs\n");
    printf("digite a opção para jogar:\n");
    scanf("%d",&opcao);
    // Loop principal do jogo
        //case 0:
        if(opcao==0){
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
    }
    if(opcao==1){
        state* Inicial=malloc(sizeof(state));
        int ponto[2]={-1,-1};
        acharVazio(Inicial->tabu, ponto);
        achaMoviveis(Inicial->posmoviveis, Inicial->tabu, ponto, Inicial->moviveis);
        for(int x = 0; x < TAM; x++){
                for(int y = 0; y < TAM; y++){
                    Inicial->tabu[x][y] = tabuleiro[x][y];
                }
        }
        bfs(Inicial);
    }
    return 0;
}
