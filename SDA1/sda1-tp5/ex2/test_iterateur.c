#include <stdio.h>

#include "iterateur.h"
#include "liste.h"
#include "sorte.h"
#include "tableau.h"

#ifndef NDEBUG
  #define assert(expr) \
    (expr) ? 0 \
           : (fprintf( \
                  stderr, "erreur: %s: %s(): l.%d: " #expr "\n", __FILE__, \
                  __func__, __LINE__), \
              1)
#else
  #define assert(expr) (void) 0
#endif

static inline int test_tableau(void) {
  int erreurs = 0;

  tableau *t = tableau_vide();
  for (size_t i = 0; i < 20; ++i)
    t = tableau_insertion_fin(t, (S) i);

  iterateur *it;
  iterateur *const fin = iterateur_fin(t);
  S x = 0;
  for (it = iterateur_debut(t); !iterateur_egal(it, fin);
       it = iterateur_suivant(it)) {
    const S valeur = iterateur_valeur(it);
    printf("%" PRI_S " ", valeur);
    erreurs += assert(valeur == x++);
  }
  printf("\n");

  iterateur_free(it);
  iterateur_free(fin);

  tableau_free(t);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste(void) {
  int erreurs = 0;
  liste *l = liste_vide();

  for (size_t i = 0; i < 20; ++i)
    l = liste_insertion_queue(l, (S) i);
  l = liste_debut(l);

  S x = 0;
  iterateur *it;
  iterateur *const fin = liste_iterateur_fin(l);
  for (it = iterateur_debut(l); !iterateur_egal(it, fin);
       it = iterateur_suivant(it)) {
    const S valeur = iterateur_valeur(it);
    printf("%" PRI_S " ", valeur);
    erreurs += assert(valeur == x++);
  }
  printf("\n");

  iterateur_free(it);
  iterateur_free(fin);

  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

int main(int argc, char *argv[argc + 1]) {
  (void) argc;
  (void) argv;

  int erreurs = 0;
  erreurs += test_tableau();
  erreurs += test_liste();

  return erreurs;
}
