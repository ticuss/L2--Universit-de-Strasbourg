#ifndef _IO_H
#define _IO_H

#include <ncurses.h>

#include "mancala.h"

////////////////////////////////////////////////////////////////////////////////
// Divers
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Afficher un jeu dans un flux.
 * \param[in] stream Le flux où afficher le jeu.
 * \param[in] m Le jeu à afficher.
 */
sda1_attribute((nonnull)) void mancala_afficher(FILE* stream, const mancala* m);

/**
 * \brief Afficher un jeu dans une fenêtre ncurses.
 * \param[in] w La fenêtre où afficher le jeu.
 * \param[in] m Le jeu à afficher.
 */
sda1_attribute((nonnull)) void mancala_curses(WINDOW* w, const mancala* m);

#endif
