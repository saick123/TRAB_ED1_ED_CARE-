#include <stdio.h>
#include <stdlib.h>


#include "idoso.h"
#include "lista_idosos.h"
#include "cuidador.h"
#include "lista_cuidadores.h"
#include  <string.h>




int main(int argc, char* argv[]){
    Lista_Idosos* lista = cria_lista_idosos_de_arquivo("Entradas/apoio.txt");
    Lista_Cuidadores* cuidadores = cria_lista_cuidadores_de_arquivo("Entradas/cuidadores.txt", lista);
    int quantidade_rodadas;
    
    sscanf(argv[1], "%d", &quantidade_rodadas);
    for(int i =0; i < quantidade_rodadas; i ++){
        atualiza_lista_idosos(lista);
       atualiza_lista_cuidadores(cuidadores);
        Idoso* aux;
        for(int j=0; j < retorna_tamanho_lista_idosos(lista); j ++){
            aux = retorna_idoso_por_posicao_lista_idosos(lista, j );
            if(verifica_morte(aux)){
                desfaz_lacos_idoso_falecido(aux);
            }
        }

        escreve_dados_saida_lista_idosos(lista);
        while(1){
            Idoso* aux = retira_primeiro_idoso_morto_lista_idosos(lista);
            if(aux==NULL){
                break;
            }
            deleta_idoso(aux);
        }
        printf("\n\n");
    }


   
    deleta_lista_cuidadores_e_cuidadores(cuidadores);
    deleta_lista_idosos_e_idosos(lista);
    return 0;
}



// anotaçoes:


/*

sempre resetar as febres baixas quando chega a 4 !!!

*/