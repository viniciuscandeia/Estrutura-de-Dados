#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

struct No
{
    int numero;
    struct No *esquerda;
    struct No *direita;
};
typedef struct No No;

void criarArvore(No **pRaiz)
{
    *pRaiz = NULL;
}

void insercao(No **pRaiz, int numero2)
{
    if (*pRaiz == NULL)
    {
        *pRaiz = (No *)malloc(sizeof(No));
        (*pRaiz)->esquerda = NULL;
        (*pRaiz)->direita = NULL;
        (*pRaiz)->numero = numero2;
    }
    else
    {
        if (numero2 < ((*pRaiz)->numero))
            insercao(&((*pRaiz)->esquerda), numero2);
        else
            insercao(&((*pRaiz)->direita), numero2);
    }
}

No *MaiorDireita(No **no)
{
    if ((*no)->direita != NULL)
        return MaiorDireita(&(*no)->direita);
    else
    {
        No *aux = *no;
        if ((*no)->esquerda != NULL) // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da esquerda!
            *no = (*no)->esquerda;
        else
        {
            *no = NULL;
            return aux;
        }
    }
}

No *MenorEsquerda(No **no)
{
    if ((*no)->esquerda != NULL)
        return MenorEsquerda(&(*no)->esquerda);
    else
    {
        No *aux = *no;
        if ((*no)->direita != NULL)
            *no = (*no)->direita;
        else
            *no = NULL;
        return aux;
    }
}

void remover(No **pRaiz, int numero)
{
    if (*pRaiz == NULL)
    {
        printf("Numero nao existe na arvore!");
        getch();
        return;
    }
    if (numero < (*pRaiz)->numero)
        remover(&(*pRaiz)->esquerda, numero);
    else if (numero > (*pRaiz)->numero)
        remover(&(*pRaiz)->direita, numero);
    else
    {
        No *pAux = *pRaiz;
        if (((*pRaiz)->esquerda == NULL) && ((*pRaiz)->direita == NULL))
        {
            free(pAux);
            (*pRaiz) = NULL;
        }
        else
        {
            if ((*pRaiz)->esquerda == NULL)
            {
                (*pRaiz) = (*pRaiz)->direita;
                pAux->direita = NULL;
                free(pAux);
                pAux = NULL;
            }
            else
            {
                if ((*pRaiz)->direita == NULL)
                {
                    (*pRaiz) = (*pRaiz)->esquerda;
                    pAux->esquerda = NULL;
                    free(pAux);
                    pAux = NULL;
                }
                else
                {
                    pAux = MaiorDireita(&(*pRaiz)->esquerda);
                    pAux->esquerda = (*pRaiz)->esquerda;
                    pAux->direita = (*pRaiz)->direita;
                    (*pRaiz)->esquerda = (*pRaiz)->direita = NULL;
                    free((*pRaiz));
                    *pRaiz = pAux;
                    pAux = NULL;
                }
            }
        }
    }
}

void exibirEmOrdem(No *pRaiz)
{
    if (pRaiz != NULL)
    {
        exibirEmOrdem(pRaiz->esquerda);
        printf("\n%i", pRaiz->numero);
        exibirEmOrdem(pRaiz->direita);
    }
}

void exibirPreOrdem(No *pRaiz)
{
    if (pRaiz != NULL)
    {
        printf("\n%i", pRaiz->numero);
        exibirPreOrdem(pRaiz->esquerda);
        exibirPreOrdem(pRaiz->direita);
    }
}

void exibirPosOrdem(No *pRaiz)
{
    if (pRaiz != NULL)
    {
        exibirPosOrdem(pRaiz->esquerda);
        exibirPosOrdem(pRaiz->direita);
        printf("\n%i", pRaiz->numero);
    }
}

int contarNos(No *pRaiz)
{
    if (pRaiz == NULL)
        return 0;
    else
        return 1 + contarNos(pRaiz->esquerda) + contarNos(pRaiz->direita);
}

int contarFolhas(No *pRaiz)
{
    if (pRaiz == NULL)
        return 0;
    if (pRaiz->esquerda == NULL && pRaiz->direita == NULL)
        return 1;
    return contarFolhas(pRaiz->esquerda) + contarFolhas(pRaiz->direita);
}

int maior(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int altura(No *pRaiz)
{
    if ((pRaiz == NULL) || (pRaiz->esquerda == NULL && pRaiz->direita == NULL))
        return 0;
    else
        return 1 + maior(altura(pRaiz->esquerda), altura(pRaiz->direita));
}

// typedef int bool;
#define false 0;
#define true 1;

bool find(int element)
{
    Node *temp = root;
    int parar = 0;
    if (root == NULL)
        return false;
    else if (temp->left == NULL && temp->right == NULL)
    {
        if (temp->value == element)
            return true;
        else
            return false;
    }
    else if (temp->value == element)
        return true;
    else
    {
        while (parar == 0)
        {
            if (temp->value < element)
            {
                if (temp->left == NULL)
                {
                    parar++;
                    if (temp->value == element)
                    {
                        break;
                        return true;
                    }
                    else
                        return false;
                }
                else
                {
                    temp = temp->right;
                    if (temp->value == element)
                    {
                        return true;
                        break;
                    }
                }
            }
            else if (temp->value > element)
            {
                if (temp->right == NULL)
                {
                    parar++;
                    if (temp->value == element)
                    {
                        return true;
                        break;
                    }
                    else
                        return false;
                }
                else
                {
                    temp = temp->left;
                    if (temp->value == element)
                    {
                        return true;
                        break;
                    }
                }
            }
        }
    }
}

int main()
{

    inicioCodigo();

    NoArv *raiz = NULL;
    NoArv *busca;

    // raiz = inserirElemento(raiz, 40);
    // raiz = inserirElemento(raiz, 50);
    // raiz = inserirElemento(raiz, 60);

    // inserirElemento2(&raiz, 40);
    // inserirElemento2(&raiz, 50);
    // inserirElemento2(&raiz, 60);

    inserirElemento3(&raiz, 583);
    inserirElemento3(&raiz, 245);
    inserirElemento3(&raiz, 731);
    inserirElemento3(&raiz, 123);
    inserirElemento3(&raiz, 389);
    inserirElemento3(&raiz, 684);
    inserirElemento3(&raiz, 278);
    inserirElemento3(&raiz, 893);

    // busca = buscarElemento(raiz, 500);
    // busca = buscarElemento2(raiz, 100);
    busca = buscarNivel(raiz, 389, 0);
    if (busca)
        wprintf(L"Valor: %d \n", busca->valor);
    else
        wprintf(L"Valor não encontrado. \n");

    wprintf(L"Altura: %d \n", alturaArvore(raiz));
    wprintf(L"Quantidade nós: %d \n", quantidadeNos(raiz));
    wprintf(L"Quantidade folhas: %d \n", quantidadeFolhas(raiz));

    imprimirArvore(raiz);
    traco(2);
    imprimirArvore2(raiz);
    traco(2);
    nivelNo(raiz, 0);
    traco(2);

    raiz = removerElemento(raiz, 245);
    imprimirArvore2(raiz);

    traco(2);
    return 0;
}
