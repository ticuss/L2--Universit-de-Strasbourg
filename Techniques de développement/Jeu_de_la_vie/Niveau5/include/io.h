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
#ifndef __IO_H
#define __IO_H
/**
 * \file io.h
 * \brief Header pour les manipulations aux contenus de la grille.
 */
#include <stdio.h>
#include "grille.h"
#include "jeu.h"
/**
 * #Introduction
 *
 * Cette module "io" nous permet de faire des opérations comme affichage et modifications du contenu
 * d'une ::grille à la base de la module ::grille
 */
/**
 * \fn void affiche_trait (int c)
 * \param c nombre colonnes
 * \brief affichange d'un trait
 */
// affichage d'un trait horizontal
void affiche_trait (int c);
/**
 * \fn static void affiche_ligne_o (int c, int* ligne);
 * \fn static void affiche_ligne_v (int c, int* ligne);
 * \brief affichage d'une ligne de la grille
 */
// affichage d'une ligne de la grille
void affiche_ligne_o(int ligne, const grille *g);
void affiche_ligne_v(int ligne, const grille *g);


/**
 * \fn void affiche_grille (grille g)
 * \param *g grille
 * \brief affichange d'une grille
 */
void affiche_grille (const grille *g, void (*affiche_ligne)(int,const grille* ));
/**
 * \fn void efface_grille (const grille g)
 * \param g grille
 * \brief effacement d'une grille
 */
void efface_grille (const grille *g);
/**
 * \fn void debut_jeu(grille *g, grille *gc)
 * \param g pointeur vers une grille
 * \param gc pointeur vers une grille (copy)
 * \brief debute le jeu
 */
void debut_jeu(grille *g, grille *gc);
/**
 * \brief Un compteur des étapes
 * \param étape un int qui représente le nombre des étapes
 *
 * \return ::int le nouveau étape
 *
 */
int temps_evolution(int etape);
#endif
