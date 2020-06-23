#
# Ce Makefile contient les cibles suivantes :
#
# all      : compile le programme
# clean    : supprime les fichiers générés automatiquement
# test     : lance tous les tests de comportement
# memcheck : lance un test d'utilisation de la mémoire

CFLAGS = -g -Wall -Wextra -Werror -Wvla # obligatoires

PROGS = backup

all: $(PROGS)

test: $(PROG)
	./test-100.sh 1 2 3 4

memcheck: $(PROG)
	./test-100.sh 5

clean:
	rm -f $(PROGS)
