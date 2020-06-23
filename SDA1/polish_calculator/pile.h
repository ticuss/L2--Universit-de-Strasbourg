#ifndef _pile_h_
#define _piles_h_

#include <stdio.h>
#include "base.h"

#define N 100000

typedef struct strpile{
  Nat h;
  float tab[N];
} strPile, *Pile;

Pile pileNouv();
Bool vide(Pile p);
Pile empiler(Pile p, float x);
Pile depiler(Pile p);
Nat hauteur(Pile p);
void afficher(Pile p);
float acces (Pile p) ;
#endif