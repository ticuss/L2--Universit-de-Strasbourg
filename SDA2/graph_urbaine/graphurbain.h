#ifndef _graphurbain_h_
// TP3  

#include "stdlib.h"
#include "memory.h"
#include "stdio.h"
#include "stdbool.h"
#include "listeui.h"
/******************************************/
/*
// grapheurbain.h
*/

typedef struct strarc { unsigned int icf, irue; struct strarc *suc; } Strarc, *ListeSom;
typedef struct { unsigned int icf; ListeSom lsucc, lpred; }  Sommet;
typedef struct strsom { Sommet  c; struct strsom *suiv; } Strsom, *grapheurbain;

// operations de creation et destruction
grapheurbain grapheurbainNouv();
void grapheurbainFree(grapheurbain g);

// operations usuelles sur les graphes
void addCarrefour(grapheurbain *g, unsigned int icar);
void supCarrefour(grapheurbain *g, unsigned int icar);

void addRue(grapheurbain *g, unsigned int ico, unsigned int ice, unsigned int irue);
void addRueDoubleSens(grapheurbain *g, unsigned int ico, unsigned int ice, unsigned int irue);
void supRue(grapheurbain *g, unsigned int ico, unsigned int ice);

bool existeArc(grapheurbain g, unsigned int ico, unsigned int ice);
bool existeCarrefour(grapheurbain g, unsigned int icar);

// operations sur les listes de successeurs et predecesseurs
// les carrefours associes a une rue
listeui carrefoursDeRue(grapheurbain g, unsigned int irue);
// les rues incidentes en un carrefour
listeui ruesDeCarrefour(grapheurbain g, unsigned int icar);
// les rues croisant une autre rue
listeui ruesCroisement(grapheurbain g, unsigned int irue);

// operations internes sur les listes chainees constituant le graph
// recherche le maillon qui contient icar
grapheurbain rechCarrefour(grapheurbain g, unsigned int icar);
// recherche le maillon de ListeSom qui contient icar
ListeSom rechArc(ListeSom ls, unsigned int icar);
// recherche le maillon de ListeSom qui contient irue
ListeSom rechArcVal(ListeSom ls, unsigned int irue);
// supprime le maillon de ListeSom qui contient icar
ListeSom supArc(ListeSom ls, unsigned int icar);
// ajoute en t�te un maillon � ListeSom qui contient icar, irue
ListeSom adjArc(ListeSom ls, unsigned int icar, unsigned int irue);

#endif