#ifndef LISTA_H
#define LISTA_H

typedef struct nolista{
	int id;
	int contador;
	struct nolista * prox;
}noLista;

typedef struct lista{
	int contador;
	noLista * prim, * ult;
}Lista;

Lista * criarLista();
void printLista(Lista * list);
noLista * buscarLista(Lista * list,int id);
void appendLista(Lista ** list, int id);

#endif 