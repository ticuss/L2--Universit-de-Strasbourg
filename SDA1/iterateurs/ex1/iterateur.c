#include "iterateur.h"

iterateur iterateur_debut(size_t taille, S tableau[static taille]) {
return (tableau + 0);
}

iterateur iterateur_fin(size_t taille, S tableau[static taille]) {
  return (tableau + taille - 1);
}

iterateur iterateur_suivant(iterateur i) {
   return ++i;
}

iterateur iterateur_precedent(iterateur i) {
 return --i;
}

S iterateur_valeur(iterateur i) {
 return *(i);
}
