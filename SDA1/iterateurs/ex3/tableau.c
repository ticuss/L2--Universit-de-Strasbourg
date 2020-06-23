#include "tableau.h"

#include <stdlib.h>
#include <string.h>

struct tableau {
  S *elements;
  size_t longueur;
  size_t taille_max;
};

static const size_t TABLEAU_SEUIL = 128;

tableau *tableau_vide(void) {
  tableau *t = malloc(sizeof *t);
  if (!t)
    return t;

  t->elements = malloc(sizeof *t->elements * TABLEAU_SEUIL);
  if (!t->elements) {
    free(t);
    return NULL;
  }

  t->taille_max = TABLEAU_SEUIL;
  t->longueur = 0;

  return t;
}

void tableau_free(tableau *t) {
  if (!t)
    return;

  free(t->elements);
  free(t);
}

static inline tableau *tableau_agrandir(tableau *t, size_t taille) {
  const size_t nouvealle_taille = sizeof *t->elements * taille;
  S *elements = realloc(t->elements, nouvealle_taille);
  if (elements) {
    t->elements = elements;
    t->taille_max = nouvealle_taille;
  }
  return t;
}

tableau *tableau_insertion_debut(tableau *t, S x) {
  if (t->longueur >= t->taille_max)
    t = tableau_agrandir(t, t->taille_max + TABLEAU_SEUIL);

  memmove(t->elements + 1, t->elements, sizeof *t->elements * t->longueur);
  if (t->longueur < t->taille_max) {
    t->elements[0] = x;
    t->longueur++;
  }

  return t;
}

tableau *tableau_insertion_fin(tableau *t, S x) {
  if (t->longueur >= t->taille_max)
    t = tableau_agrandir(t, t->taille_max + TABLEAU_SEUIL);
  if (t->longueur < t->taille_max)
    t->elements[t->longueur++] = x;

  return t;
}

tableau *tableau_modification(tableau *t, size_t position, S x) {
  t->elements[position] = x;
  return t;
}

size_t tableau_longueur(const tableau *t) {
  return t->longueur;
}

size_t tableau_taille_maximale(const tableau *t) {
  return t->taille_max;
}

const S *tableau_elements(const tableau *t) {
  return t->elements;
}

S tableau_element(const tableau *t, size_t position) {
  return t->elements[position];
}

////////////////////////////////////////////////////////////////////////////////
// Itérateur
////////////////////////////////////////////////////////////////////////////////

typedef struct iterateur_tableau {
  /* (Peut-être) À modifier ou compléter. */
  const tableau *t;
} iterateur_tableau;

static void iterateur_tableau_suivant(void *infos) {
  /* (Peut-être) À modifier ou compléter. */
  iterateur_tableau *const it = infos;
}

static void iterateur_tableau_precedent(void *infos) {
  /* (Peut-être) À modifier ou compléter. */
  iterateur_tableau *const it = infos;
}

static S iterateur_tableau_valeur(const void *infos) {
  const iterateur_tableau *const it = infos;
  return (S){0};
}

static bool iterateur_tableau_egal(const void *a, const void *b) {
  /* (Peut-être) À modifier ou compléter. */
  return true;
}

iterateur *tableau_iterateur_debut(const tableau *t) {
  iterateur_tableau *const infos = malloc(sizeof *infos);
  iterateur *const it = iterateur_nouveau(
      infos, iterateur_tableau_suivant, iterateur_tableau_precedent,
      iterateur_tableau_valeur, iterateur_tableau_egal);
  /* (Peut-être) À modifier ou compléter. */
  return it;
}

iterateur *tableau_iterateur_fin(const tableau *t) {
  iterateur_tableau *const infos = malloc(sizeof *infos);
  iterateur *const it = iterateur_nouveau(
      infos, iterateur_tableau_suivant, iterateur_tableau_precedent,
      iterateur_tableau_valeur, iterateur_tableau_egal);
  /* (Peut-être) À modifier ou compléter. */
  return it;
}
