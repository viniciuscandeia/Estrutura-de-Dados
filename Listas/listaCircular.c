#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// | LISTA CIRCULAR

typedef struct no
{
    int valor;
    bool representaUltimo;
    struct no *proximo;
} No;

// | Função para adicionar elemento no começo da lista.
// Não precisa retornar nada.
void adicionarComeco(No **lista, int valor)
{
    No *novo = malloc(sizeof(No));
    No *aux = (*lista);

    // Alocação bem-sucedida.
    if (novo)
    {
        novo->valor = valor;
        novo->proximo = (*lista);
        novo->representaUltimo = false;

        // Lista não vazia.
        if (*lista)
        {
            novo->proximo = (*lista);

            while (aux->representaUltimo == false && aux->proximo)
            {
                aux->representaUltimo = false;
                aux = aux->proximo;
            }

            aux->proximo = novo;
            aux->representaUltimo = true;

            (*lista) = novo;
        }

        // Lista vazia.
        else
        {
            novo->representaUltimo = true;
            (*lista) = novo;
        }
    }

    // Alocação malsucedida.
    else
    {
        printf("Erro ao alocar memoria.");
    }
}

// | Função para adiiconar no meio da lista.
// Não precisa retornar nada.
void adicionarMeio(No **lista, int valor, int parametro)
{
    No *novo = malloc(sizeof(No));
    No *aux = (*lista);

    // Alocação bem-sucedida.
    if (novo)
    {

        novo->valor = valor;
        novo->proximo = (*lista);
        novo->representaUltimo = false;

        // Lista não vazia.
        if (*lista)
        {
            while (true)
            {
                if (!(aux->representaUltimo) && aux->valor == parametro)
                    break;
                else if (aux->representaUltimo)
                    break;
                else
                    aux = aux->proximo;
            }

            if (!(aux->representaUltimo) && aux->valor == parametro)
            {
                novo->proximo = aux->proximo;
                aux->proximo = novo;
            }
            else
            {
                novo->proximo = (*lista);
                novo->representaUltimo = true;

                aux->representaUltimo = false;
                aux->proximo = novo;
            }
        }

        // Lista vazia.
        else
        {
            novo->representaUltimo = true;
            (*lista) = novo;
        }
    }

    // Alocação malsucedida.
    else
        printf("Erro ao alocar memoria.");
}

// | Função para adicionar elemento no final da lista.
// Não precisa retornar nada.
void adicionarFinal(No **lista, int valor)
{
    No *novo = malloc(sizeof(No));
    No *aux = (*lista);

    // Alocação bem-sucedida.
    if (novo)
    {
        novo->valor = valor;
        novo->representaUltimo = true;
        novo->proximo = (*lista);

        // Lista não vazia.
        if (*lista)
        {
            while (true)
            {
                if (aux->representaUltimo)
                    break;
                else
                    aux = aux->proximo;
            }

            aux->representaUltimo = false;
            aux->proximo = novo;
            novo->proximo = (*lista);
        }

        // Lista vazia.
        else
            (*lista) = novo;
    }

    // Alocação malsucedida.
    else
        printf("Erro ao alocar memoria.");
}

// | Função para remover elemento do começo da lista.
// Retorno será o elemento removido.
No *removerComeco(No **lista)
{
    No *remover = NULL;
    No *aux = (*lista);

    // Lista não vazia.
    if (*lista)
    {
        remover = (*lista);

        while (true)
        {
            if (aux->representaUltimo)
                break;
            else
                aux = aux->proximo;
        }

        if ((*lista)->representaUltimo)
            (*lista) = NULL;
        else
        {
            aux->proximo = remover->proximo;
            (*lista) = remover->proximo;
        }
    }

    // Lista vazia.
    else
        printf("Lista vazia.");

    return remover;
}

// | Função para remover elemento do meio da lista.
// Retorno será o elemento removido.
No *removerMeio(No **lista, int parametro)
{
    No *remover = NULL;
    No *aux = (*lista);
    No *aux2 = (*lista);

    // Lista não vazia.
    if (*lista)
    {
        while (true)
        {
            if (!(aux->representaUltimo) && aux->valor == parametro)
            {
                remover = aux;
                if (aux2 == aux)
                    (*lista) = aux->proximo;
                else
                    aux2->proximo = aux->proximo;
                break;
            }
            else if (aux->representaUltimo && aux->valor == parametro)
            {
                remover = aux;
                if (aux == (*lista))
                    (*lista) = NULL;
                else
                {
                    aux2->representaUltimo = true;
                    aux2->proximo = (*lista);
                }
                break;
            }
            else if (aux->representaUltimo && aux->valor != parametro)
                break;
            else
            {
                if (aux->proximo->valor == parametro)
                    aux2 = aux;
                aux = aux->proximo;
            }
        }
    }

    // Lista vazia.
    else
        printf("Lista vazia.");

    return remover;
}

// | Função para remover elemento do final da lista.
// Retorno será o elemento removido.
No *removerFinal(No **lista)
{
    No *remover = NULL;
    No *aux = (*lista);
    No *aux2 = (*lista);

    // Lista não vazia.
    if ((*lista))
    {
        while (true)
        {

            if (aux->representaUltimo)
            {
                remover = aux;

                while (!(aux2->proximo->representaUltimo))
                    aux2 = aux2->proximo;

                if (aux2->representaUltimo)
                    (*lista) = NULL;
                else
                {
                    aux2->representaUltimo = true;
                    aux2->proximo = (*lista);
                }

                break;
            }
            else
                aux = aux->proximo;
        }
    }

    // Lista vazia.
    else
        printf("Lista vazia.");

    return remover;
}

// | Função para mostrar a lista.
// Não precisa retornar nada.
void mostrarLista(No *lista)
{
    No *aux = lista;

    // Lista não vazia.
    if (lista)
    {
        printf("Inicio >> ");

        do
        {
            printf("%d", aux->valor);

            if (aux->representaUltimo)
                break;
            else
            {
                if (aux->proximo)
                    printf(", ");
                aux = aux->proximo;
            }

        } while (true);
    }

    // Lista vazia.
    else
        printf("Lista vazia.");

    printf("\n");
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

        inicioCodigo();

        printf(" 1 | Adicionar : COMEÇO \n");
        printf(" 2 | Adicionar :   MEIO \n");
        printf(" 3 | Adicionar :    FIM \n");
        printf(" 4 | Remover   : COMEÇO \n");
        printf(" 5 | Remover   :   MEIO \n");
        printf(" 6 | Remover   :    FIM \n");
        printf(" 7 | Imprimir lista\n");
        printf(" 0 | Sair\n\n");
        printf(" -> ");
        scanf("%d", &opcao);

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
                printf("Opcao invalida! \n");
        
            break;
        }
    }

    return 0;
}