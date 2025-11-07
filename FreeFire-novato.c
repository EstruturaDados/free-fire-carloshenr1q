// Novato (aula 2)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Definição da struct No para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Contadores globais para comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// Funções para Vetor (Lista Sequencial)

// Inserir item no vetor
void inserirItemVetor(Item* itens, int* numItens) {
    if (*numItens >= 10) {
        printf("Inventario cheio!\n");
        return;
    }
    printf("Nome: ");
    scanf("%29s", itens[*numItens].nome);
    printf("Tipo: ");
    scanf("%19s", itens[*numItens].tipo);
    printf("Quantidade: ");
    scanf("%d", &itens[*numItens].quantidade);
    (*numItens)++;
    printf("Item inserido.\n");
}

// Remover item do vetor por nome
void removerItemVetor(Item* itens, int* numItens) {
    if (*numItens == 0) {
        printf("Inventario vazio!\n");
        return;
    }
    char nome[30];
    printf("Nome a remover: ");
    scanf("%29s", nome);
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(itens[i].nome, nome) == 0) {
            for (int j = i; j < *numItens - 1; j++) {
                itens[j] = itens[j + 1];
            }
            (*numItens)--;
            printf("Item removido.\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

// Listar itens do vetor
void listarItensVetor(Item* itens, int numItens) {
    if (numItens == 0) {
        printf("Inventario vazio.\n");
        return;
    }
    printf("Itens no vetor:\n");
    for (int i = 0; i < numItens; i++) {
        printf("%s - %s - %d\n", itens[i].nome, itens[i].tipo, itens[i].quantidade);
    }
}

// Buscar sequencial no vetor
void buscarSequencialVetor(Item* itens, int numItens) {
    if (numItens == 0) {
        printf("Inventario vazio!\n");
        return;
    }
    char nome[30];
    printf("Nome a buscar: ");
    scanf("%29s", nome);
    comparacoesSequencial = 0;
    for (int i = 0; i < numItens; i++) {
        comparacoesSequencial++;
        if (strcmp(itens[i].nome, nome) == 0) {
            printf("Encontrado: %s - %s - %d\n", itens[i].nome, itens[i].tipo, itens[i].quantidade);
            printf("Comparacoes sequenciais: %d\n", comparacoesSequencial);
            return;
        }
    }
    printf("Nao encontrado.\n");
    printf("Comparacoes sequenciais: %d\n", comparacoesSequencial);
}

// Ordenar vetor por nome (Bubble Sort)
void ordenarVetor(Item* itens, int numItens) {
    for (int i = 0; i < numItens - 1; i++) {
        for (int j = 0; j < numItens - i - 1; j++) {
            if (strcmp(itens[j].nome, itens[j + 1].nome) > 0) {
                Item temp = itens[j];
                itens[j] = itens[j + 1];
                itens[j + 1] = temp;
            }
        }
    }
    printf("Vetor ordenado.\n");
}

// Buscar binária no vetor (após ordenação)
void buscarBinariaVetor(Item* itens, int numItens) {
    if (numItens == 0) {
        printf("Inventario vazio!\n");
        return;
    }
    char nome[30];
    printf("Nome a buscar (binaria): ");
    scanf("%29s", nome);
    comparacoesBinaria = 0;
    int esquerda = 0, direita = numItens - 1;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(itens[meio].nome, nome);
        if (cmp == 0) {
            printf("Encontrado: %s - %s - %d\n", itens[meio].nome, itens[meio].tipo, itens[meio].quantidade);
            printf("Comparacoes binarias: %d\n", comparacoesBinaria);
            return;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    printf("Nao encontrado.\n");
    printf("Comparacoes binarias: %d\n", comparacoesBinaria);
}

// Funções para Lista Encadeada

// Inserir item na lista (no início)
void inserirItemLista(No** cabeca) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }
    printf("Nome: ");
    scanf("%29s", novo->dados.nome);
    printf("Tipo: ");
    scanf("%19s", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    novo->proximo = *cabeca;
    *cabeca = novo;
    printf("Item inserido.\n");
}

// Remover item da lista por nome
void removerItemLista(No** cabeca) {
    if (*cabeca == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    char nome[30];
    printf("Nome a remover: ");
    scanf("%29s", nome);
    No* atual = *cabeca;
    No* anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                *cabeca = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item removido.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item nao encontrado.\n");
}

// Listar itens da lista
void listarItensLista(No* cabeca) {
    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    printf("Itens na lista:\n");
    No* atual = cabeca;
    while (atual != NULL) {
        printf("%s - %s - %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

// Buscar sequencial na lista
void buscarSequencialLista(No* cabeca) {
    if (cabeca == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    char nome[30];
    printf("Nome a buscar: ");
    scanf("%29s", nome);
    comparacoesSequencial = 0;
    No* atual = cabeca;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Encontrado: %s - %s - %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparacoes sequenciais: %d\n", comparacoesSequencial);
            return;
        }
        atual = atual->proximo;
    }
    printf("Nao encontrado.\n");
    printf("Comparacoes sequenciais: %d\n", comparacoesSequencial);
}

// Liberar memória da lista
void liberarLista(No** cabeca) {
    No* atual = *cabeca;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    *cabeca = NULL;
}

int main() {
    int estrutura;
    printf("Escolha a estrutura: 1 - Vetor, 2 - Lista Encadeada: ");
    scanf("%d", &estrutura);

    if (estrutura == 1) {
        // Vetor
        Item itens[10];
        int numItens = 0;
        int opcao;
        do {
            printf("\n1. Inserir\n2. Remover\n3. Listar\n4. Buscar Sequencial\n5. Ordenar\n6. Buscar Binaria\n7. Sair\nOpcao: ");
            scanf("%d", &opcao);
            switch (opcao) {
                case 1: inserirItemVetor(itens, &numItens); break;
                case 2: removerItemVetor(itens, &numItens); break;
                case 3: listarItensVetor(itens, numItens); break;
                case 4: buscarSequencialVetor(itens, numItens); break;
                case 5: ordenarVetor(itens, numItens); break;
                case 6: buscarBinariaVetor(itens, numItens); break;
                case 7: break;
                default: printf("Opcao invalida.\n");
            }
        } while (opcao != 7);
    } else if (estrutura == 2) {
        // Lista
        No* cabeca = NULL;
        int opcao;
        do {
            printf("\n1. Inserir\n2. Remover\n3. Listar\n4. Buscar Sequencial\n5. Sair\nOpcao: ");
            scanf("%d", &opcao);
            switch (opcao) {
                case 1: inserirItemLista(&cabeca); break;
                case 2: removerItemLista(&cabeca); break;
                case 3: listarItensLista(cabeca); break;
                case 4: buscarSequencialLista(cabeca); break;
                case 5: break;
                default: printf("Opcao invalida.\n");
            }
        } while (opcao != 5);
        liberarLista(&cabeca);
    } else {
        printf("Estrutura invalida.\n");
    }

    // Comparação de desempenho (exibir contadores ao final)
    printf("\nComparacao de desempenho:\n");
    printf("Comparacoes na ultima busca sequencial: %d\n", comparacoesSequencial);
    printf("Comparacoes na ultima busca binaria: %d\n", comparacoesBinaria);

    return 0;
}
