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
 
void Desempilha (Pilha *p, Item *item);
int Vazia (Pilha *p);
void FPVazia (Pilha *p);
void Empilha (Item x, Pilha *p);
int Tamanho (Pilha *p);

// Implementação de pilhas baseada nos slides passados durante as aulas!