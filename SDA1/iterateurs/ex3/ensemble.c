#include "ensemble.h"

#include <stdlib.h>
#include <string.h>

struct ensemble {
  S *elements;
  size_t cardinal;
  size_t taille_max;
};

static const size_t ENSEMBLE_SEUIL = 128;

ensemble *ensemble_vide(void) {
  ensemble *const e = malloc(sizeof *e);
  if (!e)
    return e;

  e->elements = malloc(sizeof *e->elements * ENSEMBLE_SEUIL);
  if (!e->elements) {
    free(e);
    return NULL;
  }

  e->cardinal = 0;
  e->taille_max = ENSEMBLE_SEUIL;

  return e;
}

void ensemble_free(ensemble *e) {
  if (!e)
    return;

  free(e->elements);
  free(e);
}

static inline int ensemble_comparator(const void *a, const void *b) {
  const S *aa = a;
  const S *bb = b;
  if (*aa < *bb)
    return -1;
  else if (*aa > *bb)
    return 1;
  else
    return 0;
}

ensemble *ensemble_insertion(ensemble *e, S x) {
  if (e->cardinal >= e->taille_max) {
    const size_t taille =
        sizeof *e->elements * (e->taille_max + ENSEMBLE_SEUIL);
    S *const elements = realloc(e->elements, taille);
    if (elements) {
      e->elements = elements;
      e->taille_max = taille;
    }
  }

  if (e->cardinal < e->taille_max) {
    e->elements[e->cardinal++] = x;
    qsort(e->elements, e->cardinal, sizeof *e->elements, ensemble_comparator);
  }

  return e;
}

ensemble *ensemble_suppression(ensemble *e, S x) {
  if (!ensemble_contient(e, x) || !e->cardinal)
    return e;

  size_t position = 0;
  for (size_t i = 0; i < e->cardinal; ++i)
    if (e->elements[i] == x)
      position = i;

  const size_t taille = sizeof *e->elements * (e->cardinal - position - 1);
  memmove(e->elements + position, e->elements + position + 1, taille);
  e->cardinal--;

  return e;
}

bool ensemble_contient(const ensemble *e, S x) {
  bool trouve = false;

  for (size_t i = 0; !trouve && i < e->cardinal; ++i)
    if (e->elements[i] == x)
      trouve = true;

  return trouve;
}

size_t ensemble_cardinal(const ensemble *e) {
  return e->cardinal;
}

bool ensemble_est_vide(const ensemble *e) {
  return e->cardinal ? true : false;
}

////////////////////////////////////////////////////////////////////////////////
// Itérateur
////////////////////////////////////////////////////////////////////////////////

typedef struct iterateur_ensemble {
size_t pos;
  const ensemble *e;
} iterateur_ensemble;

static void iterateur_ensemble_suivant(void* infos)
{
  iterateur_ensemble* const it = infos;
  it->pos++;
}


static void iterateur_ensemble_precedent(void* infos)
{
  iterateur_ensemble* const it = infos;
  it->pos--;          
}


static S iterateur_ensemble_valeur(const void * infos)
{
  const iterateur_ensemble* const it = infos;
  return it->e->elements[it->pos]; 
}



static bool iterateur_ensemble_egal(const void* a, const void* b)
{
  const iterateur_ensemble* const e1=a;
  const iterateur_ensemble* const e2=b;
  return ensemble_comparator(e1->e,e2->e)==0;
}


iterateur* ensemble_iterateur_debut(const ensemble* e)
{
  iterateur_ensemble* const infos = malloc(sizeof *infos);
  iterateur* const it = iterateur_nouveau(
      infos, iterateur_ensemble_suivant, iterateur_ensemble_precedent,
      iterateur_ensemble_valeur, iterateur_ensemble_egal);
  infos->e=e;
  *infos->e->elements=e->elements[0];
  infos->pos=0;
  return it;
}


iterateur* ensemble_iterateur_fin(const ensemble* e)
{
  iterateur_ensemble* const infos = malloc(sizeof *infos);
  iterateur* const it = iterateur_nouveau(
      infos, iterateur_ensemble_suivant, iterateur_ensemble_precedent,
      iterateur_ensemble_valeur, iterateur_ensemble_egal);
  infos->e=e;
  *infos->e->elements=e->elements[e->cardinal-1];
  infos->pos=e->cardinal-1;
  return it;
}