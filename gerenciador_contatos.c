#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char nome[100];
    char telefone[20];
    char email[100];
} Contato;


/* -------- FUNÇÃO PARA CADASTRAR -------- */
void cadastrar(Contato lista[], int *total) {

    if (*total >= MAX) {
        printf("Limite de contatos atingido.\n");
        return;
    }

    printf("Nome: ");
    fgets(lista[*total].nome, 100, stdin);
    lista[*total].nome[strcspn(lista[*total].nome, "\n")] = '\0';

    printf("Telefone: ");
    fgets(lista[*total].telefone, 20, stdin);
    lista[*total].telefone[strcspn(lista[*total].telefone, "\n")] = '\0';

    printf("Email: ");
    fgets(lista[*total].email, 100, stdin);
    lista[*total].email[strcspn(lista[*total].email, "\n")] = '\0';

    (*total)++;

    printf("Contato cadastrado com sucesso!\n");
}


/* -------- FUNÇÃO PARA LISTAR -------- */
void listar(Contato lista[], int total) {

    if (total == 0) {
        printf("Nenhum contato cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nContato %d\n", i + 1);
        printf("Nome: %s\n", lista[i].nome);
        printf("Telefone: %s\n", lista[i].telefone);
        printf("Email: %s\n", lista[i].email);
    }
}


/* -------- FUNÇÃO PARA BUSCAR -------- */
int buscar(Contato lista[], int total, char nome[]) {

    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}


/* -------- FUNÇÃO PARA EDITAR -------- */
void editar(Contato lista[], int total) {

    char nome[100];

    printf("Digite o nome do contato: ");
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int pos = buscar(lista, total, nome);

    if (pos == -1) {
        printf("Contato nao encontrado.\n");
        return;
    }

    printf("Novo telefone: ");
    fgets(lista[pos].telefone, 20, stdin);
    lista[pos].telefone[strcspn(lista[pos].telefone, "\n")] = '\0';

    printf("Novo email: ");
    fgets(lista[pos].email, 100, stdin);
    lista[pos].email[strcspn(lista[pos].email, "\n")] = '\0';

    printf("Contato atualizado.\n");
}


/* -------- FUNÇÃO PARA REMOVER -------- */
void remover(Contato lista[], int *total) {

    char nome[100];

    printf("Digite o nome do contato: ");
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int pos = buscar(lista, *total, nome);

    if (pos == -1) {
        printf("Contato nao encontrado.\n");
        return;
    }

    for (int i = pos; i < *total - 1; i++) {
        lista[i] = lista[i + 1];
    }

    (*total)--;

    printf("Contato removido.\n");
}


/* -------- FUNÇÃO RECURSIVA -------- */

int contarRecursivo(Contato lista[], int total, int indice, int tamanho) {

    if (indice >= total) {
        return 0;
    }

    int atual = 0;

    if (strlen(lista[indice].nome) > tamanho) {
        atual = 1;
    }

    return atual + contarRecursivo(lista, total, indice + 1, tamanho);
}



/* -------- FUNÇÃO PRINCIPAL -------- */
int main() {

    Contato lista[MAX];
    int total = 0;
    int opcao;

    do {

        printf("\n=== GERENCIADOR DE CONTATOS ===\n");
        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Buscar\n");
        printf("4 - Editar\n");
        printf("5 - Remover\n");
        printf("6 - Estatistica (recursivo)\n");
        printf("7 - Sair\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {

            case 1:
                cadastrar(lista, &total);
                break;

            case 2:
                listar(lista, total);
                break;

            case 3: {
                char nome[100];

                printf("Digite o nome para buscar: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                int pos = buscar(lista, total, nome);

                if (pos == -1) {
                    printf("Contato nao encontrado.\n");
                } else {
                    printf("\nContato encontrado:\n");
                    printf("Nome: %s\n", lista[pos].nome);
                    printf("Telefone: %s\n", lista[pos].telefone);
                    printf("Email: %s\n", lista[pos].email);
                }
                break;
            }

            case 4:
                editar(lista, total);
                break;

            case 5:
                remover(lista, &total);
                break;

            case 6: {
                int tamanho;
                printf("Contar nomes maiores que quantos caracteres? ");
                scanf("%d", &tamanho);
                getchar();

                int resultado = contarRecursivo(lista, total, 0, tamanho);
                printf("Total: %d\n", resultado);
                break;
            }

            case 7:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 7);

    return 0;
}
