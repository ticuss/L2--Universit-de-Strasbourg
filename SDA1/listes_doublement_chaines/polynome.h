#ifndef _POLYNOME_H_
#define _POLYNOME_H_

/** \file polynome.h
 * structures de données et déclarations pour les polynômes
 */

#include <stdio.h>
#include "liste.h"

/**
 * \defgroup polynome_module Polynôme
 * \copydetails polynome
 */


/**
 * \struct polynome
 * \brief Polynômes.
 * \see liste
 *
 * Un polynôme est une liste doublement chaînée de monômes normalisée.
 *
 * Attention, la liste doublement chaînée est toujours stockée dans
 * l'ordre des degrés des monômes qui la constituent.
 * Il n'y a pas de doublon de monômes de même degré.
 *
 * \ingroup polynome_module
 */
typedef liste polynome;

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup polynome_constructeurs Constructeurs
 * \brief Constructeurs pour ::polynome.
 *
 * \ingroup polynome_module
 */

/**
 * \brief Additionner deux polynômes.
 * \param[in] P1 Premier polynôme.
 * \param[in] P2 Second polynôme.
 * \return Le polynôme \a P1 + \ aP2.
 *
 * \warning Cette fonction retourne un nouveau polynôme qu'il ne faut pas
 *          oublier de libérer avec liste_free().
 *
 * \memberof polynome
 * \ingroup polynome_constructeurs
 */
polynome* polynome_addition(const polynome* P1, const polynome* P2);

/**
 * \brief Multiplier deux polynômes.
 * \param[in] P1 Premier polynôme.
 * \param[in] P2 Second polynôme.
 * \return Le polynôme \a P1 * \ aP2.
 *
 * \warning Cette fonction retourne un nouveau polynôme qu'il ne faut pas
 *          oublier de libérer avec liste_free().
 *
 * \memberof polynome
 * \ingroup polynome_constructeurs
 */
polynome* polynome_multiplication(const polynome* P1, const polynome* P2);

/**
 * \brief Dériver un polynôme.
 * \param[in] P1 Premier polynôme.
 * \return La dérivée du polynôme \a P1.
 *
 * \warning Cette fonction retourne un nouveau polynôme qu'il ne faut pas
 *          oublier de libérer avec liste_free().
 *
 * \memberof polynome
 * \ingroup polynome_constructeurs
 */
polynome* polynome_derivee(const polynome* P1);

////////////////////////////////////////////////////////////////////////////////
// Divers
////////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup polynome_divers Divers
 * \brief Fonctions diverses pour ::polynome.
 *
 * \ingroup polynome_module
 */

/**
 * \brief Détruire un polynôme.
 * \param[in] p Polynôme à détruire.
 *
 * \memberof polynome
 * \ingroup polynome_divers
 */
void polynome_free(polynome* p);

polynome* polynome_sread(const char* input);

/**
 * \brief Lire un polynôme depuis un fichier.
 * \param[in] stream Fichier d'entrée
 * \return Le polynome lue.
 *
 * \memberof polynome
 * \see polynome_write
 * \ingroup polynome_divers
 */
polynome* polynome_fread(FILE* stream);

/**
 * Écrire un polynôme dans un fichier.
 * \param[in] stream Fichier de destination
 * \param[in] P      Polynôme à afficher.
 *
 * \memberof polynome
 * \see polynome_fread
 * \ingroup polynome_divers
 */
void polynome_fwrite(FILE* stream, const polynome* P);

#endif
