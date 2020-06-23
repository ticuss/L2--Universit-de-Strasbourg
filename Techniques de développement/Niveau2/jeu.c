/**
 * \file jeu.c
 * code pour le jeu
 * \author Bogdanas Constantin
 */
#include "jeu.h"



int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}
int compte_voisins_vivants_non_cyclique(int i, int j, grille g) {
  int v = 0;
    if (est_vivante(i,j,g)){
  v--;
  }
  int nl;
  if(i-1<0) {nl=0;} else {nl=i-1;};
  int nc;
  if(j-1<0) {nc=0;} else {nc=j-1;};
  int ligne_max;
  if(i+2>g.nbl) {ligne_max=g.nbl;} else {ligne_max=i+2;};
  int colonne_max;
  if(j+2>g.nbc) {colonne_max=g.nbc;} else {colonne_max=j+2;};
  for (int m=nl;m<ligne_max;m++){
    for (int n=nc;n<colonne_max;n++){
      if(est_vivante(m,n,g))
      v++;
    }
  }

  return v;
}
void evolue(grille *g, grille *gc,int (*compte_voisins_vivants)(int,int,grille)) {
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = compte_voisins_vivants (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
