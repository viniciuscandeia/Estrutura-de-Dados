#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
    ! Usando seu TAD pilha, crie uma função para verificar se uma expressão
    ! composta apenas por chaves, colchetes e parênteses, representada por uma
    ! cadeia, está ou não balanceada. Por exemplo, as expressões "[{()()}{}]" e
    ! "{[([{}])]}" estão balanceadas, mas as expressões "{[(}])" e "{[)()(]}" não estão.
*/

typedef struct no
{
    char carac;
    struct no *proximo;
} No;

void adicionarPilha(No ***pilha, char carac)
{
    No *novo = malloc(sizeof(No));

    // Se a alocação for bem-sucedida
    if (novo)
    {
        novo->carac = carac;
        novo->proximo = NULL;

        // A pilha não está vazia.
        if (**pilha)
        {
            novo->proximo = (**pilha);
            **pilha = novo;
        }

        // A pilha está vazia.
        else    
            **pilha = novo;
    }

    // Se a alocação for mal-sucedida
    else
        printf("Erro ao alocar memoria.");
}

void mostrarPilha(No ***pilha)
{
    // A pilha não está vazia.
    // Expressão não balanceada.
    if (**pilha)
        printf("Expressao nao balanceada.");

    // A pilha está vazia.
    else
        printf("Expressao balanceada.");
}

void removerPilha(No ***pilha)
{
    No *remover = NULL;

    // A fila não está vazia.
    if (**pilha)
    {
        remover = **pilha;
        **pilha = remover->proximo;
    }
}

void expressaoBalanceada(No **pilha, char expressao[30])
{
    for (int i = 0; i < strlen(expressao); i++)
    {
        if (*pilha)
        {
            if (expressao[i] == ')' && (*pilha)->carac == '(' ||
                expressao[i] == ']' && (*pilha)->carac == '[' ||
                expressao[i] == '}' && (*pilha)->carac == '{')    
                removerPilha(&pilha);
        
            else
                adicionarPilha(&pilha, expressao[i]);
        }
        else
            adicionarPilha(&pilha, expressao[i]);
    }

    mostrarPilha(&pilha);
}

int main()
{

    No *pilha = NULL;

    char carac[10];
    printf("Expressao: ");
    scanf("%s", &carac);

    expressaoBalanceada(&pilha, carac);

    return 0;
}