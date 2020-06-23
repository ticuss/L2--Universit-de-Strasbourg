#ifndef _ITERATEUR_H_
#define _ITERATEUR_H_

#include <stddef.h>

#include "sorte.h"

typedef S *iterateur;

iterateur iterateur_debut(size_t taille, S tableau[static taille]);
iterateur iterateur_fin(size_t taille, S tableau[static taille]);
iterateur iterateur_suivant(iterateur i);
iterateur iterateur_precedent(iterateur i);
S iterateur_valeur(iterateur i);

#endif
