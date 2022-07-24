#include "cuidador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct cuidador{
    char* nome;
    int localizacao[2];
    FILE* dados;
};




Cuidador* inicia_cuidador(char* nome){

    Cuidador* novo_cuidador = (Cuidador*)malloc(sizeof(Cuidador));
    if(novo_cuidador == NULL){
        printf("erro na alocação de um novo cuidador em inicia cuidador (retornando NULL)");
        return NULL;
    }

    novo_cuidador->nome = strdup(nome);
    printf("%s", novo_cuidador->nome);
    char diretorio[100];
    sprintf(diretorio, "Entradas/%s.txt", novo_cuidador->nome);
    novo_cuidador->dados = fopen(diretorio, "r");
    novo_cuidador->localizacao[0] = 0;
    novo_cuidador->localizacao[1] =0;


    return novo_cuidador;
}

void deleta_cuidador(Cuidador * cuidador){
    fclose(cuidador->dados);
    free(cuidador->nome);
    free(cuidador);
    

}



void atualiza_cuidador(Cuidador  * cuidador){
    
    FILE* dados = cuidador->dados;

    char linha[100];

    fscanf(dados,"%[^\n]", linha);

    fscanf(dados,"%*c");
        
    

    char * string_aux;

    string_aux = strtok(linha, ";");
    sscanf(string_aux,"%d", &cuidador->localizacao[0]);

    string_aux = strtok(NULL, ";");
    sscanf(string_aux,"%d", &cuidador->localizacao[1]);




    return;
}


char* retorna_nome_cuidador(Cuidador* cuidador){
    return (cuidador->nome);
}

void imprime_cuidador(Cuidador* cuidador){
    printf("\nnome: %s, localizacao: [%d,%d]\n", cuidador->nome, cuidador->localizacao[0],cuidador->localizacao[1]);
    return;
}


int * retorna_localizacao_cuidador(Cuidador* cuidador){
    return (cuidador->localizacao);
}

void modifica_localizacao(Cuidador* cuidador, int * localizacao){
    cuidador->localizacao[0] =localizacao[0];
    cuidador->localizacao[1] = localizacao[1];
    return;
    
}