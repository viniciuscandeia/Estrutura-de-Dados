#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define NUMERO_ELEMENTOS 5

// & A pilha será estática.
typedef struct no
{
    int quantEle;
    int pos[NUMERO_ELEMENTOS];
} No;

// & Função para criar a pilha.
// Inicialmente, pilha vazia.
No *criaPilha(void)
{
    No *pilha = malloc(sizeof(No));
    pilha->quantEle = 0;

    return pilha;
}

// & Função para adicionar elemento na pilha (push / empilhar).
// & Lembrando que o elemento será inserido no início da pilha.
// Não é preciso retornar nada.
// Se fosse passado apenas "No *pilha", não seria possível alterar a pilha passada.
// Por isso, foi utilizado "ponteiro para ponteiro".
// Além disso, também é preciso passar o valor que queremos inserir na pilha.
void adicionaElemento(No **pilha, int num)
{

    // Se a pilha não estiver cheia.
    if ((*pilha)->quantEle < NUMERO_ELEMENTOS)
    {
        // Uma cópia da pilha atual será criada.
        int *arrayProximos = malloc(sizeof(int) * (*pilha)->quantEle);
        for (int i = 0; i < (*pilha)->quantEle; i++)
            arrayProximos[i] = (*pilha)->pos[i];

        // O novo elemento será inserido no 1° lugar da pilha.
        (*pilha)->pos[0] = num;

        // A quantidade de elementos aumentará em uma unidade.
        (*pilha)->quantEle += 1;

        // Adiciona tudo que foi copiado uma posição à frente.
        for (int i = 1; i <= (*pilha)->quantEle; i++)
            (*pilha)->pos[i] = arrayProximos[i - 1];

        // Liberando o array que tinha a cópia da pilha.
        free(arrayProximos);
    }

    // Se a pilha já estiver cheia.
    else
        printf("Array cheio! \n");
}

// & Criando uma função para retirar um elemento da pilha (pop / desempilhar).
// & Lembrando que a remoção será do 1° elemento da pilha.
// Vamos retonar qual foi o número do elemento retirado, para mostrar no main.
// Como será retirado o número do elemento, o tipo da função tem que ser int.
int removerElemento(No **pilha)
{
    // A pilha não está vazia.
    if ((*pilha)->quantEle != 0)
    {
        // Uma cópia da pilha atual será criada.
        int *arrayProximos = malloc(sizeof(int) * (*pilha)->quantEle);
        for (int i = 0; i < (*pilha)->quantEle; i++)
            arrayProximos[i] = (*pilha)->pos[i];

        // A quantidade de elementos diminuirá em uma unidade.
        (*pilha)->quantEle -= 1;

        // Aqui será a variável que será retornanda contendo o valor do 1° elemento da pilha.
        int valorRemovido = (*pilha)->pos[0];

        // Adiciona tudo que foi copiado uma posição antes.
        for (int i = 0; i < (*pilha)->quantEle; i++)
            (*pilha)->pos[i] = arrayProximos[i + 1];

        // Liberando o array que tinha a cópia da pilha.
        free(arrayProximos);

        return valorRemovido;
    }

    // A pilha está vazia.
    else
        printf("Pilha vazia.");
}

// & Criando uma função para mostrar os elementos da pilha.
// Não é preciso retornar nada.
// Como a função não irá alterar a pilha, não é necessário passar "ponteiro para ponteiro".
void mostrarPilha(No *pilha)
{

    // Se a pilha não estiver vazia.
    if (pilha->quantEle != 0)
    {
        // Mostrando cada valor da pilha.
        for (int i = 0; i < pilha->quantEle; i++)
        {
            printf("%d", pilha->pos[i]);
            if (i + 1 != pilha->quantEle)
                printf("\n");
        }
    }

    // Se a pilha estiver vazia.
    else
        printf("Pilha vazia.");

    printf("\n");
}

int main()
{

    No *pilha = criaPilha();

    int num;
    int valorRemovido;
    int opcao = 1;
    while (opcao != 0)
    {

        printf(" 1 | Inserir na pilha\n");
        printf(" 2 | Remover na pilha\n");
        printf(" 3 | Imprimir pilha\n");
        printf(" 0 | Sair\n\n");
        printf(" -> ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:

            printf("Numero: ");
            scanf("%d", &num);

            // Como a pilha será alterada dentro da função, é preciso passar o endereço dela.
            adicionaElemento(&pilha, num);
            break;

        case 2:

            // Como a pilha será alterada dentro da função, é preciso passar o endereço dela.
            valorRemovido = removerElemento(&pilha);

            // Se o elemento removido for != NULL
            if (valorRemovido)
                printf("Removido: %d \n", valorRemovido);

            break;

        case 3:

            // Como não será alterado nada da pilha, não é preciso passar o endereço dela.
            mostrarPilha(pilha);

            break;

        default:
            if (opcao != 0)
                printf("Opção inválida!");

            break;
        }
    }

    return 0;
}