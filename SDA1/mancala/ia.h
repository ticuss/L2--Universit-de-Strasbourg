#ifndef _IA_H
#define _IA_H

#include "attributes.h"
#include "mancala.h"

/**
 * \brief Choisir une action (et l'appliquer) pour un joueur donné.
 * \param[in] m Le jeu à modifier.
 * \param[in] joueur Le joueur indécis.
 * \return Le jeu modifié.
 */
sda1_attribute((nonnull, warn_unused_result)) mancala* mancala_ia(
    mancala* m, const unsigned int joueur);

#endif
