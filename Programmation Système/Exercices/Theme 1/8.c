#include <stdio.h>
#include <string.h>

#define MAX 64

struct mois
{
	char nom[9+1];
	int jours;
};

int main(int argc, char* argv[]) {
	int month = -1;
	char input[MAX];
	struct mois m[12] = {{"janvier", 31},
		{"fevrier", 29},
		{"mars", 31},
		{"avril", 30},
		{"mai", 31},
		{"juin", 30},
		{"juillet", 31},
		{"aout", 31},
		{"septembre", 30},
		{"octobre", 31},
		{"novembre", 30},
		{"decembre", 31}};

	fgets(input, MAX, stdin);

	if (input[strlen(input) - 1] == '\n')
		input[strlen(input)-1] = '\0';

	for (int i = 0; i < 12; ++i) {
		if (strcmp(input, m[i].nom) == 0) {
			month = i;
			break;
		}
	}

	if (month == -1) {
		printf("Mois invalide");
	} else {
		printf("%s, mois num %d, %d jours\n", input, month+1, m[month].jours);
	}

	
	return 0;
}
