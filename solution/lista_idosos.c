#include "lista_idosos.h"
#include "idoso.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct celula_idoso Celula_Idoso;

struct celula_idoso{  
  Idoso* idoso;
  Celula_Idoso* prox;
};

struct lista_idosos{
  Celula_Idoso* prim;
  Celula_Idoso* ult;
  int quantidade_idosos;
};


Lista_Idosos* inicia_lista_idosos(void){

  Lista_Idosos* lista = (Lista_Idosos*)malloc(sizeof(Lista_Idosos));

  if(lista == NULL)
    return NULL;  

  lista->prim = NULL;
  lista->ult = NULL;
  lista->quantidade_idosos =0;

  return lista;
}

void imprime_lista_idosos(Lista_Idosos* lista){

    printf("\nIMPRIMINDO LISTA DE IDOSOS:\n");

    if(lista == NULL){
      return;
    }

    Celula_Idoso* p = lista->prim;
    while(p != NULL){
      imprime_idoso(p->idoso);
      printf("\n");
      p = p->prox;
    }
  return;
  
}


void insere_lista_idosos(Lista_Idosos* lista, Idoso* idoso){
  Celula_Idoso* nova = (Celula_Idoso*)malloc(sizeof(Celula_Idoso));

  if(nova == NULL){
    printf("erro na alocação insere lista");
    return;
  }

  nova->idoso = idoso;
  nova->prox = NULL;

  if(lista->ult == NULL){
    lista->prim = nova;
  }else{
    lista->ult->prox = nova;
  }
  lista->ult = nova;
  lista->quantidade_idosos++;

  return;
}


Idoso* remove_lista_idosos(Lista_Idosos* lista, char* chave){
  
  Celula_Idoso* p, * ant;
  ant = NULL;
  p = lista->prim;

  while(p!=NULL){
    if(strcmp((retorna_nome(p->idoso)), chave) == 0 ){
      break;
    }
    ant = p;
    p = p->prox;
  }

  
  if(p == NULL){
    printf("\nerro, esse idoso nao existe\n");
    return NULL;
  }

    if(p == lista->prim){
      lista->prim = p->prox;
      if(lista->ult == p){
        lista->ult = NULL;
      }
    }else{
      ant->prox = p->prox;
      if(p == lista->ult){
        lista->ult = ant;
      }
    }

  Idoso* aux = p->idoso;
  free(p);
  lista->quantidade_idosos--;
  return aux;
  
}

void deleta_lista_idosos(Lista_Idosos * lista){
  if(!lista)
    return;
  Celula_Idoso* p, * ant;
  p = lista->prim;
  
  while(p!= NULL){
    ant = p;
    p = p->prox;
    free(ant);
  }
  free(lista);
  return;
}


int retorna_tamanho_lista_idosos(Lista_Idosos* lista){
  return (lista->quantidade_idosos);
}

Idoso* retorna_idoso_por_posicao_lista_idosos(Lista_Idosos* lista, int pos){
  if(pos > lista->quantidade_idosos -1 || pos < 0 || lista->quantidade_idosos ==0  )
    return NULL;
  Celula_Idoso* p = lista->prim;
  for(int i=0; i < pos; i ++){
    p = p->prox;
  }

  return p->idoso;

}

Idoso* retorna_idoso_por_nome_lista_idosos(Lista_Idosos* lista, char* nome_idoso){
  
  if(lista->quantidade_idosos ==0)
    return NULL;
  Celula_Idoso* p = lista->prim;

  while(p){
    if(strcmp(retorna_nome(p->idoso), nome_idoso) ==0 ){
      return p->idoso;
    }
    p = p->prox;
  }

  return NULL;
  
}


void retira_idosos_mortos_lista_idosos(Lista_Idosos* lista){

  int tam = retorna_tamanho_lista_idosos(lista);

  if(tam ==0)
    return;

  Celula_Idoso* p = lista->prim;
  Celula_Idoso* ant = NULL;
 

  for(int i = 0; i < tam; i ++){

    if(verifica_morte(p->idoso)){     
      
      if(p == lista->prim){
        lista->prim = p->prox;
        if(lista->ult == p){
         lista->ult = NULL;
        }
      }else{
        ant->prox = p->prox;
        if(p == lista->ult){
          lista->ult = ant;
        }
      }

      lista->quantidade_idosos--;
      ant =p;
      p = p->prox;
      free(ant);

    }else{
      ant = p;
      p = p->prox;
    }
  }
  return;

}

Lista_Idosos* cria_lista_idosos_de_arquivo(char * diretorio){

  FILE* apoio = fopen(diretorio, "r");
  char * linha;
  fscanf(apoio, "%m[^\n]%*c", &linha);
  char * string_aux;
  string_aux = strtok(linha, ";");
  Lista_Idosos* lista = inicia_lista_idosos();

  while(string_aux != NULL){
    Idoso* aux = inicia_idoso(string_aux);
    insere_lista_idosos(lista, aux);
    string_aux = strtok(NULL, ";");
  }
  free(linha);
    
  while(fscanf(apoio, "%m[^\n]%*c", &linha) != EOF){
    Idoso* aux1, * aux2;
    string_aux = strtok(linha,";");
    aux1  = retorna_idoso_por_nome_lista_idosos(lista, string_aux);
    string_aux = strtok(NULL,";");
    aux2 = retorna_idoso_por_nome_lista_idosos(lista, string_aux);
    faz_amizade(aux1, aux2);
    free(linha);
  }

    fclose(apoio);
    return lista;


}


void deleta_lista_idosos_e_idosos(Lista_Idosos* lista){
  if(!lista)
    return;
  Celula_Idoso* p, * ant;
  p = lista->prim;
  
  while(p!= NULL){
    ant = p;
    p = p->prox;
    deleta_idoso(ant->idoso);
    free(ant);
  }
  free(lista);
  return;

}


void atualiza_lista_idosos(Lista_Idosos* lista){

  if(lista->quantidade_idosos ==0 ){
    return;
  }

  Celula_Idoso * p = lista->prim;
  while(p != NULL){
    atualiza_idoso(p->idoso);
    p = p->prox;
  }
}


void escreve_dados_saida_lista_idosos(Lista_Idosos* lista){
  if(lista->quantidade_idosos ==0 ){
    return;
  }

  Celula_Idoso * p = lista->prim;
  while(p != NULL){
    escreve_dados_saida_idoso(p->idoso);
    p = p->prox;
  }

}


Idoso* retira_primeiro_idoso_morto_lista_idosos(Lista_Idosos* lista){
  if(lista->quantidade_idosos ==0){
    return NULL;
  }
  Celula_Idoso* p, * ant;
  ant = NULL;
  p = lista->prim;

  while(p!=NULL){
    if(verifica_morte(p->idoso)){
      break;
    }
    ant = p;
    p = p->prox;
  }

  if(p == NULL){
    printf("\nnao há idosos mortos\n");
    return NULL;
  }

    if(p == lista->prim){
      lista->prim = p->prox;
      if(lista->ult == p){
        lista->ult = NULL;
      }
    }else{
      ant->prox = p->prox;
      if(p == lista->ult){
        lista->ult = ant;
      }
    }

  Idoso* aux = p->idoso;
  free(p);
  lista->quantidade_idosos--;
  return aux;

  

}