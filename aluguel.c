#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARROS 100

typedef struct{
    int id;
    char nome[50];
    int ano;
    char disponibilidade[50];
} Carro;

void imprimirCarros(Carro *carros, int qtd){
    printf("Lista de Carros:\n");
    for (int i = 0; i < qtd; i++){
        printf("ID: %d,  NOME: %s,  ANO: %d,  SITUACAO: %s\n",
               carros[i].id, carros[i].nome, carros[i].ano, carros[i].disponibilidade);
    }
}

// Função para mostrar apenas os carros disponíveis
void mostrarCarrosDisponiveis(Carro *carros, int qtd){
    printf("Carros Disponiveis:\n");
    for (int i = 0; i < qtd; i++){
        if (strcmp(carros[i].disponibilidade, "Disponivel") == 0){
            printf("ID: %d, NOME: %s, ANO: %d\n", carros[i].id, carros[i].nome, carros[i].ano);
        }
    }
}

void mostrarCarrosIndisponiveis(Carro *carros, int qtd){
    printf("Carros Alugados:\n");
    for (int i = 0; i < qtd; i++){
        if (strcmp(carros[i].disponibilidade, "Indisponivel") == 0){
            printf("ID: %d, NOME: %s, ANO: %d\n", carros[i].id, carros[i].nome, carros[i].ano);
        }
    }
}

// Função para alugar um carro
void alugarCarro(Carro *carros, int qtd){
    int idCarro;
    printf("Digite o ID do carro que deseja alugar: ");
    scanf("%d", &idCarro);

    for (int i = 0; i < qtd; i++){
        if (carros[i].id == idCarro && strcmp(carros[i].disponibilidade, "Disponivel") == 0){
            strcpy(carros[i].disponibilidade, "Indisponivel");
            printf("Carro %s alugado com sucesso!\n", carros[i].nome);
            return;
        }
    }
    printf("Carro nao disponível ou ID invalido.\n");
}

// Função para receber um carro de volta
void receberCarro(Carro *carros, int qtd){
    int idCarro;
    printf("Digite o ID do carro que deseja receber de volta: ");
    scanf("%d", &idCarro);

    for (int i = 0; i < qtd; i++){
        if (carros[i].id == idCarro && strcmp(carros[i].disponibilidade, "Indisponivel") == 0){
            strcpy(carros[i].disponibilidade, "Disponivel");
            printf("Carro %s recebido com sucesso!\n", carros[i].nome);
            return;
        }
    }
    printf("ID invalido ou o carro ja esta disponivel.\n");
}

// Função para salvar os carros atualizados no arquivo
void salvarCarros(Carro *carros, int qtd){
    FILE *file = fopen("carros.txt", "w");
    if (file == NULL){
        printf("Erro ao salvar o arquivo.\n");
        return;
    }

    for (int i = 0; i < qtd; i++){
        fprintf(file, "%d,%s,%d,%s\n", carros[i].id, carros[i].nome, carros[i].ano, carros[i].disponibilidade);
    }

    fclose(file);
}

// Função para adicionar um novo carro
void adicionarCarro(Carro *carros, int *qtd) {
    if (*qtd >= MAX_CARROS) {
        printf("Nao é possivel adicionar mais carros. Limite atingido.\n");
        return;
    }

    Carro novoCarro;
    novoCarro.id = *qtd + 1; // ID automático
    printf("Digite o nome do carro: ");
    scanf(" %[^\n]", novoCarro.nome); // Leitura do nome com espaços
    printf("Digite o ano do carro: ");
    scanf("%d", &novoCarro.ano);
    strcpy(novoCarro.disponibilidade, "Disponivel"); // Definindo a disponibilidade

    carros[*qtd] = novoCarro; // Adiciona o novo carro
    (*qtd)++;
    printf("Carro %s adicionado com sucesso!\n", novoCarro.nome);
}

// Função principal
int main(){
    FILE *file;
    Carro carros[MAX_CARROS];
    char linha[256];
    int qtd = 0;
    int opcao;

    // Carrega os carros do arquivo
    file = fopen("carros.txt", "r");
    if (file == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), file) != NULL){
        linha[strcspn(linha, "\n")] = '\0'; // Remove o "\n"
        sscanf(linha, "%d,%49[^,],%d,%49[^,]", &carros[qtd].id, carros[qtd].nome, &carros[qtd].ano, carros[qtd].disponibilidade);
        qtd++;
    }
    fclose(file);

    // Menu
    do{
        printf("\n=== LOCADORA DE VEICULOS ===\n");
        printf("1 - Ver catalogo de carros\n");
        printf("2 - Alugar carro\n");
        printf("3 - Receber carro\n");
        printf("4 - Novo carro\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1){
            system("cls");
            imprimirCarros(carros, qtd);
        }
        else if (opcao == 2){
            system("cls");
            mostrarCarrosDisponiveis(carros, qtd);
            alugarCarro(carros, qtd);
            salvarCarros(carros, qtd);
        }
        else if (opcao == 3){
            system("cls");
            mostrarCarrosIndisponiveis(carros, qtd);
            receberCarro(carros, qtd);
            salvarCarros(carros, qtd);
        }
        else if (opcao == 0){
            printf("Saindo...\n");
        }
        else if (opcao == 4){
           adicionarCarro(carros, &qtd);
            salvarCarros(carros, qtd);
            system("pause");
        }
        else{
            printf("Opcao invalida.\n");
            system("pause");
            system("cls");
        }

    } while (opcao != 0);

    return 0;
}
