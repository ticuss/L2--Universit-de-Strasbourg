.PHONY: all dist clean distclean doc

NAME ?= $(shell basename $(shell pwd))
CFLAGS ?= -std=gnu11 -pedantic -O3 -march=native -g3 -ggdb -Wall -Wextra \
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

EXEC = chaine chaine-optimisee
JEU_TEST = jeuessai1.txt
JEU_TEST_TMP = /tmp/$(USER)-$(JEU_TEST)
all: $(EXEC) $(JEU_TEST)

# Programmes principaux (par défaut)
chaine: main.o file_chaine.o
	$(CC) $^ -o $@
chaine-optimisee: main.o file_chaine_optimisee.o
	$(CC) $^ -o $@

$(JEU_TEST_TMP):
	rm -rf "$@"
	for i in `seq 1 10000`; do printf "ajoute $$i\netat\n" >>"$@"; done
	for i in `seq 1 10000`; do printf "suppr\netat\n" >>"$@"; done
	echo "quit" >>"$@"

$(JEU_TEST): $(JEU_TEST_TMP)
	ln -sf "$<" "$@"

# Documentation
doc:
	doxygen Doxyfile

# Archive
dist:
	tar -czf $(NAME).tar.gz --transform="s,^,$(NAME)/," \
		*.c *.h Makefile Doxyfile

# Nettoyage
clean:
	$(RM) -r $(EXEC) *.o doc $(JEU_TEST) $(JEU_TEST_TMP)
distclean: clean
	$(RM) *.tar.gz

# Dépendances avec les en-têtes
main.o: file.h sorte.h cli.h util.h
file_chaine.o: file_chaine.c file.h sorte.h
file_chaine_optimisee.o: file_chaine_optimisee.c file.h sorte.h
