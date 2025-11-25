//Bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

//Parâmetros
#define N 9
#define TAM 3
#define PROFUNDIDADE_MAXIMA 50

//Números Aleatórios
static inline int rand_int(int a, int b) {
    return a + rand() % (b - a + 1);
}

// ==================== ESTRUTURAS ====================
typedef struct state{
    int tabu[TAM][TAM];
    int moviveis[4];
    int posmoviveis[4][2];
    int profundidade;
} state;

typedef struct {
    int maximo;
    state** states;
    int qtd;
} statesVisitados;

typedef struct no
{
    state* info;
    struct no *prox;
} No;

typedef struct pilha
{
   No *Topo;
} Pilha;

typedef struct nos
{
    state* info;
    struct nos *prox;
} Nos;

typedef struct fila
{
    Nos * ini;
    Nos * fim;
} Fila;

// ==================== FUNÇÕES DE PILHA ====================
int vaziaPilha(Pilha *p)
{
    return (p->Topo == NULL);
}

Pilha* CriaPilha (void)
{
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->Topo = NULL;
    return p;
}

void push (Pilha* p, state* v)
{
    No* aux = (No*) malloc(sizeof(No));
    aux->info = v;
    aux->prox = p->Topo;
    p->Topo = aux;
}

state* pop (Pilha *p)
{
    if (vaziaPilha(p))
    {
        printf("\n\n\t==> Pilha VAZIA.\n");
        exit(1);
    }
    state* v = p->Topo->info;
    No* temp = p->Topo;
    p->Topo = p->Topo->prox;
    free(temp);
    return v;
}

Pilha* liberaPilha (Pilha *p)
{
    No *q = p->Topo;
    while (q != NULL)
    {
        No* t = q->prox;
        free(q);
        q = t;
    }
    free(p);
    return NULL;
}

// ==================== FUNÇÕES DE FILA ====================
int VaziaFila (Fila* f)
{
    return (f->ini == NULL);
}

Fila* CriaFila ()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

void InsereFila (Fila* f, state* v)
{
    Nos* p = (Nos*)malloc(sizeof(Nos));
    p->info = v;
    p->prox = NULL;
    if (f->fim != NULL)
        f->fim->prox = p;
    f->fim = p;
    if (f->ini == NULL)
        f->ini = f->fim;
}

state* RetiraFila (Fila* f)
{
    if (VaziaFila(f))
    {
        printf("Fila vazia.\n");
        exit(0);
    }
    state* v = f->ini->info;
    Nos* temp = f->ini;
    f->ini = f->ini->prox;
    if (f->ini == NULL)
        f->fim = NULL;
    free(temp);
    return v;
}

Fila* liberaFila (Fila* f)
{
    Nos* q = f->ini;
    while (q != NULL)
    {
        Nos* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}

// ==================== FUNÇÕES DE ESTADOS VISITADOS ====================
statesVisitados* criarVisitados(){
    statesVisitados* sv = (statesVisitados*)malloc(sizeof(statesVisitados));
    sv->states = (state**)malloc(sizeof(state*) * 1000);
    sv->maximo = 1000;
    sv->qtd = 0;
    return sv;
}

void addstates(statesVisitados* sv, state* State){
    if(sv->qtd >= sv->maximo){
        int novomax = sv->maximo * 2;
        state** novosstates = (state**)realloc(sv->states, sizeof(state*) * novomax);
        if(novosstates == NULL){
            perror("realloc falhou");
            exit(1);
        }
        sv->states = novosstates;
        sv->maximo = novomax;
    }
    sv->states[sv->qtd++] = State;
}

bool verificavisitado(statesVisitados* sv, state* State){
    for(int i = 0; i < sv->qtd; i++){
        state* atual = sv->states[i];
        bool igual = true;
        for(int j = 0; j < TAM && igual; j++){
            for(int k = 0; k < TAM; k++){
                if(State->tabu[j][k] != atual->tabu[j][k]){
                    igual = false;
                    break;
                }
            }
        }
        if (igual) return true;
    }
    return false;
}

void dstrstatesvisitados(statesVisitados* sv){
    for(int i = 0; i < sv->qtd; i++){
        free(sv->states[i]);
    }
    free(sv->states);
    free(sv);
}

// ==================== FUNÇÕES DO JOGO ====================
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
            mp[i][j] = v[cont++];
        }
    }
}

void acharVazio(int matrix[TAM][TAM], int pontoVazio[2]){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            if(matrix[i][j] == -1){
                pontoVazio[0] = i;
                pontoVazio[1] = j;
                return;
            }
        }
    }
}

bool verificaSolucao(int array[9]){
    int aux[8];
    int k = 0;

    for(int i = 0; i < 9; i++){
        if(array[i] != -1){
            aux[k++] = array[i];
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
    int linha = pontoVazio[0];
    int coluna = pontoVazio[1];

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

void mostrarMoviveis(int moviveis[4]){
    printf("\nPecas que voce pode mover: ");
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

bool numeroValido(int num, int moviveis[4]){
    for(int i = 0; i < 4; i++){
        if(moviveis[i] == num){
            return true;
        }
    }
    return false;
}

void moverPeca(int m[TAM][TAM], int num, int moviveis[4], int pos[4][2], int pontoP[2]){
    for(int i = 0; i < 4; i++){
        if(moviveis[i] == num){
            m[pontoP[0]][pontoP[1]] = num;
            m[pos[i][0]][pos[i][1]] = -1;
            return;
        }
    }
}

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

void copiarTabuleiro(int destino[TAM][TAM], int origem[TAM][TAM]){
    for(int x = 0; x < TAM; x++){
        for(int y = 0; y < TAM; y++){
            destino[x][y] = origem[x][y];
        }
    }
}

state* criarNovoEstado(state* atual, int movimento){
    state* proximo = (state*)malloc(sizeof(state));

    copiarTabuleiro(proximo->tabu, atual->tabu);
    proximo->profundidade = atual->profundidade + 1;

    int pontop[2];
    acharVazio(atual->tabu, pontop);

    int linhaPeca = atual->posmoviveis[movimento][0];
    int colunaPeca = atual->posmoviveis[movimento][1];

    proximo->tabu[pontop[0]][pontop[1]] = proximo->tabu[linhaPeca][colunaPeca];
    proximo->tabu[linhaPeca][colunaPeca] = -1;

    return proximo;
}

// ==================== ALGORITMO BFS ====================
void bfs(state* Estado){
    int pontop[2];

    Fila *f = CriaFila();
    statesVisitados* visitados = criarVisitados();

    Estado->profundidade = 0;
    InsereFila(f, Estado);
    addstates(visitados, Estado);

    printf("\nIniciando busca BFS...\n");

    while(!VaziaFila(f)){
        state* atual = RetiraFila(f);

        if(verificaVitoria(atual->tabu)){
            printf("\n==> SOLUCAO ENCONTRADA!\n");
            printf("Estados explorados: %d\n", visitados->qtd);
            printf("Profundidade da solucao: %d\n", atual->profundidade);
            imprimirTabu(atual->tabu);

            liberaFila(f);
            dstrstatesvisitados(visitados);
            return;
        }

        acharVazio(atual->tabu, pontop);
        achaMoviveis(atual->posmoviveis, atual->tabu, pontop, atual->moviveis);

        for(int i = 0; i < 4; i++){
            if(atual->moviveis[i] == -1) continue;

            state* proximo = criarNovoEstado(atual, i);

            if(!verificavisitado(visitados, proximo)){
                addstates(visitados, proximo);
                InsereFila(f, proximo);
            } else {
                free(proximo);
            }
        }
    }

    printf("\nNao foi possivel encontrar uma solucao.\n");
    printf("Estados explorados: %d\n", visitados->qtd);
    liberaFila(f);
    dstrstatesvisitados(visitados);
}

// ==================== ALGORITMO IDDFS (SEM RECURSAO) ====================
void iddfs(state* Estado){
    printf("\nIniciando busca IDDFS...\n");

    int totalExplorados = 0;
    Estado->profundidade = 0;

    // Loop externo: itera sobre profundidades crescentes
    for(int limiteProf = 0; limiteProf <= PROFUNDIDADE_MAXIMA; limiteProf++){
        printf("Buscando na profundidade %d...\n", limiteProf);

        // Cria pilha e visitados para esta iteracao
        Pilha* p = CriaPilha();
        statesVisitados* visitados = criarVisitados();

        // Cria copia do estado inicial para esta iteracao
        state* inicialCopia = (state*)malloc(sizeof(state));
        copiarTabuleiro(inicialCopia->tabu, Estado->tabu);
        inicialCopia->profundidade = 0;

        int pontop[2];
        acharVazio(inicialCopia->tabu, pontop);
        achaMoviveis(inicialCopia->posmoviveis, inicialCopia->tabu, pontop, inicialCopia->moviveis);

        push(p, inicialCopia);
        addstates(visitados, inicialCopia);

        bool encontrouSolucao = false;

        // DFS iterativo com limite de profundidade
        while(!vaziaPilha(p)){
            state* atual = pop(p);
            totalExplorados++;

            // Verifica se encontrou solucao
            if(verificaVitoria(atual->tabu)){
                printf("\n==> SOLUCAO ENCONTRADA!\n");
                printf("Estados explorados: %d\n", totalExplorados);
                printf("Profundidade da solucao: %d\n", atual->profundidade);
                imprimirTabu(atual->tabu);

                encontrouSolucao = true;
                liberaPilha(p);
                dstrstatesvisitados(visitados);
                return;
            }

            // Se atingiu limite de profundidade, nao expande
            if(atual->profundidade >= limiteProf){
                continue;
            }

            // Calcula movimentos possiveis
            int pontoAtual[2];
            acharVazio(atual->tabu, pontoAtual);
            achaMoviveis(atual->posmoviveis, atual->tabu, pontoAtual, atual->moviveis);

            // Expande filhos (em ordem reversa para DFS manter ordem similar)
            for(int i = 3; i >= 0; i--){
                if(atual->moviveis[i] == -1) continue;

                state* proximo = criarNovoEstado(atual, i);

                if(!verificavisitado(visitados, proximo)){
                    addstates(visitados, proximo);
                    push(p, proximo);
                } else {
                    free(proximo);
                }
            }
        }

        // Libera memoria desta iteracao
        liberaPilha(p);
        dstrstatesvisitados(visitados);

        if(encontrouSolucao){
            return;
        }
    }

    printf("\nNao foi possivel encontrar solucao ate profundidade %d.\n", PROFUNDIDADE_MAXIMA);
    printf("Estados explorados: %d\n", totalExplorados);
}

// ==================== MODO JOGADOR ====================
void modoJogador(int tabuleiro[TAM][TAM]){
    int cordenadaPO[2];
    int moviveis[4];
    int pos[4][2];
    int escolha;
    int movimentos = 0;

    printf("\n=== MODO JOGADOR ===\n");

    while(true){
        imprimirTabu(tabuleiro);

        if(verificaVitoria(tabuleiro)){
            printf("\nPARABENS! Voce venceu em %d movimentos!\n\n", movimentos);
            break;
        }

        acharVazio(tabuleiro, cordenadaPO); // <-- corrigido: inicializa a coordenada vazia antes de achar moviveis
        achaMoviveis(pos, tabuleiro, cordenadaPO, moviveis);
        mostrarMoviveis(moviveis);

        printf("\nDigite o numero que deseja mover (0 para sair): ");
        if(scanf("%d", &escolha) != 1){
            printf("Entrada invalida!\n");
            while(getchar() != '\n');
            continue;
        }

        if(escolha == 0){
            printf("Jogo encerrado. Voce fez %d movimentos.\n", movimentos);
            break;
        }

        if(numeroValido(escolha, moviveis)){
            moverPeca(tabuleiro, escolha, moviveis, pos, cordenadaPO);
            movimentos++;
        } else {
            printf("\nO numero %d nao pode ser movido!\n", escolha);
            sleep(1);
        }
        system("clear");
    }
}

// ==================== FUNÇÃO PRINCIPAL ====================
int main()
{
    srand(time(NULL));

    int tabuleiro[TAM][TAM];
    int v[N];
    int opcao;

    // Gera tabuleiro solucionavel
    do {
        criaTabu(tabuleiro);
        int k = 0;
        for(int i = 0; i < TAM; i++){
            for(int j = 0; j < TAM; j++){
                v[k++] = tabuleiro[i][j];
            }
        }
    } while(!verificaSolucao(v));

    printf("===============================================\n");
    printf("             8-PUZZLE GAME                     \n");
    printf("===============================================\n\n");
    printf("Objetivo: Organize os numeros de 1 a 8 em ordem.\n");
    printf("Configuracao final:\n");
    printf("-------------\n");
    printf("| 1 | 2 | 3 |\n");
    printf("-------------\n");
    printf("| 4 | 5 | 6 |\n");
    printf("-------------\n");
    printf("| 7 | 8 | . |\n");
    printf("-------------\n\n");

    printf("Tabuleiro Inicial:");
    imprimirTabu(tabuleiro);

    printf("\n===============================================\n");
    printf("               MENU PRINCIPAL                  \n");
    printf("===============================================\n");
    printf("0 - Jogar manualmente\n");
    printf("1 - Resolver com BFS\n");
    printf("2 - Resolver com IDDFS\n");
    printf("===============================================\n");
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);

    switch(opcao){
        case 0:
            modoJogador(tabuleiro);
            break;

        case 1:
        {
            state* Inicial = (state*)malloc(sizeof(state));
            int ponto[2] = {-1, -1};

            copiarTabuleiro(Inicial->tabu, tabuleiro);
            acharVazio(Inicial->tabu, ponto);
            achaMoviveis(Inicial->posmoviveis, Inicial->tabu, ponto, Inicial->moviveis);
            Inicial->profundidade = 0;

            bfs(Inicial);
            break;
        }

        case 2:
        {
            state* Inicial = (state*)malloc(sizeof(state));
            int ponto[2] = {-1, -1};

            copiarTabuleiro(Inicial->tabu, tabuleiro);
            acharVazio(Inicial->tabu, ponto);
            achaMoviveis(Inicial->posmoviveis, Inicial->tabu, ponto, Inicial->moviveis);
            Inicial->profundidade = 0;

            iddfs(Inicial);
            free(Inicial);
            break;
        }

        default:
            printf("\nOpcao invalida!\n");
            break;
    }

    return 0;
}
