#include <stdio.h>
#include <sysexits.h>

#include "iterateur.h"
#include "sorte.h"

#ifndef TAILLE_TABLEAU
  #define TAILLE_TABLEAU 10
#endif

int main(int argc, char *argv[argc + 1]) {
  (void) argc;
  (void) argv;
  FILE *const sortie = stdout;

  size_t taille = TAILLE_TABLEAU;
  S tableau[TAILLE_TABLEAU];
  for (size_t i = 0; i < sizeof tableau / sizeof tableau[0]; ++i)
    tableau[i] = (S) i;

  const iterateur debut = iterateur_debut(taille, tableau);
  const iterateur fin = iterateur_fin(taille, tableau);
  for (iterateur it = debut; it != fin; it = iterateur_suivant(it)) {
    const S x = iterateur_valeur(it);
    fprintf(sortie, "%" PRI_S " ", x);
  }
  fprintf(sortie, "\n");

  fclose(sortie);

  return EX_OK;
}
