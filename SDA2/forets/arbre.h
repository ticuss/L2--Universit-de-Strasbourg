#ifndef _arbre_h_
#define _arbre_h_

#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define getMax(a,b) ((a) > (b)?(a):(b))


typedef struct s_noeud {
     int val;
      struct s_noeud    *fils, *frere; 
    } noeud, *arbre; 

/**
 * 
 * \brief Cette fonction cree un arbre vide ;
 * \return arbre
 **/

arbre arbrevide();
/**
 *
 *  \param[in] x = un integer qu'on veut introduire dans un noeud
 * \param[in] arbre frere = pointeur vers le frere 
 * \param[in] arbre fils = pointeur vers le fils 
 * \brief Cette fonction cree un node pour notre arbre aussi on reserve la mémoire pour notre noeud.
 * */

arbre nouvnoeud(int x ,arbre frere ,  arbre fils );

/**
 *
 *  \param[in] a arbre 
 *  \brief retourne le poiteur fils;
 * 
 * 
 * \return arbre
 * */
arbre fils(arbre a);
/**
 *
 *  \param[in] a arbre qu'on analyse
 *  \brief retourne le poiteur frere;
 * \return arbre
 * */

arbre frere(arbre a );
/**
 *
 *  \param[in] a arbre  qu'on analyse
 *  \brief test si l'arbre est vide ou non; 
 * \return bool
*/
bool est_vide(arbre a);
/**
 *
 *  \param[in] a arbre qu'on analyse
 *  \brief test si le noeud  est une feuille ou non; 
 * \return bool
*/

bool est_feuille(arbre a); 
/**
 *
 *  \param[in] a arbre qu'on analyse
 * \param[in] x int
 *  \brief test si x = le noeud fils ou non; 
 * \return bool
*/
bool est_fils(arbre a, int x);
/**
 *
 *  \param[in] a arbre qu'on analyse
 *  \brief cette fonction compte combien des fils on a dans cet arbre, pour le calculer  j'ai utilisé la boucle while et un compteur 
 * \return unsigned int le nombre total des fils de notre arbre 
*/
unsigned int nb_fils(arbre a);
/**
 *
 *  \param[in] a arbre qu'on analyse
 *  \brief cette fonction affiche l'arbre utilisant itération mais je ne suis pas arrivé a un bon affichage
 *  
 * */
void printfPrefixe(const arbre node); 

/**
 *
 *  \param[in] a arbre qu'on analyse
 *  \brief cette fonction calcule la hauteur du notre arbre cette fonction c'était la plus difficile pour moi 
 *  car je n'avais pas des idées comment je peux trouver la hauteur maximale de graphe j'avais perdu beaucoup du temps pour trouver une idée, et l'idée géniale c'etais de comparer 
 * hauteur(a->frere); avec  hauteur(a->fils); qui nous donne la hauteur plus grande possible
 *  
 * */
unsigned int hauteur(arbre a);
/**
 *
 *  \param[in]  a arbre qu'on analyse
 * \param[in] x integer qui est la valeur qu'on veut voir si est stocke dans l'arbre 
 * \brief cette fonction m'a faits beaucoup des problèmes car même maintenant je comprends pas pourquoi la fonction ne parcour pas les frères pour voir si c'est une étiquette ou non.
 * La fonction renvoie l'integer qui est stocké dans le noeud mais juste pour les fils gauches de la racine dans notre exemple c'est 
 * \return integer s'il appartient au arbre
*/
int etiquette(arbre a,int x);


#endif