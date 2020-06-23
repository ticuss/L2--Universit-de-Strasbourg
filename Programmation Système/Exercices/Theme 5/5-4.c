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

#define MAXNAME 64
#define BLOCKSIZE 1024

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

int main(int argc, char* argv[])
{
	char in[MAXNAME];
	char out[MAXNAME];
	int fd_in;
	int fd_out;
	char buf[BLOCKSIZE];
	int bytes_read;

	if (argc < 3) {
		fprintf(stderr, "Not enough arguments.");
		exit(EXIT_FAILURE);
	}

	fd_in = open(argv[1], O_RDONLY);
	CHECK(fd_in);
	fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	CHECK(fd_out);

	while ((bytes_read = read(fd_in, buf, BLOCKSIZE)) > 0)
		CHECK((write(fd_out, buf, bytes_read)));

	CHECK(bytes_read);

	CHECK(close(fd_in));
	CHECK(close(fd_out));

	return 0;
}
