//
// Created by Henrique on 25/09/2023.
//
#include "aux_geral.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void readline(char* string){
    char c = 0;

    do{
        c = (char) getchar();

    } while(c == '\n' || c == '\r');

    int i = 0;

    do{
        string[i] = c;
        i++;
        c = getchar();
    } while(c != '\n' && c != '\r');

    string[i]  = '\0';
}

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

    /* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
    *  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

    unsigned long i, cs;
    unsigned char *mb;
    size_t fl;
    FILE *fs;
    if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
        fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
        return;
    }
    fseek(fs, 0, SEEK_END);
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    mb = (unsigned char *) malloc(fl);
    fread(mb, 1, fl, fs);

    cs = 0;
    for(i = 0; i < fl; i++) {
        cs += (unsigned long) mb[i];
    }
    printf("%lf\n", (cs / (double) 100));
    free(mb);
    fclose(fs);
}

void scan_quote_string(char *str) {

    /*
    *	Use essa função para ler um campo string delimitado entre aspas (").
    *	Chame ela na hora que for ler tal campo. Por exemplo:
    *
    *	A entrada está da seguinte forma:
    *		nomeDoCampo "MARIA DA SILVA"
    *
    *	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
    *		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
    *		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
    *
    */

    char R;

    while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

    if(R == 'N' || R == 'n') { // campo NULO
        getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
        strcpy(str, ""); // copia string vazia
    } else if(R == '\"') {
        if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
            strcpy(str, "");
        }
        getchar(); // ignorar aspas fechando
    } else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
        str[0] = R;
        scanf("%s", &str[1]);
    } else { // EOF
        strcpy(str, "");
    }
}

struct Registro *novoRegistro(){
    Registro *registro = (Registro *)malloc(sizeof(TAM_REGISTRO));
    if(registro == NULL){
        printf("Erro ao alocar memoria do registro");
    };

    //Malocando e inicializando TecnologaOrigem
    registro->tecnologiaOrigem.tamanho = 0;//Colocar dps que ler
    //registro->tecnologiaOrigem.string = (char *)malloc((TAM_TECNOLOGIA) * sizeof(char));
    //strcpy(registro->tecnologiaOrigem.string, "NULL"); //ADicionar o valor aqui

    //Malocando e inicializando TecnologiasDestino
    registro->tecnologiaDestino.tamanho = 0;// Colocar dps que ler
    //registro->tecnologiaDestino.string = (char *)malloc((TAM_TECNOLOGIA) * sizeof(char));
    //strcpy(registro->tecnologiaDestino.string, "NULL"); //ADicionar o valor aqui

    //Inicializando as partes estaticas do registro como valores padroes para caso faltar dados
    registro->removido = '0';
    registro->grupo = 0;
    registro->popularidade = 0;
    registro->peso = 0;

    return registro;

}
void deletaRegistro(Registro *registro){
    free(registro);
}

struct Cabecalho *novoCabecalho(){
    Cabecalho *cabecalho = (Cabecalho *)malloc(sizeof(TAM_CABECALHO));
    if(cabecalho == NULL){
        printf("Erro ao alocar memoria do cabecalho");
    }

    //Inicializando struct de cabecalho
    cabecalho->status = 1; //indica se o arquivo de dados esta consistente 0(setar 0 ao abrir para escrita) 1(apos escrever)
    cabecalho->proxRRN =0; //iniciado com 0
    cabecalho->nroTecnologias = 0; //quantidade, inciail eh 0, apenas diferentes
    cabecalho->nroParesTecnologias =0;

    return cabecalho;
}
void deletaCabecalho(Cabecalho *cabecalho){
    free(cabecalho);

}

struct Lista *novaLista(){
    Lista *l = (Lista *) malloc(sizeof (Lista));

    if(l == NULL){
        printf(" Erro de alocação de memoria");
        return 0;
    }

    l->inicio = NULL;
    l->qnt = 0;

}

int lerLinhaCSV(FILE *arquivoCSV, Registro *registro) {
    char linha[1024]; // Assumindo que cada linha do CSV tem menos de 1024 caracteres
    if (fgets(linha, sizeof(linha), arquivoCSV) == NULL) {
        return 0; // Fim do arquivo
    }

    // Inicializa campos opcionais com valores padrão
    strcpy(registro->tecnologiaOrigem.string,"NULL");
    strcpy(registro->tecnologiaDestino.string,"NULL");


    // Analisa os campos da linha
    char *token = strtok(linha, ",");
    registro->removido = '0';
    if (token) {
        registro->tecnologiaOrigem.tamanho = strlen(token);
        strcpy(registro->tecnologiaOrigem.string,token);

    }
    token = strtok(NULL, ",");
    registro->grupo = atoi(token);


    token = strtok(NULL, ",");
    registro->popularidade = atoi(token);
    token = strtok(NULL, ",");
    if (token) {
        registro->tecnologiaDestino.tamanho = strlen(token);
        strcpy(registro->tecnologiaDestino.string,token);
    }
    token = strtok(NULL, ",");
    registro->peso = atoi(token);



    return 1;
}

void registroNaLista(Registro *registro,Lista *lista){

    if(lista == NULL || registro == NULL){
        return;
    }

    No *novo = (No *) malloc(sizeof(No));
    if(novo == NULL){
        printf("Erro de alocação de memoria");
        return;
    }

    novo->reg = registro;
    novo->prox = NULL;

    lista->qnt++;

    if(lista->inicio == NULL){
            lista->inicio = novo;
    }

    else{
        No *aux = lista->inicio;

        while(aux->prox != NULL){

            aux = aux->prox;

        }

        aux->prox = novo;

    }
}
int procura_tecnologia(Lista *lista,Registro *registro){

    No *n = lista->inicio;

    while (n != NULL){

        if (strcmp(n->reg->tecnologiaOrigem.string, registro->tecnologiaOrigem.string) == 0){
            return 1;
        }

        n = n->prox;
    }
    return 0;
}
int procura_par(Lista *lista,Registro *registro){

    No *n = lista->inicio;

    while (n != NULL){

        if (strcmp(n->reg->tecnologiaOrigem.string, registro->tecnologiaOrigem.string) == 0){
            if(((n->reg->tecnologiaDestino.string == NULL) || strcmp(n->reg->tecnologiaDestino.string,"\n")  == 0) && (registro->tecnologiaDestino.string == NULL) || strcmp(registro->tecnologiaDestino.string,"\n")  == 0){
                return 1;
            }else{
                return 0;
            }
            if (strcmp(n->reg->tecnologiaDestino.string, registro->tecnologiaDestino.string) == 0){
                return 0;
            }

            if(strcmp(n->reg->tecnologiaDestino.string, registro->tecnologiaOrigem.string) == 0 && strcmp(n->reg->tecnologiaOrigem.string, registro->tecnologiaDestino.string) == 0){
                return 0;
            }

            return 1;
        }

        n = n->prox;
    }

    return 0;
}

void escreverCabecalho(FILE *arquivoBinario, const Cabecalho *cabecalho) {
    fwrite(cabecalho, sizeof(Cabecalho), 1, arquivoBinario);
}
//Funcao para escrever registro variavel
// Tecnologia Origem
//    if(registro->tecnologiaOrigem.tamanho < 1){
//        strcpy(registro->tecnologiaOrigem.string, NULL);
//    } else {
//        registro->tecnologiaOrigem.string = (char *)malloc((TAM_TECNOLOGIA) * sizeof(char));
//        strcpy(registro->tecnologiaOrigem.string, "VAlor"); //ADicionar o valor aqui
//    }
//
//    //Tecnologia Destino
//    if(registro->tecnologiaDestino.tamanho < 1){
//        strcpy(registro->tecnologiaDestino.string, NULL);
//    } else {
//        registro->tecnologiaDestino.string = (char *)malloc((TAM_TECNOLOGIA) * sizeof(char));
//        strcpy(registro->tecnologiaDestino.string, "VAlor"); //ADicionar o valor aqui
//    }

int n_de_registro(FILE *arquivoCSV){
    long contador = 0;
    char flag[1];
    while(fread(flag, 1, 1, arquivoCSV)) contador++;  // conta caracter por caracter
    return contador / TAM_REGISTRO;
} //função que vai contar para definir RRN, substituir arq pela struct

void leitura_tabela(FILE *arquivoCSV, Registro *Registro){
    fread(&Registro->tecnologiaOrigem, sizeof(char), 51, arquivoCSV);
    fread(&Registro->grupo, sizeof(char), 51, arquivoCSV);
    fread(&Registro->popularidade, sizeof(char), 81, arquivoCSV);
    fread(&Registro->tecnologiaDestino, sizeof(char), 51, arquivoCSV);
    fread(&Registro->peso, sizeof(int), 1, arquivoCSV);
}

void exibe(Registro *Registro){
    printf("nomeTecnologiaOrigem: %s\n", Registro->tecnologiaOrigem.string);
    printf("grupo: %d\n", Registro->grupo);
    printf("popularidade: %d\n", Registro->popularidade);
    printf("nomeTecnologiaDestino: %s\n", Registro->tecnologiaDestino.string);
    printf("peso: %d\n\n", Registro->peso);
}

//void parte_3() {
//    FILE *arquivo;
//    int n; // Número de vezes que a busca deve ser executada
//    int totalRegistros = 0;
//    int encontrados = 0;
//    // Lê os registros do arquivo
//    while (fread(&registro[totalRegistros], sizeof(struct Registro), 1, arquivo) == 1) {
//        totalRegistros++;
//    }
//    fclose(arquivo);
//
//    scanf("%d", &n);
//
//    while (n > 0)
//    {
//        char campoBusca[TAM_REGISTRO]; //Declara e pega o que vai ser pesquisado
//        scanf("%s", campoBusca);
//
//    }
//
//
//    for (int i = 0; i < totalRegistros; i++) {
//        if (registros[i].marcado == 0) { // Verifica se o registro não está logicamente removido
//            if (strcmp(campoBusca, "nome") == 0) {
//                char buscaNome[TAM_REGISTRO];
//                printf("Digite o nome a ser buscado: ");
//                scan_quote_string(buscaNome);
//                if (strcmp(buscaNome, registros[i].nome) == 0) {
//                    encontrados++;
//                    printf("Registro encontrado: ID %d, Nome: %s, Peso: %lf\n", registros[i].id, registros[i].nome, registros[i].peso);
//                }
//            } else if (strcmp(campoBusca, "peso") == 0) {
//                double buscaPeso;
//                printf("Digite o peso a ser buscado: ");
//                scanf("%lf", &buscaPeso);
//                if (buscaPeso == registros[i].peso) {
//                    encontrados++;
//                    printf("Registro encontrado: ID %d, Nome: %s, Peso: %lf\n", registros[i].id, registros[i].nome, registros[i].peso);
//                }
//            }
//            // Adicione outros campos de busca conforme necessário
//        }
//    }
//
//    if (encontrados == 0) {
//        printf("Nenhum registro encontrado.\n");
//    }
//
//    n--;
//}

