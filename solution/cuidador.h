#ifndef CUIDADOR_H
#define CUIDADOR_H


/*Tipo que define o cuidador (tipo opaco).
 */
typedef struct cuidador Cuidador;

/*Insere os dados atuais no cuidador.
* inputs: cuidador
* output: nenhum
* pre-condicao: o cuidador não null
* pos-condicao: dados atualizados do cuidador */
void atualiza_cuidador(Cuidador  * cuidador);

/*Cria uma cuidador vazio
* inputs: nome
* output: cuidador
* pre-condicao: string alocada
* pos-condicao: cuidador alocado e com nome */
Cuidador* inicia_cuidador(char* nome);

/*Libera toda a memoria alocada para o cuidador.
* inputs: ouidador (cuidador precisam ser alocado dinamicamente)
* output: NULL
* pre-condicao: cuidador não nulo
* pos-condicao: toda memoria alocada liberada (inclusive da string)*/
void deleta_cuidador(Cuidador * cuidador);

/*Retorna o nome do cuidador
* inputs: cuidador
* output: o nome
* pre-condicao: cuidador não nulo
* pos-condicao: nenhuma */
char* retorna_nome_cuidador(Cuidador* cuidador);

/*Imprime os dados do cuidador.
* inputs: o cuidador
* output: nenhum
* pre-condicao: cuidador não nulo
* pos-condicao: dados impressos no arquivo do cuidador
*/
void imprime_cuidador(Cuidador* cuidador);

/*Atualiza localização do cuidador
* inputs: cuidador e um vetor de inteiros
* output: nenhum
* pre-condicao: cuidador e vetor não nulos
* pos-condicao: nenhuma */
void modifica_localizacao(Cuidador* cuidador, int * localizacao); //funcao para teste, apagar depois 

/*Retorna um vetor de inteiros
* inputs: cuidador 
* output: vetor de inteiros
* pre-condicao: cuidador não nulo
* pos-condicao: nenhuma */
int * retorna_localizacao_cuidador(Cuidador* cuidador);



#endif
