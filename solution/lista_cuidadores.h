#ifndef LISTA_CUIDADORES
#define LISTA_CUIDADORES    

/*Tipo que define a lista_cuidadores (tipo opaco)
 * lista sem limite de tamanho
 * */
typedef struct lista_cuidadores Lista_Cuidadores;

#include "cuidador.h"
#include "lista_idosos.h"


/* Cria uma lista de cuidadores vazia
* inputs: nenhum
* output: lista vazia
* pre-condicao: nao tem
* pos-condicao: lista alocada e vazia,  */
Lista_Cuidadores* inicia_lista_cuidadores(void); //implementada

/* Libera toda a memoria alocada
* inputs: a lista de cuidadores
* output: NULL
* pre-condicao: lista nao nula
* pos-condicao: memoria eh liberada. */
void deleta_lista_cuidadores(Lista_Cuidadores* lista); //implementada

/* Libera toda a memoria alocada
* inputs: a lista de cuidadores
* output: NULL
* pre-condicao: lista nao nula
* pos-condicao: toda a memoria eh liberada. */
void deleta_lista_cuidadores_e_cuidadores(Lista_Cuidadores* lista); 
 
/* Insere um cuidador na ULTIMA posicao da lista de cuidadores.
* inputs: a lista de cuidadores e o cuidador a ser inserido
* output: nao tem
* pre-condicao: lista e cuidador nao nulos
* pos-condicao: cuidador incluido na primeira posicao da lista*/
void insere_lista_cuidadores(Lista_Cuidadores* lista, Cuidador* cuidador); //implementada

/* Retira um determinado cuidador da lista de cuidadores e o retorna.
* inputs: a lista de cuidadores e o cuidador a ser retirado
* output: Endereco do cuidador retirado
* pre-condicao: lista e nome nao nulos
* pos-condicao: cuidador retirado da lista e ponteiros da lista ficam consistentes */
Cuidador* remove_lista_cuidadores(Lista_Cuidadores* lista, char* nome); //implementada

// OBS: Função de depuração
/* Imprime a lista de cuidador e todos os dados de cada cuidador.
 * (Formato:"
             nome: Pedro, localizacao: [100,100]
             
             "
 * )
* inputs: a lista de cuidadores
* output: nao tem
* pre-condicao: lista nao nula
* pos-condicao: cuidador impresso no arquivo do cuidador */
void imprime_lista_cuidadores(Lista_Cuidadores* lista); //implementada


/* Retorna um determinado cuidador da lista de cuidadores.
* inputs: a lista de cuidadores e a posição do cuidador a ser retornado
* output: Endereco do cuidador retornado
* pre-condicao: lista não nulo e posição não negativa
* pos-condicao: retorna cuidador e os ponteiros da lista e do cuidador ficam consistentes */
Cuidador* retorna_cuidador_posicao_lista_cuidadores(Lista_Cuidadores* lista, int pos); //implementada

/* Retorna um determinado cuidador da lista de cuidadores.
* inputs: a lista de cuidadores e o nome do cuidador a ser retornado
* output: Endereco do cuidador retornado
* pre-condicao: lista e nome não nulos
* pos-condicao: retorna cuidador, e os ponteiros da lista, do cuidador e do nome ficam consistentes */
Cuidador* retorna_cuidador_por_nome_lista_cuidadores(Lista_Cuidadores* lista, char* nome);

/* Retorna o tamanho da lista de cuidadores.
* inputs: a lista de cuidadores
* output: tamanho da lista
* pre-condicao: lista não nula
* pos-condicao: ponteiro da lista fica consistente e um inteiro retornado com sucesso */
int retorna_tamanho_lista_cuidadores(Lista_Cuidadores* lista); //implementada

/*Insere os dados atuais nos cuidadores.
* inputs: lista de cuidadores
* output: nenhum
* pre-condicao: lista e cuidadores da lista não nulos
* pos-condicao: dados atualizados dos cuidadores */
void atualiza_lista_cuidadores(Lista_Cuidadores* lista);

/* Cria uma lista de cuidadores
* inputs: caminho do diretorio e lista de idoso
* output: lista de cuidadores
* pre-condicao: caminho do diretorio, lista de idoso e idosos da lista, não nulos
* pos-condicao: lista alocada e preenchida com os cuidadores,  */
Lista_Cuidadores* cria_lista_cuidadores_de_arquivo(char * diretorio, Lista_Idosos* idosos);


#endif
