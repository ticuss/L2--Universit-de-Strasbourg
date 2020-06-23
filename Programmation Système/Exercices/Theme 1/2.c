#include <stdio.h>

int main(int argc, char* argv[]) {
	char c;
	int cpt[26] = {0};
	do {
		c = getchar();
		if (c >= 'a')
			c = (c - 'a') + 'A'; // to upper

		if (c >= 'A' && c <= 'Z')
			cpt[c - 'A'] += 1;
	} while (c != '\n');

	for (int i = 0; i < 26; ++i)
		printf("%c : %d\n", 'a' + i, cpt[i]);

	return 0;
}
