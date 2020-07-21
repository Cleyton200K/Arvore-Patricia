#include <stdio.h>
#include <stdlib.h>

#include "ArvorePatricia.h"

#define ML 101

void read(char * arquivo, Arvore ** patricia) {
	// Lê o arquivo RAIZ e armazena os valores em um vetor
	// Primeira linha diz quantos arquivos são
	// As próximas N linhas são os nomes dos arquivos
    int i, N, valido = 1;
    FILE *arq = fopen(arquivo,"r");
    if(arq!=NULL){
        fscanf(arq, "%d\n", &N);   // Lê o número de arquivos e cria um vetor com esse tamanho
        char vet[N][101];
        for(i=0; i<N; i++)   // Lê a linha, pega o nome e insere no vetor
            fscanf(arq, "%s\n", vet[i]);
        fclose(arq);
        // Abre cada arquivo, lê caractere por caractere
        // identificando as palavras e inserindo na Árvore PATRICIA
        for(int a = 0; a<N; a++){
            FILE* arqn = fopen(vet[a], "r");
            if(arqn!=NULL){
                int j = 0;
                char c, palavra[TAM_MAX];
                while(fscanf(arqn, "%c", &c) != EOF && j<=TAM_MAX){
                    if(c > 64 && c < 91)  //   Trasforma letras maiúsculas em minúsculas
                        c += 32;

                    if(c > 96 && c < 123){  // Insere o caractere no vetor, formando a palavra
                        palavra[j]=c;
                        j++;
                    }
                    else if(c >= '0' && c <= '9'){// Trata a exceção de números em uma palavra e a INVALIDA 
                        valido = 0;
                        printf("%d\n", valido);
                    }
                    else{
                        if(palavra[0] != '\0'){
                            palavra[j] = '\0';
                            //printf("%s\n",palavra);
                            if(valido == 1){
                                inserirArvore(patricia, palavra, a+1);    // Chama a função de inserção na Árvore
                            }
                            else{
                                valido = 1;
                                printf("Palavra Inválida : %s\n", palavra);
                            }
                            j=0;                                      
                            palavra[j] = '\0';
                        }
                    }
                }
                if(j > 0){
                    palavra[j] = '\0';
                    inserirArvore(patricia, palavra, a+1);
                }
                fclose(arqn);
            }
            else{
                printf("Erro ao abrir o arquivo %s\n", vet[a]);                
            }
        }
    }
    else{
        printf("Erro ao abrir o arquivo principal.\n");
        exit(1);
    }

}