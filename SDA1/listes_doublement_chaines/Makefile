.PHONY: all dist clean distclean doc

NAME ?= $(shell basename $(shell pwd))
CFLAGS ?= -std=gnu11 -pedantic -pedantic-errors -O3 -march=native -g3 -ggdb \
		-Wall -Wextra \
		-Wdouble-promotion -Wformat=2 -Winit-self -Wswitch-default \
		-Wswitch-enum -Wunused-parameter -Wuninitialized -Wfloat-equal \
		-Wshadow -Wunsafe-loop-optimizations -Wundef -Wbad-function-cast \
		-Wcast-qual -Wcast-align -Wwrite-strings -Wconversion \
		-Wjump-misses-init -Wlogical-op -Wstrict-prototypes \
		-Wold-style-definition -Wmissing-prototypes -Wmissing-declarations \
		-Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
		-Wnull-dereference -Wswitch-bool -Wduplicated-cond -Wdate-time

EXEC = polynomes

all: $(EXEC)
polynomes: main.o polynome.o liste.o
	$(CC) $^ -o $@

# Documentation
doc:
	doxygen Doxyfile

# Archive
dist:
	tar -czf $(NAME).tar.gz --transform="s,^,$(NAME)/," \
		*.c *.h Makefile Doxyfile tests results

check: all

# Nettoyage
clean:
	$(RM) -r $(EXEC) *.o doc
distclean: clean
	$(RM) *.tar.gz

# Dépendances avec les en-têtes
main.o: main.c monome.h liste.h polynome.h util.h
polynome.o: polynome.c polynome.h liste.h monome.h
liste.o: liste.c liste.h polynome.h monome.h
