#ifndef _LISTE_AVANCEE_H_
#define _LISTE_AVANCEE_H_

#include <stddef.h>
#include <stdbool.h>

#include "sorte.h"
#include "liste.h"

liste* liste_range(S debut, S fin, S pas);
liste* liste_reverse(const liste* l);
liste* liste_map(const liste* l, S (*f)(S));
liste* liste_filter(const liste* l, bool (*f)(S));
S liste_reduce(const liste* l, S (*f)(S, S));
void liste_fold_left(const liste* l, void (*f)(void*, S), void* resultat);
void liste_fold_right(const liste* l, void (*f)(S, void*), void* resultat);

S liste_somme(const liste* l);
S liste_produit(const liste* l);
S liste_minimum(const liste* l);
S liste_maximum(const liste* l);
liste* liste_carre(const liste* l);
bool liste_odd(const liste* l);
bool liste_even(const liste* l);
bool liste_any(const liste* l, bool (*f)(S));
bool liste_all(const liste* l, bool (*f)(S));

//les fonctions ajoutés 
S add(S x, S y);
S produit(S x,S y);
S min(S x, S y);
S max(S x, S y);
S carre(S x);



#endif
