/*
 * Copyright (c) 2019 Bogdanas Constantin <ticu369@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * \file io.c
 * code pour les entrees et sorties
 * \author Bogdanas Constantin
 */

#include "io.h"
#include "grille.h"


void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}
int temps_evolution(int etape){
  printf("%d iemes etape. A votre commande:  ",etape);
  etape++;
  return etape;
}



void affiche_ligne_o(int ligne, const grille *g) {
  for (int i = 0; i < g->nbc; ++i) {
    if (est_vivante(ligne, i, *g))
      printf("| O ");
    else if (g->cellules[ligne][i]==-1)
      printf("| X ");
    else
      printf("|   ");
  }
  printf("|\n");
  return;
}

void affiche_ligne_v(int ligne, const grille *g) {
  for (int i = 0; i < g->nbc; ++i) {
    if (est_vivante(ligne, i, *g))
      printf("| %d ",g->cellules[ligne][i]);
    else if (g->cellules[ligne][i]==-1)
      printf("| X ");
    else
      printf("|   ");
  }
  printf("|\n");
  return;
}


void affiche_grille(const grille *g,void (*affiche_ligne)(int,const grille* )) {
 printf("\n");
  affiche_trait(g->nbc);
  for (int i = 0; i < g->nbl; ++i) {
    affiche_ligne(i, g);
    affiche_trait(g->nbc);
  }
  printf("\n");
  return;
}

void efface_grille (const grille *g){
	printf("\n\033[%dA",g->nbl*2 + 5);
}


void debut_jeu(grille *g, grille *gc) {
  int c = getchar();
  int etape=1;
  int (*compte_voisins_vivants)(int,int,grille);
  compte_voisins_vivants=compte_voisins_vivants_cyclique;
  void (*affiche_ligne)(int,const grille* );
  affiche_ligne=affiche_ligne_o;
  	  	  	  while (c != 'q') { // touche 'q' pour quitter
  	  	  		  switch (c) {
  	  	  		  case '\n': { // touche "entree" pour évoluer
  	  	  			  	 evolue(g, gc,compte_voisins_vivants);
  	  	  			  	 efface_grille(g);
  	  	  			  	 affiche_grille(g,affiche_ligne);
  	  	  			  	 etape=temps_evolution(etape);
  	  	  			  	 break;
  	  	  		  	  	  	  }
			case 'n': { // touche "n" pour chargement dynamique d'un fichier
			      char c[180];
			      etape=1;
printf("Saisissez le nom du dossier à charger.   \n");
			      scanf("%s",c);
			      libere_grille(g);
			      libere_grille(gc);
			      init_grille_from_file(c,g);
			      alloue_grille(g->nbl, g->nbc, gc);
			      affiche_grille(g,affiche_ligne);
			      printf("0 iemes etape. A votre commande:  ");
			      getchar();
			      break;
			    	}
case 'c': {
			      if(compte_voisins_vivants==compte_voisins_vivants_cyclique){
			        compte_voisins_vivants=compte_voisins_vivants_non_cyclique;
			        printf("Attention:  Mode changé à non cyclique.");
			      }
			      else{
			        compte_voisins_vivants=compte_voisins_vivants_cyclique;
			        printf("Attention:  Mode changé à cyclique.    ");
			      }
			      printf("\033[F");
			       printf("\033[%uC", 35);
			       printf("%c",32);
			       printf("\033[%uD",2);
			      getchar();
			      break;
			}
case 'v': { // touche  v
     if(affiche_ligne==affiche_ligne_o){
         affiche_ligne=affiche_ligne_v;
     }
     else{
       affiche_ligne=affiche_ligne_o;
     }

     printf("\e[%uC", 34);
            printf("%c",32);
            printf("\e[%uD",2);
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

