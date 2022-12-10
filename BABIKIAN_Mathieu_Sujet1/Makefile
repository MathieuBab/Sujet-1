### variables ###
CC = gcc # compilateur
CFLAGS = -Wall # option de compilation
EXEC = main # exécutable
SRC = $(wildcard *.c) # contient la liste des fichiers sources .c
LIB = $(wildcard *.h) # contient la liste des fichiers fichiers .h
DATA = $(wildcard *.csv) # contient la liste des fichiers fichiers .csv
OBJ = $(SRC:.c=.o) # contient la liste des fichiers objets en fonction des fichiers sources .c 


### variables spéciales ###
# $@ nom de l'option
# $< première dépendance
# $^ liste des dépendances


### cibles ###

# Cible pour exécuter l'exécutable
all: $(EXEC)
	./$(EXEC)

# Cible pour créer les fichiers objets
%.o : %.c
	$(CC) -c $< -o $@

# Cible pour compiler l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Cible pour compresser le TP
tar:
	tar -zcvf Babikian_Mathieu_Sujet1.tar.gz $(SRC) $(LIB) $(DATA) Makefile Readme.txt

# .PHONY permet d'ignorer un potentiel fichier "clean" pour que l'on puisse utiliser l'option qui suit
.PHONY : clean
# Cible pour supprimer tous les fichiers objet
clean :
	rm -rf *.o
# Cible pour supprimer tous les fichiers objet puis l'exécutable
mrproper : clean
	rm -rf main



