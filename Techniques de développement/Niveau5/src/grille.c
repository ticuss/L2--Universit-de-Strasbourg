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
void libere_grille(grille *g) {
  int i;
  int m=g->nbl;
  for(i=0;i<m;i++){
    free(g->cellules[i]);
  }
  free(g->cellules);
  }

void init_grille_from_file(char const *const filename, grille *const g) {
  FILE *pfile = fopen(filename, "r");

  if (pfile == NULL) {
    fprintf(stderr,
            "Erreur (%s:%d): Lecture du fichier \"%s\" impossible (%s)\n",
            __FILE__, __LINE__ - 4, filename, strerror(errno));
    exit(EXIT_FAILURE);
  }

  int l, c;
  fscanf(pfile, "%d", &l);
  fscanf(pfile, "%d", &c);
  alloue_grille(l, c, g);

  int vivantes = 0;
  fscanf(pfile, "%d", &vivantes);
  for (int n = 0; n < vivantes; ++n) {
    fscanf(pfile, "%d", &l);
    fscanf(pfile, "%d", &c);
    set_vivante(l, c, *g);
  }
   int mute = 0;
   fscanf(pfile, "%d", &mute);
   for (int n = 0; n < mute; ++n) {
    fscanf(pfile, "%d", &l);
    fscanf(pfile, "%d", &c);
    set_mute(l, c, *g);
  }

  fclose(pfile);
  return;
}


void copie_grille(const grille *const gs, grille *const gd) {
  assert(gs->nbl == gd->nbl && gs->nbc == gd->nbc);
  for (int i = 0; i < gs->nbl; ++i)
    for (int j = 0; j < gs->nbc; ++j)
      gd->cellules[i][j] = gs->cellules[i][j];
}

extern inline bool est_vivante(int i, int j, grille g);
extern inline void set_vivante(int i, int j, grille g);
extern inline void set_morte(int i, int j, grille g);
extern inline void set_mute(int i, int j, grille g);
