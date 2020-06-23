.PHONY: all dist clean distclean doc
NAME ?= $(shell basename $(shell pwd))
CC ?= cc
CFLAGS ?=  -march=native -g3 -ggdb
override CFLAGS += -std=gnu11 -pedantic -pedantic-errors -Wall -Wextra
EXEC = main
all: $(EXEC)
%: %.o
	$(CC) $(LDFLAGS) $^ -o $ $@ $(LOADLIBES) $(LDLIBS)

%.o: %.c
	$(CC) $(LDFLAGS) $(CFLAGS) -c "$<" -o "$@"

doc:
	doxygen Doxyfile


dist :
	tar --lzma -cf Bogdanas_Constantin-GoL-2.0.tar.gz \
		*.c *.h Makefile Doxyfile grilles
clean:
	$(RM) *.o $(EXEC)

distclean: clean
	$(RM) -r *.tar.xz doc


main: main.o grille.o jeu.o io.o
main.o: main.c grille.h io.h jeu.h
grille.o: grille.c grille.h
jeu.o: jeu.c jeu.h grille.h jeu.h
io.o: io.c io.h grille.h jeu.h
