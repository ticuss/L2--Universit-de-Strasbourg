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

void cp(const char* in, const char* out)
{
	int fd_in;
	int fd_out;
	char buf[BLOCKSIZE];
	int bytes_read;

	fd_in = open(in, O_RDONLY);
	CHECK(fd_in);
	fd_out = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	CHECK(fd_out);

	while ((bytes_read = read(fd_in, buf, BLOCKSIZE)) > 0)
		CHECK((write(fd_out, buf, bytes_read)));

	CHECK(bytes_read);

	CHECK(close(fd_in));
	CHECK(close(fd_out));
}

void cp_dir(const char* in, const char* out)
{
	DIR* dp;
	struct dirent* ent;
	struct stat st;
	char filepath_in[PATH_MAX];
	char filepath_out[PATH_MAX];

	if ((dp = opendir(in)) == NULL) {
		perror("Unable to open directory");
		exit(EXIT_FAILURE);
	}

	CHECK(mkdir(out, 0777));

	while ((ent = readdir(dp)) != NULL) {
		if ((strncmp(ent->d_name, ".", PATH_MAX) > 0) && (strncmp(ent->d_name, "..", PATH_MAX) > 0)) {
			CHECK(snprintf(filepath_in, PATH_MAX, "%s/%s", in, ent->d_name));
			CHECK(snprintf(filepath_out, PATH_MAX, "%s/%s", out, ent->d_name));
			printf("%s -> %s\n", filepath_in, filepath_out);

			CHECK(stat(filepath_in, &st));
			if (S_ISDIR(st.st_mode))
				cp_dir(filepath_in, filepath_out);
			else
				cp(filepath_in, filepath_out);
		}
	}

	CHECK(closedir(dp));
}



int main(int argc, char* argv[])
{
	if (argc < 3) {
		fprintf(stderr, "Not enough arguments.\nUsage : ./THIS from(DIR) to(DIR)\n");
		exit(EXIT_FAILURE);
	}

	cp_dir(argv[1], argv[2]);
	
	return EXIT_SUCCESS;

	return 0;
}
