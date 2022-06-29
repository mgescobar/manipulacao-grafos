/*
################################################################################
#                                INCLUSÕES                                     #
################################################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"


/*
################################################################################
#                                DEFINIÇÕES                                    #
################################################################################
*/

typedef struct grafo{
   	Lista* vertices;
   	Lista* visitados;
}Grafo;

typedef struct Vertice{
	int numero;
   	Lista* verticesAdjacentes;
   	bool visitado;
}Vertice;


/*
################################################################################
#                                FUNÇÕES AUX                                   #
################################################################################
*/

Grafo* criarGrafo(){
	Grafo* g = (Grafo*) malloc(sizeof(Grafo));
	g->vertices = criarLista();
	g->visitados = criarLista();
	return g;
}


/*Vertce*/
Vertice* criarVertice(int n){
	Vertice* v = (Vertice*) malloc(sizeof(Vertice));
	v->numero = n;
	v->verticesAdjacentes = criarLista();
	v->visitado = false;
	return v;
}

void impirmirAdjacente(void* vertice){
	printf("%d ", ((Vertice*)vertice)->numero);
}

void imprimirVertice(void* vertice){
	Vertice* v = (Vertice*)vertice;

	printf("Numero: ");
	printf("%d\n", v->numero);
	printf("Vértices Adjacentes: ");
	Lista* temp = v->verticesAdjacentes;
	while(!listaVazia(temp)){
		impirmirAdjacente(temp->info);
	temp = temp->prox;
	}
	printf("\n---------------\n");
}

void adicionarVertice(Grafo* grafo, int n){	
  	grafo->vertices = addFim(grafo->vertices, criarVertice(n));
}


bool verticesIguais(void* vertice1, void* vertice2){
  return ((Vertice*) vertice1)->numero == ((Vertice*) vertice2)->numero;
}

Vertice* buscarVertice(Lista* vertices, int numero){
   return (Vertice*) buscar(vertices, criarVertice(numero), &verticesIguais);
}

void imprimirGrafo(void* grafo){
	Grafo* g = ((Grafo*)grafo);
	imprimirLista(g->vertices, &imprimirVertice);
}

void inserirAresta(Grafo* g, int v1, int v2){
	if(buscarVertice(g->vertices, v1) == NULL || buscarVertice(g->vertices, v2) == NULL){
		printf(" um dos vertices não existe\n");
		return;
	}
	Vertice* vertice1 = buscarVertice(g->vertices, v1);
	Vertice* vertice2 = buscarVertice(g->vertices, v2);
	vertice1->verticesAdjacentes = addFim(vertice1->verticesAdjacentes, vertice2);
	//vertice2->verticesAdjacentes = addFim(vertice2->verticesAdjacentes, vertice1);
}

void removerAresta(Grafo* g, int v1, int v2){
	if(buscarVertice(g->vertices, v1) == NULL || buscarVertice(g->vertices, v2) == NULL){
		printf(" um dos vertices não existe\n");
		return;
	}
	Vertice* vertice1 = buscarVertice(g->vertices, v1);
	Vertice* vertice2 = buscarVertice(g->vertices, v2);
	vertice1->verticesAdjacentes = retirar(vertice1->verticesAdjacentes, vertice2, &verticesIguais);
	//vertice2->verticesAdjacentes = retirar(vertice2->verticesAdjacentes, vertice1, &verticesIguais);
}

void visitarSubGrafoEmProfundidade(Grafo* g, int vertice){
	Vertice* v = buscarVertice(g->vertices, vertice);
   	printf("Profundidade - CINZA: Visitando o vértice %d em pre-ordem\n", vertice);
   	v->visitado = true;
   	Lista* temp = v->verticesAdjacentes;
    while(!listaVazia(temp)){
    	Vertice* vertice = temp->info;
    	if(!vertice->visitado)
          	visitarSubGrafoEmProfundidade(g, vertice->numero);
        temp = temp->prox;
	}
   	printf("Profundidade - PRETO: Visitando o vértice %d em pos-ordem\n", vertice);
}

void visitarEmProfundidade(Grafo* g, int numero){
	Lista* lista = g->vertices;
   	while(!listaVazia(lista)){
   		Vertice* v = lista->info;
       	v->visitado = false;
       	lista = lista->prox;
   	}
   
   	Lista* temp = g->vertices;
   	while(((Vertice*)temp->info)->numero != numero){
   		temp = temp->prox;
   	}
    //while(!listaVazia(temp)){
    	Vertice* v = temp->info;
    	if(v->visitado == false)
          	visitarSubGrafoEmProfundidade(g, v->numero);
        temp = temp->prox;
	//}
}  

void visitarSubGrafoEmLargura(Grafo* g, int numero){
	Vertice* v = buscarVertice(g->vertices, numero);
	v->visitado = true;
	Fila* f = novaFila();
	nafila(f, numero);
	printf("Largura - CINZA: Visitando o vértice %d em pre-ordem\n", numero);
	while (!vazia(f)){
	  int u = foradafila(f); 
	  Vertice* v2 = buscarVertice(g->vertices, u);
	  Lista* adj = v2->verticesAdjacentes;
	  while(!listaVazia(adj)){
	  	 Vertice* v3 = adj->info;
	     if (!v3->visitado){
	         v3->visitado = true;
	         printf("Largura - CINZA: Visitando o vértice %d em pre-ordem\n", v3->numero);
	         nafila(f, v3->numero);                             
	     }
	     adj = adj->prox;
	  }
	  printf("Largura - PRETO: Visitando o vértice %d em pos-ordem\n", u);
	}
}

void visitarEmLargura(Grafo* g, int numero){
	Lista* lista = g->vertices;
   	while(!listaVazia(lista)){
   		Vertice* v = lista->info;
       	v->visitado = false;
       	lista = lista->prox;
   	}
   
   	Lista* temp = g->vertices;
   	while(((Vertice*)temp->info)->numero != numero){
   		temp = temp->prox;
   	}
    //while(!listaVazia(temp)){
    	Vertice* v = temp->info;
    	if(v->visitado == false)
          	visitarSubGrafoEmLargura(g, v->numero);
        //temp = temp->prox;
	//}
}  

/*
################################################################################
#                                MAIN                                          #
################################################################################
*/

int main(){
	int botao, n1, n2;
	Grafo* g = criarGrafo();
	
    imprimirGrafo(g);
    printf("\n");           
    adicionarVertice(g, 0);
    adicionarVertice(g, 1);
    adicionarVertice(g, 2);
    adicionarVertice(g, 3);
    adicionarVertice(g, 4);
    adicionarVertice(g, 5);
    adicionarVertice(g, 6);
    adicionarVertice(g, 7);
    adicionarVertice(g, 8);
    adicionarVertice(g, 9);
    adicionarVertice(g, 10);
    inserirAresta(g, 0, 1);
    inserirAresta(g, 0, 2);
    inserirAresta(g, 0, 3);
    inserirAresta(g, 1, 4);
    inserirAresta(g, 1, 5);
    inserirAresta(g, 2, 6);
    inserirAresta(g, 2, 7);
    inserirAresta(g, 3, 9);
    inserirAresta(g, 4, 8);
    inserirAresta(g, 8, 7);
    inserirAresta(g, 7, 5);
    inserirAresta(g, 7, 10);
    imprimirGrafo(g);
    printf("\n");
    visitarEmProfundidade(g, 0);
    printf("\n");
    visitarEmLargura(g, 0);
    printf("\n");
    

	while(1){    
		printf("1- Adicionar Vertice \n2- Adicionar Aresta \n3- Remover Aresta \n4- Imprimir Grafo \n5- Visitar em Profundidade \n6- Visitar em Largura \n7- Sair \n");
    	scanf("%d", &botao);
    	printf("\n");
	    switch(botao){
	    	case(1):
	    		printf("Número do Vértice a ser adicionado: ");
	    		scanf("%d", &n1);
	    		printf("\n");
	    		adicionarVertice(g, n1);
	    		printf("\n");
	    		break;
	    	case(2):	
	    		printf("Número do Vértice de partida: ");
	    		scanf("%d", &n1);
	    		printf("Número do Vértice de chegada: ");
	    		scanf("%d", &n2);
	    		printf("\n");
	    		inserirAresta(g, n1, n2);
	    		printf("\n");
	    		break;
	    	case(3):
	    		printf("Número do Vértice de partida: ");
	    		scanf("%d", &n1);
	    		printf("Número do Vértice de chegada: ");
	    		scanf("%d", &n2);
	    		printf("\n");
	    		removerAresta(g, n1, n2);	
	    		printf("\n");
	    		break;
	    	case(4):
	    		imprimirGrafo(g);
	    		printf("\n");
	    		break;
	    	case(5):
	    		printf("Número do Vértice de partida: ");
	    		scanf("%d", &n1);
	    		printf("\n");
	    		visitarEmProfundidade(g, n1);
	    		printf("\n");	
	    		break;
	    	case(6):
	    		printf("Número do Vértice de partida: ");
	    		scanf("%d", &n1);
	    		printf("\n");
	    		visitarEmLargura(g, n1);	
	    		printf("\n");
	    		break;
	    	case(7):
	    		exit(0);
	    	default:
	    		printf("Essa opção não existe.\n");
	    		printf("\n");
	    }
	}
}
