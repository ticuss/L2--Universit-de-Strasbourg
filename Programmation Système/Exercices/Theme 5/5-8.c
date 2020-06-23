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

void rwx(unsigned long droits)
{
	for (int i = 0; i < 3; ++i) {
		if (droits & 1 << ((3-i)*3 - 1))
			printf("r");
		else
			printf("-");
		if (droits & 1 << ((3-i)*3 - 2))
			printf("w");
		else
			printf("-");
		if (droits & 1 << ((3-i)*3 - 1))
			printf("x");
		else
			printf("-");
	}
}


int main(int argc, char* argv[])
{
	struct stat st;

	if (argc < 2) {
		fprintf(stderr, "Not enough arguments: please provide a file.");
		exit(EXIT_FAILURE);
	}

	CHECK((lstat(argv[1], &st)));

	// type
	switch (st.st_mode & S_IFMT) {
	case S_IFBLK:
		printf("b");
		break;
	case S_IFCHR:
		printf("c");
		break;
	case S_IFDIR:
		printf("d");
		break;
	case S_IFLNK:
		printf("l");
		break;
	case S_IFREG:
		printf("-");
		break;
	}

	rwx((unsigned long) st.st_mode);

	return EXIT_SUCCESS;
}
