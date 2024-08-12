#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

int funcaoRecursiva(int valor)
{
    if (valor == 0)
        return 1;
    else if (valor == 1)
        return 2;
    else
        return 2 * funcaoRecursiva(valor - 1) + 2 * funcaoRecursiva(valor - 2) + valor;
}

/*
    f(2)
    2 * f(1) + 2 * f(0) + 2
    2 * (2) + 2 * (1) + 2 = 8

    f(3)
    2 * f(2) + 2 * f(1) + 3
    2 * [2 * f(1) + 2 * f(0) + 2] + 2 * (2) + 3
    2 * [2 * (2) + 2 * (1) + 2] + 2 * (2) + 3
    2 * [4 + 2 + 2] + 4 + 3
    2 * [8] + 7
    16 + 7
    23

    f(4)
    2 * f(3) + 2 * f(2) + 4
    2 * [2 * f(2) + 2 * f(1) + 3] + 2 * [2 * f(1) + 2 * f(0) + 2] + 4
    2 * [2 * (2 * f(1) + 2 * f(0) + 2) + 2 * f(1) + 3] + 2 * [2 * f(1) + 2 * f(0) + 2] + 4
    2 * [2 * (2 * (2) + 2 * (1) + 2) + 2 * (2) + 3] + 2 * [2 * (2) + 2 * (1) + 2] + 4
    2 * [2 * (4 + 2 + 2) + 4 + 3] + 2 * [4 + 2 + 2] + 4
    2 * [2 * (8) + 7] + 2 * [8] + 4
    2 * [23] + 2 * 8 + 4
    46 + 16 + 4
    62 + 4
    66
*/

int valorMinimo(int *vetor, int tamanhoVetor)
{
    int menorValor = vetor[0];
    for (int i = 1; i < tamanhoVetor; i++)
    {
        if (vetor[i] < menorValor)
        {
            menorValor = vetor[i];
        }
    }
    return menorValor;
}

int main()
{

    printf("Valor para f(0): %d \n", funcaoRecursiva(0));
    printf("Valor para f(1): %d \n", funcaoRecursiva(1));
    printf("Valor para f(2): %d \n", funcaoRecursiva(2));
    printf("Valor para f(3): %d \n", funcaoRecursiva(3));
    printf("Valor para f(4): %d \n", funcaoRecursiva(4));

    int vetor[] = {1, 3, -2, 4};
    printf("Menor: %d", valorMinimo(vetor, 4));

    return 0;
}