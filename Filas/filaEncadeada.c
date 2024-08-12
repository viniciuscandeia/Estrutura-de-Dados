#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

/*
    | FILA - Uma explicação rápida de como funciona:
        ! Fila é igual fila de um banco, por exemplo. O 1° que chega, é o 1° a sair.
        Se você chega em uma fila com 2 pessoas, você será o 3° a sair.

        Inicialmente, a fila está vazia:
        ! fila == NULL
        Aí você chega, a fila não está mais vazia:
        ! fila != NULL, pois fila = voce
        E como você sabe que só tem você na fila, não terá ninguém atrás de você:
        ! voce -> proximo = NULL
        Se chegar outra pessoa (digamos, Alok), ela ficará atrás de você:
        ! voce -> proximo = Alok
        E como ele é o último da fila:
        ! Alok -> proximo = NULL
        Mas aí chega Bidu na fila, Alok deixa de ser o último:
        ! Alok -> proximo = Bidu
        E Bidu passa a ser o último:
        ! Bidu -> proximo = NULL

        Como sabemos quem vem atrás de cada pessoa, podemos fazer algo assim:
        * pessoa = voce -> proximo -> proximo
                  (você)   (Alok)     (Bidu)
        Podemos interpretar isso como:
            & Quem está atrás de você? Alok
            & Quem está atrás de Alok? Bidu

 */

// Aqui está as informações de cada elemento da fila.
// Por exemplo, em uma fila de banco, através dessas informações,
// seria possível identificar o nome, a idade, ... , de cada pessoa.
typedef struct no
{
    int valor;

    /*
        Além disso, também é necessário informar qual o elemento próximo da fila.
        Por exemplo:
            Representação de um pessoa: (°-°)

            ? INÍCIO -> (°-°), (°-°), (°-°) <- FIM

            Ententendo essa fila:

                Declarando a fila:
                    & No *fila = NULL

                Declarando os pessoas:
                    * No *pessoa1 (DJ Juninho Portugal, é show)
                    # No *pessoa2 (Zeca Pagodinho)
                    ! No *pessoa3 (Dorgival Dantas)

                No banco, pessoa1 (DJ Juninho Portugal, é show) aparece para usar o caixa eletrônico.
                A agência só tinha um caixa, e ele já estava sendo usado.
                A pessoa1 (DJ Juninho Portugal, é show) teve que ficar esperando a vez.

                * Definindo as características do pessoa1 (DJ Juninho Portugal, é show).
                     1° : a cor
                        * pessoa1 -> idade = 37 (não encontrei a idade dele)
                     2° : quem está depois dele (como ele é o último da fila)
                        * pessoa1 -> proximo = NULL

                Mas aí chega pessoa2 (Zeca Pagodinho).

                        * pessoa1 -> proximo = pessoa2

                # Definindo as características do pessoa2 (Zeca Pagodinho).
                    1° : a cor
                        # pessoa2 -> cor = 63
                    2° : quem está depois dele (como ele é o último da fila)
                        # pessoa2 -> proximo = NULL

                Então, entra no banco a pessoa3 (Dorgival Dantas)

                        # pessoa2 -> proximo = pessoa3 (Dorgival Dantas)

                ! Definindo as características do pessoa3 (Dorgival Dantas).
                    1° : a cor
                        ! pessoa3 -> cor = 51
                    2° : quem está depois dele (como ele é o último da fila)
                        ! pessoa3 -> proximo = NULL

                & Recapitulando:
                    & 1° : O início da fila será a pessoa1 (DJ Juninho Portugal, é show)
                    & 2° : Depois de pessoa1 (DJ Juninho Portugal, é show), será a pessoa2 (Zeca Pagodinho)
                    & 3° : Depois de pessoa2 (Zeca Pagodinho), será a pessoa3 (Dorgival Dantas)
                    & 4° : Como a pessoa3 (Dorgival Dantas) é a última, então o próximo dela será NULL
     */

    struct no *proximo;
} No;

// & Criando a função para adicionar na fila.
// & Lembrando que o elemento será inserido no final da fila.
// Não é preciso retornar nada.
// Se fosse passado apenas "No *fila", não seria possível alterar a fila passada.
// Por isso, foi utilizado "ponteiro para ponteiro".
// Além disso, também é preciso passar o valor que queremos inserir na fila.
void adicionarElemento(No **fila, int num)
{
    // Este será o elemento que será adicionao à fila.
    // A informação que ele contém será usada para formar a fila.
    // Por isso, é preciso alocar memória para cada elemento.
    No *novo = malloc(sizeof(No));

    // Pegando o 1° elemento da fila.
    No *elementoAtual = *fila;

    // Se a tentativa de alocar for bem-sucedida.
    if (novo)
    {
        // ! 1° : atribuía as informações do elemento.
        novo->valor = num;

        // ! 2° : quem está depois dele;
        // Como o elemento será inserido no final da fila, não terá ninguém atrás dele.
        novo->proximo = NULL;

        // Pode ser que a fila esteja vazia ou não.
        // Será necessário criar para as duas situações.

        // A fila não está vazia.
        // Você pode ler esse if como " *fila != NULL "
        if (*fila)
        {

            // O próximo do último elemento da fila é NULL.
            // Ou seja, é possível cruzar toda a fila usando esse conhecimento.
            // Para encontrar o último elemento, é preciso testar o próximo do "elementoAtual".
            // Se ele existir, uma nova atribuição será feita.
            while (elementoAtual->proximo)
            {
                // "elementoAtual" receberá o próximo elemento depois dele.
                // Se ele for o 1°, receberá o 2°.
                // Se ele for o 2°, receberá o 3°.
                // ...
                elementoAtual = elementoAtual->proximo;
            }
            // Antes, o próximo depois do último elemento era NULL.
            // Isso será alterado, ao atribuir "novo" para o próximo do "elementoAtual".
            elementoAtual->proximo = novo;
        }

        // A fila está vaiza.
        else
            *fila = novo;

        // Se a fila estiver vazia, "novo" será o 1° elemento.
        // Se a fila não estiver vazia, "novo" será o último elemento.
    }

    // Se a tentativa de alocar for mal-sucedida.
    else
        printf("Erro ao alocar elemento!");
}

// & Criando a função para remover da fila.
// & Lembrando que o elemento removido será do início da fila.
// Vamos retonar qual foi o elemento retirado, para mostrar no main.
// Como será retirado um elemento, o tipo da função tem que ser igual ao tipo do elemento.
No *removerElemento(No **fila)
{

    // Este será o elemento que será removido da fila.
    // É possível chamar a função com a fila vazia, ou seja, a função não eliminará nada.
    No *remover = NULL;

    // A fila não está vazia.
    if (*fila)
    {
        // Pegando o 1° elemento da fila.
        remover = *fila;

        // O 2° elemento passará a ser o 1°.
        *fila = remover->proximo;
    }

    // A fila está vazia.
    else
        printf("Fila vazia.");

    // Estará retornando o elemento removido caso a fila não esteja vazia.
    // Ou, então, retornará NULL.
    return remover;
}

// & Criando a função para mostras os elementos da fila.
// Não é preciso retornar nada.
// Como a função não irá alterar a fila, não é necessário passar "ponteiro para ponteiro".
void mostrarFila(No *fila)
{
    // Pegando o 1° elemento da fila.
    No *elementoAtual = fila;

    // A fila não está vazia.
    if (fila)
    {
        printf("Inicio >> ");

        // O próximo do último elemento da fila é NULL.
        // Ou seja, é possível cruzar toda a fila usando esse conhecimento.
        // O "elementoAtual" ficará sendo testado até que assuma o valor NULL.
        // O que indica que ele passou por toda a fila.

        // Se colocasse "elementoAtual -> proximo", caso a fila tivesse 1 elemento, não iria ser mostrado.
        // Pois, o próximo de um único elemento é NULL.
        // E o teste iria falhar.
        while (elementoAtual)
        {
            printf("%d", elementoAtual->valor);

            // Se o próximo depois do "elementoAtual" existir.
            if (elementoAtual->proximo)
                printf(", ");

            // "elementoAtual" receberá o próximo elemento depois dele.
            // Se ele for o 1°, receberá o 2°.
            // Se ele for o 2°, receberá o 3°.
            // ...
            elementoAtual = elementoAtual->proximo;
        }
    }

    // A fila está vazia.
    else
        printf("Fila vazia.");

    printf("\n");
}

int main()
{

    No *fila = NULL;

    int num;
    No *remover;
    int opcao = 1;

    while (opcao != 0)
    {

        printf(" 1 | Inserir na fila\n");
        printf(" 2 | Remover na fila\n");
        printf(" 3 | Imprimir fila\n");
        printf(" 0 | Sair\n\n");
        printf(" -> ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:

            printf("Numero: ");
            scanf("%d", &num);

            // Como a fila será alterada dentro da função, é preciso passar o endereço dela.
            adicionarElemento(&fila, num);

            break;

        case 2:

            // Como a fila será alterada dentro da função, é preciso passar o endereço dela.
            remover = removerElemento(&fila);

            // Se o elemento removido for != NULL
            if (remover)
                printf("Removido: %d \n", remover->valor);

            break;

        case 3:

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