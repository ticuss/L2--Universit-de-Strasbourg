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
  copie_grille(g, gc); // copie temporaire de la grille
  for (int i = 0; i < g->nbl; i++) {
    for (int j = 0; j < g->nbc; ++j) {
      if(est_vivante(i,j,*gc)){
        if ((compte_voisins_vivants(i,j,*gc)<2)||(compte_voisins_vivants(i,j,*gc)>3))
        {
          set_morte(i,j,*g);
        }
        else  g->cellules[i][j]++;
      }
      else{
        if(compte_voisins_vivants(i,j,*gc)==3)
        set_vivante(i,j,*g);
      }

    }
  }
}

