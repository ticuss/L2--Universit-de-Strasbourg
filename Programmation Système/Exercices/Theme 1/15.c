#include <stdio.h>

void ecrire_2(unsigned int n) {
	for (int i = 0; i < (sizeof(unsigned int)*8); ++i) {
		printf("%d", ((1 << ((sizeof(unsigned int)*8) - i - 1)) & n) > 0);
	}
	printf("\n");
}

int main() {
	ecrire_2(15);
	return 0;
}
