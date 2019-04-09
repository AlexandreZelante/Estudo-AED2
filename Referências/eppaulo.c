/*Busca em profundidade para determinar se o grafo eh biconexo e retornar a VERTICE critica
    cor 0 -> branco
    cor 1 -> cinza
    cor 2 -> preto
    O vertice inicial comeca em 0 ate 11
*/

/*Para numerar certo os vertices (Apos descobrir os minimos) precisamos comparar os minimos de u e v(pai de u).
    Se u->minimo <= v->minimo entao fica a direita de v.
    Senao fica a esquerda de v.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define VERTICE 12

typedef struct s {
    int label;
    int cor;
    struct s* pai;
    int minimo;
    int ordem;
    struct s* prox;
} NO;

typedef struct {
    NO* novo[VERTICE];
} LISTA;

void busca (LISTA *inicio, NO* v, int *ord) {
    for (NO* u = v->prox; u != NULL; u = u->prox) {
        int y = u->label;
        NO* p = inicio->novo[y];
        if (p->cor == 0) {
            p->cor = 1;
            p->pai = v->label;
            *ord = *ord + 1;
            p->ordem = *ord;
            busca (inicio,p,ord);
        }
        p->cor = 2;
    }
}

void DFS2 (LISTA *inicio, NO* v) {
    for (NO* u = v->prox; u != NULL; u = u->prox){
        int y = u->label;
        NO* p = inicio->novo[y];
        if (p->pai == v->label) DFS2 (inicio,p);
    }
    for (NO* z = v->prox; z != NULL; z = z->prox) {
        int q = z->label;
        NO* r = inicio->novo[q];
        if (r->label != v->pai && r->minimo < v->minimo) v->minimo = r->minimo;
    }
}

void DFS(LISTA *inicio) {
    int ord = 0;
    //Realiza a troca da cor branco para cinza do Vertice inicial e chama a busca
    if (inicio->novo[1]->cor == 0) {
        inicio->novo[1]->cor = 1;
        inicio->novo[1]->pai = -1;
        inicio->novo[1]->ordem = ord;
        busca (inicio, inicio->novo[1],&ord);
    }
    //Verifica se ordem+1 eh igual a quantidade de Vertices para ver se andou por todos os vertices e chama DFS2 que calcula o minimo
    if (ord+1 == VERTICE) {
        inicio->novo[1]->minimo = inicio->novo[1]->label;
        DFS2 (inicio,inicio->novo[1]);
    }
    //Verifica se o grafo eh biconexo
    bool biconexo = true;
    for (int i = 0; i < VERTICE; i++) {
        if (inicio->novo[i] != inicio->novo[1] && inicio->novo[i]->label == inicio->novo[i]->minimo) biconexo = false;
        //Aqui faz a verificacao do label com o minimo porque se forem iguais, existe Aresta Critica
        if (inicio->novo[i]->label == inicio->novo[i]->minimo) {
            if (i != 0) printf ("Aresta critica entre os vertices %d e %d \n", inicio->novo[i]->label, inicio->novo[i]->pai);
        }
    }
    if (biconexo == false) printf ("Nao eh biconexo\n");
    else printf ("Eh biconexo\n");

}

void inicializa (LISTA *inicio) {
    for (int i = 0; i < VERTICE; i++) {
        NO* novo = (NO*) malloc (sizeof(NO));
        novo->prox = NULL;
        novo->label = i;
        novo->cor = 0;
        novo->minimo = i;
        novo->ordem = 0;
        novo->pai = -1;
        inicio->novo[i] = novo;
    }
}

void aresta (LISTA *inicio, int i, int aresta) {
    NO* novo = (NO*) malloc (sizeof (NO));
    novo->prox = NULL;
    novo->label = aresta;
    novo->cor = 0;
    novo->pai = -1;
    novo->ordem = 0;

    NO* p = inicio->novo[i];
    while (p->prox != NULL) p = p->prox;
    p->prox = novo;
}

void printa (LISTA *inicio) {
    for (int i = 0; i < VERTICE; i++) {
        NO* p = inicio->novo[i];
        while (p != NULL) {
            printf ("%d ",p->label);
            p = p->prox;
        }
        printf ("\n");
    }
}

int main () {

    LISTA* novo;
    inicializa(novo);


    for (int i = 0; i < VERTICE; i++) {
        int resp = 1;
        printf ("Adicione VERTICEs do vertice %d (-1 - Parar)\n",i);
        while (resp != -1) {
            scanf ("%d",&resp);
            if (resp == -1) break;
            aresta (novo,i,resp);
        }
    }

    printa (novo);

    DFS (novo);
}
