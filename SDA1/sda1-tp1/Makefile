.PHONY: all dist clean distclean doc

NAME ?= $(shell basename $(shell pwd))
CFLAGS ?= -O3 -march=native -g3 -ggdb
override CFLAGS += -std=gnu11 -pedantic -pedantic-errors \
		-Wall -Wextra \
		-Wdouble-promotion -Wformat=2 -Winit-self -Wswitch-default \
		-Wswitch-enum -Wunused-parameter -Wuninitialized -Wfloat-equal \
		-Wshadow -Wunsafe-loop-optimizations -Wundef -Wbad-function-cast \
		-Wcast-qual -Wcast-align -Wwrite-strings -Wconversion \
		-Wjump-misses-init -Wlogical-op -Wstrict-prototypes \
		-Wold-style-definition -Wmissing-prototypes -Wmissing-declarations \
		-Wredundant-decls -Wnested-externs
# D'autres warnings intéressants (en général, certains sont inutiles dans ce
# cas particulier) mais pas encore reconnus par la version de GCC disponible
# sur une Ubuntu 14.04... :
#
# -Wmissing-include-dirs -Wnull-dereference -Wswitch-bool -Wduplicated-cond
# -Wdate-time

EXEC = fonctionnel mutation
TEST_ENORME=jeutest6_enorme.txt
all: $(EXEC) tests/$(TEST_ENORME)

# Programmes principaux (par défaut)
fonctionnel: fonctionnel.o files_fct.o
mutation: mutation.o files_mut.o

# Génère un fichier de test énorme.
# (On le stocke dans /tmp pour soulager les accès disques, surtout s'il s'agit
# de disques réseau...)
#
# Mettre TAILLE_MAX à 100000 pour mesurer le temps:
#   $ make clean
#   $ make CPPFLAGS='-DTAILLE_MAX=100000'
tests/$(TEST_ENORME):
	$(RM) -r /tmp/$(TEST_ENORME)
	for i in `seq 1 1000`; do cat tests/jeutest5_1000.txt >>/tmp/$(TEST_ENORME); done
	ln -sf "/tmp/$(TEST_ENORME)" "$@"

# Documentation
doc:
	doxygen Doxyfile.fct
	doxygen Doxyfile.mut

# Archive
dist:
	tar -czf $(NAME).tar.gz --transform="s,^,$(NAME)/," \
		*.c *.h Makefile Doxyfile.* tests/*.txt resultats/*.txt

# Nettoyages
clean:
	$(RM) -r $(EXEC) *.o html* "$(TEST_ENORME)"
distclean: clean
	$(RM) *.tar.gz

# Dépendances avec les en-têtes
fonctionnel.o: fonctionnel.c files_fct.h sorte.h cli.h
files_fct.o: files_fct.c files_fct.h sorte.h util.h
mutation.o: mutation.c files_mut.h sorte.h cli.h
files_mut.o: files_mut.c files_mut.h sorte.h util.h
