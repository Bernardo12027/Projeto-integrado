#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_REGISTROS 100
#define MAX_NOME 50
#define MAX_DESC 100

typedef struct {
    int id;
    char funcionario[MAX_NOME];
    char data[11];
    float horas;
    float valor_hora;  
    float valor_total; 
    char descricao[MAX_DESC];
    int aprovado; 
} RegistroHoras;

RegistroHoras registros[MAX_REGISTROS];
int totalRegistros = 0;

void limparBuffer() {
    while (getchar() != '\n');
}

int validarData(const char* data) {
    if (strlen(data) != 10) return 0;
    if (data[2] != '/' || data[5] != '/') return 0;
    
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(data[i])) return 0;
    }
    return 1;
}

void cadastrarHoras() {
    if (totalRegistros >= MAX_REGISTROS) {
        printf("Limite máximo de registros atingido!\n");
        return;
    }

    RegistroHoras novo;
    novo.id = totalRegistros + 1;

    printf("\n--- Cadastro de Horas Extras ---\n");
    
    printf("Nome do funcionario: ");
    fgets(novo.funcionario, MAX_NOME, stdin);
    novo.funcionario[strcspn(novo.funcionario, "\n")] = 0;

    do {
        printf("Data (DD/MM/AAAA): ");
        fgets(novo.data, 11, stdin);
        limparBuffer();
    } while (!validarData(novo.data));

    printf("Horas trabalhadas: ");
    scanf("%f", &novo.horas);
    limparBuffer();

    printf("Valor da hora extra (R$): ");
    scanf("%f", &novo.valor_hora);
    limparBuffer();

    novo.valor_total = novo.horas * novo.valor_hora;

    printf("Descricao: ");
    fgets(novo.descricao, MAX_DESC, stdin);
    novo.descricao[strcspn(novo.descricao, "\n")] = 0;

    novo.aprovado = 0; 

    registros[totalRegistros++] = novo;
    printf("\nRegistro cadastrado com sucesso! ID: %d\n", novo.id);
    printf("Valor total a receber: R$ %.2f\n", novo.valor_total);
}

void listarRegistros() {
    printf("\n--- Listagem de Registros ---\n");
    
    for (int i = 0; i < totalRegistros; i++) {
        const char* status;
        switch(registros[i].aprovado) {
            case 0: status = "PENDENTE"; break;
            case 1: status = "APROVADO"; break;
            case 2: status = "REPROVADO"; break;
        }

        printf("\nID: %d\n", registros[i].id);
        printf("Funcionario: %s\n", registros[i].funcionario);
        printf("Data: %s | Horas: %.2f\n", registros[i].data, registros[i].horas);
        printf("Valor da hora: R$ %.2f | Valor total: R$ %.2f\n", 
               registros[i].valor_hora, registros[i].valor_total);
        printf("Descricao: %s\n", registros[i].descricao);
        printf("Status: %s\n", status);
    }
}

void aprovarHoras() {
    printf("\n--- Aprovar/Reprovar Horas ---\n");
    
    for (int i = 0; i < totalRegistros; i++) {
        if (registros[i].aprovado == 0) {
            printf("\nID: %d | %s | %s | %.2f horas\n", 
                   registros[i].id, 
                   registros[i].funcionario,
                   registros[i].data,
                   registros[i].horas);
            printf("Valor total: R$ %.2f\n", registros[i].valor_total);
            printf("Descricao: %s\n", registros[i].descricao);
            
            printf("Aprovar? (1 = Sim, 2 = Nao, 0 = Manter pendente): ");
            int resposta;
            scanf("%d", &resposta);
            
            if (resposta >= 0 && resposta <= 2) {
                registros[i].aprovado = resposta;
                printf("Status atualizado!\n");
            } else {
                printf("Opcao invalida! Mantendo pendente.\n");
            }
        }
    }
}

void relatorioHoras() {
    printf("\n--- Relatorio de Horas Aprovadas ---\n");
    
    float totalHoras = 0;
    float totalValor = 0;
    
    for (int i = 0; i < totalRegistros; i++) {
        if (registros[i].aprovado == 1) {
            printf("%s: %.2f horas em %s\n", 
                   registros[i].funcionario,
                   registros[i].horas,
                   registros[i].data);
            printf("  Valor: R$ %.2f (R$ %.2f x %.2f horas)\n",
                   registros[i].valor_total,
                   registros[i].valor_hora,
                   registros[i].horas);
            totalHoras += registros[i].horas;
            totalValor += registros[i].valor_total;
        }
    }
    
    printf("\nTotal de horas aprovadas: %.2f\n", totalHoras);
    printf("Total a pagar: R$ %.2f\n", totalValor);
}

void relatorioPorFuncionario() {
    printf("\n--- Relatorio por Funcionario ---\n");
    
    if (totalRegistros == 0) {
        printf("Nenhum registro encontrado.\n");
        return;
    }
    
    char funcionarios[MAX_REGISTROS][MAX_NOME];
    int totalFuncionarios = 0;
    
    for (int i = 0; i < totalRegistros; i++) {
        int encontrado = 0;
        for (int j = 0; j < totalFuncionarios; j++) {
            if (strcmp(registros[i].funcionario, funcionarios[j]) == 0) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(funcionarios[totalFuncionarios], registros[i].funcionario);
            totalFuncionarios++;
        }
    }
    
    for (int i = 0; i < totalFuncionarios; i++) {
        float horasFunc = 0;
        float valorFunc = 0;
        
        for (int j = 0; j < totalRegistros; j++) {
            if (strcmp(registros[j].funcionario, funcionarios[i]) == 0 && registros[j].aprovado == 1) {
                horasFunc += registros[j].horas;
                valorFunc += registros[j].valor_total;
            }
        }
        
        if (horasFunc > 0) {
            printf("\n%s:\n", funcionarios[i]);
            printf("  Total de horas: %.2f\n", horasFunc);
            printf("  Total a receber: R$ %.2f\n", valorFunc);
        }
    }
}

int main() {
    int opcao;
    
    printf("=== Sistema de Controle de Horas Extras ===\n");
    printf("Prototipo em C - Projeto Base27\n\n");

    do {
        printf("\nMenu Principal:\n");
        printf("1. Cadastrar horas extras\n");
        printf("2. Listar todos os registros\n");
        printf("3. Aprovar/Reprovar horas\n");
        printf("4. Relatorio de horas aprovadas\n");
        printf("5. Relatorio por funcionario\n");  // Nova opção
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                cadastrarHoras();
                break;
            case 2:
                listarRegistros();
                break;
            case 3:
                aprovarHoras();
                break;
            case 4:
                relatorioHoras();
                break;
            case 5:
                relatorioPorFuncionario();
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}