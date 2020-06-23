#ifndef _arbrin_h_
#define _arbrin_h_
#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include <time.h>
typedef struct s_noeud 
{ 
    int elmt; 
    struct s_noeud * FilsGauche, * FilsDroit;
 } noeud, *abin;  


void raler(char *msg, int returnCode);

abin emptyNode();
abin createNode(int elemt);

abin enraciner(abin left, int elt, abin right);
bool isPresente(const abin binaire, int elemt) ;
Nat nombreNode(abin node) ;
Nat nombreFeuille(abin node) ;
abin extremeLeft(const abin node) ;
abin extremeRight(const abin node) ;
void printfPrefixe(const abin node) ;
void freeAllNodes(abin new1) ;

int getAleatInt(int min, int max);

#endif