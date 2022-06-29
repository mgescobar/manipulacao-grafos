#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/*
################################################################################
#                                FILA                                          #
################################################################################
*/

void erro(char msg[]){
     printf("%s", msg);
     getchar();
     exit(0);     
}

Fila* novaFila(){
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->tamanho = 0;
    f->inicio = 0;
    return f;
}

bool cheia(Fila* f)
{
	return f->tamanho == N;
}

bool vazia(Fila* f)
{ 
	return f->tamanho == 0;
}

void printElemento(Fila* f, int i) {
	printf("Elemento na pos %d , valor: %d\n", i, f->data[i]);
}

void print(Fila* f){
		printf("***********************************************\n");
		int fim = (f->inicio + f->tamanho) % N;
		printf("Fila=[inicio=%d, fim=%d]\n",f->inicio, fim);
		if (fim >= f->inicio)
			for (int i = f->inicio; i < fim; i++)
				printElemento(f, i);
		else {
			for (int i = f->inicio; i < N; i++)
				printElemento(f, i);
			for (int i = 0; i < fim; i++)
				printElemento(f, i);
		}
		printf(" ");     
}

void nafila(Fila* f, int elemento){
     printf("Inserindo %d\n", elemento);
     if (cheia(f))
        erro("Fila Cheia\n");
     int fim = (f->inicio + f->tamanho) % N;
     f->data[fim] = elemento;
     f->tamanho++;
}

int foradafila(Fila* f){ 
		if (vazia(f))
			erro("Erro: Tentando remover da fila vazia...\n");
		int temp = f->data[f->inicio];
		printf("Removendo %d\n", temp);
		f->inicio = (f->inicio + 1) % N;
		f->tamanho--;
		return temp;    
}

int frente(Fila* f){ 
		if (vazia(f))
			erro("Erro: Tentando obter a frente da fila vazia...\n");
		return f->data[f->inicio];
}


/*
################################################################################
#                                LISTA                                         #
################################################################################
*/

bool listaVazia(Lista* lista){
  return (lista == NULL);
}

Lista* ultimo(Lista* lista){
  Lista* ultimo = lista;
  while (!listaVazia(ultimo) && !listaVazia(ultimo->prox))
    ultimo = ultimo->prox;
  return ultimo;
}

Lista* criarLista(){
  return NULL;
}

Lista* addInicio(Lista* lista, void* elemento){
  Lista* novo = (Lista*)malloc(sizeof(Lista));
  novo->info = elemento;
  novo->prox = lista;
  return novo;
}

Lista* addFim(Lista* lista, void* elemento){
  if(!listaVazia(lista))
    ultimo(lista)->prox = addInicio(NULL, elemento);
  return listaVazia(lista) ? addInicio(NULL, elemento) : lista;
}


Lista* retirar(Lista* lista, void* elemento, bool iguais(void*, void*))
{
   Lista* anterior = NULL;
   Lista* temp = lista;
   while(!listaVazia(temp) && !iguais(temp->info, elemento)){
      anterior = temp;
      temp = temp->prox;
   }
   if (listaVazia(temp))
      return lista;
   if (anterior == NULL)
      lista = temp->prox;
   else
      anterior->prox = temp->prox;
   free(temp);
   return lista;
}


void imprimirLista(Lista* lista, void imprimirElemento(void*)){
  if(listaVazia(lista)){
  	printf("lista vazia\n\n");
  }
  while(!listaVazia(lista)){
    	imprimirElemento(lista->info);
    lista = lista->prox;
  }
}

void* buscar(Lista* lista, void* elemento, bool iguais(void*, void*)){
   Lista* temp = lista;
   while(temp != NULL){
      if (iguais(temp->info, elemento))
      	 return temp->info;
      temp = temp->prox;
   }
   return NULL;
}

Lista* liberar(Lista* lista){
   while(!listaVazia(lista)){
      Lista* temp = lista->prox;
      free(lista);
      lista = temp;
   }
   return NULL;
}
