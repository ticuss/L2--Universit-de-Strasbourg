
//author BOGDANAS CONSTANTIN 

// file_dbl.h
#ifndef __FILES_DBL_H__
#define __FILES_DBL_H__

/*-------------------------------------
*Rappel de la signature
*
*    filevide : -> File
*    adjq : S File -> File
*    supt : File -> File
*    tete : File -> S
*    estvide : File -> Bool
*    lgr : File -> Nat
*
*   comme d'habitude, toutes les fonctions C correspondantes seront préfixées par file_
*   (sauf filevide qui devient file_vide() )
*------------------------------------*/
#include<stdbool.h>
#define S int
#define S_ELEM 42
#define FILE_VIDE ((file) NULL)
typedef unsigned Nat;
typedef struct strfile {
    S val;
    struct strfile *next, 
                   *prev;
} Strfile, *file;
// une file est implantée par une liste doublement chaînée avec un pointeur
// sur le dernier élément (l'adjonction en queue change donc le point d'accès)
// la valeur de next du dernier élément pointe sur le premier élément de la liste
// la valeur de prev du premier élément pointe sur le dernier élément de la liste



// pre : vrai
// post : retourne FILE_VIDE
// modif : aucune
file    file_vide();

// pre : vrai
// post : retourne la file modifiée par adjonction en queue
//        attention, cette adresse peut être différente de celle donnée
// modif : la structure pointée par f est modifiée, allocation d'une nouvelle cellule
file    file_adjq(S x, file f);

// pre file_supt(f) = ! file_estvide(f) 
// post : retourne la file modifiée par la suppression de la tête
// modif : la structure pointée f est modifiée, désallocation d'une cellule
file    file_supt(file f);

// pre file_tete(f) = ! file_estvide(f)
// post : retourne la tête de la file
// modif : aucune
S       file_tete(file f);

// pre : vrai
// post : test de vacuité
// modif : aucune
bool    file_estvide(file f);

// pre : vrai
// post : retourne le nombre d'élement dans la file
// modif : aucune
Nat     file_lgr(file f);

// pre : vrai
// post : 
// modif : 
file file_ins(file f, Nat place, S x);

// pre : vrai
// post : 
// modif : 
file file_dd(file f, Nat decD);

// pre : vrai
// post : 
// modif : 
file file_gg(file f, Nat decG);

void raler(char *msg);









#endif
