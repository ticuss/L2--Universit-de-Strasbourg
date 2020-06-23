
CFLAGS=-Wall -Wextra 


main: arbrbin.o 
	gcc $(CFLAGS) -g $^ -o $@ -lm

arbrbin.o: arbrbin.c arbrbin.h 
	gcc $(CFLAGS) -g -c $^ -lm

clean:
	rm -rf *.o main *.gch

dist:
	tar -czf bogdanas_constantin.tar.gz *.c *.h Makefile