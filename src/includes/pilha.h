typedef struct {
    int dir;
    int esq;
} Item;

typedef struct Celula_str *Apontador;
 
typedef struct Celula_str {
    Item item;
    Apontador prox;
} Celula;
 
typedef struct {
    Apontador fundo, topo;
    int tamanho;
} Pilha;
// #1:
void Desempilha (Pilha *p, Item *item);
// #2:
int Vazia (Pilha *p);
// #3
void FPVazia (Pilha *p);
// #4
void Empilha (Item x, Pilha *p);
// #5
int Tamanho (Pilha *p);

// Implementação de pilhas baseada nos slides passados durante as aulas!