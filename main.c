#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50


typedef struct { // Estrutura de um funcionário
    char nome[MAX_NOME];
    int horasExtras;
    int aprovado; // -1 = pendente, 0 = rejeitado, 1 = aprovado
} Funcionario;

// Ponteiro para o vetor dinâmico
Funcionario *funcionarios = NULL;
int totalFuncionarios = 0;


void cadastrarFuncionario() { // Função para cadastrar funcionário usando realloc
    funcionarios = realloc(funcionarios, (totalFuncionarios + 1) * sizeof(Funcionario));

    if (funcionarios == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    printf("Nome do funcionário: ");
    getchar(); // limpar buffer
    fgets(funcionarios[totalFuncionarios].nome, MAX_NOME, stdin);

    funcionarios[totalFuncioncidoso].nome[strcspn(funcionarios[totalFuncionidoso].nome, "\n")] = 0;

    funcionarios[totalFuncionarios].horasExtras = 0;
    funcionarios[totalFuncionarios].aprovado = -1;

    totalFuncionarios++;

    printf("Funcionário cadastrado com sucesso!\n");
}

void registrarHoras() { // Registrar horas extras
    int id, horas;

    if (totalFuncionarios == 0) {
        printf("Nenhum funcionário cadastrado!\n");
        return;
    }

    printf("Digite o ID do funcionário (0 a %d): ", totalFuncionarios - 1);
    scanf("%d", &id);

    if (id < 0 || id >= totalFuncionarios) {
        printf("ID inválido!\n");
        return;
    }

    printf("Horas extras: ");
    scanf("%d", &horas);

    funcionarios[id].horasExtras = horas;
    funcionarios[id].aprovado = -1;

    printf("Horas registradas com sucesso!\n");
}


void listar() { // Listar todos os funcionários
    if (totalFuncionarios == 0) {
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    printf("\n----- FUNCIONÁRIOS -----\n");
    for (int i = 0; i < totalFuncionarios; i++) {
        printf("ID: %d | Nome: %s | Horas: %d | Status: ",
               i,
               funcionarios[i].nome,
               funcionarios[i].horasExtras);

        if (funcionarios[i].aprovado == -1) printf("Pendente\n");
        else if (funcionarios[i].aprovado == 1) printf("Aprovado\n");
        else printf("Rejeitado\n");
    }
    printf("------------------------\n");
}


void aprovarHoras() { // Aprovar ou rejeitar horas extras
    int id, op;

    if (totalFuncionarios == 0) {
        printf("Nenhum funcionário cadastrado!\n");
        return;
    }

    printf("ID do funcionário: ");
    scanf("%d", &id);

    if (id < 0 || id >= totalFuncionarios) {
        printf("ID inválido!\n");
        return;
    }

    printf("Aprovar horas de %s?\n", funcionarios[id].nome);
    printf("[1] Aprovar\n[2] Rejeitar\nOpção: ");
    scanf("%d", &op);

    if (op == 1) funcionarios[id].aprovado = 1;
    else funcionarios[id].aprovado = 0;

    printf("Processo concluído!\n");
}


int main() { // Menu principal
    int opcao;

    do {
        printf("\n==== SISTEMA DE HORAS EXTRAS ====\n");
        printf("1 - Cadastrar funcionário\n");
        printf("2 - Registrar horas extras\n");
        printf("3 - Listar funcionários\n");
        printf("4 - Aprovar horas\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarFuncionario(); break;
            case 2: registrarHoras(); break;
            case 3: listar(); break;
            case 4: aprovarHoras(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    // liberar memória
    free(funcionarios);

    return 0;
}
