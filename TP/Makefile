#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa main.cpp
# Autor		: Junio veras de Jesus Lima
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		    : make cleanW ou cleanL - remove objetos e executável
#---------------------------------------------------------------------

CC = g++
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/estrutura.o $(OBJ)/main.o
HDRS = $(INC)/estrutura.h
CFLAGS = -Wall -c -I $(INC)

EXE = $(BIN)/tp01.exe

all: $(EXE)
	
$(EXE): $(OBJS)
	$(CC) -o $(BIN)/tp01.exe $(OBJS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/estrutura.o: $(HDRS) $(SRC)/estrutura.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/estrutura.o $(SRC)/estrutura.cpp

cleanW:
	del $(OBJ) *.o
	del $(BIN) tp01.exe

cleanL:
	rm $(OBJ)/*.o
	rm $(BIN)/*