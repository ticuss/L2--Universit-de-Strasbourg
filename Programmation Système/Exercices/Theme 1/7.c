#include <stdio.h>

#define MAX 256

int start_with(char* subchain, char* mainchain) {
	if (*subchain == '\0' || *subchain == '\n')
		return 1;
	if (*subchain == *mainchain)
		return start_with(++subchain, ++mainchain);
	return 0;
}

int contains(char* subchain, char* mainchain) {
	if (*subchain == '\0')
		return 1;
	if (*subchain == *mainchain)
		return start_with(++subchain, ++mainchain);
	if (*mainchain == '\0')
		return 0;
	return contains(subchain, ++mainchain);
}

int main(int argc, char* argv[]) {
	char buf[MAX];
	char str[MAX];

	fgets(buf, MAX, stdin);
	fgets(str, MAX, stdin);

	if (contains(str,buf))
		puts("Contenue !");
	else
		puts("Pas contenue :(");

	return 0;
}
