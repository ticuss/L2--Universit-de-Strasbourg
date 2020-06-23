.PHONY: all dist clean distclean doc

NAME ?= $(shell basename $(shell pwd))
LDLIBS ?= -lm
CFLAGS ?= -O3 -march=native -g3 -ggdb
override CFLAGS += -std=gnu11 -pedantic -pedantic-errors \
		-Wall -Wextra \
		-Wdouble-promotion -Wformat=2 -Winit-self -Wswitch-default \
		-Wswitch-enum -Wunused-parameter -Wuninitialized -Wfloat-equal \
		-Wshadow -Wundef -Wbad-function-cast \
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

EXEC = test_liste
all: $(EXEC)
test_liste: test_liste.o liste.o liste_avancee.o
%: %.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LOADLIBES) $(LDLIBS)

# Documentation
doc:
	doxygen Doxyfile

# Archive
dist:
	tar -czf $(NAME).tar.gz --transform="s,^,$(NAME)/," *.c *.h Makefile

# Nettoyage
clean:
	$(RM) -r $(EXEC) *.o doc
distclean: clean
	$(RM) *.tar.gz

# Dépendances avec les en-têtes
liste.o: liste.c liste.h sorte.h
liste_avancee.o: liste_avancee.c liste_avancee.h liste.h sorte.h
test_liste.o: test_liste.c liste.h sorte.h
