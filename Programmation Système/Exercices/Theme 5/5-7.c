#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include <stdnoreturn.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define CHECK(op) do {if(op == -1) raler(1, #op);} while (0)

noreturn void raler (int syserr, const char *msg, ...)
{
    va_list ap ;

    va_start (ap, msg) ;
    vfprintf (stderr, msg, ap) ;
    fprintf (stderr, "\n") ;
    va_end (ap) ;

    if (syserr == 1) {
    perror (" ") ;
    }
    exit (EXIT_FAILURE) ;
}

#define BLOCKSIZE 4096
#define MY_EOF 0x100

int mygetchar(int buf_size)
{
	static char buf[BLOCKSIZE];
	static int index = 0;
	static int real_size = BLOCKSIZE;

	index %= real_size;

	if (index == 0)
		CHECK((real_size = read(0, buf, buf_size)));

	if (real_size != 0) 
		return buf[index++];
	else
		return MY_EOF;
}

int main(int argc, char* argv[])
{
	long tmp_parsing;
	int blksize = 0;
	if (argc < 2) {
		fprintf(stderr, "Not enough arguments.");
		exit(EXIT_FAILURE);
	}

	// parsing arg
	errno = 0;
	tmp_parsing = strtol(argv[1], NULL, 10);
	if (errno) {
		perror("Bad argument");
		exit(EXIT_FAILURE);
	} else if (tmp_parsing > BLOCKSIZE) {
		fprintf(stderr, "Max blocksize is 4096 !");
		exit(EXIT_FAILURE);
	}
	blksize = (int) tmp_parsing;


	int c;
	while ((c = mygetchar(blksize)) != MY_EOF)
		putc(c, stdout);



	return 0;
}
