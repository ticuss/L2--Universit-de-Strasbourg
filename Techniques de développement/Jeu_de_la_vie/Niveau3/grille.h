#ifndef __GRILLE_H
#define __GRILLE_H
/**
 * \file gille.h
 * \brief Header pour ::grille, cette fiche concerne tous les opéraions à gérer les grilles.
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
typedef struct {int nbl; int nbc; int** cellules;} grille;
/**
 * \fn void alloue_grille (int l, int c, grille* g);
 * La création d'une nouvelle grille se fait à l'aide de la fonction   
 *alloue_grille pour allouer la mémoire pour une grille
 *et la fonction init_grille_from_file pour charger une grille à partir d'une fiche.  
 *
 * fn void alloue_grille (int l, int c, grille* g)
 * param l nombre de lignes
 * param c nombre de colonnes
 * param g pointeur vers une grille
 * brief alloue une grille de taille l*c, et initialise toutes les cellules
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
 * \fn void libere_grille (grille* g)
 * \param g pointeur vers une grille
 * \brief libre une grille
 *
 */
void libere_grille (grille* g);

/*/**
 * \fn void init_grille_from_file(char const *const filename, grille *const g)
 * \param filename pointeur vers un fichier
 * \param g pointeur vers une grille
 * \brief alloue et initalise la grille g  partir d'un fichier
 * alloue et initalise la grille g à partir d'un fichier
 */
void init_grille_from_file(char const*const filename, grille* g);
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
inline bool est_vivante(int i, int j, grille g) {
  return ((g.cellules[i][j]) > 0);
}

/**
 *
 * \void copie_grille (grille gs, grille gd)
 * \param gs grille
 * \param gd grille
 * \brief recopie gs dans gd
 *\recopie gs dans gd (sans allocation)
 */
void copie_grille(const grille *gs, grille *gd);

/**
* \brief rend non viable la cellule (i,j) de la grille g
* \param [in] x Index de la ligne
* \param [in] y Index de la colonne
* \param [in] g Structure grille
* \relates grille
*/
static inline void set_nonViable(int x, int y, grille g) {g.cellules[x][y] = -1;}

/**
* \brief teste si la cellule (i,j) de la grille g est non viable
* \param [in] i Index de la ligne
* \param [in] j Index de la colonne
* \param [in] g Structure grille
* \relates grille
* \return 1 si la cellule est non viable, 0 dans le cas contraire.
*/
static inline int est_nonViable(int i, int j, grille g) {return g.cellules[i][j] == -1;}
/**
 * \brief fait vieillir la cellule d'1 an
 * \param [in] i Index de la ligne
 * \param [in] j Index de la colonne
 * \param [in] g Structure grille
 * \relates grille
 */
static inline void vieillir(int i, int j, grille g) {g.cellules[i][j] += 1;}

inline void set_mute(int i, int j, grille g) {
  g.cellules[i][j] = -1;
}


#endif
