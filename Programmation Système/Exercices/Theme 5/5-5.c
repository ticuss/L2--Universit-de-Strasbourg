#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

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

#define BLOCKSIZE 256
#define MY_EOF 0x100

int getchar()
{
	static char buf[BLOCKSIZE];
	static int index = 0;
	static int real_size = BLOCKSIZE;

	index %= real_size;

	if (index == 0)
		CHECK((real_size = read(0, buf, BLOCKSIZE)));

	if (real_size != 0) 
		return buf[index++];
	else
		return MY_EOF;
}

int main()
{
	int c;
	while ((c = getchar()) != MY_EOF)
		putc(c, stdout);

	return 0;
}

