#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "idoso.h"
#include "lista_idosos.h"
#include "lista_cuidadores.h"
#include "cuidador.h"

/*
#define MORTO 0
#define VIVO 1
#define QUEDA 2
*/


enum situacao{
    MORTO,
    VIVO,
    VIVO_QUEDA
};

typedef enum situacao e_Situacao;


#define SEM_FEBRE 0
#define FEBRE_BAIXA 1
#define FEBRE_ALTA 2

#define AJUDA_CUIDADOR 2
#define AJUDA_AMIGO 1
#define NOT_AJUDA 0


typedef struct informacoes Informacoes_Idoso;

struct informacoes{
    float temperatura;
    int localizacao[2];
    e_Situacao situacao;
    int contador_febre_baixa;
};


struct idoso{
    char * nome;
    Informacoes_Idoso informacoes;
    Lista_Idosos* amigos;   
    Lista_Cuidadores* cuidadores;
    FILE * dado_entrada;
    FILE * dado_saida;
};


static long double calcula_distancia_entre_pontos(int * vet1, int *vet2, char * nome);
static int retorna_quantidade_contador_baixas(Idoso* idoso);

Idoso* inicia_idoso(char * nome){

    Idoso* novo_idoso = (Idoso*)malloc(sizeof(Idoso));



    if(novo_idoso == NULL){
        printf("erro de alocação de memoria em inicia_idoso");
        return NULL;
    }


    novo_idoso->nome = strdup(nome);
    novo_idoso->informacoes.temperatura = 36.0;
    novo_idoso->informacoes.localizacao[0] = 0;
    novo_idoso->informacoes.localizacao[1] =0;
    novo_idoso->informacoes.situacao = VIVO;
    novo_idoso->informacoes.contador_febre_baixa =0;

    novo_idoso->amigos = inicia_lista_idosos();
    novo_idoso->cuidadores = inicia_lista_cuidadores();

    char diretorio[100];
    sprintf(diretorio, "Entradas/%s.txt", nome);
    novo_idoso->dado_entrada = fopen(diretorio, "r");
    sprintf(diretorio, "Saidas/%s-saida.txt", nome);
    novo_idoso->dado_saida = fopen(diretorio, "w");


    return novo_idoso;

}




void deleta_idoso(Idoso* idoso){

    deleta_lista_idosos(idoso->amigos);
    deleta_lista_cuidadores(idoso->cuidadores);
    free(idoso->nome);
    fclose(idoso->dado_entrada);
    fclose(idoso->dado_saida);


    free(idoso);
    
}




void imprime_idoso(Idoso* idoso){
    if(verifica_morte(idoso)){
        printf("\nnome do falecido: %s\n", retorna_nome(idoso));
        return ;
    }
    printf("\nnome: %s, temp: %0.1f, localizacao: [%d,%d], situacao: %d, ajuda?: %d, quantidade_febre_baixa_seguia: %d\n", idoso->nome, idoso->informacoes.temperatura, idoso->informacoes.localizacao[0],
    idoso->informacoes.localizacao[1], idoso->informacoes.situacao, alerta_ajuda(idoso), retorna_quantidade_contador_baixas(idoso));
    return;
}


int verifica_queda(Idoso* idoso){
    if(idoso->informacoes.situacao != VIVO_QUEDA){
        return 0;
    }
    return 1;
}


int verifica_morte(Idoso* idoso){
    if(idoso->informacoes.situacao != MORTO){
        return 0;
    }
    return 1;
}





const int* retorna_localizacao(Idoso* idoso){
    return ((const int *)(&(idoso->informacoes.localizacao)));
}

float retorna_temperatura(Idoso* idoso){
    return (idoso->informacoes.temperatura);
}

int verifica_febre(Idoso* idoso){

    if(retorna_temperatura(idoso) <= 37)
        return SEM_FEBRE;
    
    else if(retorna_temperatura(idoso) > 37 && retorna_temperatura(idoso) < 38)
        return FEBRE_BAIXA;
    
    else
        return FEBRE_ALTA;
    
}

int alerta_ajuda(Idoso* idoso){
    if(idoso->informacoes.situacao == VIVO_QUEDA || verifica_febre(idoso) == FEBRE_ALTA || retorna_quantidade_contador_baixas(idoso) == 4){
        return AJUDA_CUIDADOR;
    }
    else if(verifica_febre(idoso) == FEBRE_BAIXA){
        return AJUDA_AMIGO;
    }else{
        return NOT_AJUDA;
    }
}


void adiciona_amigo_idoso(Idoso* idoso1, Idoso* idoso2){

    
    insere_lista_idosos( idoso1->amigos, idoso2);
    
    return;
}


void faz_amizade(Idoso* idoso1, Idoso* idoso2){

    
    adiciona_amigo_idoso(idoso1, idoso2);

    adiciona_amigo_idoso(idoso2, idoso1);

   return;
}

char* retorna_nome(Idoso* idoso){
    return (idoso->nome);
}


void adiciona_cuidador_idoso(Idoso* idoso, Cuidador* cuidador){
    insere_lista_cuidadores(idoso->cuidadores, cuidador);
    return;
}



void atualiza_idoso(Idoso* idoso){

    if(verifica_morte(idoso)){
        return;
    }

    idoso->informacoes.situacao = VIVO;

    FILE* dado_entrada = idoso->dado_entrada;
    char linha[100];


    fscanf(dado_entrada,"%[^\n]", linha); // fazer teste pra ver o caso da ultima linha
    fscanf(dado_entrada,"%*c");

    if(linha[0] == 'f'){
        idoso->informacoes.situacao = MORTO;
        return;
    }

    char * string_aux;
    string_aux = strtok(linha, ";");
    sscanf(string_aux, "%f", &idoso->informacoes.temperatura);


    string_aux = strtok(NULL, ";");
    sscanf(string_aux,"%d", &idoso->informacoes.localizacao[0]);

    string_aux = strtok(NULL, ";");
    sscanf(string_aux, "%d", &idoso->informacoes.localizacao[1]);

    int n= -1;
    string_aux = strtok(NULL, ";");
    sscanf(string_aux ,"%d", &n);
    
    if(n == 1){
        idoso->informacoes.situacao = VIVO_QUEDA;
    }
    if(n == -1 ){
        printf("erro em atualiza idoso (n == -1)");
    }

    if(idoso->informacoes.temperatura > 36.99999 && idoso->informacoes.temperatura < 37.99999 && !verifica_queda(idoso)){
        idoso->informacoes.contador_febre_baixa++;
    }else if (idoso->informacoes.temperatura >= 38.00001){
        idoso->informacoes.contador_febre_baixa =0 ;
    }
    
    
}

Idoso* retorna_amigo_perto(Idoso* idoso){ 
    int tam = retorna_tamanho_lista_idosos(idoso->amigos);

    if(tam ==0)
        return NULL;

    Lista_Idosos * amigos = idoso->amigos;
    Idoso* aux = retorna_idoso_por_posicao_lista_idosos(amigos, 0 );
    Idoso* perto = aux;
    printf("\nidoso: %s\n", retorna_nome(idoso));
    long double distancia;
    long double distancia_menor = calcula_distancia_entre_pontos(idoso->informacoes.localizacao, aux->informacoes.localizacao, retorna_nome(idoso));

    for(int i =1; i < tam; i ++){
        aux = retorna_idoso_por_posicao_lista_idosos(amigos, i);
        distancia = calcula_distancia_entre_pontos(idoso->informacoes.localizacao, aux->informacoes.localizacao, retorna_nome(idoso));
        printf("\nnome do amigo: %s\n", retorna_nome(aux));
        printf("\nantes da comparacao:%Lf %Lf\n", distancia, distancia_menor);
        if(distancia_menor > distancia){
            distancia_menor = distancia;
            perto = aux;
        }
        printf("\ndepois da comparacao:%Lf %Lf\n", distancia, distancia_menor);
    }

    return perto;
}

Cuidador* retorna_cuidador_perto(Idoso* idoso){ 
    int tam = retorna_tamanho_lista_cuidadores(idoso->cuidadores);
    if(tam ==0)
        return NULL;

    Lista_Cuidadores * cuidadores = idoso->cuidadores;
    Cuidador* aux = retorna_cuidador_posicao_lista_cuidadores(cuidadores, 0 );
    Cuidador* perto = aux;
    long double  distancia = -1;
    long double distancia_menor = calcula_distancia_entre_pontos(idoso->informacoes.localizacao, retorna_localizacao_cuidador(aux), retorna_nome(idoso));
    int * loca = retorna_localizacao_cuidador(aux);
    for(int i =1; i < tam; i ++){
        aux = retorna_cuidador_posicao_lista_cuidadores(cuidadores, i);
        distancia = calcula_distancia_entre_pontos(idoso->informacoes.localizacao, retorna_localizacao_cuidador(aux), retorna_nome(idoso));
        int * loca = retorna_localizacao_cuidador(aux);
        imprime_cuidador(aux);
        if(distancia_menor > distancia){
            distancia_menor = distancia;
            perto = aux;
        }
    }

    return perto;
}


#define VET_TAM 2

static long double calcula_distancia_entre_pontos(int * vet1, int *vet2, char * nome){
    unsigned long long int  d=0;
    for(int i=0; i < VET_TAM; i ++){
        d+= ((unsigned long long int )(vet1[i] - vet2[i]))*(vet1[i] - vet2[i]); 
    }
    d = (long double)d;
    d = sqrt(d);
    
    return d;

}
//sujestão
/*
   static double calcula_distancia_entre_pontos2(int* vet1, int* vet2){
  6         long long int sum =  ((((long long int)vet1[0]-(long long int)vet2[0])*((long long int)vet1[0]-(long long int)vet2[0]))+(((long long int)vet1[1]-(long long int)vet2[1])*((long long int)vet1[1]-(long long int)vet2[1])));
  7
  8         return sqrt(sum);
  9 }
*/

void desfaz_lacos_idoso_falecido(Idoso* idoso){

    if(!verifica_morte(idoso)){
        return;
    }

    int tam = retorna_tamanho_lista_idosos(idoso->amigos);

    Idoso* aux;
    char* idoso_nome = retorna_nome(idoso);
    // percorrendo amigos do falecido
    for(int i=0; i < tam; i ++){
        aux = retorna_idoso_por_posicao_lista_idosos(idoso->amigos, i);
        remove_lista_idosos(aux->amigos, idoso_nome );
    }

}


static int retorna_quantidade_contador_baixas(Idoso* idoso){
    return idoso->informacoes.contador_febre_baixa;
}



// funcoes para teste

Lista_Cuidadores* retorna_lista_cuidadores(Idoso* idoso){
    return (idoso->cuidadores);
}


Lista_Idosos* retorna_lista_idosos_amigos(Idoso* idoso){
    return (idoso->amigos);
}

void escreve_dados_saida_idoso(Idoso* idoso){

    FILE* saida = idoso->dado_saida;
    if(verifica_morte(idoso)){
        fprintf(saida,"falecimento\n");
        return ;
    }

    if(alerta_ajuda(idoso) == NOT_AJUDA){

        fprintf(saida,"tudo ok\n");
        
    } else if(alerta_ajuda(idoso) == AJUDA_CUIDADOR){

        Cuidador* aux;
        aux = retorna_cuidador_perto(idoso);
        if(aux == NULL)
            return;
        if(verifica_queda(idoso)){
            fprintf(saida,"queda, acionou %s\n", retorna_nome_cuidador(aux));
        }else if(verifica_febre(idoso) == FEBRE_ALTA){
            fprintf(saida,"febre alta, acionou %s\n", retorna_nome_cuidador(aux));
        } else{
            fprintf(saida,"febre baixa pela quarta vez, acionou %s\n", retorna_nome_cuidador(aux));
            idoso->informacoes.contador_febre_baixa =0;
        }

    }else{

        if(retorna_tamanho_lista_idosos(retorna_lista_idosos_amigos(idoso)) == 0){
            fprintf(saida,"Febre baixa mas, infelizmente, o idoso está sem amigos na rede\n");
            return ;
        }

        Idoso* aux = retorna_amigo_perto(idoso);
        if(aux == NULL)
            return;
        char* nome_amigo = retorna_nome(aux);
        fprintf(saida, "febre baixa, acionou amigo %s\n",nome_amigo);
        

    }

    return;
}
