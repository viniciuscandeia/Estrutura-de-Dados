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
    struct no *direita, *esquerda;
    int altura;
} NoArv;

// * Função que cria um novo nó
NoArv *novoNo(int num)
{
    NoArv *novo = malloc(sizeof(NoArv));
    if (novo)
    {
        novo->valor = num;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    }
    else
        printf("Erro ao aolocar nó! \n");
    return novo;
}

// * Função para descobrir a maior subárvore
int maiorSub(int subEsq, int subDir)
{
    if (subEsq > subDir)
        return subEsq;
    else
        return subDir;
}

// * Função para descobrir a altura do nó
int alturaNo(NoArv *raiz)
{
    if (raiz == NULL)
        return -1;
    else
        return raiz->altura;
}

// * Função para calcular o fator de balanceamento
int fatorBalanceamento(NoArv *raiz)
{
    if (raiz)
        return (alturaNo(raiz->esquerda) - alturaNo(raiz->direita));
    else
        return 0;
}

// * Função para rotacionar à esquerda
NoArv *rotacaoEsquerda(NoArv *raiz)
{
    printf("\n ============= RE ===========\n");
    imprimirArvore(raiz, 1);

    NoArv *aux1, *aux2;
    aux1 = raiz->direita;
    aux2 = aux1->esquerda;
    aux1->esquerda = raiz;
    raiz->direita = aux2;
    raiz->altura = maiorSub(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    aux1->altura = maiorSub(alturaNo(aux1->esquerda), alturaNo(aux1->direita)) + 1;
    imprimirArvore(raiz, 1);

    return aux1;
}

// * Função para rotacionar à direita
NoArv *rotacaoDireita(NoArv *raiz)
{
    printf("\n ============ RD ============\n");
    imprimirArvore(raiz, 1);

    NoArv *aux1, *aux2;
    aux1 = raiz->esquerda;
    aux2 = aux1->direita;
    aux1->direita = raiz;
    raiz->esquerda = aux2;
    raiz->altura = maiorSub(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    aux1->altura = maiorSub(alturaNo(aux1->esquerda), alturaNo(aux1->direita)) + 1;
    imprimirArvore(raiz, 1);

    return aux1;
}

// * Função para rotação direita esquerda (dupla esquerda)
NoArv *rotacaoDuplaEsquerda(NoArv *raiz)
{
    printf("RDE\n");
    raiz->direita = rotacaoDireita(raiz->direita);
    imprimirArvore(raiz, 1);

    return rotacaoEsquerda(raiz);
}

// * Função para rotação esquerda direita (dupla direita)
NoArv *rotacaoDuplaDireita(NoArv *raiz)
{
    printf("RDD\n");
    raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
    imprimirArvore(raiz, 1);

    return rotacaoDireita(raiz);
}

// * Função para balancear a árvore
NoArv *balancearArvore(NoArv *raiz)
{
    int fb = fatorBalanceamento(raiz);
    if (fb < -1 && fatorBalanceamento(raiz->direita) <= 0)
    {
        imprimirArvore(raiz, 1);
        raiz = rotacaoEsquerda(raiz);
        imprimirArvore(raiz, 1);
    }
    else if (fb > 1 && fatorBalanceamento(raiz->esquerda) >= 0)
    {
        imprimirArvore(raiz, 1);
        raiz = rotacaoDireita(raiz);
        imprimirArvore(raiz, 1);
    }
    else if (fb > 1 && fatorBalanceamento(raiz->esquerda) < 0)
    {
        imprimirArvore(raiz, 1);
        raiz = rotacaoDuplaDireita(raiz);
        imprimirArvore(raiz, 1);
    }
    else if (fb < -1 && fatorBalanceamento(raiz->direita) > 0)
    {
        imprimirArvore(raiz, 1);
        raiz = rotacaoDuplaEsquerda(raiz);
        imprimirArvore(raiz, 1);
    }
    return raiz;
}

// * Função para inserir em uma Árvore Binária de Busca (com retorno e com recursão)
NoArv *inserirElemento(NoArv *raiz, int num)
{
    if (raiz == NULL)
        return novoNo(num);
    else
    {
        if (num < raiz->valor)
            raiz->esquerda = inserirElemento(raiz->esquerda, num);
        else if (num > raiz->valor)
            raiz->direita = inserirElemento(raiz->direita, num);
        else
            printf("O elemento ja existe! \n");
    }
    raiz->altura = maiorSub(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    raiz = balancearArvore(raiz);

    imprimirArvore(raiz, 1);

    return raiz;
}

// * Função para mostrar os elementos de uma Árvore Binária de Busca (Em Ordem)
void imprimirArvore(NoArv *raiz, int nivel)
{
    if (raiz)
    {
        imprimirArvore(raiz->direita, nivel + 1);
        printf("\n\n");
        for (int i = 0; i < nivel; i++)
            printf("\t");
        printf("%d", raiz->valor);
        imprimirArvore(raiz->esquerda, nivel + 1);
    }
}

// * Função para remover nó de uma Árvore Binária de Busca
NoArv *removerElemento(NoArv *raiz, int num)
{
    if (raiz == NULL)
    {
        printf("Valor não encontrado. \n");
        return NULL;
    }
    else
    {
        if (num == raiz->valor)
        {
            if (raiz->esquerda == NULL && raiz->direita == NULL)
            {
                free(raiz);
                printf("Elemento folha removido: %d !\n", num);
                return NULL;
            }
            else
            {
                if (raiz->esquerda != NULL && raiz->direita != NULL)
                {
                    NoArv *aux = raiz->esquerda;
                    while (aux->direita != NULL)
                        aux = aux->direita;
                    raiz->valor = aux->valor;
                    aux->valor = num;
                    printf("Elemento trocado: %d !\n", num);
                    raiz->esquerda = removerElemento(raiz->esquerda, num);
                    return raiz;
                }
                else
                {
                    NoArv *aux;
                    if (raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", num);
                    return aux;
                }
            }
        }
        else
        {
            if (num < raiz->valor)
                raiz->esquerda = removerElemento(raiz->esquerda, num);
            else
                raiz->direita = removerElemento(raiz->direita, num);
        }
        raiz->altura = maiorSub(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
        raiz = balancearArvore(raiz);
        return raiz;
    }
}

int main()
{

    NoArv *raiz = NULL;

    raiz = inserirElemento(raiz, 35);
    imprimirArvore(raiz, 1);

    raiz = inserirElemento(raiz, 39);
    imprimirArvore(raiz, 1);

    raiz = inserirElemento(raiz, 51);
    imprimirArvore(raiz, 1);

    raiz = inserirElemento(raiz, 20);
    imprimirArvore(raiz, 1);

    raiz = inserirElemento(raiz, 13);
    imprimirArvore(raiz, 1);

    raiz = inserirElemento(raiz, 28);
    imprimirArvore(raiz, 1);

    raiz = inserirElemento(raiz, 22);
    imprimirArvore(raiz, 1);

    return 0;
}