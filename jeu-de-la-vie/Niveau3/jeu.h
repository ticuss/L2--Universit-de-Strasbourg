#ifndef __JEU_H
#define __JEU_H

#include "grille.h"
/**
 * \fn int compte_voisins_vivants(int i, int j, grille g)
 * \param i indice ligne
 * \param j indice colonne
 * \param g grille
 * \return v nombre de voisins vivants
 * \brief compte le nombre de voisins vivants de la cellule
 *
 *modulo modifié pour traiter correctement les bords i=0 et j=0
 *dans le calcul des voisins avec bords cycliques
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * \brief Caldul le nombre des voisins vivants d'une cellule.
 *
 * \details Ici, on vous propose deux mode de calcul: Cyclique et Non_Cyclique.
 * Ils se réalise par /code compte_voisins_vivants_cyclique(); /endcode et /code compte_voisins_vivants_non_cyclique(); /endcode respectivement.
 *
 * \param[in] i L'indice de ligne.
 * \param[in] j L'indice de colonne.
 * \param[in] g La grille comme source de data.
 * \return int Le nombre total des voisins vivants.
 *
 * \pre La cellule \code (i,j) \endcode existe dans la ::grille
 *
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g);

int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

/**
 * \brief Une fonction qui sert au jeu pour se progresser
 * \param[in] *g La ::grille comme source de data
 * \param[in] *gc Une copie de la ::grille de source qui est est utile seulement temporairement pour les calcul.
 * \param[in] (*compte_voisins_vivants(int,int,grille)) Un pointeur de fonction qui nous permet de changer entre deux mode de calcul.
 * \pre Les pointeurs ne sont pas pointeur NULL.
 * \return void
 *
 */
void evolue (grille *g, grille *gc, int (*compte_voisins_vivants)(int,int,grille));

#endif
