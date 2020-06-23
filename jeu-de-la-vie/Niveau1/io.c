/**
 * \file io.c
 * code pour les entrees et sorties
 * \author Bogdanas Constantin
 */

#include "io.h"
/**
 * \fn void affiche_trait (int c)
 * \param c nombre colonnes
 * \brief affichange d'un trait
 */

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}
/**
 * \fn static void affiche_ligne (int ligne,const grille *g)
 * \brief affichage d'une ligne de la grille
 */

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}
/**
 * \fn void affiche_grille (grille *g)
 * \param *g grille
 * \brief affichange d'une grille
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}
/**
 * \fn void efface_grille (const grille *g)
 * \param g grille
 * \brief effacement d'une grille
 */

void efface_grille (grille g){
	printf("\n\033[%dA",g.nbl*2 + 5);
}
/**
 * \fn void debut_jeu(grille *g, grille *gc)
 * \param g pointeur vers une grille
 * \param gc pointeur vers une grille (copy)
 * \brief debute le jeu
 */

void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n': { // touche "n" pour chargement dynamique d'un fichier
			      char c[180];
			      printf("Saisissez le nom du dossier à charger.   \n");
			      scanf("%s",c);
			      libere_grille(g);
			      libere_grille(gc);
			      init_grille_from_file(c,g);
			      alloue_grille(g->nbl, g->nbc, gc);
			      affiche_grille(*g);
			      printf("0 iemes etape. A votre commande:  ");

			      getchar();
			      break;
			    }
			default :
			{ // touche non traitée
				printf("\n\033[1A");
				break;
			}
		}
		c = getchar();
	}
	return;
}

