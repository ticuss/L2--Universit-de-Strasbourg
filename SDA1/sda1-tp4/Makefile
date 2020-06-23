.PHONY: all dist clean distclean doc

################################################################################
# Variables diverses
################################################################################

NAME ?= $(shell basename $(shell pwd))
FILES = *.c *.h Makefile Doxyfile .clang-format .gitignore
EXEC = jeu test_liste

################################################################################
# Options et flags de compilation
################################################################################

CFLAGS ?= -O3 -march=native -g3 -ggdb
LDLIBS ?= -lcurses

override CFLAGS += -std=gnu11 -pedantic -pedantic-errors \
		-Wall -Wextra \
		-Wdouble-promotion -Wformat=2 -Winit-self -Wswitch-default \
		-Wswitch-enum -Wunused-parameter -Wuninitialized -Wfloat-equal \
		-Wshadow -Wundef -Wbad-function-cast -Wcast-qual -Wcast-align \
		-Wwrite-strings -Wconversion -Wstrict-prototypes \
		-Wold-style-definition -Wmissing-prototypes -Wmissing-declarations \
		-Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
		-Wnull-dereference -Wswitch-bool -Wdate-time
# D'autres warnings intéressants, dans certains cas, mais pas reconnus par
# clang:
#
#   -Wunsafe-loop-optimizations -Wjump-misses-init -Wlogical-op
#   -Wduplicated-cond

################################################################################
# Cibles « standard » et cibles bonus
################################################################################

all: $(EXEC)

# Documentation
doc:
	doxygen Doxyfile

# Création de l'archive... On souhaite qu'il y ait un répertoire racine dans
# l'archive. Ne pas oublier d'utiliser $(USER) dans les chemins pour les
# systèmes multi-utilisateurs...
#
# La ligne suivante suffirait si on pouvait être sûr que la variante tar
# utilisée est GNU tar... (par exemple, BSD tar ne reconnaît pas --transform)
#
#   tar -czf "$(NAME).tar.gz" --transform="s,^,$(NAME)/," *.c *.h Makefile Doxyfile
dist:
	mkdir -p "/tmp/$(USER)-dist/$(NAME)"
	cp -R $(FILES) "/tmp/$(USER)-dist/$(NAME)"
	(cd "/tmp/$(USER)-dist/"; tar -czf "$(NAME).tar.gz" "$(NAME)")
	mv "/tmp/$(USER)-dist/$(NAME).tar.gz" ./
	$(RM) -r "/tmp/$(USER)-dist/$(NAME)"

# Formattage
format:
	command -v clang-format >/dev/null 2>&1 && clang-format -i --style=file *c *h

# Nettoyage
clean:
	$(RM) -r $(EXEC) *.o doc
distclean: clean
	$(RM) *.tar.gz

################################################################################
# Dépendances
################################################################################

# Penser à utliser l'option -MM pour les dépendances avec les en-têtes !
#
#   gcc -MM *.c >dependencies

# Éxécutables
jeu: main.o liste.o mancala.o ia.o io.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) $(LOADLIBES)
test_liste: test_liste.o liste.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) $(LOADLIBES)

# Fichiers objets
ia.o: ia.c ia.h attributes.h mancala.h liste.h
io.o: io.c io.h mancala.h attributes.h liste.h
liste.o: liste.c liste.h attributes.h
main.o: main.c attributes.h liste.h mancala.h ia.h io.h
mancala.o: mancala.c mancala.h attributes.h liste.h
test_liste.o: test_liste.c attributes.h liste.h but.h
