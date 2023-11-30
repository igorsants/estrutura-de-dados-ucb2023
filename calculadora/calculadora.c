#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "calculadora.h"

Pilha* criarPilha() {
    Pilha * p = (Pilha *)malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro: Falha ao alocar memória para a pilha.\n");
        exit(EXIT_FAILURE);
    }
    p->Topo = NULL;
    return p;
}

Item * criarItem(double valor){
    Item *novoItem = (Item *)malloc(sizeof(Item));
    if (novoItem == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoItem->dado = valor;
    novoItem->proximo = NULL;
    return novoItem;
}

void empilhar(Pilha *p, double valor){
    Item *novoNo = criarItem(valor);
    novoNo->proximo = p->Topo;
    p->Topo = novoNo;
}

double desempilhar(Pilha *p){
     if (p->Topo != NULL) {
        Item *temp = p->Topo;
        double valor = temp->dado;
        p->Topo = temp->proximo;
        free(temp);
        return valor;
    } else {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }   
}

double obterTopo(const Pilha *p) {
    if (p->Topo != NULL) {
        return p->Topo->dado;
    } else {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

void aplicarFuncaoUnaria(Pilha *p, double (*funcao)(double)) {
    if (p->Topo != NULL) {
        double operando = desempilhar(p);
        empilhar(p, funcao(operando));
    } else {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

void executarOperacaoBinaria(Pilha *p, char operador) {
    if (p->Topo != NULL) {
        double operando2 = desempilhar(p);
        double operando1 = desempilhar(p);

        switch (operador) {
            case '+':
                empilhar(p, operando1 + operando2);
                break;
            case '-':
                empilhar(p, operando1 - operando2);
                break;
            case '*':
                empilhar(p, operando1 * operando2);
                break;
            case '/':
                if (operando2 != 0.0) {
                    empilhar(p, operando1 / operando2);
                } else {
                    printf("Erro: Divisão por zero\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case '^':
                empilhar(p, pow(operando1, operando2));
                break;
            default:
                printf("Erro: Operador inválido\n");
                exit(EXIT_FAILURE);
        }
    } else {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

void imprimirPilha(const Pilha *p) {
    printf("Pilha: ");
    int indice = 1;
    for (Item *temp = p->Topo; temp != NULL; temp = temp->proximo) {
        printf("[%d] %.2f ", indice++, temp->dado);
    }
    printf("\n");
}

double avaliarExpressaoPosfixada(const char *expressao) {
    Pilha p;
     p = *criarPilha();

    for (int i = 0; expressao[i] != '\0'; ++i) {
        if (isdigit(expressao[i]) || (expressao[i] == '.' && isdigit(expressao[i + 1]))) {
            char *endptr;
            double numero = strtod(&expressao[i], &endptr);
            i = endptr - expressao - 1;
            empilhar(&p, numero);
        } else if (expressao[i] == ' ' || expressao[i] == '\t') {
            continue;
        } else {
            if (isalpha(expressao[i])) {
                char operador[4] = {0};
                int j = 0;
                while (isalpha(expressao[i]) && j < 3) {
                    operador[j++] = expressao[i++];
                }
                --i;
                
                if (strcmp(operador, "sen") == 0) {
                    aplicarFuncaoUnaria(&p, sin);
                } else if (strcmp(operador, "cos") == 0) {
                    aplicarFuncaoUnaria(&p, cos);
                } else if (strcmp(operador, "tan") == 0) {
                    aplicarFuncaoUnaria(&p, tan);
                } else if (strcmp(operador, "log") == 0) {
                    aplicarFuncaoUnaria(&p, log10);
                } else {
                    printf("Erro: Operador inválido\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                executarOperacaoBinaria(&p, expressao[i]);
            }
        }

        // Impressão para facilitar a visualização de como o codigo funciona com notação pós-fixada
        imprimirPilha(&p);
    }

    return obterTopo(&p);
}
