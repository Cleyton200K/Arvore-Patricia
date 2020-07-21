#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

#define TAM_MAX 47
#define Alfabeto 26


typedef struct arvore{
  int modo; // Modo 0 : Nó Tipo PALAVRA
  		     //  Modo 1 : Nó Tipo LÓGICO
  int pos;//   Posição de divergência
  char palavra[TAM_MAX];
  Lista * indiceInvertido;// Lista de Ocorrências

  struct arvore * filhos[Alfabeto+1];

}Arvore;


Arvore * criarArvore(char * palavra, int modo ){
  //Aloca espaço e seta algumas definições gerais de um Nó Árvore Patricia
  Arvore * patricia = (Arvore * ) (malloc(sizeof(Arvore)));
  if(patricia != NULL){
	  patricia->modo = modo;
	  strcpy(patricia->palavra, palavra);	  
	  for(int i = 0; i <= Alfabeto; i++)
	    patricia->filhos[i] = NULL;
    return patricia;
  }else{
    printf("Não foi possível Alocar Memória...\n");
    exit(1);
  }
}
int matchPalavra(char * a, char * b){  
  //Compara as Palavras e retorna a posição carácter onde divergem
  //Ou o fim de ambas, se forem Iguais
  int i = 0 ;
  while(a[i] == b[i] && a[i] != '\0' && b[i] != '\0')
    i++;  
  return i;
}
int getFilho(char * palavra, int posicao){
  //Trata a exceção do \0  
	int buscar = Alfabeto;
  	if(palavra[posicao] != '\0')  
    	buscar = palavra[posicao] - 97;
    return buscar;
}

Arvore * findPalavra(Arvore * patricia, char * palavra ){    
  if(patricia == NULL){  	
  	return NULL;//A palavra não está na Árvore
  }else{
    if(patricia->modo){  		
  		int posicao = matchPalavra(palavra, patricia->palavra);//Comparamos a palavra com Nó

    	if(posicao == patricia->pos)//verifica se a palavra tem o mesmo PREFIXO que os filhos deste nó lógico 
    		findPalavra(patricia->filhos[getFilho(palavra, posicao)], palavra);

    	else// Senão retorna NULL, palavra não está na Árvore
    		return NULL;
    }else    	
    	return patricia;//Palvra encontrada
  }  
}

void associaFilho(Arvore ** pai, Arvore * filho){
  //Associa um Ramo da àrvore (PAI)
  //A folha novaPalavra (FILHO)
  (*pai)->filhos[getFilho(filho->palavra, (*pai)->pos)] = filho;
}

void inserirArvore(Arvore ** patricia, char * palavra, int id){
	Arvore * novaPalavra, * novoLogico;
	if((*patricia) == NULL){
		//Cria e insere uma Nó Árvore Tipo Palavra
		novaPalavra = criarArvore(palavra,0);
		if(novaPalavra != NULL){
			novaPalavra->indiceInvertido = criarLista(); 
			appendLista(&(novaPalavra->indiceInvertido), id);
		}  		
		*patricia = novaPalavra;

	}else{
		int posicao = matchPalavra((*patricia)->palavra, palavra);// Faz a comparação com o PREFIXO  se o Nó atual é Lógico, ou se for Tipo Palavra pega a divergência
		if((*patricia)->modo){
			if(posicao != (*patricia)->pos){//Se A posição for dirente, Significa queO PREFIXO deste Nó Lógico não satifaz a Palavra
				novoLogico = criarArvore(palavra,1);//Portanto, cria-se um novo Nó Lógico que bifurca entre a palavra sendo inserida e o Nó mais abaixo
				if(novoLogico != NULL){
					novoLogico->palavra[posicao] = '\0';
					novoLogico->pos = posicao;
				}
				novoLogico->filhos[getFilho((*patricia)->palavra, posicao)] = *patricia;
				*patricia = novoLogico;
			}
			inserirArvore(&((*patricia)->filhos[getFilho(palavra,posicao)]), palavra, id);
		
		}else{// Aqui o Nó atual é do tipo PALAVRA
			if(palavra[posicao] == (*patricia)->palavra[posicao]){//Verifica se a o carácter de DIVERGÊNCIA entre a Palavra sendo inserida, e a palavra do Nó atual, são Iguais
				//Isso é um absurdo, portanto as palavras são iguais, então apenas incrementa-se o indiceInvertido
				appendLista(&((*patricia)->indiceInvertido), id);
			}else{//Se não Um Nó Lógico é feito, e aponta para as duas Palavras
				novaPalavra = criarArvore((*patricia)->palavra,0);
				if(novaPalavra != NULL)				
					novaPalavra->indiceInvertido = (*patricia)->indiceInvertido;
				(*patricia)->palavra[posicao] = '\0';
				(*patricia)->modo = 1;
				(*patricia)->pos = posicao;
				(*patricia)->indiceInvertido = NULL;
				associaFilho(patricia,novaPalavra);
				inserirArvore(&((*patricia)->filhos[getFilho(palavra,posicao)]), palavra, id);
			}	
		}
	}
 
}
void printArvoreNivel(Arvore * patricia){
  //Impressão Mostrando os níveis da Árvore  
  if(patricia->modo){   
    printf("Posicao %d :  <", patricia->pos);
    for(int i = 0; i <= Alfabeto; i++)
      if(patricia->filhos[i] != NULL){  
        printf(" <");
        printArvoreNivel(patricia->filhos[i]);  
        printf("> ");
      }    
      printf("> ");     
  }else{
    printf("%s",patricia->palavra);
  }
}
void printArvore(Arvore * patricia){
  //Impressão do Indice  
  if(patricia->modo){    
    for(int i = 0; i <= Alfabeto; i++)
      if(patricia->filhos[i] != NULL)    
        printArvore(patricia->filhos[i]);    
     
  }else{
    printf("%s ",patricia->palavra);
    printLista(patricia->indiceInvertido);
    printf("\n");
  }
}