#ifndef _polo_h_
#define _polo_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pile.h"
#include <ctype.h>
#include <math.h>


/**
   \param[in] *s un caractere de forme int.
   \brief Cette fonction transforme un char de forme int dans un int utilisant la relation  de code ascii
    '0' = 48
    '1' = 49
    '2' = 50
    ...
    et faisant le calcul 
    *val = (*s - '0') + 10 * *val;
    \return char
*/
char * sget_int(char *s, int *val);



/**
 * \param[in] *s un caracter de forme float.
 * \brief Transforme un char de forme float dans un float.
 * On parcourt la chaîne de caractères pour obtenir la position du point décimal.
 * Si un caractère autre qu'un point est rencontré, on l'ajoute au résultat.Lorsqu'on 
 * a terminé de parcourir la chaîne de caractères, on doit tenir compte de la puissance 
 * des chiffres avant la virgule décimale. Par exemple, le premier chiffre avant le point
 *  décimal est simplement ajouté au résultat. Le deuxième chiffre avant la virgule 
 * décimale est multiplié par 10,0 et ajouté au résultat, etc. Cela est accompli avec
 *  une simple boucle while comme indiqué dans le code.
*/

float sget_float(char *s);

/**
 * \brief Fonction qui testes  sget_float() et sget_int;
 * */

void test ();
/**
 * \brief fonction pour gestion d'erreur
 **/
void raler(const char *msg);


/**
 * \param[in] Pile p Une pile defini dans la fichier pile.c
 * \param[in] *s chaine de caractere qu'on veux analyser
 * \return un nombre float qui est le dernier element dans la pile .
 * \brief Pour cette fonction j' ai utilise la structure défini dans le fichier pile.h
 * et aussi les fonctions empiler() , depiler ().
 * j'ai utilisé  strtok() pour la separation  de la chaine de caractere, et pour
 *  la tranformation de caractere en float j'ai utilisé strtof(). 
 * J'ai séparé les operations avec des if et else parce que c'est plus clair personnellement. 
 * chaque opération qu'on fait on empile le resultat et comme ca la dernier element de la pile 
 * est le resultat finel
 * pour la partie gestion d'erreurs j'ai fais que pour les operations non défini
 * j'ai pas reussi d'implementer les autres comme mauvais input etc.
**/
float poloInv(Pile p ,char *s);


#endif