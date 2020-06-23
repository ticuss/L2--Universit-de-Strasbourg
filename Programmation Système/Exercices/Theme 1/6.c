#include <stdio.h>
#include <string.h>

#define MAX 256

int main(int argc, char* argv[]) {
	char buf[MAX];
	char str[MAX];

	fgets(buf, MAX, stdin);
	unsigned long len = strlen(buf);
	strncpy(str, buf, len);

	if (str[len-1] == '\n')
		str[len-1] = '\0'; // get rif of '\n'

	puts(str);
	printf("len : %lu\n", len);
	return 0;
}
