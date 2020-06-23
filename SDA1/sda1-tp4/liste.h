#ifndef _LISTE_H_
#define _LISTE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "attributes.h"

/**
 * \brief Liste
 */
typedef struct liste liste;

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Retourne une liste vide.
 * \return Une liste vide.
 *
 * \post liste_longueur() retourne 0.
 * \post liste_est_vide() retourne true.
 */
sda1_attribute((warn_unused_result)) liste* liste_vide(void);

/**
 * \brief Inserer des graines en tete de liste.
 * \param[in] l Liste d'entrée.
 * \param[in] graines Graines à insérer en tête.
 * \return La liste avec \a graines en tête.
 *
 * \post liste_ieme(l, 0) == graines
 * \post liste_longueur(liste_inserer_tete(l, g)) == (liste_longueur(l) + 1)
 */
sda1_attribute((warn_unused_result)) liste* liste_inserer_tete(
    liste* l, unsigned int graines);

/**
 * \brief Supprimer le ième élément d'une liste.
 * \param[in] l Liste d'entrée.
 * \param[in] i Indice de l'élément à supprimer.
 * \return La liste privée du ième élément.
 *
 * \pre 0 <= i < liste_longueur(l) lorsque liste_longueur(l) > 0
 * \post (liste_longueur(liste_supprimer(l, i)) == (liste_longueur(l) - 1))
 *       || (liste_longueur(liste_supprimer(l, i)) == 0)
 *
 * \note Pas de précondition sur la vacuité de la liste d'entrée.
 */
sda1_attribute((warn_unused_result)) liste* liste_supprimer(liste* l, size_t i);

////////////////////////////////////////////////////////////////////////////////
// Destructeurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Détruire une liste.
 * \note Peut accepter un pointeur nul / une liste vide.
 */
void liste_detruire(liste* l);

////////////////////////////////////////////////////////////////////////////////
// Sélecteurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Déterminer si une liste est vide.
 * \param[in] l La liste à éxaminer.
 * \return Un booléen qui indique si la liste fournie est vide.
 * \retval true si la liste est vide.
 * \retval false si la liste n'est pas vide.
 */
bool liste_est_vide(const liste* l);

/**
 * \brief Déterminer la longueur d'une liste.
 * \param[in] l La liste à éxaminer.
 * \return La longueur de la liste.
 */
size_t liste_longueur(const liste* l);

/**
 * \brief Obtenir le ième élément d'une liste.
 * \param[in] l La liste à éxaminer.
 * \return Le ième élément de la liste.
 *
 * \pre liste_longueur(l) > 0
 * \pre 0 <= i < liste_longueur(l)
 */
sda1_attribute((nonnull)) unsigned int liste_ieme(const liste* l, size_t i);

////////////////////////////////////////////////////////////////////////////////
// Modificateurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Égrainer une liste.
 * \param[in] l La liste à égrainer.
 * \param[in] i L'indice où démarrer l'égrainage.
 *
 * \pre liste_longueur(l) > 0
 * \post liste_ieme(l, i) == 0
 * \post Les graines à la position i ont été réparties sur les positions
 *       suivantes de manière circulaire.
 */
sda1_attribute((nonnull, warn_unused_result)) liste* liste_egrainer(
    liste* l, size_t i);

/**
 * \brief Égrainer une liste.
 * \param[in] l
 * \param[in] i
 * \param[in] graines
 *
 * \pre liste_longueur(l) > 0
 * \post liste_ieme(l, i) == graines
 */
sda1_attribute((nonnull, warn_unused_result)) liste* liste_modifier(
    liste* l, size_t i, unsigned int graines);

////////////////////////////////////////////////////////////////////////////////
// Divers
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Afficher une liste.
 * \param[in] stream Le flux où afficher la liste.
 * \param[in] l La liste à afficher.
 */
void liste_afficher(FILE* stream, const liste* l);

#endif
