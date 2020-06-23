#ifndef _MANKALA_H_
#define _MANKALA_H_

#include <stdint.h>

#include "attributes.h"
#include "liste.h"

typedef struct mancala mancala;

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Initialiser le jeu.
 * \param[in] champs Le nombre de champs par joueur.
 * \param[in] graines Le nombre de graines par champs.
 * \return Un jeu initialisé.
 */
sda1_attribute((warn_unused_result)) mancala* mancala_init(
    size_t champs, unsigned int graines);

////////////////////////////////////////////////////////////////////////////////
// Destructeurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Détruire un jeu.
 * \param[in] m le jeu à détruire.
 */
void mancala_free(mancala* m);

////////////////////////////////////////////////////////////////////////////////
// Sélecteurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Déterminer si égrainer le champ i est un coup valide pour le joueur.
 * \param[in] m le jeu du mancala à éxaminer.
 * \param[in] i l'indice du champ à égrainer.
 * \return Un booléen qui indique si le champ i peut être égrainé par le joueur.
 * \retval true si le champ peut être égrainé par le joueur courant.
 * \retval false sinon.
 */
sda1_attribute((nonnull)) bool mancala_coup_valide(const mancala* m, size_t i);

/**
 * \brief Déterminer si le joueur peut brûler des champs.
 * \param[in] m le jeu du mancala à éxaminer.
 * \return Un booléen qui indique si le joueur peut brûler des champs.
 * \retval true si le joueur peut brûler des champs.
 * \retval false sinon.
 */
sda1_attribute((nonnull)) bool mancala_peut_bruler(const mancala* m);

/**
 * \brief Déterminer si la partie est finie.
 * \param[in] m le jeu du mancala à éxaminer.
 * \return Un booléen qui indique si la partie est finie.
 * \retval true si la partie est finie.
 * \retval false sinon.
 */
sda1_attribute((nonnull)) bool mancala_partie_finie(const mancala* m);

/**
 * \brief Obtenir l'indice du champ en cours de sélection.
 * \param[in] m le jeu du mancala à éxaminer.
 * \return L'indice du champ sélectionné.
 */
sda1_attribute((nonnull)) size_t mancala_selection(const mancala* m);

/**
 * \brief Obtenir l'indice du joueur qui doit jouer.
 * \param[in] m le jeu du mancala à éxaminer.
 * \return L'indice du joueur qui doit jouer.
 */
sda1_attribute((nonnull)) unsigned int mancala_joueur(const mancala* m);

/**
 * \brief Obtenir le score du joueur 1.
 * \param[in] m le jeu du mancala à éxaminer.
 * \return Le score du joueur 1.
 */
sda1_attribute((nonnull)) unsigned int mancala_score_joueur_1(const mancala* m);

/**
 * \brief Obtenir le score du joueur 2.
 * \param[in] m le jeu du mancala à éxaminer.
 * \return Le score du joueur 2.
 */
sda1_attribute((nonnull)) unsigned int mancala_score_joueur_2(const mancala* m);

/**
 * \brief Obtenir le plateau du jeu.
 * \param[in] m Le plateau du jeu de mancala.
 * \return Le plateau sous forme de liste.
 *
 * \warning Ne pas modifier la liste obtenue.
 */
sda1_attribute((nonnull)) const liste* mancala_plateau(const mancala* m);

////////////////////////////////////////////////////////////////////////////////
// Modificateurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Sélectionner le champ à gauche du champ sélectionné.
 * \param[in] m Le jeu du mancala.
 * \return Le jeu modifié.
 */
sda1_attribute((nonnull, warn_unused_result)) mancala* mancala_selection_gauche(
    mancala* m);

/**
 * \brief Sélectionner le champ à droite du champ sélectionné.
 * \param[in] m Le jeu du mancala.
 * \return Le jeu modifié.
 */
sda1_attribute((nonnull, warn_unused_result)) mancala* mancala_selection_droite(
    mancala* m);

/**
 * \brief Égrainer le champ i.
 * \param[in] m Le jeu du mancala.
 * \param[in] i L'indice du champ à égrainer.
 * \return Le jeu modifié.
 */
sda1_attribute((nonnull, warn_unused_result)) mancala* mancala_egrainer(
    mancala* m, size_t i);

/**
 * \brief Brûler des champs à la colonne i.
 * \param[in] m Le jeu du mancala.
 * \param[in] i L'indice du champ à brûler.
 * \return Le jeu modifié.
 */
sda1_attribute((nonnull, warn_unused_result)) mancala* mancala_bruler(
    mancala* m, size_t i);

#endif
