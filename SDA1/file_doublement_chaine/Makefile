
CFLAGS=-Wall -Wextra 


main: test_files.o files_dbl.o  
	gcc $(CFLAGS) -g $^ -o $@ -lm

test_files.o: test_files.c 
	gcc $(CFLAGS) -g -c $^ -lm

files_dbl.o: files_dbl.c files_dbl.h
	gcc $(CFLAGS) -g -c $^ -lm

clean:
	rm -rf *.o main *.gch

dist:
	tar -czf bogdanas_constantin.tar.gz *.c *.h Makefile