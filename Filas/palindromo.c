#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#include <string.h>
#include <ctype.h>

#include "aditivos.h"

/*
    ! Usando seus TADs fila e pilha, implemente um
    ! programa em que o usuário digita cadeias e ele diz,
    ! para cada cadeia, se ela é palíndroma ou não
*/

typedef struct no
{
    char caracter;
    struct no *proximo;
} No;

void adicionarElemento(No ***fila, char caracter)
{
    No *novo = malloc(sizeof(No));

    // A alocação foi bem-sucedida.
    if (novo)
    {
        novo->caracter = caracter;
        novo->proximo = NULL;

        // A fila não está vazia.
        if (**fila)
        {
            No *aux = **fila;

            while (aux->proximo)
                aux = aux->proximo;

            aux->proximo = novo;
        }

        // A fila está vazia.
        else
            **fila = novo;
    }

    // A alocação foi mal-sucedida.
    else
        printf("Erro ao alocar memoria. \n");
}

No *removerElemento(No ***fila)
{
    No *remover = NULL;

    // A fila não está vazia.
    if (**fila)
    {
        remover = **fila;
        (**fila) = remover->proximo;
    }

    // A fila está vazia.
    else
        printf("Fila vazia. \n");

    return remover;
}

void mostrarFila(No ****fila)
{
    No *aux = ***fila;

    // A fila não está vazia.
    if (***fila)
    {
        printf("Inicio >> ");
        while (aux)
        {
            printf("%c", aux->caracter);
            if (aux->proximo)
                printf(", ");

            aux = aux->proximo;
        }
    }

    // A fila está vazia.
    else
        printf("Fila vazia.");
}

void mostrarFila2(No ***fila)
{

    if (**fila)
    {
        printf("Nao palindromo \n");
        mostrarFila(&fila);
    }
    else
        printf("Palindromo");
}

void expressaoPalindroma(No **fila, char expressao[20])
{
    int numEspacos = 0;
    for (int i = 0; i < strlen(expressao); i++)
        if (expressao[i] == ' ' || expressao[i] == ',' || expressao[i] == '!')
            numEspacos += 1;

    int numTotal = strlen(expressao) - numEspacos;
    char *expressaoCopia = malloc(sizeof(char) * numTotal);

    numEspacos = 0;

    for (int i = 0; i < strlen(expressao); i++)
    {
        if (expressao[i] != ' ' && expressao[i] != ',' && expressao[i] != '!')
        {
            expressaoCopia[numEspacos] = expressao[i];
            numEspacos += 1;
        }
    }

    for (int i = 0; i < strlen(expressaoCopia); i++)
        if (toupper(expressaoCopia[i]) != toupper(expressaoCopia[strlen(expressaoCopia) - 1 - i]))
            adicionarElemento(&fila, expressaoCopia[i]);

    mostrarFila2(&fila);

    free(expressaoCopia);
}

int main()
{

    No *fila = NULL;

    char frase[30];
    printf("NAO COLOQUE LETRAS ACENTUADAS.\n");
    printf("Frase: ");
    scanf(" %80[^\n]", frase);

    expressaoPalindroma(&fila, frase);

    free(fila);

    return 0;
}