#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdnoreturn.h>
#include <stdarg.h>
#include <stdlib.h>

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
	int mask = 0x100;
	char str[10];
	static const char* r = "rwx";
	for (int i = 0; i < 9; ++i) {
		if (droits & mask)
			str[i] = '-';
		else 
			str[i] = r[i%3];
		mask >>= 1;
	}
	printf("%s", str);
}

void print_stat(const char* path)
{
	struct stat st;
	CHECK((lstat(path, &st)));

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
}

int main(int argc, char* argv[])
{
	DIR* dp;
	struct dirent* ent;
	char filepath[PATH_MAX];

	if (argc < 2)
		raler(0, "You must provide ONE paramater which is a path to a directory");

	if ((dp = opendir(argv[1])) == NULL) {
		perror("Unable to open directory");
		exit(EXIT_FAILURE);
	}

	while ((ent = readdir(dp)) != NULL) {
		if (ent->d_name[0] != '.') {
			snprintf(filepath, PATH_MAX, "%s/%s", argv[1], ent->d_name);
			print_stat(filepath);
			printf(" %s\n", ent->d_name);
		}
	}

	closedir(dp);

	return EXIT_SUCCESS;
}

