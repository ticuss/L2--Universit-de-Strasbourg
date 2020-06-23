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
 * \fn static void affiche_ligne (int c, int* ligne);
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
 * \param[in] étape un int qui représente le nombre des étapes
 *
 * \return ::int le nouveau étape
 *
 * \ingroup grille_interact
 */
int temps_evolution(int etape);
#endif
