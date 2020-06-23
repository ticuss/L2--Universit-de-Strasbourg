.PHONY: archive clean distclean
CFLAGS=-std=gnu11 -pedantic -march=native -Wall -Wextra -g
LDFLAGS=-lm

pc: main.o expression.o
	$(CC) $^ -o $@ $(LDFLAGS)

main.o: main.c expression.h
expression.o: expression.c expression.h

NAME=$(shell basename $(shell pwd))
archive:
	tar -czf bogdanas_constantin.tar.gz  *.c *.h Makefile tests Rapport_Projet.pdf check.sh
clean:
	rm -rf *.o pc
distclean: clean
	rm -rf *.tar.gz
