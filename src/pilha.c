#include <stdio.h>
#include <stdlib.h>
#include "includes/pilha.h"

int Tamanho (Pilha *p) {
    return p->tamanho;
}

int Vazia (Pilha *p) {
    return p->topo == p->fundo;
}

void FPVazia (Pilha *p) {
    p->topo = (Apontador) malloc(sizeof(Celula));
    p->fundo = p->topo;
    p->topo->prox = NULL;
    p->tamanho = 0;
}

void Empilha (Item x, Pilha *p) {
    Apontador aux;
    aux = (Apontador) malloc(sizeof(Celula));
    p->topo->item = x;
    aux->prox = p->topo;
    p->topo = aux;
    p->tamanho++;
}

void Desempilha (Pilha *p, Item *item) {
    Apontador q;
    if (Vazia(p)) { return; }
    q = p->topo;
    p->topo = q->prox;
    free(q);
    p->tamanho--;
    *item = p->topo->item;
}

// Funções desenvolvidas de acordo com os slides de aula!