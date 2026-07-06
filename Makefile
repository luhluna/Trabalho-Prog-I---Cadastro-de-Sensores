CC = gcc
DEL = rm
SRC = ./src
OBJS = ./objs

TARGET = programa_sensores

all: objetos
	$(CC) $(OBJS)/main.o $(OBJS)/menus.o $(OBJS)/cadastros.o $(OBJS)/relatorios.o $(OBJS)/utils.o $(OBJS)/pesquisas.o -o $(TARGET)

objetos:
	$(CC) -c $(SRC)/menus.c -o $(OBJS)/menus.o
	$(CC) -c $(SRC)/cadastros.c -o $(OBJS)/cadastros.o 
	$(CC) -c $(SRC)/utils.c -o $(OBJS)/utils.o
	$(CC) -c $(SRC)/relatorios.c -o $(OBJS)/relatorios.o
	$(CC) -c $(SRC)/pesquisas.c -o $(OBJS)/pesquisas.o
	$(CC) -c main.c -o $(OBJS)/main.o

limpar:
	$(DEL) $(OBJS)/*.o
	$(DEL) $(TARGET)