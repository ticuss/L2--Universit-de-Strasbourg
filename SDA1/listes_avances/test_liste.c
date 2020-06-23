#include <stdio.h>
#include <stdbool.h>

#include "sorte.h"
#include "liste.h"
#include "liste_avancee.h"

#ifndef NDEBUG
  #define assert(expr) \
    (expr) ? \
    0 : \
    (fprintf( \
        stderr, "erreur: %s: %s(): l.%d: "#expr"\n", __FILE__, \
        __func__, __LINE__), 1)
#else
  #define assert(expr) (void) 0
#endif

static inline int test_liste_insertion_tete(void)
{
  int erreurs = 0;

  /* Initialisation. */
  liste* l = liste_vide();
  for (size_t i = 0; i < 20; ++i)
    l = liste_insertion_tete(l, (S) i);
  l = liste_debut(l);

  S x = 19;
  for (const liste* parcours = l; parcours; parcours = liste_suivant(parcours))
  {
    const S element = liste_element(parcours);
    erreurs += assert(element == x);
    x--;

    // printf("%"S_PRI" ", element);
  }
  erreurs += assert(liste_longueur(l) == 20);
  // printf("\n");

  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_insertion_queue(void)
{
  int erreurs = 0;
  /* Initialisation. */
  liste* l = liste_vide();
  for (size_t i = 0; i < 20; ++i)
    l = liste_insertion_queue(l, (S) i);
  l = liste_debut(l);

  S x = 0;
  for (const liste* parcours = l; parcours; parcours = liste_suivant(parcours))
  {
    const S element = liste_element(parcours);
    erreurs += assert(element == x);
    x++;

    // printf("%"S_PRI" ", element);
  }
  erreurs += assert(liste_longueur(l) == 20);
  // printf("\n");

  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_suppression_tete(void)
{
  int erreurs = 0;
  /* Initialisation. */
  liste* l = liste_vide();
  for (size_t i = 0; i < 20; ++i)
    l = liste_insertion_queue(l, (S) i);
  l = liste_suppression_tete(l);
  l = liste_debut(l);

  erreurs += assert(liste_longueur(l) == 19);
  erreurs += assert(liste_element(liste_debut(l)) == 1);
  erreurs += assert(liste_element(liste_fin(l)) == 19);

  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_suppression_queue(void)
{
  int erreurs = 0;
  /* Initialisation. */
  liste* l = liste_vide();
  for (size_t i = 0; i < 20; ++i)
    l = liste_insertion_queue(l, (S) i);
  l = liste_suppression_queue(l);
  l = liste_debut(l);

  erreurs += assert(liste_longueur(l) == 19);
  erreurs += assert(liste_element(liste_debut(l)) == 0);
  erreurs += assert(liste_element(liste_fin(l)) == 18);

  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_range(void)
{
  int erreurs = 0;

  {
    liste* const l = liste_range(0, 10, 1);
    erreurs += assert(liste_longueur(l) == 10);
    if (liste_longueur(l) == 10)
      for (size_t i = 0; i < 10; ++i)
        erreurs += assert(liste_element(liste_ieme(l, i)) == (S) i);
    liste_free(l);
  }
  {
    liste* const l = liste_range(10, 0, -1);
    erreurs += assert(liste_longueur(l) == 10);
    if (liste_longueur(l) == 10)
      for (size_t i = 0; i < 10; ++i)
      {
        const S attendu = 10 - (S) i;
        erreurs += assert(liste_element(liste_ieme(l, i)) == attendu);
      }
    liste_free(l);
  }
  {
    liste* const l = liste_range(0, 20, 2);
    erreurs += assert(liste_longueur(l) == 10);
    if (liste_longueur(l) == 10)
      for (size_t i = 0; i < 10; ++i)
      {
        const S attendu = (S) i * 2;
        erreurs += assert(liste_element(liste_ieme(l, i)) == attendu);
      }
    liste_free(l);
  }
  {
    liste* const l = liste_range(20, 0, -2);
    erreurs += assert(liste_longueur(l) == 10);
    if (liste_longueur(l) == 10)
      for (size_t i = 0; i < 10; ++i)
      {
        const S attendu = (10 - (S) i) * 2;
        erreurs += assert(liste_element(liste_ieme(l, i)) == attendu);
      }
    liste_free(l);
  }

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_reverse(void)
{
  int erreurs = 0;

  {
    liste* const l = liste_range(0, 10, 1);
    liste* const reverse = liste_reverse(l);
    erreurs += assert(liste_longueur(reverse) == 10);
    if (liste_longueur(reverse) == 10)
      for (size_t i = 0; i < 10; ++i)
        erreurs += assert(liste_element(liste_ieme(reverse, i)) == 9 - (S) i);
    liste_free(l);
    liste_free(reverse);
  }

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline S add_one(S x) { return x + 1; }
static inline S sub_one(S x) { return x - 1; }
static inline S mul_two(S x) { return x * 2; }
static inline S zero_if_even(S x) { return x % 2 ? x : 0; }

static inline int test_liste_map(void)
{
  int erreurs = 0;
  
  {
    liste* const l = liste_range(0, 10, 1);
    liste* const map = liste_map(l, add_one);
    erreurs += assert(liste_longueur(map) == 10);
    if (liste_longueur(map) == 10)
      for (size_t i = 0; i < 10; ++i)
        erreurs += assert(liste_element(liste_ieme(map, i)) == (S) i + 1);
    liste_free(l);
    liste_free(map);
  }
  {
    liste* const l = liste_range(0, 10, 1);
    liste* const map = liste_map(l, sub_one);
    erreurs += assert(liste_longueur(map) == 10);
    if (liste_longueur(map) == 10)
      for (size_t i = 0; i < 10; ++i)
        erreurs += assert(liste_element(liste_ieme(map, i)) == (S) i - 1);
    liste_free(l);
    liste_free(map);
  }
  {
    liste* const l = liste_range(0, 10, 1);
    liste* const map = liste_map(l, mul_two);
    erreurs += assert(liste_longueur(map) == 10);
    if (liste_longueur(map) == 10)
      for (size_t i = 0; i < 10; ++i)
        erreurs += assert(liste_element(liste_ieme(map, i)) == (S) i * 2);
    liste_free(l);
    liste_free(map);
  }
  {
    liste* const l = liste_range(0, 10, 1);
    liste* const map = liste_map(l, zero_if_even);
    erreurs += assert(liste_longueur(map) == 10);
    if (liste_longueur(map) == 10)
    {
      for (size_t i = 0; i < 10; i += 2)
        erreurs += assert(liste_element(liste_ieme(map, i)) == (S) 0);
      for (size_t i = 1; i < 10; i += 2)
        erreurs += assert(liste_element(liste_ieme(map, i)) == (S) i);
    }
    liste_free(l);
    liste_free(map);
  }


  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline bool is_odd(S x) { return x % 2; }
static inline bool is_even(S x) { return !is_odd(x); }
static inline bool gt_5(S x) { return x > 5; }
static inline bool le_5(S x) { return x <= 5; }

static inline int test_liste_filter(void)
{
  int erreurs = 0;
  
  {
    liste* const l = liste_range(0, 10, 1);
    liste* const filtered = liste_filter(l, is_odd);
    erreurs += assert(liste_longueur(filtered) == 5);
    if (liste_longueur(filtered) == 5)
      for (size_t i = 0; i < 5; ++i)
        erreurs += assert(liste_element(liste_ieme(filtered, i)) == (S) i * 2 + 1);
    liste_free(l);
    liste_free(filtered);
  }
  {
    liste* const l = liste_range(0, 10, 1);
    liste* const filtered = liste_filter(l, is_even);
    erreurs += assert(liste_longueur(filtered) == 5);
    if (liste_longueur(filtered) == 5)
      for (size_t i = 0; i < 5; ++i)
        erreurs += assert(liste_element(liste_ieme(filtered, i)) == (S) i * 2);
    liste_free(l);
    liste_free(filtered);
  }
  {
    liste* const l = liste_range(0, 10, 1);
    liste* const filtered = liste_filter(l, gt_5);
    erreurs += assert(liste_longueur(filtered) == 4);
    if (liste_longueur(filtered) == 4)
      for (size_t i = 0; i < 4; ++i)
        erreurs += assert(liste_element(liste_ieme(filtered, i)) == (S) i + 6);
    liste_free(l);
    liste_free(filtered);
  }
  {
    liste* const l = liste_range(0, 10, 1);
    liste* const filtered = liste_filter(l, le_5);
    erreurs += assert(liste_longueur(filtered) == 6);
    if (liste_longueur(filtered) == 6)
      for (size_t i = 0; i < 6; ++i)
        erreurs += assert(liste_element(liste_ieme(filtered, i)) == (S) i);
    liste_free(l);
    liste_free(filtered);
  }

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline S sum(S a, S b) { return a + b; }
static inline S prod(S a, S b) { return a * b; }

static inline int test_liste_reduce(void)
{
  int erreurs = 0;

  {
    liste* const l = liste_range(0, 10, 1);
    erreurs += assert(liste_reduce(l, sum) == 45);
    erreurs += assert(liste_reduce(l, prod) == 0);
    erreurs += assert(liste_reduce(liste_suivant(l), prod) == 362880);
    liste_free(l);
  }
  
  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline void add_left(void* x, S y) { S* a = x; *a = *a + y; }
static inline void add_right(S x, void* y) { S* b = y; *b = x + *b; }
static inline void sub_left(void* x, S y) { S* a = x; *a = *a - y; }
static inline void sub_right(S x, void* y) { S* b = y; *b = x - *b; }

static inline int test_liste_fold_left(void)
{
  int erreurs = 0;

  liste* const l = liste_range(0, 10, 1);
  {
    S x = 0;
    liste_fold_left(l, add_left, &x);
    erreurs += assert(x == 45);
  }
  {
    S x = 0;
    liste_fold_left(l, sub_left, &x);
    erreurs += assert(x == -45);
  }
  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_fold_right(void)
{
  int erreurs = 0;

  liste* const l = liste_range(0, 10, 1);
  {
    S x = 0;
    liste_fold_right(l, add_right, &x);
    erreurs += assert(x == 45);
  }
  {
    S x = 0;
    liste_fold_right(l, sub_right, &x);
    erreurs += assert(x == -5);
  }
  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_somme(void)
{
  int erreurs = 0;

  liste* const l = liste_range(0, 10, 1);
  erreurs += assert(liste_somme(l) == 45);
  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_produit(void)
{
  int erreurs = 0;

  liste* const l = liste_range(0, 10, 1);
  erreurs += assert(liste_produit(l) == 0);
  erreurs += assert(liste_produit(liste_suivant(l)) == 362880);
  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_minimum(void)
{
  int erreurs = 0;

  liste* const l = liste_range(0, 10, 1);
  erreurs += assert(liste_minimum(l) == 0);
  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_maximum(void)
{
  int erreurs = 0;

  liste* const l = liste_range(0, 10, 1);
  erreurs += assert(liste_maximum(l) == 9);
  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_carre(void)
{
  int erreurs = 0;

  liste* const l = liste_range(0, 10, 1);
  liste* const c = liste_carre(l);

  erreurs += assert(liste_longueur(c) == 10);
  if (liste_longueur(c) == 10)
    for (size_t i = 0; i < 10; ++i)
      erreurs += assert(liste_element(liste_ieme(c, i)) == (S) (i * i));
  liste_free(l);
  liste_free(c);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline bool lt_0(S x) {return x < 0; }
static inline bool ge_0(S x) {return x >= 0; }

static inline int test_liste_any(void)
{
  int erreurs = 0;

  liste* const l = liste_range(0, 10, 1);

  erreurs += assert(!liste_any(l, lt_0));
  erreurs += assert(liste_any(l, ge_0));
  erreurs += assert(liste_any(l, gt_5));
  erreurs += assert(liste_any(l, le_5));

  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}

static inline int test_liste_all(void)
{
  int erreurs = 0;

  liste* const l = liste_range(0, 10, 1);

  erreurs += assert(!liste_all(l, lt_0));
  erreurs += assert(liste_all(l, ge_0));
  erreurs += assert(!liste_all(l, gt_5));
  erreurs += assert(!liste_all(l, le_5));

  liste_free(l);

  fprintf(stderr, "%s(): %s\n", __func__, erreurs ? "FAIL" : "OK");
  return erreurs;
}


int main(int argc, char* argv[argc + 1])
{
  (void) argc; (void) argv;

  int erreurs = 0;

  erreurs += test_liste_insertion_tete();
  erreurs += test_liste_insertion_queue();
  erreurs += test_liste_suppression_tete();
  erreurs += test_liste_suppression_queue();
  erreurs += test_liste_range();
  erreurs += test_liste_reverse();
  erreurs += test_liste_map();
  erreurs += test_liste_filter();
  erreurs += test_liste_reduce();
  erreurs += test_liste_fold_left();
  erreurs += test_liste_fold_right();
  erreurs += test_liste_somme();
  erreurs += test_liste_produit();
  erreurs += test_liste_minimum();
  erreurs += test_liste_maximum();
  erreurs += test_liste_carre();
  erreurs += test_liste_any();
  erreurs += test_liste_all();

  return erreurs ? 1 : 0;
}
