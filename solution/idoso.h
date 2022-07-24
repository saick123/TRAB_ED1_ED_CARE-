#ifndef IDOSO_H

#define IDOSO_H


typedef struct idoso Idoso;

#include "lista_idosos.h"
#include "cuidador.h"
#include "lista_cuidadores.h"

#define TAM_LOCALIZACAO 2
#include <stdio.h>

/* escreve dados do idoso no arquivo de saida do idoso
* inputs: um idoso
* output: void
* pre-condicao: o idoso exista
* pos-condicao: impressão correta dos dados do idoso no arquivo*/
void escreve_dados_saida_idoso(Idoso* idoso);   

/* cria um novo idoso com o nome repassado
* inputs: um char* contendo o nome
* output: um idoso válido
* pre-condicao: o nome seja válido, os arquivos de entrada devem existir na pasta de entradas
* pos-condicao: um idoso é criado com sucesso e retornado  */
Idoso* inicia_idoso(char * nome); //implementada

/* atualiza as informações de um idoso lendo os dados de entrada
* inputs: um idoso
* output: void
* pre-condicao: o idoso exista
* pos-condicao: idoso tem suas informações atualizada com sucesso  */
void atualiza_idoso(Idoso* idoso); //implementada

/* retorna o cuidador menos distante do idoso repassado
* inputs: um idoso
* output: um cuidador 
* pre-condicao: O idoso exista
* pos-condicao: o cuidador mais perto do idoso é retornado com sucesso*/
Cuidador* retorna_cuidador_perto(Idoso* idoso);  //implementada

/* retorna o amigo menos distante idoso repassado
* inputs: um idoso
* output: um idoso
* pre-condicao: o idoso passado exista
* pos-condicao: o idoso mais perto do idoso passao é retornado com sucesso  */
Idoso* retorna_amigo_perto(Idoso* idoso);  //implementada

/* retorna 1 para idoso em queda, 0 para idoso que não está em queda
* inputs: um idoso
* output: um inteiro
* pre-condicao: o idoso exista
* pos-condicao: um inteiro representando queda ou não é retornado com sucesso  */
int verifica_queda(Idoso* idoso); //implementada

/* retorna 1 para idoso, 0 para idoso vivo
* inputs: um idoso
* output: um inteiro
* pre-condicao: o idoso exista
* pos-condicao: um inteiro representando morte ou não é retornado com sucesso  */
int verifica_morte(Idoso* idoso); //implementada

/* libera a memória de um idoso
* inputs: um idoso 
* output: void 
* pre-condicao: nenhuma 
* pos-condicao: um idoso é liberado da memória com sucesso */
void deleta_idoso(Idoso* idoso);    //implementada                                                    

/* retorna um float representando a temperatura atual de um certo idoso passado
* inputs: um idoso
* output: um numero float
* pre-condicao: o idoso exista
* pos-condicao: um float representando a temperatura do idoso é retornado com sucesso */
float retorna_temperatura(Idoso* idoso); // implementada

/* retorna um inteiro representando a condição de febre e um determinado idoso, 0 para em febre, 1 para febre baixa, 2 para febre alta
* inputs: um idoso
* output:  um inteiro
* pre-condicao: o idoso exista
* pos-condicao: um inteiro representando a condição e febre de um determinado idoso é retornado com sucesso*/
int verifica_febre(Idoso* idoso); // implementada

/* retorna um inteiro representando a condição de ajuda e um determinado idoso, 0 para não precisa de ajuda, 1 para ajuda de amigo, 2 para ajuda de cuidador
* inputs: um idoso
* output: um inteiro
* pre-condicao: o idoso exista
* pos-condicao: um inteiro representando a condição de ajuda de um determinado idoso é retornado com sucesso */
int alerta_ajuda(Idoso* idoso); //implementada 

/* função para depuração que retorna um ponteiro para um vetor de inteiros de tamanho 2 que contém a localização de um idoso
* inputs: um idoso
* output: um ponteiro constante para inteiro
* pre-condicao: o idoso exista
* pos-condicao: é retornado com sucesso um ponteiro para inteiro constant que repesenta o vetor de temperatura do idoso */
const int * retorna_localizacao(Idoso* idoso); // implementada

/* faz amizade entre 2 idosos, insere o idoso1 na lista de amigos do idoso2 e vice-versa
* inputs: 2 idosos
* output: void
* pre-condicao: os 2 idosos devem existir 
* pos-condicao: os idosos são inseridos com sucesso entre usas listas de amigos*/
void faz_amizade(Idoso* idoso1, Idoso* idoso2); //implementada                                     

/* função que adiciona na lista de amigos do idoso1 o idoso2
* inputs: 2 idosos
* output: void
* pre-condicao: os 2 idosos devem existir 
* pos-condicao: o idoso 2 é inserido com sucesso na lista de amigos do idoso1*/
void adiciona_amigo_idoso(Idoso* idoso1, Idoso* idoso2);       //implementada                    

/* função que adiciona o cuidador na lista de cuidadores do idoso
* inputs: um idoso e um cuidador
* output: void
* pre-condicao: o idoso e o cuidador devem existir 
* pos-condicao: o cuidador é inserido com sucesso na lista de cuidadores do idoso*/
void adiciona_cuidador_idoso(Idoso* idoso, Cuidador* cuidador);   //implementada                   

/* função de teste, imprime os dados de um determinado idoso no terminal
* inputs: um idoso
* output: void
* pre-condicao: o idoso exista 
* pos-condicao: o idoso é impresso com sucesso*/
void imprime_idoso(Idoso* idoso); //implementada

/* retorna um ponteiro para o nome do idoso especificado
* inputs: um idoso
* output: um char* para a string nome
* pre-condicao: o idoso exista
* pos-condicao: um ponteiro para char é retornado com sucesso e aponta para o nome do idoso*/
char* retorna_nome(Idoso* idoso); //implementada

/* remove o idoso passado(se morto) da lista de amigos de todos os seus amigos
* inputs: um idoso
* output: void
* pre-condicao:  o idoso exista
* pos-condicao: ele é removido da lista de amigos de cada amigo dele*/
void desfaz_lacos_idoso_falecido(Idoso* idoso); //implementada

/* retorna um ponteiro para a lista de cuidadores de um determinado idoso
* inputs: um idoso
* output: um ponteiro para uma lista de lista de cuidadores
* pre-condicao: o idoso exista
* pos-condicao: é retornado com sucesso a lista de cuidadores do idoso passado*/
Lista_Cuidadores* retorna_lista_cuidadores(Idoso* idoso);               /*
                                                                                auxiliares    
                                                                        */
/* retorna a lista de idosos amigos de um determinado idoso
* inputs: um idoso
* output: uma lista de idosos
* pre-condicao: o idoso exista
* pos-condicao: é retornado a lista de idosos que é a lista de idosos amigos de um determinado idoso passado*/
Lista_Idosos* retorna_lista_idosos_amigos(Idoso* idoso);



#endif
