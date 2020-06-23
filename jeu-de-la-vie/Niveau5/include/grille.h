/*
 * Copyright (c) 2019 Bogdanas Constantin <ticu369@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
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
// structure grille : nombre de lignes, nombre de colonnes,
//tableau de tableau de cellules

typedef struct {
	int nbl;/**numero de ligne **/
	int nbc;/**numero de Colonne **/
	int** cellules; /** les cellules de la grille en tableau */
	} grille;


/**
 * \fn void alloue_grille (int l, int c, grille* g);
 * La création d'une nouvelle grille se fait à l'aide de la fonction   
 *alloue_grille pour allouer la mémoire pour une grille
 *et la fonction init_grille_from_file pour charger une grille à partir d'une fiche.  
 *
 * param l nombre de lignes
 * param c nombre de colonnes
 * param g pointeur vers une grille
 * brief alloue une grille de taille l*c, et initialise toutes les cellules
 */

void alloue_grille (int l, int c, grille* g);
/**
 * \brief Détruire la ::grille g.
 * \param g grille à détruire.
 * libère une grille
 *
 * \fn void libere_grille (grille* g)
 * \param g pointeur vers une grille
 * \brief libre une grille
 *
 */
void libere_grille (grille* g);

/**
 * \fn void init_grille_from_file(char const *const filename, grille *const g)
 * \param filename pointeur vers un fichier
 * \param g pointeur vers une grille
 * \brief alloue et initalise la grille g  partir d'un fichier
 * alloue et initalise la grille g à partir d'un fichier
 */
void init_grille_from_file(char const*const filename, grille* g);
/**
 * \brief Mettre l'état de la cellule (i,j) dans ::grille g à vivante
 * \param i la position en ligne
 * \param j la position en colonne
 * \param g la ::grille à accéder
 * \return void
 * rend vivante la cellule (i,j) de la grille g
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}
/**
 * \brief Mettre l'état de la cellule (i,j) dans ::grille g à morte
 * \param i la position en ligne
 * \param j la position en colonne
 * \param g la ::grille à accéder
 * \return void
 *rend morte la cellule (i,j) de la grille g
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}
/**
 * \brief Tester si l'état de la cellule (i,j) dans ::grille g est vivante
 * \param i la position en ligne
 * \param j la position en colonne
 * \param g la ::grille à accéder
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
* \param  x Index de la ligne
* \param  y Index de la colonne
* \param  g Structure grille
* \relates grille
*/
static inline void set_nonViable(int x, int y, grille g) {g.cellules[x][y] = -1;}

/**
* \brief teste si la cellule (i,j) de la grille g est non viable
* \param  i Index de la ligne
* \param  j Index de la colonne
* \param  g Structure grille
* \relates grille
* \return 1 si la cellule est non viable, 0 dans le cas contraire.
*/
static inline int est_nonViable(int i, int j, grille g) {return g.cellules[i][j] == -1;}
/**
 * \brief fait vieillir la cellule d'1 an
 * \param  i Index de la ligne
 * \param  j Index de la colonne
 * \param  g Structure grille
 * \relates grille
 */
/**
 * \brief Mettre l'état de la cellule (i,j) dans ::grille g à mute
 * \param i la position ligne
 * \param j la position colonne
 * \param g la grille à accéder
 * \return void
 */
inline void set_mute(int i, int j, grille g) {
  g.cellules[i][j] = -1;
}

#endif
