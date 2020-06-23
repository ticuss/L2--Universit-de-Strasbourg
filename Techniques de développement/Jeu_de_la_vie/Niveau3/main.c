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
