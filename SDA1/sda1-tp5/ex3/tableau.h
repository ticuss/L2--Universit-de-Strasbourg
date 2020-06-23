#ifndef _TABLEAU_H
#define _TABLEAU_H

#include <stddef.h>

#include "attributes.h"
#include "iterateur.h"
#include "sorte.h"

typedef struct tableau tableau;

sda1_attribute((warn_unused_result)) tableau* tableau_vide(void);
void tableau_free(tableau* t);

sda1_attribute((warn_unused_result)) tableau* tableau_insertion_debut(
    tableau* t, S x);

sda1_attribute((warn_unused_result)) tableau* tableau_insertion_fin(
    tableau* t, S x);

sda1_attribute((warn_unused_result)) tableau* tableau_modification(
    tableau* t, size_t position, S x);

size_t tableau_longueur(const tableau* t);
size_t tableau_taille_maximale(const tableau* t);
const S* tableau_elements(const tableau* t);
S tableau_element(const tableau* t, size_t position);

sda1_attribute((warn_unused_result)) iterateur* tableau_iterateur_debut(
    const tableau* t);

sda1_attribute((warn_unused_result)) iterateur* tableau_iterateur_fin(
    const tableau* t);

#endif
