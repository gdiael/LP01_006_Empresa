# Arquivo de Script Makefile
# 
# Aula de LP1 2018.2
# 20/09/2018
# Clonagem atual para teste :
# 				git clone https://github.com/gdiael/LP01_003_corridaSapos.git
#
# Gdiael Souto Barros
#

CC = g++

OBJ = ./build
SRC = ./src
BIN = ./bin
INC = ./include

F01 = funcionario
F02 = empresa
F03 = main

PROG1 = $(BIN)/Empresa

CPPFLAGS = -Wall -pedantic -std=c++11 -I$(INC)

OBJ1 = $(OBJ)/$(F01).o $(OBJ)/$(F02).o $(OBJ)/$(F03).o
OBJ2 = $(SRC)/$(F01).cpp $(SRC)/$(F02).cpp $(SRC)/$(F03).cpp

all: mkdirs $(PROG1)

mkdirs:
	mkdir -p $(BIN)
	mkdir -p $(OBJ)

$(PROG1): $(OBJ1)
	$(CC) $(CPPFLAGS) -o $(PROG1) $(OBJ1)

db$(PROG1): $(OBJ2)
	$(CC) -g $(CPPFLAGS) -o $(PROG1) $(OBJ2)

$(OBJ)/$(F01).o: $(SRC)/$(F01).cpp $(INC)/$(F01).h
	$(CC) $(CPPFLAGS) -c $(SRC)/$(F01).cpp -o $(OBJ)/$(F01).o

$(OBJ)/$(F02).o: $(SRC)/$(F02).cpp $(INC)/$(F02).h $(INC)/$(F01).h
	$(CC) $(CPPFLAGS) -c $(SRC)/$(F02).cpp -o $(OBJ)/$(F02).o

$(OBJ)/$(F03).o: $(SRC)/$(F03).cpp $(INC)/$(F01).h $(INC)/$(F02).h
	$(CC) $(CPPFLAGS) -c $(SRC)/$(F03).cpp -o $(OBJ)/$(F03).o

clean: 
	rm -f $(BIN)/*
	rm -f $(OBJ)/*

debug: db$(PROG1)
	gdb $(PROG1)

run: all
	$(PROG1)