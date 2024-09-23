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

// wemerson
void imprimirCarros(Carro *carros, int qtd) {
    int i;
    printf("\n---------- Lista de Carros ----------\n\n");
    for (i = 0; i < qtd; i++) {
        printf("ID: %d,  NOME: %s,  ANO: %d,  SITUACAO: %s\n",
               carros[i].id, carros[i].nome, carros[i].ano, carros[i].disponibilidade);
    }
}
// wemerson
int mostrarCarrosDisponiveis(Carro *carros, int qtd) {
    printf("\n----- Carros disponiveis para alugar -----\n\n");
    int i; int qtd_disponiveis = 0;
    for (i = 0; i < qtd; i++) {
        if (strcmp(carros[i].disponibilidade, "Disponivel") == 0) {
            printf("ID: %d, NOME: %s, ANO: %d\n", carros[i].id, carros[i].nome, carros[i].ano);
            qtd_disponiveis++;
        }
    }
    if(qtd_disponiveis == 0){
		printf("\nNenhum carro disponivel para alugar!\n");
		return 0;
	}
}

// wemerson
int mostrarCarrosIndisponiveis(Carro *carros, int qtd) {
    printf("\n----- Carros Alugados -----\n\n");
    int i; int qtd_alugados = 0;
    for (i = 0; i < qtd; i++) {
        if (strcmp(carros[i].disponibilidade, "Indisponivel") == 0) {
            printf("ID: %d, NOME: %s, ANO: %d\n", carros[i].id, carros[i].nome, carros[i].ano);
            qtd_alugados++;
        }
    }
      if(qtd_alugados == 0){
		printf("\nNenhum carro alugado no momento!\n");
		return 0;
	}
}

// wemerson
void alugarCarro(Carro *carros, int qtd) {
    int idCarro, i;
    printf("\nDigite o ID do carro que deseja alugar: ");
    scanf("%d", &idCarro);
    for (i = 0; i < qtd; i++) {
        if (carros[i].id == idCarro && strcmp(carros[i].disponibilidade, "Disponivel") == 0) {
            strcpy(carros[i].disponibilidade, "Indisponivel");
            printf("\nCarro %s alugado com sucesso!\n", carros[i].nome);
            return;
        }
    }
    printf("Carro nao disponivel ou ID invalido.\n");
}

// wemerson
void receberCarro(Carro *carros, int qtd) {
    int idCarro, i;
    printf("\nDigite o ID do carro que deseja receber de volta: ");
    scanf("%d", &idCarro);

    for (i = 0; i < qtd; i++) {
        if (carros[i].id == idCarro && strcmp(carros[i].disponibilidade, "Indisponivel") == 0) {
            strcpy(carros[i].disponibilidade, "Disponivel");
            printf("\nCarro %s recebido com sucesso!\n", carros[i].nome);
            return;
        }
    }
    printf("ID invalido ou o carro ja esta disponivel.\n");
}

// lauanderson
void excluirCarro(Carro *carros, int *qtd) {
    int idCarro, i, j;
    printf("\n-------- Exclusao de Veiculo --------\n");
    printf("\nDigite o ID do carro que deseja excluir: ");
    scanf("%d", &idCarro);

    for (i = 0; i < *qtd; i++) {
        if (carros[i].id == idCarro) {
            printf("\nCarro %s excluido com sucesso!\n", carros[i].nome);

            // Mover os proximos carros, para uma posicao atraz
            for (j = i; j < *qtd - 1; j++) {
                carros[j] = carros[j + 1];
            }

            (*qtd)--;

            return;
        }
    }
    printf("ID inválido.\n");
}
// lauanderson
void salvarCarros(Carro *carros, int qtd) {
    FILE *pont_arq = fopen("carros.txt", "w");
    if (pont_arq == NULL) {
        printf("Erro ao salvar o arquivo.\n");
        return;
    }
    int i;
    for (i = 0; i < qtd; i++) {
        fprintf(pont_arq, "%d,%s,%d,%s\n", carros[i].id, carros[i].nome, carros[i].ano, carros[i].disponibilidade);
    }

    fclose(pont_arq);
}

// lauanderson
int obterProximoId(Carro *carros, int qtd) {
    int maxId = 0;
    int i;
    for (i = 0; i < qtd; i++) {
        if (carros[i].id > maxId) {
            maxId = carros[i].id;
        }
    }
    return maxId + 1;
}

// lauanderson
void adicionarCarro(Carro *carros, int *qtd) {
    if (*qtd >= MAX_CARROS) {
        printf("Nao eh possivel adicionar mais carros. Limite atingido.\n");
        return;
    }

    Carro novoCarro;
    novoCarro.id = obterProximoId(carros, *qtd); // id unico
    system("cls");
    printf("\n-------- Adicao de Veiculo --------\n");
    printf("\nDigite o nome do carro: ");
    scanf(" %[^\n]", novoCarro.nome);
    printf("Digite o ano do carro: ");
    scanf("%d", &novoCarro.ano);
    strcpy(novoCarro.disponibilidade, "Disponivel");

    carros[*qtd] = novoCarro; // Adiciona o novo carro
    (*qtd)++;
    printf("\nCarro %s adicionado com sucesso!\n", novoCarro.nome);
}

// lauanderson
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
        fprintf(pont_arq, "3,HB20,2021,Indisponivel\n");
        fclose(pont_arq); // fechar
        pont_arq = fopen("carros.txt", "r");
    }

    // Le uma linha de (pont_arq) e armazena na variável -> linha
    while (fgets(linha, sizeof(linha), pont_arq) != NULL) {
        linha[strcspn(linha, "\n")] = '\0'; // Remover o "\n"
        sscanf(linha, "%d,%49[^,],%d,%49[^,]", &carros[qtd].id, carros[qtd].nome, &carros[qtd].ano, carros[qtd].disponibilidade);
        qtd++;
    }
    fclose(pont_arq); // fechar

    // Menu
    do {
        printf("\n====== LOCADORA DE VEICULOS ======\n\n");
        printf("1 - Ver catalogo de carros\n");
        printf("2 - Alugar carro\n");
        printf("3 - Receber carro de volta\n");
        printf("4 - Adicionar carro\n");
        printf("5 - Excluir carro\n");
        printf("0 - Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            system("cls");
            imprimirCarros(carros, qtd);
        } else if (opcao == 2) {
            system("cls");
            int q = mostrarCarrosDisponiveis(carros, qtd);
            if (q != 0){
            	alugarCarro(carros, qtd);
            	salvarCarros(carros, qtd);
			}
			system("pause");
			system("cls");

        } else if (opcao == 3) {
            system("cls");
            int q = mostrarCarrosIndisponiveis(carros, qtd);
            if (q != 0){
				receberCarro(carros, qtd);
            	salvarCarros(carros, qtd);
			}
			system("pause");
			system("cls");
        } else if (opcao == 4) {
            adicionarCarro(carros, &qtd);
            salvarCarros(carros, qtd);
            system("pause");
			system("cls");
        } else if (opcao == 5) {
        	system("cls");
            imprimirCarros(carros, qtd);
            excluirCarro(carros, &qtd);
            salvarCarros(carros, qtd);
            system("pause");
			system("cls");
        } else if (opcao == 0) {
            printf("Saindo...\n");
        } else {
            printf("Opcao invalida.\n");
            system("pause");
			system("cls");
        }

    } while (opcao != 0);

    return 0;
}
