/**
 * \file grille.c
 * code pour la grille
 * \author Bogdanas Constantin
 */


#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grille.h"
/**
 * \fn void alloue_grille (int l, int c, grille* g)
 * \param l nombre de lignes
 * \param c nombre de colonnes
 * \param g pointeur vers une grille
 * \brief alloue une grille de taille l*c, et initialise toutes les cellules
 */


#include "grille.h"

void alloue_grille (int l, int c, grille* g){

	g->nbl=l;
	g->nbc=c;
	int i;
	g->cellules=(int**)malloc(l*sizeof(int*));
	for (i=0; i<l; i++){
		g->cellules[i]=(int*)calloc(c,sizeof(int));

	}

}
/**
 * \fn void libere_grille (grille* g)
 * \param g pointeur vers une grille
 * \brief libre une grille
 */
void libere_grille (grille* g){
	int i;
	for (i=0; i<g->nbl; i++){
		free(g->cellules[i]); }
	free(g->cellules);
}

/**
 * \fn void init_grille_from_file(char const *const filename, grille *const g)
 * \param filename pointeur vers un fichier
 * \param g pointeur vers une grille
 * \brief alloue et initalise la grille g  partir d'un fichier
 */

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fclose (pfile);
	return;
}
/**
 * \fn void copie_grille(const grille *const gs, grille *const gd)
 * \param gs grille
 * \param gd grille
 * \brief recopie gs dans gd
 */


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
