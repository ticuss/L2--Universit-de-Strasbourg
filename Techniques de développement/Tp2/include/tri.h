#include <stdio.h>
#include "tableau.h"
#ifndef __tri_h__
#define __tri_h__
extern tableau t ;

// fait remonter une bulle jusqu'à la case k
void bulle (int k) ;

// tri (décroissant) du tableau t par la méthode du tri à bulle 
void trier ();

#endif
