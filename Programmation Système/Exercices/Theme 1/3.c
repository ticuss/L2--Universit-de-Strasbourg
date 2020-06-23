#include <stdio.h>

int is_letter(char c) {
	return (c>='a' && c<='z') || (c >= 'A' && c <= 'Z');
}

int main(int argc, char* argv[]) {
	char c;
	int cpt = 0;
	int not_word = 0;
	do {
		while((c = getchar()) != ' ') {
			if (c == '\n')
				break;
			if (!is_letter(c)) {
				not_word = 1;
			}
		}
		if (c == '\n' || not_word) {
			not_word = 0; // reset
		} else {
			++cpt;
		}
	} while (c != '\n');

	printf("%d word(s).\n", cpt);
	return 0;
}
