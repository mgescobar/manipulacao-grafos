#include<stdbool.h>

#define N 10

typedef struct lista{
  void* info;
  struct lista* prox;
}Lista;


typedef struct fila{
     int data[N]; 
     int tamanho;
     int inicio;
}Fila;

// Alloca e retorna a fila criada
Fila* criarFila();

// Exita caso encontre um erro na mensagem
void erro(char msg[]);

// Insere um elemento na fila
void nafila(Fila* f, int elemento);

// Booleanos que retorna o estado da fila
bool cheia(Fila* f);
bool vazia(Fila* f);

// Retira elemento da fila
int foradafila(Fila* f);

// Imprime um elemento da fila
void printElemento(Fila *f, int i);

// Imprime a estrutura da fila na tela
void print(Fila* f);

// Retorna inicio da fila
int frente(Fila* f);

// Booleano que retorna estado da lista
bool listaVazia(Lista* lista);

// Cria uma nova lista e a retorna
Lista* criarLista();

// Insere inicio da lista
Lista* addInicio(Lista* lista, void* elemento);

// Insere fim da lista
Lista* addFim(Lista* lista, void* elemento);

// Retira elemento iguais da lista com auxilio de uma lista temporaria
// e após isso retorna nova lista organizada
Lista* retirar(Lista* lista, void* elemento, bool iguais(void*, void*));

// Realiza impressão da lista por completo
void imprimirLista(Lista* lista, void imprimirElemento(void*));

// Realiza busca no elemento da lista
void* buscar(Lista* lista, void* elemento, bool iguais(void*, void*));
