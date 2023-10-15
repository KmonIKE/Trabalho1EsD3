#include <stdio.h>
#include "./auxiliar/aux_geral.h"

int maina() {
/*  Parte 4 Funcionando
    int escolha;
    char arquivo[32];
    FILE *arq;
    scanf(" %s", &escolha, arquivo);
    if(!(arq = fopen(arquivo, "r+"))) {    // testa se o arquivo existe
        printf("Falha no processamento do arquivo\n");
        return 0;
    }

    Registro *registro = novoRegistro();
    int RRN;
    scanf("%d", &RRN);
    if (n_de_registro((FILE *) arquivo) <= RRN) {
        printf("Registro inexistente.");
        return 0;
    }
    fseek((FILE *) arquivo, RRN * TAM_REGISTRO, SEEK_SET);  // coloca o ponteiro no inicio do registro (byte offset)
    leitura_tabela(arquivo, registro);
    exibe(registro);
    fclose((FILE *) arquivo);
    return 0;
*/


    return 0;



}

#include <stdio.h>
#include <string.h>

#define MAX_REGISTERS 100 // Defina o número máximo de registros que podem ser armazenados
#define MAX_STRING_SIZE 100 // Defina o tamanho máximo para campos de string

// Estrutura para representar um registro
//struct Registro {
//    int id;
//    char nome[MAX_STRING_SIZE];
//    double peso;
//    // Adicione outros campos conforme necessário
//    int marcado; // 0 para não marcado, 1 para marcado como logicamente removido
//};


//int main() {
//    FILE *arquivo;
//    char nomeArquivo[] = "dados.txt"; // Nome do arquivo de dados
////    struct Registro registros[MAX_REGISTERS];
//                    int totalRegistros = 0;
//
//    // Abre o arquivo para leitura
//    arquivo = fopen(nomeArquivo, "r");
//
//    if (arquivo == NULL) {
//        perror("Erro ao abrir o arquivo.");
//        return 1;
//    }
//
//                    // Lê os registros do arquivo
//                    while (fread(&registro[totalRegistros], sizeof(struct Registro), 1, arquivo) == 1) {
//                        totalRegistros++;
//                    }
//                    fclose(arquivo);
//
//                    int n; // Número de vezes que a busca deve ser executada
//                    scanf("%d", &n);
//
//                    while (n > 0) {
//                        char campoBusca[MAX_STRING_SIZE];
//                //        printf("Digite o campo de busca (nome, peso, etc.): ");
//                        scanf("%s", campoBusca);
//
//                    // Lógica para realizar a busca com base no campo especificado
//                    int encontrados = 0;
//                    for (int i = 0; i < totalRegistros; i++) {
//                        if (registros[i].marcado == 0) { // Verifica se o registro não está logicamente removido
//                            if (strcmp(campoBusca, "nome") == 0) {
//                                char buscaNome[MAX_STRING_SIZE];
//                                printf("Digite o nome a ser buscado: ");
//                                scan_quote_string(buscaNome);
//                                if (strcmp(buscaNome, registros[i].nome) == 0) {
//                                    encontrados++;
//                                    printf("Registro encontrado: ID %d, Nome: %s, Peso: %lf\n", registros[i].id, registros[i].nome, registros[i].peso);
//                                }
//                            } else if (strcmp(campoBusca, "peso") == 0) {
//                                double buscaPeso;
//                                printf("Digite o peso a ser buscado: ");
//                                scanf("%lf", &buscaPeso);
//                                if (buscaPeso == registros[i].peso) {
//                                    encontrados++;
//                                    printf("Registro encontrado: ID %d, Nome: %s, Peso: %lf\n", registros[i].id, registros[i].nome, registros[i].peso);
//                                }
//                            }
//                            // Adicione outros campos de busca conforme necessário
//                        }
//                    }
//
//                    if (encontrados == 0) {
//                        printf("Nenhum registro encontrado.\n");
//                    }
//
//                    n--;
//                }
//
//    return 0;
//}

