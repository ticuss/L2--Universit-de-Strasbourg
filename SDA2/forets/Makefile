
CFLAGS=-Wall -Wextra 


main:  arbre.o  
	gcc $(CFLAGS) -g $^ -o $@ 

pile.o: arbre.c arbre.h 
	gcc $(CFLAGS) -g -c $^ 

clean:
	rm -rf *.o main *.gch

dist:
	tar -czf bogdanas_constantin.tar.gz *.c *.h Makefile