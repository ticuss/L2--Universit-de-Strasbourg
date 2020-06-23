#include <stdio.h>

int main(int argc, char* argv[]) {
	int cpt = 0;
	char c = 'a';
	while (cpt < 10 && (c = getchar()) != EOF) {
		putchar(c);
		if (c == '\n')
			++cpt;
	}
	
	return 0;
}
