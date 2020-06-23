#ifndef _CONTENEURS_H_
#define _CONTENEURS_H_

#include "ensemble.h"
#include "iterateur.h"
#include "liste.h"
#include "tableau.h"

#define iterateur_debut(x) \
  _Generic((x), liste * \
           : liste_iterateur_debut, tableau * \
           : tableau_iterateur_debut, ensemble * \
           : ensemble_iterateur_debut)(x)
#define iterateur_fin(x) \
  _Generic((x), liste * \
           : liste_iterateur_fin, tableau * \
           : tableau_iterateur_fin, ensemble * \
           : ensemble_iterateur_fin)(x)

#endif
