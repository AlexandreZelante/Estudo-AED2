// Alexandre Zelante Comuni          N°USP: 10723795

//Cores:
//cor = 'b' BRANCO
//cor = 'c' CINZA
//cor = 'p' PRETO

/*Algoritmo baseado no pseudo-código dado em sala de aula com referências retiradas do livro "Algoritmos - Thomas H. Cormen"*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define NV 11

typedef struct n{
    struct n* prox;
    int pai;
    int cor;
    int minor;
    int valor;
    int ord;
    bool crit;
}NO;

typedef struct{
    NO* graf[NV+1];
}GRAFO;

void DFS1(GRAFO*g, int*ordem, NO*ver){
    NO* u = ver->prox;
    while(u != NULL){
        int y = u->valor;
        NO* ini = g->graf[y];
        if(ini->cor == 'b'){
            *ordem = *ordem + 1;
            ini->ord = *ordem;
            ini->cor = 'c';
            ini->pai = ver->valor;
            DFS1(g,ordem,ini);
        }
        ini->cor = 'p';
        u = u->prox;
    }
}

void DFS2(GRAFO*g, NO*ver){
    NO* u = ver->prox;
    while(u != NULL){
        int valor = u->valor;
        NO* ini = g->graf[valor];
        if(ini->pai == ver->valor){
            DFS2(g,ini);
        }
        u = u->prox;
    }
    NO* k = ver->prox;
    while(k != NULL){
        int j = k->valor;
        NO* q = g->graf[j];
        if(q->valor != ver->pai && q->minor < ver->minor){
            ver->minor = q->minor;
        }
        k = k->prox;
    }
}

bool DFST(GRAFO*g){
    //Inicializa o grafo
    for(int i  = 0; i < NV + 1; i++){
        NO* primeiro = (NO*) malloc(sizeof(NO));
        primeiro->cor = 'b';
        primeiro->crit = false;
        primeiro->minor = i;
        primeiro->ord = 0;
        primeiro->pai = -1;
        primeiro->valor = i;
        g->graf[i] = primeiro;
    }
    
    int ord = 0;
    g->graf[1]->cor = 'c';
    g->graf[1]->ord = ord;
    DFS1(g, &ord, g->graf[1]);

    if(ord != NV + 1){ 
        return false;
    }

    g->graf[1]->minor = g->graf[1]->ord;
    DFS2(g, g->graf[1]);

    for(int i = 0; i < NV + 1; i++){
        if(g->graf[i] != g->graf[1] && g->graf[i]->valor == g->graf[i]->minor) return false;
        
        //Verifica se existe aresta critica
        if(g->graf[i]->valor == g->graf[i]->minor){
            if(i != 0) {
                //Retorna a aresta crítica
                g->graf[i]->crit = true;

                printf("Possui uma aresta critica: vertices %d e %d \n", g->graf[i]->valor, g->graf[i]->pai);   
            }
        }
    }

    return true; // É biconexo
}

void criarArestas(GRAFO*g, int valor, int ar){
    NO* ini = g->graf[valor];
    while(ini->prox != NULL){
        ini = ini->prox;
    }
    NO* add = (NO*) malloc(sizeof(NO));
    add->cor = 'b';
    add->valor = ar;
    add->pai = -1;
    add->ord = 0;

    ini->prox = add;
}

void verificarBiconexo(bool condicaoBiconexo){
    if(condicaoBiconexo == true){
        printf("O grafo eh biconexo!");
    }else{
        printf("O grafo nao eh biconexo!");
    }
}

int main(){
    GRAFO*g;

    int i = 0;
    while(i<NV + 1){
        printf("Insira os vertices, use -99 para indicar o fim");
        int insert = 0;
        while(true){
            scanf("%d", &insert);
            if(insert == -99) break;
            criarArestas(g, i, insert);
        }
        i++;
    }

    //Chama a funcao DFST e retorna se é biconexo
    bool ehBiconexo = DFST(g); 
    //Chama funcao para printar se eh ou nao biconexo
    verificarBiconexo(ehBiconexo);

    return 0;
}



Saída do programa:

Possui uma aresta critica: vertices 7 e 4
O grafo nao eh biconexo!