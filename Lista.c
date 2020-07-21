#include <stdlib.h>
#include <stdio.h>

typedef struct nolista{
	int id;// ID do arquivo
	int contador;//Ocorrências da Palavra no Arquivo 
	struct nolista * prox;
}noLista;

typedef struct lista{	
	noLista * IncideInvertido; 
}Lista;

Lista * criarLista(){
	// Aloca espaço e seta o ponteiro IncideInvertido para NULL
	Lista * list = (Lista * ) malloc(sizeof(Lista));	
	list->IncideInvertido =  NULL;
	return list;
}
noLista * buscarLista(Lista * list,int id){
	// Faz a busca pelo ID || Retorna NULL se não encontrar
	noLista * p = list->IncideInvertido;
	while(p != NULL && id != p->id){
		p = p->prox;
	}
	return p;
}
void printLista(Lista * list){
	for(noLista * p = list->IncideInvertido; p != NULL; p = p->prox){
		printf("%d %d ", p->contador, p->id);
	}
}

void appendLista(Lista ** list, int id){
	// Faz a busca pelo ID
	noLista * temp = buscarLista(*list,id), * ant = NULL;	
	if(temp == NULL){// Se não encontrar faz a inserção Ordenada pelo ID
		temp = (noLista *) malloc(sizeof(noLista));
		if(temp != NULL){
			temp->id = id;
			temp->contador = 1;
			temp->prox = NULL;
			if((*list)->IncideInvertido == NULL){// Se a Lista Estiver Vazia
				(*list)->IncideInvertido = temp;
			}else{// Inserção Geral			
				for(noLista * p = (*list)->IncideInvertido; p != NULL && p->id < id; p = p->prox)//Percorre a lista Pa
					ant = p;

				if(ant == NULL){
					temp->prox = (*list)->IncideInvertido;
					(*list)->IncideInvertido = temp;
				}else{
					temp->prox = ant->prox;
					ant->prox = temp;
				}

			}
		}
	}else{
		temp->contador++;

	}
}
