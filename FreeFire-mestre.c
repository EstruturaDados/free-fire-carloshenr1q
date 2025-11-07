// Mestre (aula 2)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Contadores globais para comparações
int comparacoesBubble = 0;
int comparacoesInsertion = 0;
int comparacoesSelection = 0;

// Função para mostrar componentes
void mostrarComponentes(Componente componentes[], int n) {
    printf("\nComponentes:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %s, Tipo: %s, Prioridade: %d\n", i + 1, componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
}

// Bubble Sort por nome (string)
void bubbleSortNome(Componente componentes[], int n) {
    comparacoesBubble = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoesBubble++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo (string)
void insertionSortTipo(Componente componentes[], int n) {
    comparacoesInsertion = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        while (j >= 0 && strcmp(componentes[j].tipo, chave.tipo) > 0) {
            comparacoesInsertion++;
            componentes[j + 1] = componentes[j];
            j--;
        }
        componentes[j + 1] = chave;
    }
}

// Selection Sort por prioridade (int)
void selectionSortPrioridade(Componente componentes[], int n) {
    comparacoesSelection = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoesSelection++;
            if (componentes[j].prioridade < componentes[minIdx].prioridade) {
                minIdx = j;
            }
        }
        Componente temp = componentes[minIdx];
        componentes[minIdx] = componentes[i];
        componentes[i] = temp;
    }
}

// Busca Binária por nome (apenas após ordenação por nome)
int buscaBinariaPorNome(Componente componentes[], int n, char chave[]) {
    int esquerda = 0, direita = n - 1;
    int comparacoes = 0;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoes++;
        int cmp = strcmp(componentes[meio].nome, chave);
        if (cmp == 0) {
            printf("Componente-chave encontrado na posicao %d apos %d comparacoes.\n", meio + 1, comparacoes);
            return meio;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    printf("Componente-chave nao encontrado apos %d comparacoes.\n", comparacoes);
    return -1;
}

// Função para medir tempo de execução
double medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], int n) {
    clock_t inicio = clock();
    algoritmo(componentes, n);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

int main() {
    Componente componentes[20];
    int numComponentes = 0;
    int ordenadoPorNome = 0;  // Flag para verificar se está ordenado por nome

    int opcao;
    do {
        printf("\n--- Sistema de Montagem da Torre de Fuga ---\n");
        printf("1. Cadastrar componente\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente-chave (Busca Binaria - apenas apos ordenacao por nome)\n");
        printf("6. Mostrar componentes\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  // Consumir newline

        switch (opcao) {
            case 1: {
                if (numComponentes >= 20) {
                    printf("Limite de 20 componentes atingido.\n");
                    break;
                }
                printf("Nome do componente: ");
                fgets(componentes[numComponentes].nome, 30, stdin);
                componentes[numComponentes].nome[strcspn(componentes[numComponentes].nome, "\n")] = 0;  // Remover newline
                printf("Tipo do componente: ");
                fgets(componentes[numComponentes].tipo, 20, stdin);
                componentes[numComponentes].tipo[strcspn(componentes[numComponentes].tipo, "\n")] = 0;
                printf("Prioridade (1-10): ");
                scanf("%d", &componentes[numComponentes].prioridade);
                getchar();  // Consumir newline
                numComponentes++;
                ordenadoPorNome = 0;  // Reset flag
                break;
            }
            case 2: {
                if (numComponentes == 0) {
                    printf("Nenhum componente cadastrado.\n");
                    break;
                }
                double tempo = medirTempo(bubbleSortNome, componentes, numComponentes);
                printf("Ordenacao por nome concluida em %.6f segundos com %d comparacoes.\n", tempo, comparacoesBubble);
                ordenadoPorNome = 1;
                mostrarComponentes(componentes, numComponentes);
                break;
            }
            case 3: {
                if (numComponentes == 0) {
                    printf("Nenhum componente cadastrado.\n");
                    break;
                }
                double tempo = medirTempo(insertionSortTipo, componentes, numComponentes);
                printf("Ordenacao por tipo concluida em %.6f segundos com %d comparacoes.\n", tempo, comparacoesInsertion);
                ordenadoPorNome = 0;
                mostrarComponentes(componentes, numComponentes);
                break;
            }
            case 4: {
                if (numComponentes == 0) {
                    printf("Nenhum componente cadastrado.\n");
                    break;
                }
                double tempo = medirTempo(selectionSortPrioridade, componentes, numComponentes);
                printf("Ordenacao por prioridade concluida em %.6f segundos com %d comparacoes.\n", tempo, comparacoesSelection);
                ordenadoPorNome = 0;
                mostrarComponentes(componentes, numComponentes);
                break;
            }
            case 5: {
                if (numComponentes == 0) {
                    printf("Nenhum componente cadastrado.\n");
                    break;
                }
                if (!ordenadoPorNome) {
                    printf("Primeiro ordene por nome para usar busca binaria.\n");
                    break;
                }
                char chave[30];
                printf("Nome do componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = 0;
                buscaBinariaPorNome(componentes, numComponentes, chave);
                break;
            }
            case 6: {
                mostrarComponentes(componentes, numComponentes);
                break;
            }
            case 7: {
                printf("Saindo...\n");
                break;
            }
            default: {
                printf("Opcao invalida.\n");
            }
        }
    } while (opcao != 7);

    return 0;
}
