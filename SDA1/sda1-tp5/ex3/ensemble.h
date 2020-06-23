#ifndef _ENSEMBLE_H
#define _ENSEMBLE_H

#include <stdbool.h>
#include <stddef.h>

#include "attributes.h"
#include "iterateur.h"
#include "sorte.h"

typedef struct ensemble ensemble;

sda1_attribute((warn_unused_result)) ensemble* ensemble_vide(void);

void ensemble_free(ensemble* e);

sda1_attribute((nonnull, warn_unused_result)) ensemble* ensemble_insertion(
    ensemble* e, S x);

sda1_attribute((nonnull, warn_unused_result)) ensemble* ensemble_suppression(
    ensemble* e, S x);

sda1_attribute((nonnull)) bool ensemble_contient(const ensemble* e, S x);

sda1_attribute((nonnull)) size_t ensemble_cardinal(const ensemble* e);

sda1_attribute((nonnull)) bool ensemble_est_vide(const ensemble* e);

sda1_attribute((nonnull, warn_unused_result))
    iterateur* ensemble_iterateur_debut(const ensemble* e);

sda1_attribute((nonnull, warn_unused_result)) iterateur* ensemble_iterateur_fin(
    const ensemble* e);

#endif
