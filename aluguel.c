#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARROS 100
#define MAX_NOME 50

// Estrutura para armazenar dados do carro
typedef struct
{
    int id;
    char nome[MAX_NOME];
    int ano;
    char disponibilidade[MAX_NOME];
} Carro;

// Função para imprimir a lista de carros
void imprimirCarros(Carro *carros, int count)
{
    printf("Lista de Carros:\n");
    for (int i = 0; i < count; i++)
    {
        printf("ID: %d, Nome: %s, Ano: %d, Disponibilidade: %s\n",
               (carros + i)->id, (carros + i)->nome, (carros + i)->ano, (carros + i)->disponibilidade);
    }
}

// Função para exibir apenas os carros disponíveis
void mostrarCarrosDisponiveis(Carro *carros, int count)
{
    printf("Carros Disponiveis:\n");
    for (int i = 0; i < count; i++)
    {
        if (strcmp((carros + i)->disponibilidade, "Disponivel") == 0)
        {
            printf("ID: %d, Nome: %s, Ano: %d\n",
                   (carros + i)->id, (carros + i)->nome, (carros + i)->ano);
        }
    }
}

// Função para alugar um carro (atualizar disponibilidade)
void alugarCarro(Carro *carros, int count)
{
    int idCarro, alugado = 0;

    mostrarCarrosDisponiveis(carros, count); // Mostra os carros disponíveis
    printf("Digite o ID do carro que deseja alugar: ");
    scanf("%d", &idCarro);

    // Procura pelo carro com o ID informado
    for (int i = 0; i < count; i++)
    {
        if ((carros + i)->id == idCarro && strcmp((carros + i)->disponibilidade, "Disponivel") == 0)
        {
            strcpy((carros + i)->disponibilidade, "Indisponivel");
            printf("Carro %s alugado com sucesso!\n", (carros + i)->nome);
            alugado = 1;
            break;
        }
    }

    if (!alugado)
    {
        printf("Carro nao disponível ou ID invalido.\n");
    }
}

// RECEBER (atualizar disponibilidade)
void ReceberCarro(Carro *carros, int count)
{
    int idCarro, devolvido = 0;
    printf("Carros alugados:\n");
    for (int i = 0; i < count; i++)
    {
        if (strcmp((carros + i)->disponibilidade, "Indisponivel") == 0)
        {
            printf("ID: %d, Nome: %s, Ano: %d\n",
                   (carros + i)->id, (carros + i)->nome, (carros + i)->ano);
        }
    }
    printf("Digite o ID do carro que deseja receber de volta: ");
    scanf("%d", &idCarro);

    // Procura pelo carro com o ID informado
    for (int i = 0; i < count; i++)
    {
        if ((carros + i)->id == idCarro && strcmp((carros + i)->disponibilidade, "Indisponivel") == 0)
        {
            strcpy((carros + i)->disponibilidade, "Disponivel");
            printf("Carro %s recebido com sucesso!\n", (carros + i)->nome);
            devolvido = 1;
            break;
        }
    }

    if (!devolvido)
    {
        printf("Carro nao disponivel ou ID invalido.\n");
    }
}

// Função para salvar a lista de carros atualizada no arquivo
void salvarCarros(Carro *carros, int count)
{
    FILE *file = fopen("carros.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao salvar o arquivo.\n");
        return;
    }

    // Regrava todos os carros no arquivo
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%s,%d,%s\n", (carros + i)->id, (carros + i)->nome, (carros + i)->ano, (carros + i)->disponibilidade);
    }

    fclose(file);
}

int main()
{
    FILE *file;
    Carro carros[MAX_CARROS];
    char linha[256];
    int count = 0;
    int opcao;

    // Carrega os carros do arquivo
    file = fopen("carros.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê cada linha do arquivo
    while (fgets(linha, sizeof(linha), file) != NULL)
    {

        linha[strcspn(linha, "\n")] = '\0'; // Remove o "\n" e coloca "\0"

        sscanf(linha, "%d,%49[^,],%d,%49[^,]", &carros[count].id, carros[count].nome, &carros[count].ano, carros[count].disponibilidade);
        count++;
    }
    fclose(file);

    // Menu interativo
    do
    {
        printf("\n=== LOCADORA DE VEICULOS ===\n");
        printf("1 - Catalogo de carros\n");
        printf("2 - Alugar veiculo\n");
        printf("3 - Sair\n");
        printf("4 - Receber veiculo\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            system("cls"); // Limpa a tela
            imprimirCarros(carros, count);
            break;
        case 2:
            system("cls"); // Limpa a tela
            alugarCarro(carros, count);
            salvarCarros(carros, count); // Salva o arquivo atualizado
            break;
        case 3:
            printf("Saindo...\n");
            break;
        case 4:
            system("cls"); // Limpa a tela
            ReceberCarro(carros, count);
            salvarCarros(carros, count); // Salva o arquivo atualizado
            break;
        default:
            printf("opcao invalida.\n");
        }
    } while (opcao != 3);

    return 0;
}
