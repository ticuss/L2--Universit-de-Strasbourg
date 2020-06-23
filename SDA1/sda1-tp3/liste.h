#ifndef _LISTE_H_
#define _LISTE_H_

/**
 * \file liste.h
 * \brief Header pour les listes doublement chaînées.
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include "monome.h"

/**
 * \defgroup liste_module Liste
 * \copydetails liste
 */

/**
 * \struct liste
 * \brief Listes de termes représentés par des ::monome.
 *
 * # Introduction
 * 
 * ::liste représente des listes de ::monome.
 *
 * # Constructeurs
 * \see \ref liste_constructeurs
 *
 * \copydetails liste_constructeurs
 *
 * # Destructeurs
 * \see \ref liste_destructeurs
 *
 * \copydetails liste_destructeurs
 *
 * # Sélecteurs
 * \see \ref liste_selecteurs
 *
 * \copydetails liste_selecteurs
 *
 * # Divers
 * \see \ref liste_divers
 *
 * \copydetails liste_divers
 *
 * # Exemple
 *
 * \code
 * liste* l = liste_vide();
 * liste_free(l);
 * \endcode
 *
 * \ingroup liste_module
 */
typedef struct liste liste;

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup liste_constructeurs Constructeurs
 * \brief Constructeurs pour ::liste.
 *
 * \ingroup liste_module
 */

/**
 * \brief Obtenir une liste vide.
 * \return Une liste vide.
 *
 * \memberof liste
 * \ingroup liste_constructeurs
 * \see liste_free
 */
liste* liste_vide(void);

/**
 * \brief Insérer un nouveau terme dans la liste.
 * \param[in,out] l Liste où insérer le terme.
 * \param[in]     t Terme à insérer.
 * \return Le maillon qui contient t.
 *
 * Le nouveau terme est inséré juste avant le maillon pointé par l.
 *
 * \post
 * - La valeur précédemment retournée pour \a l par la fonction
 *   liste_precedent() doit être retournée par la fonction liste_precedent()
 *   pour le résultat de liste_inserer().
 * - La valeur retournée pour le résultat de liste_inserer() par la fonction
 *   liste_precedent() doit être \a l.
 * - Le monome \a t est le monome se trouvant dans le maillon retourné par la
 *   fonction liste_inserer().
 *
 * \memberof liste
 * \ingroup liste_constructeurs
 */
liste* liste_inserer(liste* l, monome t);

/**
 * \brief Supprimer le maillon pointé.
 * \param[in,out] l Une liste
 * \return La maillon suivant s'il y en a un sinon le maillon précédent.
 *
 * \memberof liste
 * \ingroup liste_constructeurs
 */
liste* liste_supprimer(liste* l);

/**
 * \brief Échanger un monôme avec le monôme suivant.
 * \param[in,out] l une liste (position courante)
 * \return La liste
 *
 * \pre \code !liste_est_vide(l) && !liste_est_vide(liste_suivant(l)) \endcode
 * \memberof liste
 * \ingroup liste_constructeurs
 */
liste* liste_echanger(liste* l);

/**
 * \brief Normaliser une liste.
 * \param[in,out] l Une liste.
 * \return La liste normalisée.
 *
 * Place ses monômes dans l'ordre de leurs degrés et élimine les duplicata
 * (en faisant la somme des coefficients).
 *
 * \post Pour un degré d donné, 0 un 1 monome dans la liste.
 * \post Dégré d'un monôme dans la liste > au degré du monôme suivant.
 *
 * \memberof liste
 * \ingroup liste_constructeurs
 */
liste* liste_normaliser(liste* l);

////////////////////////////////////////////////////////////////////////////////
// Destructeurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup liste_destructeurs Destructeurs
 * \brief Destructeurs pour ::liste.
 *
 * Une ::liste peut être détruite avec liste_free().
 *
 * \ingroup liste_module
 */

/**
 * \brief Détruit une ::liste.
 * \param[in] l Liste à détruire
 *
 * \warning \a l ne doit pas être utiisée après cet appel
 *
 * \memberof liste
 * \ingroup liste_destructeurs
 */
void liste_free(liste* l);

////////////////////////////////////////////////////////////////////////////////
// Sélecteurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup liste_selecteurs Sélecteurs
 * \brief Sélecteurs pour ::liste.
 *
 * liste_estvide() permet de vérifier si une ::liste est vide tandis que
 * liste_longueur() retourne la longueur d'une ::liste. L'élément contenu par
 * un maillon donné peut être obtenu avec la fonction liste_monome().
 *
 * La fonction liste_est_debut() permet de déterminer si un maillon donné
 * correspond au début de la ::liste dont il fait partie tandis que
 * la fonction liste_debut() retourne le maillon se trouvant aud début d'une
 * ::liste.
 *
 * \ingroup liste_module
 */

/**
 * \brief Obtenir le monome contenu dans un maillon.
 * \param[in] l Liste à éxaminer.
 * \return Le monome contenu dans le maillon.
 *
 * \pre !liste_est_vide(l)
 *
 * \memberof liste
 * \ingroup liste_selecteurs
 */
monome liste_monome(const liste* l);

/**
 * \brief Déterminer si une liste est vide.
 * \param[in] l Liste à éxaminer.
 * \return Un booléen qui indique si la liste est vide.
 * \retval true Si la liste est vide,
 * \retval false sinon.
 *
 * \memberof liste
 * \ingroup liste_selecteurs
 */
bool liste_est_vide(const liste* l);

/**
 * \brief Déterminer si un maillon est le début de sa liste.
 * \param[in] l Liste à éxaminer.
 * \return Un booléen qui indique si le maillon est le début de sa liste.
 * \retval true Si le maillon est le début de sa liste.
 * \retval false sinon.
 *
 * \memberof liste
 * \ingroup liste_selecteurs
 */
bool liste_est_debut(const liste* l);

/**
 * \brief Déterminer si un maillon est le début de sa liste.
 * \param[in] l Liste à éxaminer.
 * \return Premier maillon de la liste.
 *
 * \memberof liste
 * \ingroup liste_selecteurs
 */
liste* liste_debut(const liste* l);

/**
 * \brief Obtenir le maillon suivant dans la liste.
 * \param[in] l Une liste
 * \return Maillon suivant dans la liste.
 *
 * \pre !liste_est_vide(l)
 *
 * \memberof liste
 * \ingroup liste_selecteurs
 */
liste* liste_suivant(const liste* l);

/**
 * \brief Obtenir le maillon précédent dans la liste.
 * \param[in] l Une liste
 * \return Maillon précédent dans la liste.
 *
 * \pre !liste_est_vide(l)
 *
 * \memberof liste
 * \ingroup liste_selecteurs
 */
liste* liste_precedent(const liste* l);

/** \memberof liste
 * \brief Obtenir le ième maillon de la liste chaînée.
 * \param[in] l Liste à éxaminer.
 * \param[in] i Position du maillon.
 * \return ième maillon de la liste chaînée.
 *
 * \pre 0 <= i < liste_longueur(l)
 * \note liste_debut(l) == liste_ieme(l, 0)
 *
 * \memberof liste
 * \ingroup liste_selecteurs
 */
liste* liste_ieme(const liste* l, size_t i);

/**
 * \brief Déterminer la longueur d'une liste.
 * \param[in] l La liste à éxaminer.
 * \return Longueur de la liste.
 *
 * \memberof liste
 * \ingroup liste_selecteurs
 */
size_t liste_longueur(const liste* l);

////////////////////////////////////////////////////////////////////////////////
// Divers
////////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup liste_divers Divers
 * \brief Fonctions diverses pour ::liste.
 *
 * \ingroup liste_module
 */

/**
 * \brief Lire une liste depuis une chaîne de caractères.
 * \param[in] string Chaîne de caractères.
 * \return La liste lue.
 *
 * \memberof liste
 * \see liste_write
 */
liste* liste_sread(const char* string);

/**
 * \brief Lire une liste depuis un fichier.
 * \param[in] stream Fichier d'entrée
 * \return La liste lue.
 *
 * \memberof liste
 * \see liste_write
 */
liste* liste_fread(FILE* stream);

/**
 * Écrire une liste dans un fichier.
 * \param[in] stream Fichier de destination
 * \param[in] l      Liste à afficher.
 *
 * \memberof liste
 * \see liste_fread
 */
void liste_fwrite(FILE* stream, const liste* l);

#endif
