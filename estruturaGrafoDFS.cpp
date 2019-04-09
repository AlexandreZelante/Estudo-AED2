#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define TAM 2

typedef struct s{
    int cor;
    int chave;
    struct s* pai;
    struct s *prox;
} NO;

typedef struct{
    NO *vetor[TAM];
} GRAFO;

void inicializarGrafo(GRAFO*g){
    for(int i = 0; i < TAM; i++){
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->chave = i;
        novo->cor = BRANCO;
        novo->prox = NULL;
        g->vetor[i] = novo;
    }   
}

void inserirArestas(GRAFO*g, int vertice, int chave){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = chave;
    novo->cor = BRANCO;
    novo->prox = NULL;

    NO* p = g->vetor[vertice];
    while(p){
        p = p->prox;
    }
    p->prox = novo;
}

void printarGrafo(GRAFO*g){
    for(int i = 0; i < TAM; i++){
        NO* p = g->vetor[i];
        printf("%d : ", g->vetor[i]->chave); 
        while(p){
            printf(" %d ", p->chave);
            p = p->prox;
        }
    }
}


void DFST(GRAFO*g){
    //Como já foi inicializado eu não preciso deixar todas brancas de novo

    //Agora eu vou escolher um vertice inicial e definir ele como cinza e chamar a função DFS
    g->vetor[0]->cor = CINZA;
    g->vetor[0]->pai = -1;
    
}

void DFS(GRAFO*g, NO*v){
    NO* u = v->prox; //Pega um adjacente ao que foi dado
    while(u){ //Enquanto houver um adjacente
        if(u->cor == BRANCO){ //Se ele não foi visitado
            u->cor = CINZA; //Marca como visitado
            u->pai = v; //Define o pai que era o anterior 
            DFS(g, u); //Chama a função recursivamente
        }
        u = u->prox;
    }
    v->cor = PRETO;
}

int main(){
    printf("Hello World!");

    GRAFO g;
    inicializarGrafo(&g);

    inserirArestas(&g, 0, 0);
    inserirArestas(&g, 0, 2);
    inserirArestas(&g, 1, 2);
    inserirArestas(&g, 1, 4);

    printarGrafo(&g);

    return 0;
}