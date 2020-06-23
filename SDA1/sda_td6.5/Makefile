
CFLAGS=-Wall -Wextra 


main: pile.o polo.o  
	gcc $(CFLAGS) -g $^ -o $@ -lm

pile.o: pile.c pile.h 
	gcc $(CFLAGS) -g -c $^ -lm

polo.o: polo.c polo.h
	gcc $(CFLAGS) -g -c $^ -lm

clean:
	rm -rf *.o main *.gch

dist:
	tar -czf bogdanas_constantin.tar.gz *.c *.h Makefile

	