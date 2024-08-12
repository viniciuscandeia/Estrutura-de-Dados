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
} NoArv;

// * Função para inserir em uma Árvore Binária de Busca (com retorno e com recursão)
NoArv *inserirElemento(NoArv *raiz, int num)
{
    if (raiz == NULL)
    {
        NoArv *aux = malloc(sizeof(NoArv));
        aux->valor = num;
        aux->esquerda = NULL;
        aux->direita = NULL;
        return aux;
    }
    else
    {
        if (num < raiz->valor)
            raiz->esquerda = inserirElemento(raiz->esquerda, num);
        else
            raiz->direita = inserirElemento(raiz->direita, num);
        return raiz;
    }
}

// * Função para mostrar os elementos de uma Árvore Binária de Busca (Em Ordem)
void imprimirArvore(NoArv *raiz)
{
    if (raiz)
    {
        printf("%d ", raiz->valor);
        imprimirArvore(raiz->esquerda);
        imprimirArvore(raiz->direita);
    }
}

// * Função para mostrar os elementos de uma Árvore Binária de Busca (Pré-Ordem)
void imprimirArvore2(NoArv *raiz)
{
    if (raiz)
    {
        imprimirArvore2(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimirArvore2(raiz->direita);
    }
}

// * Função para inserir em uma Árvore Binária de Busca (sem retorno e com recursão)
void *inserirElemento2(NoArv **raiz, int num)
{
    if ((*raiz) == NULL)
    {
        (*raiz) = malloc(sizeof(NoArv));
        (*raiz)->valor = num;
        (*raiz)->esquerda = NULL;
        (*raiz)->direita = NULL;
    }
    else
    {
        if (num < (*raiz)->valor)
            inserirElemento2(&((*raiz)->esquerda), num);
        else
            inserirElemento2(&((*raiz)->direita), num);
    }
}

// * Função para inserir em uma Árvore Binária de Busca (sem retorno e sem recursão)
void *inserirElemento3(NoArv **raiz, int num)
{
    NoArv *aux = (*raiz);
    while (aux)
    {
        if (num < aux->valor)
            raiz = &(aux->esquerda);
        else
            raiz = &(aux->direita);
        aux = (*raiz);
    }
    aux = malloc(sizeof(NoArv));
    aux->valor = num;
    aux->esquerda = NULL;
    aux->direita = NULL;
    (*raiz) = aux;
}

// * Função para buscar um elemento em uma Árvore Binária de Busca (com recursão)
NoArv *buscarElemento(NoArv *raiz, int num)
{
    if (raiz)
    {
        if (raiz->valor == num)
            return raiz;
        else if (num < raiz->valor)
            return buscarElemento(raiz->esquerda, num);
        else
            return buscarElemento(raiz->direita, num);
    }
    return NULL;
}

// * Função para buscar um elemento em uma Árvore Binária de Busca (sem recursão, iterativa)
NoArv *buscarElemento2(NoArv *raiz, int num)
{
    while (raiz)
    {
        if (num < raiz->valor)
            raiz = raiz->esquerda;
        else if (num > raiz->valor)
            raiz = raiz->direita;
        else
            return raiz;
    }
    return NULL;
}

// * Função para calcular a altura de uma Árvore Binária de Busca
int alturaArvore(NoArv *raiz)
{
    if (raiz == NULL)
        return -1;
    else
    {
        int valorEsq = alturaArvore(raiz->esquerda);
        int valorDir = alturaArvore(raiz->direita);
        if (valorEsq > valorDir)
            return valorEsq + 1;
        else
            return valorDir + 1;
    }
}

// * Função para calcular a quantidade de nós de uma Árvore Binária de Busca
int quantidadeNos(NoArv *raiz)
{
    if (raiz == NULL)
        return 0;
    else
        return 1 + quantidadeNos(raiz->esquerda) + quantidadeNos(raiz->direita);
}

// * Função para calcular a quantidade de folhas de uma Árvore Binária de Busca
int quantidadeFolhas(NoArv *raiz)
{
    if (raiz == NULL)
        return 0;
    else if (raiz->esquerda == NULL && raiz->direita == NULL)
        return 1;
    else
        return quantidadeFolhas(raiz->esquerda) + quantidadeFolhas(raiz->direita);
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
            return raiz;
        }
    }
}

// * Função para descobrir o nível de um nó na Árvore Binária de Busca (Pré-Ordem)
void nivelNo(NoArv *raiz, int nivel)
{
    if (raiz)
    {
        nivelNo(raiz->esquerda, nivel + 1);
        printf("%d(%d) ", raiz->valor, nivel);
        nivelNo(raiz->direita, nivel + 1);
    }
}

// * Função para buscar o nível de um nó na Árvore Binária de Busca
NoArv *buscarNivel(NoArv *raiz, int num, int nivel)
{
    if (raiz)
    {
        if (raiz->valor == num)
        {
            printf("Nivel de %d: %d \n", num, nivel);
            return raiz;
        }
        else if (num < raiz->valor)
            return buscarNivel(raiz->esquerda, num, nivel + 1);
        else
            return buscarNivel(raiz->direita, num, nivel + 1);
    }
    return NULL;
}

// * Função para somar os valores das folhas de uma Árvore Binária de Busca
int somarFolhas(NoArv *raiz)
{
    if (raiz == NULL)
        return 0;
    else if (raiz->esquerda == NULL && raiz->direita == NULL)
        return raiz->valor;
    else
        return somarFolhas(raiz->esquerda) + somarFolhas(raiz->direita);
}

int main()
{

    NoArv *raiz = NULL;
    NoArv *busca;

    inserirElemento3(&raiz, 583);
    inserirElemento3(&raiz, 245);
    inserirElemento3(&raiz, 731);
    inserirElemento3(&raiz, 123);
    inserirElemento3(&raiz, 389);
    inserirElemento3(&raiz, 684);
    inserirElemento3(&raiz, 278);
    inserirElemento3(&raiz, 893);

    printf("Soma: %d \n", somarFolhas(raiz));

    nivelNo(raiz, 0);

    // busca = buscarElemento(raiz, 500);
    // busca = buscarElemento2(raiz, 100);
    // busca = buscarNivel(raiz, 389, 0);
    // if (busca)
    //     printf("Valor: %d \n", busca->valor);
    // else
    //     printf("Valor não encontrado. \n");

    // printf("Altura: %d \n", alturaArvore(raiz));
    // printf("Quantidade nós: %d \n", quantidadeNos(raiz));
    // printf("Quantidade folhas: %d \n", quantidadeFolhas(raiz));

    // imprimirArvore(raiz);
    // traco(2);
    // imprimirArvore2(raiz);
    // traco(2);
    // nivelNo(raiz, 0);
    // traco(2);

    // raiz = removerElemento(raiz, 245);
    // imprimirArvore2(raiz);

    return 0;
}
