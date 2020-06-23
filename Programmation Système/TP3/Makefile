#
# Ce Makefile contient les cibles suivantes :
#
# all      : compile le programme
# clean    : supprime les fichiers générés automatiquement
# memcheck : lance un test d'utilisation de la mémoire

.PHONY: all memcheck clean


CFLAGS = -g -Wall -Wextra -Werror -Wvla # obligatoires

PROGS = chronos

all: $(PROGS)

chronos: chronos.o table.o
chronos.o: chronos.c table.h
table.o: table.c table.h

VGOPTS=--show-leak-kinds=all
memcheck: chronos
	sleep 10 | \
	valgrind --leak-check=full $(VGOPTS) --error-exitcode=100 \
	./chronos sujet.table

clean:
	rm -f $(PROGS) chronos.o table.o
