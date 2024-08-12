#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

typedef struct no
{
    int valor;
    struct no *proximo;
} No;

void inserirFila(No **fila, int num)
{
    No *novo = malloc(sizeof(No));
    No *aux;
    if (novo)
    {
        novo->valor = num;
        // Inserção no final da fila, logo, não tem ninguém atrás dele.
        novo->proximo = NULL;
        if (*fila == NULL)
        {
            // Fila vazia
            *fila = novo;
        }
        else
        {
            // Fila não vazia
            aux = *fila;
            while (aux->proximo)
            {
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }
    }
    else
    {
        printf("Erro ao alocar Nó!");
    }
}

No *removerFila(No **fila)
{
    No *remover = NULL;

    if (*fila == NULL)
    {
        printf("Fila vazia.");
    }
    else
    {
        remover = *fila;
        *fila = remover->proximo;
    }

    return remover;
}

void imprimirFila(No *fila)
{

    while (fila)
    {
        printf("%d ", fila->valor);
        fila = fila->proximo;
    }
    printf("\n");
}

int main()
{

    No *fila = NULL;
    int opcao = 1;
    int num;

    while (opcao != 0)
    {

        printf("Valor: \n\n"
               " 1 "
               "| Inserir \n"
               " 2 "
               "| Remover \n"
               " 3 "
               "| Mostrar \n"
               " 0 "
               "| Sair\n\n"
               " >> ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Número: ");
            scanf("%d", &num);
            inserirFila(&fila, num);

            break;
        case 2:
            No *removido = removerFila(&fila);
            printf("Removido: %d", removido->valor);

            break;
        case 3:
            imprimirFila(fila);

            break;

        case 0:
            break;

        default:
            printf("Opção inválida!");
            break;
        }
    }
    return 0;
}