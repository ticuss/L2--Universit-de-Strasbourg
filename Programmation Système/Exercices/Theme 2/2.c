#include <stdio.h>

int main(int argc, char* argv[]) {
	int cpt = 0;
	char car_to_count;
	if (argc > 1)
		car_to_count = argv[1][0];
	else
		car_to_count = '\n';

	char c;
	while ( (c = getchar()) != EOF)
		if (c == car_to_count)
			++cpt;

	printf("%d", cpt);

	return 0;
}
