#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define autor "João Victor Carvalho de Oliveira"
#define data "04/10/2021"
#define ed "Pilha"

typedef struct no
{
    int dado;
    struct no *proximo;
} No;

typedef struct pilha
{
    No* topo;
} Pilha;

Pilha* iniciar(void)
{
    Pilha *nova_pilha = (Pilha*) malloc(sizeof(Pilha));
    nova_pilha->topo = NULL;
    return nova_pilha;
}

No* inserir(No *tp, int valor)
{
    No* novo_no = (No*) malloc(sizeof(No));
    novo_no->dado = valor;
    novo_no->proximo = tp;
    return novo_no;
}

void excluir(Pilha *p, int valor)
{
    No *aux = p->topo;
    No *anterior = NULL;
    while (aux != NULL)
    {
        if (aux->dado == valor)
        {
            break;
        }
        else
        {
            anterior = aux;
        }

        aux = aux->proximo;
    }

    if (aux == NULL)
    {
        printf("\nNão foi encontrado nenhum valor %i dentro da pilha.\n", valor);
        return;
    }

    if (anterior == NULL)
    {
        p->topo = aux->proximo;
    }
    else
    {
        anterior->proximo = aux->proximo;
    }

    printf("\nO dado %i foi excluido com sucesso!\n", aux->dado);
    free(aux);
}

void imprimir(Pilha *p)
{
    if (p->topo == NULL)
    {
        printf("A pilha está vazia.\n");
        return;
    }

    No *aux = p->topo;
    printf("Valores dentro da pilha: ");
    while (aux != NULL)
    {
        printf("%d", aux->dado);
        if (aux->proximo == NULL)
        {
            break;
        }
        printf(", ");
        aux = aux->proximo;
    }
    printf("\n");
}

No* buscar(Pilha *p, int valor)
{
    No *aux = p->topo;
    while (aux != NULL)
    {
        if (aux->dado == valor)
        {
            break;
        }

        aux = aux->proximo;
    }

    if (aux == NULL)
    {
        return NULL;
    }
    
    return aux;
}

int num_elementos(Pilha *p)
{
    No *aux = p->topo;
    int count = 0;
    while (aux != NULL)
    {
        count++;
        aux = aux->proximo;
    }
    return count;
}

int main(int argc, char const *argv[])
{
    Pilha *p = NULL;
    bool sair = true;

    printf("\nUniversidade Paulista (UNIP)\n");
    printf("Nome: %s\n", autor);
    printf("Data: %s\n", data);
    printf("Estrutura de dado: %s\n", ed);
    printf("\n1 - Iniciar/Reiniciar\n");
    printf("2 - Inserir\n");
    printf("3 - Excluir\n");
    printf("4 - Imprimir\n");
    printf("5 - Buscar\n");
    printf("6 - Nr. de Elementos\n");
    printf("7 - Sair\n");

    while (sair)
    {
        int opcao, valor;

        printf("\nDigite a sua opção: ");
        scanf("%i", &opcao);
        printf("\n");

        switch (opcao)
        {
            case 1:
                p = iniciar();
                printf("A pilha foi iniciada/reiniciada com sucesso!\n");
                break;
            case 2:
                printf("Digite um valor: ");
                scanf("%i", &valor);

                if (p == NULL)
                {
                    printf("\nVocê precisa iniciar a pilha antes de inserir um dado.\n");
                    break;
                }

                p->topo = inserir(p->topo, valor);
                break;
            case 3:
                printf("Digite o valor a ser excluido: ");
                scanf("%i", &valor);

                if (p == NULL)
                {
                    printf("\nVocê precisa iniciar a pilha antes de excluir um dado.\n");
                    break;
                }

                excluir(p, valor);
                break;
            case 4:
                if (p == NULL)
                {
                    printf("A pilha não foi inicializada, tente novamente.\n");
                    break;
                }

                imprimir(p);
                break;
            case 5:
                printf("Digite o valor para a busca: ");
                scanf("%i", &valor);

                if (p == NULL)
                {
                    printf("\nVocê precisa iniciar a pilha antes de buscar um dado.\n");
                    break;
                }

                No* no_buscado = buscar(p, valor);
                if (no_buscado == NULL)
                {
                    printf("\nO valor %i não foi encontrado dentro da pilha.\n", valor);
                }
                else
                {
                    printf("\nO valor %i foi encontrado dentro da pilha.\n", no_buscado->dado);
                }
                break;
            case 6:
                if (p == NULL)
                {
                    printf("A pilha não foi inicializada, tente novamente.\n");
                    break;
                }
                printf("Nr. de elementos dentro da pilha: %i\n", num_elementos(p));
                break;
            case 7:
                printf("Saindo...\n");
                sleep(1);
                sair = false;
                break;
            default:
                printf("Opção incorreta, tente novamente\n");
                return 1;
        }
    }
    return 0;
}