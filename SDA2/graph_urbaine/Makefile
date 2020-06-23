CC=gcc
CFLAGS=-Wall
LDFLAGS=
EXEC=grapheurbain

all: $(EXEC)

grapheurbain: grapheurbain_main.o grapheurbain.o dico.o listeg.o listeui.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o $(EXEC)