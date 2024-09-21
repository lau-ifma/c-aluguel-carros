#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARROS 100
#define MAX_NOME 50

// Estrutura para armazenar dados do carro
typedef struct{
    int id;
    char nome[MAX_NOME];
    int ano;
    char disponibilidade[MAX_NOME];
} Carro;

// Função para imprimir a lista de carros
void imprimirCarros(Carro *carros, int count){
    printf("Lista de Carros:\n");
    for (int i = 0; i < count; i++){
        printf("ID: %d,  NOME: %s,  ANO: %d,  SITUACAO: %s\n",
               carros[i].id, carros[i].nome, carros[i].ano, carros[i].disponibilidade);
    }
}

// Função para mostrar apenas os carros disponíveis
void mostrarCarrosDisponiveis(Carro *carros, int count){
    printf("Carros Disponiveis:\n");
    for (int i = 0; i < count; i++){
        if (strcmp(carros[i].disponibilidade, "Disponivel") == 0){
            printf("ID: %d, NOME: %s, ANO: %d\n", carros[i].id, carros[i].nome, carros[i].ano);
        }
    }
}

void mostrarCarrosIndisponiveis(Carro *carros, int count){
    printf("Carros Alugados:\n");
    for (int i = 0; i < count; i++){
        if (strcmp(carros[i].disponibilidade, "Indisponivel") == 0){
            printf("ID: %d, NOME: %s, ANO: %d\n", carros[i].id, carros[i].nome, carros[i].ano);
        }
    }
}

// Função para alugar um carro
void alugarCarro(Carro *carros, int count){
    int idCarro;
    printf("Digite o ID do carro que deseja alugar: ");
    scanf("%d", &idCarro);

    for (int i = 0; i < count; i++){
        if (carros[i].id == idCarro && strcmp(carros[i].disponibilidade, "Disponivel") == 0){
            strcpy(carros[i].disponibilidade, "Indisponivel");
            printf("Carro %s alugado com sucesso!\n", carros[i].nome);
            return;
        }
    }
    printf("Carro nao disponível ou ID invalido.\n");
}

// Função para receber um carro de volta
void receberCarro(Carro *carros, int count){
    int idCarro;
    printf("Digite o ID do carro que deseja receber de volta: ");
    scanf("%d", &idCarro);

    for (int i = 0; i < count; i++){
        if (carros[i].id == idCarro && strcmp(carros[i].disponibilidade, "Indisponivel") == 0){
            strcpy(carros[i].disponibilidade, "Disponivel");
            printf("Carro %s recebido com sucesso!\n", carros[i].nome);
            return;
        }
    }
    printf("ID invalido ou o carro ja esta disponivel.\n");
}

// Função para salvar os carros atualizados no arquivo
void salvarCarros(Carro *carros, int count){
    FILE *file = fopen("carros.txt", "w");
    if (file == NULL){
        printf("Erro ao salvar o arquivo.\n");
        return;
    }

    for (int i = 0; i < count; i++){
        fprintf(file, "%d,%s,%d,%s\n", carros[i].id, carros[i].nome, carros[i].ano, carros[i].disponibilidade);
    }

    fclose(file);
}

// Função principal
int main(){
    FILE *file;
    Carro carros[MAX_CARROS];
    char linha[256];
    int count = 0;
    int opcao;

    // Carrega os carros do arquivo
    file = fopen("carros.txt", "r");
    if (file == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), file) != NULL){
        linha[strcspn(linha, "\n")] = '\0'; // Remove o "\n"
        sscanf(linha, "%d,%49[^,],%d,%49[^,]", &carros[count].id, carros[count].nome, &carros[count].ano, carros[count].disponibilidade);
        count++;
    }
    fclose(file);

    // Menu
    do{
        printf("\n=== LOCADORA DE VEICULOS ===\n");
        printf("1 - Ver catalogo de carros\n");
        printf("2 - Alugar carro\n");
        printf("3 - Receber carro\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1){
            system("cls");
            imprimirCarros(carros, count);
        }
        else if (opcao == 2){
            system("cls");
            mostrarCarrosDisponiveis(carros, count);
            alugarCarro(carros, count);
            salvarCarros(carros, count);
        }
        else if (opcao == 3){
            system("cls");
            mostrarCarrosIndisponiveis(carros, count);
            receberCarro(carros, count);
            salvarCarros(carros, count);
        }
        else if (opcao == 4){
            printf("Saindo...\n");
        }
        else{
            printf("Opcao invalida.\n");
        }

    } while (opcao != 4);

    return 0;
}
