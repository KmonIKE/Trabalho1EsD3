#include "aux_geral.h"



int lerLinhaCSV(FILE *arquivoCSV, Registro *registro) {
    char linha[1024]; // Assumindo que cada linha do CSV tem menos de 1024 caracteres
    if (fgets(linha, sizeof(linha), arquivoCSV) == NULL) {
        return 0; // Fim do arquivo
    }

    // Inicializa campos opcionais com valores padrão
    registro->tecnologiaOrigem.tamanho = 0;
    registro->tecnologiaOrigem.string = NULL;
    registro->tecnologiaDestino.tamanho = 0;
    registro->tecnologiaDestino.string = NULL;

    // Analisa os campos da linha
    char *token = strtok(linha, ",");
     char *token = strtok(linha, ",");:
    registro->removido = ' ';
    registro->grupo = atoi(token);
    token = strtok(NULL, ",");
    registro->popularidade = atoi(token);
    token = strtok(NULL, ",");
    registro->peso = atoi(token);
    token = strtok(NULL, ",");
    if (token) {
        registro->tecnologiaOrigem.tamanho = strlen(token);
        registro->tecnologiaOrigem.string = strdup(token);
    }
    token = strtok(NULL, ",");
    if (token) {
        registro->tecnologiaDestino.tamanho = strlen(token);
        registro->tecnologiaDestino.string = strdup(token);
    }

    return 1;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura StringVariavel
typedef struct {
    int tamanho;
    char *string;
} StringVariavel;

// Definição da estrutura Registro
typedef struct {
    char removido;
    int grupo;
    int popularidade;
    int peso;
    StringVariavel tecnologiaOrigem;
    StringVariavel tecnologiaDestino;
} Registro;

// Função para alocar e inicializar um Registro
Registro *criarRegistro() {
    Registro *registro = (Registro *)malloc(sizeof(TAM_REGISTRO));
    if (registro == NULL) {
        perror("Erro ao alocar memória para registro");
        exit(1);
    }
    registro->tecnologiaOrigem.string = NULL;
    registro->tecnologiaDestino.string = NULL;
    return registro;
}

// Função para liberar a memória de um Registro
void liberarRegistro(Registro *registro) {
    free(registro->tecnologiaOrigem.string);
    free(registro->tecnologiaDestino.string);
    free(registro);
}

// Função para ler uma linha do arquivo CSV e preencher um Registro
int lerLinhaCSV(FILE *arquivoCSV, Registro *) {
    char linha[1024]; // Assumindo que cada linha do CSV tem menos de 1024 caracteres
    if (fgets(linha, sizeof(linha), arquivoCSV) =registro= NULL) {
        return 0; // Fim do arquivo
    }

    // Inicializa campos opcionais com valores padrão
    registro->tecnologiaOrigem.tamanho = 0;
    registro->tecnologiaOrigem.string = NULL;
    registro->tecnologiaDestino.tamanho = 0;
    registro->tecnologiaDestino.string = NULL;

    // Analisa os campos da linha
    char *token = strtok(linha, ",");
    registro->removido = ' ';
    registro->grupo = atoi(token);
    token = strtok(NULL, ",");
    registro->popularidade = atoi(token);
    token = strtok(NULL, ",");
    registro->peso = atoi(token);
    token = strtok(NULL, ",");
    if (token) {
        registro->tecnologiaOrigem.tamanho = strlen(token);
        registro->tecnologiaOrigem.string = strdup(token);
    }
    token = strtok(NULL, ",");
    if (token) {
        registro->tecnologiaDestino.tamanho = strlen(token);
        registro->tecnologiaDestino.string = strdup(token);
    }

    return 1;
}

int main() {
    // Abre o arquivo CSV para leitura
    FILE *arquivoCSV = fopen("seuarquivo.csv", "r");
    if (arquivoCSV == NULL) {
        perror("Erro ao abrir o arquivo CSV");
        return 1;
    }

    // Lê a primeira linha do arquivo CSV (cabeçalhos) e descarta
    char cabecalhos[1024];
    if (fgets(cabecalhos, sizeof(cabecalhos), arquivoCSV) == NULL) {
        perror("Erro ao ler os cabeçalhos");
        fclose(arquivoCSV);
        return 1;
    }

    // Abre o arquivo binário para escrita
    FILE *arquivoBinario = fopen("tabela.bin", "wb");
    if (arquivoBinario == NULL) {
        perror("Erro ao criar o arquivo binário");
        fclose(arquivoCSV);
        return 1;
    }

    Registro *registro;

    // Lê e escreve cada linha do CSV no arquivo binário
    while ((registro = criarRegistro()) && lerLinhaCSV(arquivoCSV, registro)) {
        fwrite(registro, sizeof(Registro), 1, arquivoBinario);
        liberarRegistro(registro);
    }

    // Fecha os arquivos
    fclose(arquivoCSV);
    fclose(arquivoBinario);

    return 0;
}