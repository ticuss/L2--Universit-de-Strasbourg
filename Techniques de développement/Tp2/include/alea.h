#include <stdlib.h>
#include "tableau.h"
#ifndef __alea_h__
#define __alea_h__

extern tableau t ;

// tire un entier aléatoire entre 0 et m
int alea (int m);

// remplit t avec des valeurs aléatoires
void remplir (int m);
#endif
