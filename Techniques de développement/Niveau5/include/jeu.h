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
 *\fn int compte_voisins_vivants_cyclique (int i, int j, grille g);
 *\fn int compte_voisins_vivants_non_cyclique (int i, int j, grille g);
 * \details Ici, on vous propose deux mode de calcul: Cyclique et Non_Cyclique.
 * Ils se réalise par /code compte_voisins_vivants_cyclique(); /endcode et /code compte_voisins_vivants_non_cyclique(); /endcode respectivement.
 *
 * \param i L'indice de ligne.
 * \param j L'indice de colonne.
 * \param g La grille comme source de data.
 * \return int Le nombre total des voisins vivants.
 *
 * \pre La cellule \code (i,j) \endcode existe dans la ::grille
 *
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g);

int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

/**
 * \brief Une fonction qui sert au jeu pour se progresser
 * \fn void evolue (grille *g, grille *gc, int (*compte_voisins_vivants)(int,int,grille));
 * \param *g La ::grille comme source de data
 * \param *gc Une copie de la ::grille de source qui est est utile seulement temporairement pour les calcul.
 * \param (*compte_voisins_vivants(int,int,grille)) Un pointeur de fonction qui nous permet de changer entre deux mode de calcul.
 * \pre Les pointeurs ne sont pas pointeur NULL.
 * \return void
 *
 */
void evolue (grille *g, grille *gc, int (*compte_voisins_vivants)(int,int,grille));

#endif
