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
 * \file main.c
 * \code  main
 * \author Bogdanas Constantin
*/


#include <stdio.h>
#include <stdlib.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"


int main(int argc, char **argv) {
  grille g, gc;
   void (*affiche_ligne)(int,const grille* )=affiche_ligne_o;
  if (argc != 2) {
      printf("Vous n'avez chargé auquan fichier\nSaisissez 'n' pour charger une nouvelle grille par saisir son nom\nou\nun autre charactere pour quitter et relancer par %s <fichier grille>\n", argv[0]);
      int nouveau=getchar();
      if(nouveau!='n') return 0;
      char c[180];
      printf("Saisissez le nom du dossier à charger: ");
      scanf("%s",c);
      init_grille_from_file(c,&g);
      getchar();
  }

  else init_grille_from_file(argv[1], &g);
  alloue_grille(g.nbl, g.nbc, &gc);
  affiche_grille(&g,affiche_ligne);
  debut_jeu(&g, &gc);

  libere_grille(&g);
  libere_grille(&gc);
  return EXIT_SUCCESS;
}
