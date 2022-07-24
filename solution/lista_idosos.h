#ifndef LISTA_IDOSOS
#define LISTA_IDOSOS

/*Tipo que define o cuidador (tipo opaco).
 */
typedef struct lista_idosos Lista_Idosos;

#include "idoso.h"

/* Cria uma nova lista de idosos
* inputs: nenhum
* output: lista vazia
* pre-condicao: nao tem
* pos-condicao: lista alocada e vazia,  */
Lista_Idosos* inicia_lista_idosos(void); 

/* libera a lista de idosos, mas nao seu conteudo
* inputs: uma lista já alocada
* output: void
* pre-condicao: nao tem
* pos-condicao: uma lista com a memoria liberada, mas o conteudo ainda está alocado */
void deleta_lista_idosos(Lista_Idosos* lista); //implementada


/* libera toda a memoria de uma lista
* inputs: uma lista
* output: void
* pre-condicao: nao tem
* pos-condicao: toda a memória da lista, inclusive de seu conteúdo foi liberado  */
void deleta_lista_idosos_e_idosos(Lista_Idosos* lista); 

/* insere um novo idoso na lista de idosos
* inputs: uma lista e um idoso
* output: void
* pre-condicao: a lista exista, o idoso exista
* pos-condicao: lista com o novo idoso inserido no final */
void insere_lista_idosos(Lista_Idosos* lista, Idoso* idoso); //implementada

/* remove um determinado idoso com determinado nome da lista
* inputs: lista e chave(nome)
* output: idoso retirado
* pre-condicao: lista exista, chave exista
* pos-condicao: lista sem o idoso repassado  */
Idoso* remove_lista_idosos(Lista_Idosos* lista, char* chave); //implementada

/* imprime os idosos de uma lista de idosos
* inputs: lista de idosos
* output: void
* pre-condicao: lista exista
* pos-condicao: todos os idosos da lista imprimidos com sucesso  */
void imprime_lista_idosos(Lista_Idosos* lista); //implementada

/* retorna o tamanho da lista especificada
* inputs: lista de idosos
* output: um inteiro que corresponda ao tamanho da lista
* pre-condicao: a lista exista
* pos-condicao: um inteiro é retornado com sucesso  */
int retorna_tamanho_lista_idosos(Lista_Idosos* lista); //implementada

/* retorna um idoso de acordo com sua posição na lista
* inputs: uma lista de idosos e uma posição
* output: um idoso
* pre-condicao: a lista exista
* pos-condicao: um idoso é retornado com sucesso, se a posição for inválida, retorna-se NULL */
Idoso* retorna_idoso_por_posicao_lista_idosos(Lista_Idosos* lista, int pos); //implementada

/* retorna um idoso de acordo com o nome repassado
* inputs: uma lista de idosos e um char * 
* output: um idoso
* pre-condicao: a lista exista , o char* exista
* pos-condicao: lista alocada e vazia,  */
Idoso* retorna_idoso_por_nome_lista_idosos(Lista_Idosos* lista, char* nome_idoso);

/* atualiza as informações de cada idoso na lista de idosos
* inputs: um lista de idosos
* output: void
* pre-condicao: a lista exista
* pos-condicao: todos os idosos são retirados com sucesso  */
void atualiza_lista_idosos(Lista_Idosos* lista);

/* retira todos os idosos mortos de uma lista e os libera
* inputs: uma lista de idosos
* output: void
* pre-condicao: a lista exista
* pos-condicao: todos os idosos foram retirados e liberados com sucesso  */
void retira_idosos_mortos_lista_idosos(Lista_Idosos* lista);

/* retira e retorna o primeiro idoso morto encontrado percorrendo a lista do começo ao final
* inputs: uma lista de idosos
* output: um idoso retirado
* pre-condicao: a lista exista
* pos-condicao: o idoso seja retirado e liberado com sucesso */ 
Idoso* retira_primeiro_idoso_morto_lista_idosos(Lista_Idosos* lista);

/* cria uma lista de idosos a partir de um arquivo de mesmo formato que o arquivo apoio.txt
* inputs: o diretorio do seu arquivo
* output: uma lista de idosos criado a partir do arquivo
* pre-condicao: o diretório deve ser válido
* pos-condicao: a lista é criada com sucesso  */
Lista_Idosos* cria_lista_idosos_de_arquivo(char * diretorio);

/* escreve em cada arquivo de saida de cada idoso na lista, os dados de acordo com as situações em que eles estão
* inputs: uma lista de idosos
* output: void
* pre-condicao: a lista exista
* pos-condicao: a lista é criada com sucesso e o arquivo usado é fechado  */
void escreve_dados_saida_lista_idosos(Lista_Idosos* lista);

#endif
