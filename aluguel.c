#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARROS 100

typedef struct {
    int id;
    char nome[50];
    int ano;
    char disponibilidade[50];
} Carro;

// Funções para manipulação de carros (sem alterações)

void imprimirCarros(Carro *carros, int qtd) {
    printf("Lista de Carros:\n");
    for (int i = 0; i < qtd; i++) {
        printf("ID: %d,  NOME: %s,  ANO: %d,  SITUACAO: %s\n",
               carros[i].id, carros[i].nome, carros[i].ano, carros[i].disponibilidade);
    }
}

void mostrarCarrosDisponiveis(Carro *carros, int qtd) {
    printf("Carros Disponiveis:\n");
    for (int i = 0; i < qtd; i++) {
        if (strcmp(carros[i].disponibilidade, "Disponivel") == 0) {
            printf("ID: %d, NOME: %s, ANO: %d\n", carros[i].id, carros[i].nome, carros[i].ano);
        }
    }
}

void mostrarCarrosIndisponiveis(Carro *carros, int qtd) {
    printf("Carros Alugados:\n");
    for (int i = 0; i < qtd; i++) {
        if (strcmp(carros[i].disponibilidade, "Indisponivel") == 0) {
            printf("ID: %d, NOME: %s, ANO: %d\n", carros[i].id, carros[i].nome, carros[i].ano);
        }
    }
}

void alugarCarro(Carro *carros, int qtd) {
    int idCarro;
    printf("Digite o ID do carro que deseja alugar: ");
    scanf("%d", &idCarro);

    for (int i = 0; i < qtd; i++) {
        if (carros[i].id == idCarro && strcmp(carros[i].disponibilidade, "Disponivel") == 0) {
            strcpy(carros[i].disponibilidade, "Indisponivel");
            printf("Carro %s alugado com sucesso!\n", carros[i].nome);
            return;
        }
    }
    printf("Carro nao disponivel ou ID invalido.\n");
}

void receberCarro(Carro *carros, int qtd) {
    int idCarro;
    printf("Digite o ID do carro que deseja receber de volta: ");
    scanf("%d", &idCarro);

    for (int i = 0; i < qtd; i++) {
        if (carros[i].id == idCarro && strcmp(carros[i].disponibilidade, "Indisponivel") == 0) {
            strcpy(carros[i].disponibilidade, "Disponivel");
            printf("Carro %s recebido com sucesso!\n", carros[i].nome);
            return;
        }
    }
    printf("ID invalido ou o carro ja esta disponivel.\n");
}

void salvarCarros(Carro *carros, int qtd) {
    FILE *pont_arq = fopen("carros.txt", "w");
    if (pont_arq == NULL) {
        printf("Erro ao salvar o arquivo.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        fprintf(pont_arq, "%d,%s,%d,%s\n", carros[i].id, carros[i].nome, carros[i].ano, carros[i].disponibilidade);
    }

    fclose(pont_arq);
}

void adicionarCarro(Carro *carros, int *qtd) {
    if (*qtd >= MAX_CARROS) {
        printf("Nao eh possivel adicionar mais carros. Limite atingido.\n");
        return;
    }

    Carro novoCarro;
    novoCarro.id = *qtd + 1; // adiciona o Id
    printf("Digite o nome do carro: ");
    scanf(" %[^\n]", novoCarro.nome);  // LER NOME COM ESPACOS
    printf("Digite o ano do carro: ");
    scanf("%d", &novoCarro.ano);
    strcpy(novoCarro.disponibilidade, "Disponivel");

    carros[*qtd] = novoCarro; // Adiciona o novo carro
    (*qtd)++;
    printf("Carro %s adicionado com sucesso!\n", novoCarro.nome);
}

int main() {
    FILE *pont_arq;
    Carro carros[MAX_CARROS];
    char linha[256];
    int qtd = 0;
    int opcao;

    pont_arq = fopen("carros.txt", "r");
    if (pont_arq == NULL) {
        pont_arq = fopen("carros.txt", "w");
        if (pont_arq == NULL) {
            printf("Erro ao criar o arquivo.\n");
            return 1;
        }
        fprintf(pont_arq, "1,Fiesta,2020,Disponivel\n"); 
        fprintf(pont_arq, "2,Onix,2022,Disponivel\n"); 
        fclose(pont_arq);
        pont_arq = fopen("carros.txt", "r"); // abrindo arqvo novamente p/ leitura
    }

    // lê uma linha de (pont_arq) e armazena na variavell -> linha
    while (fgets(linha, sizeof(linha), pont_arq) != NULL) {
        linha[strcspn(linha, "\n")] = '\0'; // Remover o "\n"
        sscanf(linha, "%d,%49[^,],%d,%49[^,]", &carros[qtd].id, carros[qtd].nome, &carros[qtd].ano, carros[qtd].disponibilidade);
        qtd++;
    }
    fclose(pont_arq);

    // Menu
    do {
        printf("\n=== LOCADORA DE VEICULOS ===\n");
        printf("1 - Ver catalogo de carros\n");
        printf("2 - Alugar carro\n");
        printf("3 - Receber carro\n");
        printf("4 - Novo carro\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            system("cls");
            imprimirCarros(carros, qtd);
        } else if (opcao == 2) {
            system("cls");
            mostrarCarrosDisponiveis(carros, qtd);
            alugarCarro(carros, qtd);
            salvarCarros(carros, qtd);
        } else if (opcao == 3) {
            system("cls");
            mostrarCarrosIndisponiveis(carros, qtd);
            receberCarro(carros, qtd);
            salvarCarros(carros, qtd);
        } else if (opcao == 0) {
            printf("Saindo...\n");
        } else if (opcao == 4) {
            adicionarCarro(carros, &qtd);
            salvarCarros(carros, qtd);
            system("pause");
        } else {
            printf("Opcao invalida.\n");
            system("pause");
            system("cls");
        }

    } while (opcao != 0);

    return 0;
}
