#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

#define QUANTIDADE_CARACTER 20

typedef struct no
{
    int quantElem;
    char pos[2][QUANTIDADE_CARACTER];
} No;

void adicionarElemento(No **fila, char caracter)
{
    // A fila não está cheia.
    if ((*fila)->quantElem < QUANTIDADE_CARACTER)
    {
        // A fila não está vazia.
        if (*fila)
            (*fila)->quantElem += 1;

        // A fila está vazia.
        else
            (*fila)->quantElem = 0;

        (*fila)->pos[0][(*fila)->quantElem] = caracter;
    }

    // A fila já está cheia.
    else
        printf("Fila cheia.");
}

char removerElemento(No **fila)
{
}

int main()
{

    inicioCodigo();

    traco(2);
    return 0;
}