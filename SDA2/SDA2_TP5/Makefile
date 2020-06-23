
CFLAGS=-Wall -Wextra 


main:  arbin.o  
	gcc $(CFLAGS) -g $^ -o $@ 

arbin.o: arbin.c arbin.h 
	gcc $(CFLAGS) -g -c $^ 

clean:
	rm -rf *.o main *.gch *.out

dist:
	tar -czf bogdanas_constantin.tar.gz *.c *.h Makefile