#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "calculadora.h"

int main() {
    // Tamanho máximo para a expressão
    #define MAX_TAMANHO 100

    char expressao[MAX_TAMANHO];

    printf("Digite a expressao posfixada: ");
    scanf("%99[^\n]", expressao);

    double resultado = avaliarExpressaoPosfixada(expressao);
    printf("Resultado: %.2f\n", resultado);

    return 0;
}
