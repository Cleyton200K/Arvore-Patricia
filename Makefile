#Objetos que compoem o Arquivo
OBJS = Main.c ArvorePatricia.c ArvorePatricia.h Lista.c Lista.h Leitura.c Leitura.h

#Compilador utilizado
CC = gcc

#Nome do Executável
OBJ_NAME = IndiceInvertido

#Copilamos o Executável aqui
all : $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME)