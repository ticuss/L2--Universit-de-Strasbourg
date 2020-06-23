#include <stdio.h>
#include <string.h>

// Il fait juste gérer les \n et ça marche

#define MAXFICHE 32
#define MAXNOM 50
#define MAXTEL 10

struct fiche
{
	int occupe ;
	char nom [MAXNOM] ;
	char telephone [MAXTEL] ;
} ;
typedef struct fiche fiche ;


int main(int argc, char* argv[]) {
	fiche carnet[MAXFICHE];
	char buf[MAXNOM];

	for (int i = 0; i < MAXFICHE; ++i)
		carnet[i].occupe = 0;

	char choice;
	do {
		printf("c: chercher\na: afficher\n+: ajouter\n-: detruire\nq: quitter :(\n");
		while ((choice = getchar()) == '\n');
		(void)getchar();

		switch (choice) {
		case 'c':
			printf("\nEntrez un nom: ");
			fgets(buf, MAXNOM, stdin);
			for (int i = 0; i < MAXFICHE; ++i)
				if (carnet[i].occupe != 0 && (strcmp(carnet[i].nom, buf) == 0))
					printf("\nNumero: %d", i);
			break;
		
		case 'a':
			printf("\nEntrez numero de fiche: ");
			choice = getchar();
			if (choice < MAXFICHE && carnet[choice].occupe)
				printf("Nom : %s", carnet[choice].nom);
			break;

		case '+':
			for (choice = 0; choice < MAXFICHE && carnet[choice].occupe; ++choice);

			if (choice < MAXFICHE) {
				printf("\nEntrez un nom: ");
				fgets(buf, MAXNOM, stdin);
				snprintf(carnet[choice].nom, MAXNOM, "%s", buf);
				carnet[choice].occupe = 1;
			} else {
				printf("\nPlus de place!");
			}
			break;
		case '-':
			printf("\nEntrez le numero a supprimer: ");
			choice = getchar();
			if (choice > 0 && choice < MAXFICHE)
				carnet[choice].occupe = 0;
			break;
		}
		printf("\n");
	} while (choice != 'q');
	return 0;
}
