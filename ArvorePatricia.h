#ifndef ARVOREPATRICIA_H
#define ARVOREPATRICIA_H

#include "Lista.h"

#define TAM_MAX 47
#define Alfabeto 36


typedef struct arvore{
  int modo;// Modo 0 : Nó Tipo PALAVRA
  		  //  Modo 1 : Nó Tipo LÓGICO
  int pos;//Posição de divergência
  char palavra[TAM_MAX];
  Lista * indice;// Lista de Ocorrências

  struct arvore * filhos[Alfabeto+1];

}Arvore;

Arvore * criarArvore(char * palavra, int modo );
int matchPalavra(char * a, char * b);
int getFilho(char * palavra, int posicao);
Arvore * findPalavra(Arvore * patricia, char * palavra );
void associaFilho(Arvore ** pai, Arvore * filho);
void inserirArvore(Arvore ** patricia, char * palavra, int id);
void printArvore(Arvore * patricia);
void printArvoreNivel(Arvore * patricia);

#endif