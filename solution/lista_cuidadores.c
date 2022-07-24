#include "lista_cuidadores.h"
#include "lista_idosos.h"
#include "cuidador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula_cuidador Celula_Cuidador;

struct celula_cuidador{
    Cuidador* cuidador;
    Celula_Cuidador* prox;
};

struct lista_cuidadores{
    Celula_Cuidador* prim;
    Celula_Cuidador* ult;
    int quantidade_cuidadores;
};

Lista_Cuidadores* inicia_lista_cuidadores(void){

    Lista_Cuidadores* lista = (Lista_Cuidadores*)malloc(sizeof(Lista_Cuidadores));
    if(!lista){
        printf("\nerro de alocação em inicia_lista_cuidadores\n");
        return NULL;
    }
    lista->prim = NULL;
    lista->ult = NULL;
    lista->quantidade_cuidadores= 0;

    return lista;

}


void imprime_lista_cuidadores(Lista_Cuidadores* lista){
    
    if(lista == NULL){
      return;
    }
    printf("\nIMPRIMINDO LISTA:\n");
    Celula_Cuidador* p = lista->prim;
    while(p != NULL){
      imprime_cuidador(p->cuidador);
      printf("\n");
      p = p->prox;
    }
  return;
  
}


void insere_lista_cuidadores(Lista_Cuidadores* lista, Cuidador* cuidador){

  Celula_Cuidador* nova = (Celula_Cuidador*)malloc(sizeof(Celula_Cuidador));
  if(nova == NULL){
    printf("erro na alocação insere lista");
    return;
  }
  nova->cuidador = cuidador;
  nova->prox = NULL;

  if(lista->ult == NULL){
    lista->prim = nova;
  }else{
    lista->ult->prox = nova;
  }
  lista->ult = nova;
  lista->quantidade_cuidadores++;
  return;
}


Cuidador* remove_lista_cuidadores(Lista_Cuidadores* lista, char* nome){
  
  Celula_Cuidador* p, * ant;
  ant = NULL;
  p = lista->prim;

  while(p!=NULL){
    if(strcmp(retorna_nome_cuidador(p->cuidador), nome) ==0){
      break;
    }
    ant = p;
    p = p->prox;
  }

  if(p == NULL){
    printf("\nerro, esse cuidador nao esta na lista\n");
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

  Cuidador* aux = p->cuidador;
  free(p);
  lista->quantidade_cuidadores--;
  
  return aux;
  
}


void deleta_lista_cuidadores(Lista_Cuidadores* lista){
  
  if(!lista)
    return;
  Celula_Cuidador* p, * ant;
  p = lista->prim;
  
  while(p!= NULL){
    ant = p;
    p = p->prox;
    free(ant);
  }
  free(lista);
  return;
}

int retorna_tamanho_lista_cuidadores(Lista_Cuidadores* lista){
  return (lista->quantidade_cuidadores);
}



Cuidador* retorna_cuidador_posicao_lista_cuidadores(Lista_Cuidadores* lista, int pos){
  
  if(pos > lista->quantidade_cuidadores -1 || lista->quantidade_cuidadores == 0 || pos < 0 )
    return NULL;

  Celula_Cuidador* p = lista->prim;
  for(int i=0; i < pos; i ++){
    p = p->prox;
  }

  return p->cuidador;

}


Lista_Cuidadores* cria_lista_cuidadores_de_arquivo(char * diretorio, Lista_Idosos* idosos){
  FILE* cuidadores_txt = fopen(diretorio, "r");

  Lista_Cuidadores* lista = inicia_lista_cuidadores();


  char * linha;
  fscanf(cuidadores_txt,"%m[^\n]%*c", &linha);
  char * string_aux;
  string_aux = strtok(linha, ";");
  FILE* teste = fopen("ola.txt", "w");
  while(string_aux!=NULL){
    fprintf(teste,"%s\n", string_aux);
    Cuidador* aux = inicia_cuidador(string_aux);
    insere_lista_cuidadores(lista,aux);
    string_aux = strtok(NULL, ";");
  }
  fclose(teste);
  free(linha);
  
  while(fscanf(cuidadores_txt,"%m[^\n]%*c", &linha) != EOF){
    
    string_aux = strtok(linha, ";");
    Idoso* idoso_aux = retorna_idoso_por_nome_lista_idosos(idosos, string_aux);
    while(1){

      string_aux = strtok(NULL, ";");
      if(!string_aux){
        break;
      }
      Cuidador* cuidador = retorna_cuidador_por_nome_lista_cuidadores(lista, string_aux);
      adiciona_cuidador_idoso(idoso_aux, cuidador);

    }
    free(linha);
  }
  fclose(cuidadores_txt);
  return lista;
}


void deleta_lista_cuidadores_e_cuidadores(Lista_Cuidadores* lista){
  if(!lista)
    return;
  Celula_Cuidador* p, * ant;
  p = lista->prim;
  
  while(p!= NULL){
    ant = p;
    p = p->prox;
    deleta_cuidador(ant->cuidador);
    free(ant);
  }

  free(lista);
  return;
}

Cuidador* retorna_cuidador_por_nome_lista_cuidadores(Lista_Cuidadores* lista, char * nome){
  Celula_Cuidador* p = lista->prim;
  if(lista->quantidade_cuidadores ==0 ){
    return NULL;
  }

  while(p!= NULL){
    if(strcmp(retorna_nome_cuidador(p->cuidador), nome) ==0 ){
      return (p->cuidador);
    }
    p = p->prox;
  }
  return NULL;
}


void atualiza_lista_cuidadores(Lista_Cuidadores* lista){
  if(lista->quantidade_cuidadores ==0 ){
    return;
  }
  Celula_Cuidador* p= lista->prim;
  while(p != NULL){
    atualiza_cuidador(p->cuidador);
    p = p->prox;
  }
  

}