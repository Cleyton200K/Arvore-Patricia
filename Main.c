#include <stdio.h>
#include <stdlib.h>
#include "ArvorePatricia.h"
#include "Leitura.h"

int main(){
  Arvore * patricia = NULL;
  read("ArquivoPrincipal.txt",&patricia);
  printArvore(patricia);
  printArvoreNivel(patricia);
  return 0;
}
