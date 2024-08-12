#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
    | LISTA ENCADEADA - Como entender?
        ! De maneira direta: é uma fila sem restições.
        Por exemplo:
            Só é possível adicionar em uma fila no final
            Só é possível remover em uma fila pelo começo

        ! Em uma lista, a manipulação é livre.
        ! Pode tanto inserir, como remover de qualquer lugar.

        É possível fazer algo do tipo:
            * Lista: a, b, c, d, e
            Quero adicionar 9 no meio da lista:
            * Lista: a, b, 9, c, d, e
            Ou talvez no final:
            * Lista: a, b, c, d, e, 9
            Quem sabe no começo:
            * Lista: 9. a, b, c, d, e

        ! Você que decide como será manipulado.
 */

typedef struct no
{
    int valor;
    struct no *proximo;
} No;

// Inserir no início
void inserirInicio(No **lista, int valor)
{
    No *novo = malloc(sizeof(No));

    if (novo)
    {
        novo->valor = valor;
        novo->proximo = *lista;

        *lista = novo;
    }

    else
        printf("Erro ao alocar No!");
}

// Inserir no meio
void inserirMeio(No **lista, int valor, int anterior)
{
    No *novo = malloc(sizeof(No));
    No *aux = *lista;

    if (novo)
    {
        novo->valor = valor;

        if ((*lista) == NULL)
        {
            // Lista vazia
            novo->proximo = NULL;
            *lista = novo;
        }
        else
        {
            // Lista não vazia

            // Ele irá procurar o nó com valor "anterior"
            while (aux->proximo && aux->valor != anterior)
                aux = aux->proximo;

            // O próximo do novo nó será o nó depois do nó com valor "anterior"
            novo->proximo = aux->proximo;
            // O próximo nó depois do nó com valor "anterior" será o novo nó
            aux->proximo = novo;
        }
    }
    else
        printf("Erro ao alocar No!");
}

// Inserir no final
void inserirFinal(No **lista, int valor)
{
    No *novo = malloc(sizeof(No));
    No *aux = *lista;

    if (novo)
    {
        novo->proximo = NULL;
        novo->valor = valor;

        if (*lista == NULL)
        {
            // Lista vazia
            *lista = novo;
        }
        else
        {
            // Lista não vazia
            while (aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;
        }
    }
    else
        printf("Erro ao alocar No!");
}

// Remover no início
No *removerInicio(No **lista)
{
    No *remover = NULL;
    No *aux = *lista;

    // Lista não vazia
    if (*lista)
    {

        // Pegando o 1° da lista
        remover = *lista;

        // Pegando o 2° da lista
        aux = aux->proximo;

        // O 2° passará a ser o 1°
        *lista = aux;
    }

    // Lista vazia
    else
        printf("Fila vazia.");

    return remover;
}

// Remover no meio
No *removerMeio(No **lista, int valor)
{
    No *remover = NULL;
    No *aux = *lista;
    No *aux2 = NULL;

    // Lista não vazia
    if (*lista)
    {

        while (aux->proximo && aux->valor != valor)
        {
            // Se o valor do próximo for igual ao "valor"
            if (aux->proximo->valor == valor)
                aux2 = aux;
            aux = aux->proximo;
        }

        // Encontrou o valor
        if (aux->valor == valor)
        {
            remover = aux;
            aux2->proximo = aux->proximo;
        }

        // A lista acabou e não encontrou o valor
        else if (aux->proximo == NULL)
            printf("Valor nao encontrado na lista.");
    }
    
    // Lista vazia
    else
        printf("Fila vazia.");

    return remover;
}

// Remover no final
No *removerFinal(No **lista)
{
    No *remover = NULL;
    No *aux = *lista;
    No *aux2 = *lista;

    // Lista não vazia
    if (*lista)
    {
        while (aux->proximo)
        {

            // Se o próximo depois do próximo do nó for NULL,
            // então o nó atual será o penúltimo
            if (aux->proximo->proximo == NULL)
                aux2 = aux;
            aux = aux->proximo;
        }

        aux2->proximo = NULL;

        remover = aux;
    }

    // Lista vazia
    else
        printf("Fila vazia.");

    return remover;
}

// Imprimir fila
void imprimirLista(No *lista)
{
    No *aux = lista;

    // Fila não vazia
    if (lista)
    {

        printf("Inicio -> ");
        while (aux)
        {
            printf("%d", aux->valor);

            if (aux->proximo)
                printf(", ");

            aux = aux->proximo;
        }
    }

    // Fila vazia
    else
        printf("Fila vazia.");

    printf("\n");
}

int main()
{

    int opcao = 1;
    int num;
    int pos;
    No *lista = NULL;
    No *removido = NULL;

    while (opcao != 0)
    {

        printf(" 1 | Inserir no inicio\n");
        printf(" 2 | Inserir no meio\n");
        printf(" 3 | Inserir no fim\n");
        printf(" 4 | Remover no inicio\n");
        printf(" 5 | Remover no meio\n");
        printf(" 6 | Remover no fim\n");
        printf(" 7 | Imprimir lista\n");
        printf(" 0 | Sair\n\n");
        printf(" -> ");
        scanf("%d", &opcao);

        switch (opcao)
        {

        case 1:

            printf("Numero: ");
            scanf("%d", &num);

            inserirInicio(&lista, num);

            break;

        case 2:

            printf("Numero -> ");
            scanf("%d", &num);

            imprimirLista(lista);

            printf("Posicao -> ");
            scanf("%d", &pos);

            inserirMeio(&lista, num, pos);

            break;

        case 3:

            printf("Numero: ");
            scanf("%d", &num);

            inserirFinal(&lista, num);

            break;

        case 4:

            removido = removerInicio(&lista);

            if (removido)
                printf("Removido: %d \n", removido->valor);

            break;

        case 5:

            imprimirLista(lista);

            printf("Numero: ");
            scanf("%d", &num);

            removido = removerMeio(&lista, num);

            if (removido)
                printf("Removido: %d \n", removido->valor);

            break;

        case 6:

            removido = removerFinal(&lista);

            if (removido)
                printf("Removido: %d \n", removido->valor);

            break;

        case 7:

            imprimirLista(lista);

            break;

        default:

            if (opcao != 0)
                printf("Opcao invalida! \n");

            break;
        }
    }

    return 0;
}