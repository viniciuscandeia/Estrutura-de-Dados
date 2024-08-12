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
    | PILHA - Como funciona?
        ! Imagine uma pilha de pratos, ou de livros.
        Quando queremos adicionar um item na pilha, colocamos no topo dela.
        Já quando vamos remover algo da pilha, começamos pelo topo dela.

        ! Ou seja, iremos inserir ou remover no topo.

        Por exemplo, uma pilha vazia:
        ! pilha = NULL
        Coloco um prato na pia:
        ! pilha != NULL, pois pilha = prato1
        Aí coloco outro prato na pia
        ! pilha = prato2
        E o prato que está depois (ou abaixo) do prato2, é o prato1
        ! prato2 -> proximo = prato1

        Como sabemos qual vem depois de cada prato, podemos fazer algo assim:
        * prato = prato2 -> prato1
                  (1°)      (2°)
*/

// Aqui está as informações de cada elemento da pilha.
// Por exemplo, em uma pilha de pratos, através dessas informações,
// seria possível identificar o tamanho, a cor, ... , de cada prato.
typedef struct no
{

    // Todas as características são declaradas aqui.
    int valor;

    /*
        Além disso, também é necessário informar qual o elemento próximo da pilha.
        Por exemplo:
            Representação de um prato: -__-

            * -__- <- TOPO
            # -__-
            ! -__-
            ?      <- FIM

            Ententendo essa pilha:

                Declarando o topo:
                    & No *topo = NULL

                Declarando os pratos:
                    * No *prato1 (prato verde)
                    # No *prato2 (prato roxo)
                    ! No *prato3 (prato amarelo)

                * Definindo as características do prato1 (prato verde).
                     1° : a cor
                        * prato1 -> cor = verde
                     2° : quem está depois dele (prato2 (prato roxo))
                        * prato1 -> proximo = topo

                # Definindo as características do prato2 (prato roxo).
                    1° : a cor
                        # prato2 -> cor = roxo
                    2° : quem está depois dele (prato3 (prato amarelo))
                        # prato2 -> proximo = prato1

                ! Definindo as características do prato3 (prato amarelo).
                    1° : a cor
                        ! prato3 -> cor = amarelo
                    2° : quem está depois dele (no caso, não há nenhum prato além dele, então será NULL)
                        ! prato3 -> proximo = NULL

                & Recapitulando:
                    & 1° : O topo da pilha será o prato1 (prato verde)
                    & 2° : Depois do prato1 (prato verde), será o prato2 (prato roxo)
                    & 3° : Depois do prato2 (prato roxo), será o prato3 (prato amarelo)
                    & 4° : Como o prato3 (prato amarelo) é o último, então o próximo dele será NULL
     */

    struct no *proximo;
} No;

// & Criando a função para adicionar na pilha (push / empilhar).
// & Lembrando que o elemento será inserido no início da pilha.
// Não é preciso retornar nada.
// Se fosse passado apenas "No *pilha", não seria possível alterar a pilha passada.
// Por isso, foi utilizado "ponteiro para ponteiro".
// Além disso, também é preciso passar o valor que queremos inserir na pilha.
void adicionarElemento(No **pilha, int num)
{
    // Aqui é o elemento que será adicionado à pilha.
    // ! Quando falo "elemento", entenda como "prato" ou "livro".
    // A informação que ele contém será usada para formar a pilha.
    // Por isso, é preciso alocar memória para cada elemento.
    No *novo = malloc(sizeof(No));

    // Se a tentativa de alocar for bem-sucedida.
    if (novo)
    {
        // ! 1° : atribuía as informações do elemento.
        novo->valor = num;

        // Pode ser que a pilha esteja vazia ou não.
        // Será necessário criar para as duas situações.

        // A pilha não estará vazia.
        // Você pode ler esse if como " *pilha != NULL "
        if (*pilha)
        {
            // É preciso saber quem era o elemento que estava em 1°
            No *antigoPrimeiro = *pilha;

            // ! 2° : quem está depois dele
            // O antigo 1° ficará depois do novo elemento.
            // Ou seja, o antigo 1° passará a ser o 2°.
            // E o novo elemento será o 1°.
            novo->proximo = antigoPrimeiro;

            // O novo elemento criado ocupará a 1° posição da pilha.
            *pilha = novo;
        }

        // A pilha estará vazia.
        else
        {
            // ! 2° : quem está depois dele
            // Ele será o 1° elemento da pilha, então, não terá ninguém depois dele.
            novo->proximo = NULL;

            // O novo elemento criado ocupará a 1° posição da pilha.
            *pilha = novo;
        }
    }

    // Se a tentativa de alocar for mal-sucedida.
    else
        printf("Erro ao alocar elemento!");
}

// & Criando uma função para retirar um elemento da pilha (pop / desempilhar).
// & Lembrando que a remoção será do 1° elemento da pilha.
// Vamos retonar qual foi o elemento retirado, para mostrar no main.
// Como será retirado um elemento, o tipo da função tem que ser igual ao tipo do elemento.
No *removerElemento(No **pilha)
{
    // Este será o elemento que será removido da pilha.
    // É possível chamar a função com a pilha vazia, ou seja, a função não eliminará nada.
    No *remover = NULL;

    // A pilha não está vazia.
    if (*pilha)
    {
        // Pegando o 1° elemento da pilha
        remover = *pilha;

        // O 2° elemento passará a ser o 1°, após a remoção do antigo 1°
        *pilha = remover->proximo;
    }

    // A pilha está vazia.
    else
        printf("Pilha vazia.");

    // Estará retornando o elemento removido caso a pilha não esteja vazia.
    // Ou, então, retornará NULL
    return remover;
}

// & Criando uma função para mostrar os elementos da pilha.
// Não é preciso retornar nada.
// Como a função não irá alterar a pilha, não é necessário passar "ponteiro para ponteiro".
void mostrarPilha(No *pilha)
{
    // O "elementoAtual" receberá o 1° elemento da pilha.
    No *elementoAtual = pilha;

    // A pilha não está vazia.
    if (pilha)
    {
        // A pilha será mostrada de maneira vertical, tipo, uma pilha (rs).

        // O próximo do último elemento da pilha é NULL.
        // Ou seja, é possível cruzar toda a pilha usando esse conhecimento.
        // O "elementoAtual" ficará sendo testado até que assuma o valor NULL.
        // O que indica que ele passou por toda a pilha.
        while (elementoAtual)
        {
            printf("%d", elementoAtual->valor);

            // Se o próximo elemento depois do "elementoAtual" existir, irá pular uma linha.
            // Se o "elementoAtual" for o 1°, e o 2° elemento existir, irá pular uma linha.
            if (elementoAtual->proximo)
                printf("\n");

            // "elementoAtual" receberá o próximo elemento depois dele.
            // Se ele for o 1°, receberá o 2°.
            // Se ele for o 2°, receberá o 3°.
            // ...
            elementoAtual = elementoAtual->proximo;
        }
    }

    // A pilha está vazia.
    else
        printf("Pilha vazia.");

    printf("\n\n");
}

int main()
{

    // Inicialmente, a pilha está vazia.
    // O uso do * é porque será preciso alterar as informações da pilha por meio das funções.
    // Caso não colocasse, será possível alterar apenas pelo main.
    No *pilha = NULL;

    int num;
    No *remover;
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
            adicionarElemento(&pilha, num);
            break;

        case 2:

            // Como a pilha será alterada dentro da função, é preciso passar o endereço dela.
            remover = removerElemento(&pilha);

            // Se o elemento removido for != NULL
            if (remover)
                printf("Removido: %d \n", remover->valor);
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