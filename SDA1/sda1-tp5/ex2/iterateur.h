#ifndef _ITERATEUR_H_
#define _ITERATEUR_H_

#include <stdbool.h>

#include "attributes.h"
#include "liste.h"
#include "sorte.h"
#include "tableau.h"

typedef struct iterateur iterateur;

sda1_attribute((warn_unused_result)) iterateur *liste_iterateur_debut(
    const liste *l);

sda1_attribute((warn_unused_result)) iterateur *liste_iterateur_fin(
    const liste *l);

sda1_attribute((warn_unused_result)) iterateur *tableau_iterateur_debut(
    const tableau *t);

sda1_attribute((warn_unused_result)) iterateur *tableau_iterateur_fin(
    const tableau *t);

#define iterateur_debut(x) \
  _Generic((x), liste * \
           : liste_iterateur_debut, tableau * \
           : tableau_iterateur_debut)(x)
#define iterateur_fin(x) \
  _Generic((x), liste * \
           : liste_iterateur_fin, tableau * \
           : tableau_iterateur_fin)(x)

sda1_attribute((nonnull, warn_unused_result)) iterateur *iterateur_suivant(
    iterateur *i);

sda1_attribute((nonnull, warn_unused_result)) iterateur *iterateur_precedent(
    iterateur *i);

sda1_attribute((nonnull)) bool iterateur_egal(
    const iterateur *a, const iterateur *b);

sda1_attribute((nonnull)) S iterateur_valeur(const iterateur *it);

void iterateur_free(iterateur *i);

#endif
