#ifndef _LISTE_H
#define _LISTE_H

#include <stdbool.h>
#include <stddef.h>

#include "attributes.h"
#include "iterateur.h"
#include "sorte.h"

typedef struct liste liste;

sda1_attribute((warn_unused_result)) liste* liste_vide(void);

void liste_free(liste* l);

sda1_attribute((warn_unused_result)) liste* liste_insertion(liste* l, S x);

sda1_attribute((warn_unused_result)) liste* liste_insertion_tete(liste* l, S x);

sda1_attribute((warn_unused_result)) liste* liste_insertion_queue(
    liste* l, S x);

sda1_attribute((warn_unused_result)) liste* liste_suppression_tete(liste* l);

sda1_attribute((warn_unused_result)) liste* liste_suppression_queue(liste* l);

sda1_attribute((warn_unused_result)) liste* liste_fin(const liste* l);

sda1_attribute((warn_unused_result)) liste* liste_debut(const liste* l);

sda1_attribute((warn_unused_result)) liste* liste_suivant(const liste* l);

sda1_attribute((warn_unused_result)) liste* liste_precedent(const liste* l);

sda1_attribute((warn_unused_result)) liste* liste_ieme(
    const liste* l, size_t i);

sda1_attribute((nonnull)) S liste_element(const liste* l);

bool liste_est_vide(const liste* l);
size_t liste_longueur(const liste* l);

sda1_attribute((warn_unused_result)) iterateur* liste_iterateur_debut(
    const liste* l);

sda1_attribute((warn_unused_result)) iterateur* liste_iterateur_fin(
    const liste* l);

#endif
