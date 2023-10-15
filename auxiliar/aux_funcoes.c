//
// Created by Henrique on 25/09/2023.
//

#include "aux_funcoes.h"
#include "aux_geral.h"
#include "aux_arquivos.h"
#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int cria_tabela(char *filename){


    FILE* csv = abre_arquivo(filename,"r");

    Registro *registro = novoRegistro();
    Cabecalho *cabecalho = novoCabecalho();
    Lista *lista = novaLista();

    //Le e descarta a primeira linha do arquivo
    char primeiraLinha[1024];
    if (fgets(primeiraLinha, sizeof(primeiraLinha), csv) == NULL) {
        perror("Erro ao ler os cabeçalhos");
        fecha_arquivo(csv);
        return 1;
    }

    // Abre o arquivo binário para escrita
    FILE* binario = abre_arquivo("tabela.bin","wb");

    if (binario == NULL) {
        perror("Erro ao criar o arquivo binário");
        fecha_arquivo(csv);
        return 1;
    }

    // Escreve o cabeçalho no arquivo binário
    escreverCabecalho(binario, cabecalho);

    // Lê e escreve cada linha do CSV no arquivo binário
    Registro* temp = malloc(sizeof(Registro));
    while(lerLinhaCSV(csv, temp)) {
        fwrite(&registro->tecnologiaOrigem.string, sizeof(char)*registro->tecnologiaOrigem.tamanho, 1, binario);
        fwrite(&registro->grupo, sizeof(int), 1, binario);
        fwrite(&registro->popularidade, sizeof(int), 1, binario);
        fwrite(&registro->tecnologiaDestino.string, sizeof(char)*registro->tecnologiaDestino.tamanho, 1, binario);
        fwrite(&registro->peso, sizeof(int), 1, binario);
        cabecalho->proxRRN++;

        int Nome = procura_tecnologia(lista,temp);
        int Par = procura_par(lista, temp);

        if (!Nome){

            registroNaLista(temp,lista);

            if (!Nome){
                cabecalho->nroTecnologias = cabecalho->nroTecnologias + 1;
            }

            if (!Par){
                cabecalho->nroParesTecnologias = cabecalho->nroParesTecnologias + 1;
            }
        }

        temp = malloc(sizeof(Registro));


    }



    rewind(binario);
    cabecalho->status = '1'; // Arquivo consistente agora
    escreverCabecalho(binario, cabecalho);

    //printf("a");


    binarioNaTela("tabela.bin");

    fecha_arquivo(csv);
    deletaCabecalho(cabecalho);
    deletaRegistro(registro);
}
int select_all(char *filename){

    FILE* binario = abre_arquivo(filename,"rb");

    Cabecalho *cabecalho = novoCabecalho();
    Registro *registro = novoRegistro();

    //Lendo cabecalho
    fseek(binario, 0, 0);

    fread(&(cabecalho->status), sizeof(char),1, binario);
    fread(&(cabecalho->proxRRN),sizeof(int),1, binario);
    fread(&(cabecalho->nroTecnologias), sizeof(int), 1, binario);
    fread(&(cabecalho->nroParesTecnologias), sizeof(int), 1, binario);


    while(!feof(binario)){


//----------------------------------LEIUTRA DOS DADOS DO ARQUIVO BINARIO--------------------------------------//
        if(fread(&(registro->removido),sizeof(char),1,binario)){


            if(registro->removido == '0') {

                fread(&(registro->grupo), sizeof(int), 1, binario);
                fread(&(registro->popularidade), sizeof(int), 1, binario);
                fread(&(registro->peso), sizeof(int), 1, binario);

                //string variavel
                fread(&registro->tecnologiaOrigem.tamanho, sizeof(int), 1, binario);
                fread(registro->tecnologiaOrigem.string, sizeof(char)*registro->tecnologiaOrigem.tamanho,1 , binario);
                registro->tecnologiaOrigem.string[registro->tecnologiaOrigem.tamanho] = '\0';

//                char aux;
//                for(int i = 0; i < registro->tecnologiaOrigem.tamanho; i++){
//                    fread(&aux, sizeof(char), 1, binario);
//                    if(aux == '$'){
//                        continue;
//                    }else{
//                        registro->tecnologiaOrigem.string[i] = aux;
//                    }
//                }
//                int tam = TAM_TECNOLOGIA - registro->tecnologiaOrigem.tamanho;
//
//                for(int i = 0; i < tam; i++){
//                    fread(&aux, sizeof(char), 1, binario);
//                }


                fread(&registro->tecnologiaDestino.tamanho, sizeof(int), 1, binario);
                fread(registro->tecnologiaDestino.string, sizeof(char)*registro->tecnologiaDestino.tamanho,1 , binario);
                registro->tecnologiaDestino.string[registro->tecnologiaDestino.tamanho] = '\0';

                char lixo = '$';
                while (!feof(binario) && lixo == '$') {
                    fread(&lixo, sizeof(char), 1, binario);
                }

                if (!feof(binario)) {
                    fseek(binario, -1, 1);
                }

                printf("%d,%d,%d,%s, %s \n", registro->grupo, registro->popularidade, registro->peso,registro->tecnologiaOrigem.string, registro->tecnologiaDestino.string);

//                printf("%d ,", registro->grupo);
//                printf("%d ,", registro->popularidade);
//                printf("%d ,", registro->peso);
//
//                if (registro->tecnologiaOrigem.string != NULL) {
//                    printf("%s ,", registro->tecnologiaOrigem.string);
//                } else {
//                    printf(" ");
//                }
//
//                if (registro->tecnologiaDestino.string != NULL) {
//                    printf("%s ", registro->tecnologiaDestino.string);
//                } else {
//                    printf(" ");

                    //printf("%d,%d,%d,%s,%s\n", registro->grupo, registro->popularidade, registro->peso, registro->tecnologiaOrigem.string, registro->tecnologiaDestino.string);

                //}

            }

            if(registro->removido == '1'){
                    fread(&(registro->grupo),sizeof(int),1,binario);
                    fread(&(registro->popularidade),sizeof(int),1,binario);
                    fread(&(registro->peso),sizeof(int),1,binario);

                    //string variavel
                    fread(&registro->tecnologiaOrigem.tamanho,sizeof(int),1,binario);
                    fread(registro->tecnologiaOrigem.string,sizeof(char),registro->tecnologiaOrigem.tamanho,binario);

                    fread(&registro->tecnologiaDestino.tamanho,sizeof(int),1,binario);
                    fread(registro->tecnologiaDestino.string,sizeof(char),registro->tecnologiaDestino.tamanho,binario);

                    if (feof(binario)){
                    return 0;
                    }

                    char lixo = '$';
                    while (!feof(binario) && lixo == '$'){
                    fread(&lixo, 1, sizeof(char), binario);
                     }

                    if (!feof(binario)){
                    fseek(binario, -1, 1);
                    }


                }





//----------------------------------LEIUTRA DOS DADOS DO ARQUIVO BINARIO



            // Imprime o conteúdo da struct Registro
        }
}


//----------------------------------PRINT DOS DADOS DO ARQUIVO--------------------------------------//


    printf("a");
    deletaCabecalho(cabecalho);
    deletaRegistro(registro);
}

int main(){
    cria_tabela("dados2.csv");
    //select_all("binario3.bin");
//    int escolha;
//    char arquivo[32];
//    FILE *arq;
//    scanf(" %s", &escolha, arquivo);
//    if(!(arq = fopen(arquivo, "r+"))) {    // testa se o arquivo existe
//        printf("Falha no processamento do arquivo\n");
//        return 0;
//    }
//
//    Registro *registro = novoRegistro();
//    int RRN;
//    scanf("%d", &RRN);
//    if (n_de_registro((FILE *) arquivo) <= RRN) {
//        printf("Registro inexistente.");
//        return 0;
//    }
//    fseek((FILE *) arquivo, RRN * TAM_REGISTRO, SEEK_SET);  // coloca o ponteiro no inicio do registro (byte offset)
//    leitura_tabela(arquivo, registro);
//    exibe(registro);
//    fclose((FILE *) arquivo);
//    return 0;

}