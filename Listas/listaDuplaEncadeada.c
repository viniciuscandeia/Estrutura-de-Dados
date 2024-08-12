#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct no
{
    int valor;
    struct no *proximo;
    struct no *anterior;
} No;

// & Função para adicionar no começo da lista.
// Não precisa retornar nada.
void adicionarComeco(No **lista, int valor)
{
    No *novo = malloc(sizeof(No));
    No *aux = *lista;

    // Alocação bem-sucedida.
    if (novo)
    {
        novo->valor = valor;
        novo->anterior = NULL;
        novo->proximo = NULL;

        // Lista não vazia.
        if (*lista)
        {
            novo->proximo = (*lista);
            (*lista)->anterior = novo;
            (*lista) = novo;
        }

        // Lista vazia.
        else
        {
            (*lista) = novo;
        }
    }

    // Alocação malsucedida.
    else
    {
        printf("Erro ao alocar memoria.");
    }
}

// & Função para adicionar no final da lista.
// Não precisa retornar nada.
void adicionarFinal(No **lista, int valor)
{
    No *novo = malloc(sizeof(No));

    // Alocação bem-sucedida.
    if (novo)
    {
        novo->valor = valor;
        novo->proximo = NULL;
        novo->anterior = NULL;

        // Lista não vazia.
        if (*lista)
        {
            No *aux = (*lista);
            while (aux->proximo)
            {
                aux = aux->proximo;
            }

            novo->anterior = aux;
            aux->proximo = novo;
        }

        // Lista vazia.
        else
        {
            (*lista) = novo;
        }
    }

    // Alocação malsucedida.
    else
    {
    }
}

// & Função para adicionar no meio da lista.
// Não precisa retornar nada.
void adicionarMeio(No **lista, int valor, int parametro)
{
    No *novo = malloc(sizeof(No));
    No *aux = (*lista);

    // Alocação bem-sucedida.
    if (novo)
    {
        novo->valor = valor;
        novo->proximo = NULL;
        novo->anterior = NULL;

        // Lista não vazia.
        if ((*lista))
        {
            while (aux->proximo && aux->valor != parametro)
            {
                aux = aux->proximo;
            }

            if (aux->proximo)
            {
                novo->proximo = aux->proximo;
                novo->anterior = aux;
                aux->proximo->anterior = novo;
                aux->proximo = novo;
            }

            else
            {
                novo->anterior = aux;
                aux->proximo = novo;
            }
        }

        // Lista vazia.
        else
        {
            (*lista) = novo;
        }
    }

    // Alocação malsucedida.
    else
    {
        printf("Erro ao alocar memória.");
    }
}

// & Função para remover no começo da lista.
// Retorno do elemento que será removido.
No *removerComeco(No **lista)
{
    No *remover = NULL;
    No *aux = (*lista);

    // Lista não vazia.
    if (*lista)
    {
        remover = (*lista);

        if (aux->proximo)
        {
            aux = aux->proximo;
            aux->anterior = NULL;
        }
        else
        {
            aux = NULL;
        }

        (*lista) = aux;
    }

    // Lista vazia.
    else
    {
        printf("Lista vazia.");
    }

    return remover;
}

// & Função para remover no meio da lista.
// Retorno do elemento que será removido.
No *removerMeio(No **lista, int parametro)
{
    No *remover = NULL;
    No *aux = (*lista);
    No *aux2 = NULL;

    // Lista não vazia.
    if ((*lista))
    {
        while (aux->proximo && aux->valor != parametro)
        {
            aux = aux->proximo;
        }

        if (aux->valor == parametro)
        {
            remover = aux;

            aux->anterior->proximo = aux->proximo;
            aux->proximo->anterior = aux->anterior;
        }

        else
        {
            printf("Valor nao encontrado.");
        }
    }

    // Lista vazia.
    else
    {
        printf("Lista vazia.");
    }

    return remover;
}

// & Função para remover no final da lista.
// Retorno do elemento que será removido.
No *removerFinal(No **lista)
{
    No *remover = NULL;
    No *aux = (*lista);
    No *aux2 = NULL;

    // Lista não vazia.
    if ((*lista))
    {
        while (aux->proximo)
        {
            aux = aux->proximo;
        }

        remover = aux;

        if (aux->anterior)
        {
            aux->anterior->proximo = NULL;
        }
        else
        {
            (*lista) = NULL;
        }
    }

    // Lista vazia.
    else
    {
        printf("Lista vazia.");
    }

    return remover;
}

// & Função para mostrar a lista.
// Não precisa retornar nada.
void mostrarLista(No *lista)
{
    No *aux = lista;

    // Lista não vazia.
    if (lista)
    {
        printf("Inicio >> ");
        while (aux)
        {
            printf("%d", aux->valor);

            if (aux->proximo)
            {
                printf(", ");
            }

            aux = aux->proximo;
        }
    }

    // Lista vazia.
    else
    {
        printf("Lista vazia.");
    }
}

int main()
{

    No *lista = NULL;
    No *remover = NULL;

    int opcao = 1;
    int num;
    int pos;

    while (opcao != 0)
    {

        printf(" 1 " L"| Adicionar : COMEÇO \n");
        printf(" 2 " L"| Adicionar :   MEIO \n");
        printf(" 3 " L"| Adicionar :    FIM \n");
        printf(" 4 " L"| Remover   : COMEÇO \n");
        printf(" 5 " L"| Remover   :   MEIO \n");
        printf(" 6 " L"| Remover   :    FIM \n");
        printf(" 7 " L"| Imprimir lista\n");
        printf(" 0 " L"| Sair\n\n");
        printf(" -> ");
        wscanf(L"%d", &opcao);

        switch (opcao)
        {
        case 1:

            printf("Numero: ");
            scanf("%d", &num);

            // Como a lista será alterada dentro da função, é preciso passar o endereço dela.
            adicionarComeco(&lista, num);

            break;

        case 2:

            printf("Numero: ");
            scanf("%d", &num);

            mostrarLista(lista);

            printf("Posicao: ");
            scanf("%d", &pos);

            // Como a lista será alterada dentro da função, é preciso passar o endereço dela.
            adicionarMeio(&lista, num, pos);

            break;

        case 3:

            printf("Numero: ");
            scanf("%d", &num);

            // Como a lista será alterada dentro da função, é preciso passar o endereço dela.
            adicionarFinal(&lista, num);

            break;

        case 4:

            // Como a lista será alterada dentro da função, é preciso passar o endereço dela.
            remover = removerComeco(&lista);

            // Se o elemento removido for != NULL
            if (remover)
                printf("Removido: %d \n", remover->valor);

            break;

        case 5:

            mostrarLista(lista);

            printf("Posicao: ");
            scanf("%d", &pos);

            // Como a lista será alterada dentro da função, é preciso passar o endereço dela.
            remover = removerMeio(&lista, pos);

            // Se o elemento removido for != NULL
            if (remover)
                printf("Removido: %d \n", remover->valor);

            break;

        case 6:

            // Como a lista será alterada dentro da função, é preciso passar o endereço dela.
            remover = removerFinal(&lista);

            // Se o elemento removido for != NULL
            if (remover)
                printf("Removido: %d \n", remover->valor);

            break;

        case 7:

            // Como não será alterado nada da lista, não é preciso passar o endereço dela.
            mostrarLista(lista);

            break;

        default:
            if (opcao != 0)
                printf("Opção inválida! \n");
            break;
        }
    }

    
    return 0;
}