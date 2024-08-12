#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

// | FILA DUPLA

/*
    | FILA DUPLA - Já estou no inferno? Não??? E esse demônio aí??
        ! Uma fila que pode adicionar ou remover tanto no começo, como no final.
*/

typedef struct no
{
    int valor;
    struct no *proximo;
} No;

// & Função para adicionar elemento no começo da fila.
// Não precisa retornar nada.
void adicionarComeco(No **fila, int valor)
{
    No *novo = malloc(sizeof(No));
    No *aux = (*fila);

    // Alocação foi bem-sucedida.
    if (novo)
    {
        novo->proximo = NULL;
        novo->valor = valor;

        // Fila não vazia.
        if (*fila)
        {
            novo->proximo = (*fila);
            (*fila) = novo;
        }

        // Fila vazia.
        else
            (*fila) = novo;
    }

    // Alocação foi mal-sucedida.
    else
        printf("Erro ao alocar memória.");
}

// & Função para adicionar elemento no final da fila.
// Não precisa retornar nada.
void adicionarFinal(No **fila, int valor)
{
    No *novo = malloc(sizeof(No));
    No *aux = (*fila);

    // Alocação foi bem-sucedida.
    if (novo)
    {

        novo->valor = valor;
        novo->proximo = NULL;

        // Fila não vazia.
        if ((*fila))
        {
            while (aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;
        }

        // Fila vazia.
        else
            (*fila) = novo;
    }

    // Alocação foi mal-sucedida.
    else
        printf("Erro ao alocar memória! \n");
}

// & Função para remover elemento do começo da fila.
// Retorno será o elemento removido.
No *removerComeco(No **fila)
{
    No *remover = NULL;

    // Fila não vazia.
    if (*fila)
    {
        remover = (*fila);
        (*fila) = remover->proximo;
    }

    // Fila vazia.
    else
        printf("Fila vazia.");

    return remover;
}

// & Função para remover elemento do final da fila.
// Retorno será o elemento removid.
No *removerFinal(No **fila)
{
    No *remover = NULL;
    No *aux = *fila;

    // Fila não vazia.
    if (*fila)
    {
        while (aux->proximo->proximo)
            aux = aux->proximo;

        remover = aux->proximo;
        aux->proximo = NULL;
    }

    // Fila vazia.
    else
        printf("Fila vazia. \n");

    return remover;
}

// & Função para mostrar a fila.
// Não precisa retornar nada.
void mostrarFila(No *fila)
{
    No *aux = (fila);

    // Fila não vazia.
    if (fila)
    {
        printf("Inicio >> ");
        while (aux)
        {
            printf("%d", aux->valor);

            if (aux->proximo)
                printf(", ");
            aux = aux->proximo;
        }
    }

    // Fila vazia.
    else
        printf("Fila vazia. \n");

    printf("\n");
}

int main()
{

    No *fila = NULL;
    No *remover;

    int opcao = 1;
    int num;

    while (opcao != 0)
    {

        printf(" 1 | Inserir no comeco da fila\n");
        printf(" 2 | Inserir no final  da fila\n");
        printf(" 3 | Remover no comeco da fila\n");
        printf(" 4 | Remover no final  da fila\n");
        printf(" 5 | Imprimir fila\n");
        printf(" 0 | Sair\n\n");
        printf(" -> ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:

            printf("Numero: ");
            scanf("%d", &num);

            // Como a fila será alterada dentro da função, é preciso passar o endereço dela.
            adicionarComeco(&fila, num);

            break;

        case 2:

            printf("Numero: ");
            scanf("%d", &num);

            // Como a fila será alterada dentro da função, é preciso passar o endereço dela.
            adicionarFinal(&fila, num);

            break;

        case 3:

            // Como a fila será alterada dentro da função, é preciso passar o endereço dela.
            remover = removerComeco(&fila);

            // Se o elemento removido for != NULL
            if (remover)
                printf("Removido: %d \n", remover->valor);

            break;

        case 4:

            // Como a fila será alterada dentro da função, é preciso passar o endereço dela.
            remover = removerFinal(&fila);

            // Se o elemento removido for != NULL
            if (remover)
                printf("Removido: %d \n", remover->valor);

            break;

        case 5:

            // Como não será alterado nada da fila, não é preciso passar o endereço dela.
            mostrarFila(fila);

            break;

        default:
            if (opcao != 0)
                printf("Opcao invalida! \n");

            break;
        }
    }

    return 0;
}