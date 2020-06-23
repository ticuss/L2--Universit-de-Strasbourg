.PHONY: all archive clean distclean doc format

################################################################################
# Variables diverses
################################################################################

NAME ?= $(shell basename $(shell pwd))
FILES = *.c *.h Makefile .clang-format
EXEC = test_iterateur

################################################################################
# Options et flags de compilation
################################################################################

LDLIBS ?= -lm
CFLAGS ?= -O3 -march=native -g3 -ggdb

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
test_iterateur: test_iterateur.o iterateur.o

# Fichiers objets
iterateur.o: iterateur.c iterateur.h sorte.h
test_iterateur.o: test_iterateur.c sorte.h iterateur.h
