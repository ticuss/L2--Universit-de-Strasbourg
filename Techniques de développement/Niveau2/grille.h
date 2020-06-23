#ifndef __GRILLE_H
#define __GRILLE_H
/**
 * \file gille.h
 * \brief Header pour ::grille, cette fiche concerne tous les opéraions à gérer les grilles.
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
typedef struct {int nbl; int nbc; int** cellules;} grille;
/**
 * \fn void alloue_grille (int l, int c, grille* g);
 * La création d'une nouvelle grille se fait à l'aide de la fonction   
 *alloue_grille pour allouer la mémoire pour une grille
 *et la fonction init_grille_from_file pour charger une grille à partir d'une fiche.  
 */

/**
 * \brief Allouer la mémoire pour une ::grile
 * \return void
 * \param[in] l-taille de ligne, c-taille de colonne, g-pointeur de type grille
 * \see file_detruit
 *
 * \memberof grille
 * \ingroup file_constructeurs
 */
void alloue_grille (int l, int c, grille* g);
/**
 * \brief Détruire la ::grille g.
 * \param[in] g grille à détruire.
 * libère une grille
 *
 */
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char * filename, grille* g);
/**
 * \brief Mettre l'état de la cellule (i,j) dans ::grille g à vivante
 * \param[in] i la position en ligne
 * \param[in] j la position en colonne
 * \param[in] g la ::grille à accéder
 * \return void
 * rend vivante la cellule (i,j) de la grille g
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}
/**
 * \brief Mettre l'état de la cellule (i,j) dans ::grille g à morte
 * \param[in] i la position en ligne
 * \param[in] j la position en colonne
 * \param[in] g la ::grille à accéder
 * \return void
 *rend morte la cellule (i,j) de la grille g
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}
/**
 * \brief Tester si l'état de la cellule (i,j) dans ::grille g est vivante
 * \param[in] i la position en ligne
 * \param[in] j la position en colonne
 * \param[in] g la ::grille à accéder
 * \return un boolean qui représente si la cellule est vivante
 *
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] == 1;}

// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

#endif
