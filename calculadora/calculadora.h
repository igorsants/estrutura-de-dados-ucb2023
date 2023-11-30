#ifndef CALCULADORA_H_
#define CALCULADORA_H_

typedef struct Item {
    double dado;
    struct Item *proximo;
} Item;

typedef struct Pilha{
    Item* Topo;
} Pilha;

Pilha* criarPilha();
Item * criarItem(double v);
void empilhar(Pilha *p, double v);
double desempilhar(Pilha *pilha);
double obterTopo(const Pilha *pilha);
void aplicarFuncaoUnaria(Pilha *pilha, double (*funcao)(double));
void executarOperacaoBinaria(Pilha *pilha, char operador);
void imprimirPilha(const Pilha *p);
double avaliarExpressaoPosfixada(const char *expressao);

#endif
