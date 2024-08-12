#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

/*
    & Crie um programa que pede ao usuário valores inteiros e exibe seu
    & correspondente em binário.
 */

typedef struct no
{
    int valorBinario;
    struct no *proximo;
} No;

void adicionarPilha(No ***pilha, int numBinario)
{
    No *novo = malloc(sizeof(No));

    // Se a alocação for bem-sucedida
    if (novo)
    {
        novo->valorBinario = numBinario;
        novo->proximo = NULL;

        // A pilha não está vazia.
        if (**pilha)
        {
            novo->proximo = (**pilha);
            **pilha = novo;
        }

        // A pilha está vazia.
        else
        {
            **pilha = novo;
        }
    }

    // Se a alocação for mal-sucedida
    else
    {
        printf("Erro ao alocar memoria.");
    }
}

void mostrarPilha(No ***pilha)
{
    printf("\nBinario: ");
    while (**pilha)
    {
        printf("%d", (**pilha)->valorBinario);
        (**pilha) = (**pilha)->proximo;
    }
    printf("\n");
}

int numeroBinario(No **pilha, int numDecimal)
{
    int restoDivisao;
    int resultadoDivisao;

    while (numDecimal != 0)
    {
        printf("\n%4d | %4d\n", numDecimal, 2);
        printf("      -------\n");

        restoDivisao = numDecimal % 2;

        adicionarPilha(&pilha, restoDivisao);

        resultadoDivisao = floor(numDecimal / 2);
        numDecimal = resultadoDivisao;

        printf("%4d   %4d \n", restoDivisao, resultadoDivisao);
    }

    if (numDecimal == 1)
    {
        adicionarPilha(&pilha, numDecimal);
    }

    mostrarPilha(&pilha);

    return 0;
}

int main()
{

    int num;
    printf("Numero: ");
    scanf("%d", &num);

    No *pilha = NULL;

    int resultadoBinario = numeroBinario(&pilha, num);

    return 0;
}