////////////////////////////////////////////////////////////////////////////////
// features required by this implemetation
////////////////////////////////////////////////////////////////////////////////

/*
 * Be sure to define all required macros before any header includes !
 * See also the feature_test_macros(7) manpage for further information.
 */

/* To enable extended features in ncurses */
#ifndef _XOPEN_SOURCE_EXTENDED
  #define _XOPEN_SOURCE_EXTENDED
#endif

////////////////////////////////////////////////////////////////////////////////
// headers
////////////////////////////////////////////////////////////////////////////////

/* The associated header */
#include "io.h"

/* Other headers */
#include <ncurses.h>

#include "liste.h"

static inline size_t mancala_premier_champ(
    const mancala* m, unsigned int joueur) {
  return joueur == 0 ? 1 : ((liste_longueur(mancala_plateau(m)) / 2) + 1);
}

static inline size_t mancala_dernier_champ(
    const mancala* m, unsigned int joueur) {
  const size_t longueur = liste_longueur(mancala_plateau(m));
  return joueur == 0 ? ((longueur / 2) - 1) : (longueur - 1);
}

void mancala_afficher(FILE* stream, const mancala* m) {
  const liste* l = mancala_plateau(m);

  const size_t longueur = liste_longueur(l);
  const size_t milieu = longueur / 2;

  const size_t premier_champ[] = {
      [0] = mancala_premier_champ(m, 0),
      [1] = mancala_premier_champ(m, 1),
  };
  const size_t dernier_champ[] = {
      [0] = mancala_dernier_champ(m, 0),
      [1] = mancala_dernier_champ(m, 1),
  };

  const unsigned int joueur = mancala_joueur(m);
  fprintf(stream, "Joueur %u\n", joueur);

  /* Affichage numéros champs. */
  fprintf(stream, "    \033[2m");
  for (size_t i = dernier_champ[1]; i >= premier_champ[1]; --i)
    fprintf(stream, "  %02zu", i);
  fprintf(stream, "\033[0m\n");
  /* Affichage champs joueur 2. */
  fprintf(stream, "    ");
  for (size_t i = dernier_champ[1]; i >= premier_champ[1]; --i) {
    const unsigned int graines = liste_ieme(l, i);
    const char* const champd = joueur ? "\033[1m" : "";
    const char* const red = graines == 0 ? "\033[31m" : "";
    fprintf(stream, "  %s%s%02u\033[0m", champd, red, graines);
  }
  fprintf(stream, "\n");

  fprintf(stream, "  %02u", liste_ieme(l, 0));
  for (size_t i = 1; i < milieu; ++i)
    fprintf(stream, "    ");
  fprintf(stream, "  %02u", liste_ieme(l, milieu));
  fprintf(stream, "\n");

  /* Affichage champs joueur 1. */
  fprintf(stream, "    ");
  for (size_t i = premier_champ[0]; i <= dernier_champ[0]; ++i) {
    const unsigned int graines = liste_ieme(l, i);
    const char* const champd = joueur ? "" : "\033[1m";
    const char* const red = graines == 0 ? "\033[31m" : "";
    fprintf(stream, "  %s%s%02u\033[0m", champd, red, graines);
  }
  fprintf(stream, "\n");
  /* Affichage numéros champs. */
  fprintf(stream, "    \033[2m");
  for (size_t i = premier_champ[0]; i <= dernier_champ[0]; ++i)
    fprintf(stream, "  %02zu", i);
  fprintf(stream, "\033[0m\n");
}

void mancala_curses(WINDOW* w, const mancala* m) {
  const liste* l = mancala_plateau(m);

  const unsigned int joueur = mancala_joueur(m);
  const size_t selection = mancala_selection(m);
  const size_t longueur = liste_longueur(l);
  const size_t milieu = longueur / 2;

  const size_t premier_champ[] = {
      [0] = mancala_premier_champ(m, 0),
      [1] = mancala_premier_champ(m, 1),
  };
  const size_t dernier_champ[] = {
      [0] = mancala_dernier_champ(m, 0),
      [1] = mancala_dernier_champ(m, 1),
  };
  const unsigned int scores[2] = {
      [0] = mancala_score_joueur_1(m),
      [1] = mancala_score_joueur_2(m),
  };

  wmove(w, 0, 0);

  wprintw(w, "  ");
  wattron(w, A_REVERSE | COLOR_PAIR(4) | (!joueur ? A_BOLD : A_DIM));
  wprintw(w, " J1 %3zupts ", scores[0]);
  wattroff(w, A_REVERSE | COLOR_PAIR(4) | (!joueur ? A_BOLD : A_DIM));
  size_t spaces = (milieu - 2) * 4;
  spaces = spaces > 12 ? spaces - 12 : 0;
  for (size_t i = 0; i < spaces; ++i)
    wprintw(w, " ");
  wattron(w, A_REVERSE | COLOR_PAIR(5) | (joueur ? A_BOLD : A_DIM));
  wprintw(w, " J2 %3zupts ", scores[1]);
  wattroff(w, A_REVERSE | COLOR_PAIR(5) | (joueur ? A_BOLD : A_DIM));
  wprintw(w, "\n\n");

  /* Affichage champs joueur 2. */
  wprintw(w, "    ");
  for (size_t i = dernier_champ[1]; i >= premier_champ[1]; --i) {
    const unsigned int graines = liste_ieme(l, i);
    wattron(w, i == selection ? (A_BOLD | COLOR_PAIR(5)) : A_DIM);
    if (graines == 0) {
      wattroff(w, COLOR_PAIR(5));
      wattron(w, COLOR_PAIR(1));
    }
    wprintw(w, "  %02u", graines);
    wattroff(w, i == selection ? (A_BOLD | COLOR_PAIR(5)) : A_DIM);
    if (graines == 0)
      wattroff(w, COLOR_PAIR(1));
  }
  wprintw(w, "\n");

  wprintw(w, "  %02u", liste_ieme(l, 0));
  for (size_t i = 1; i < milieu; ++i)
    wprintw(w, "    ");
  wprintw(w, "  %02u", liste_ieme(l, milieu));
  wprintw(w, "\n");

  /* Affichage champs joueur 1. */
  wprintw(w, "    ");
  for (size_t i = premier_champ[0]; i <= dernier_champ[0]; ++i) {
    const unsigned int graines = liste_ieme(l, i);
    wattron(w, i == selection ? (A_BOLD | COLOR_PAIR(4)) : A_DIM);
    if (graines == 0) {
      wattroff(w, COLOR_PAIR(4));
      wattron(w, COLOR_PAIR(1));
    }
    wprintw(w, "  %02u", graines);
    wattroff(w, i == selection ? (A_BOLD | COLOR_PAIR(4)) : A_DIM);
    if (graines == 0)
      wattroff(w, COLOR_PAIR(1));
  }
  wprintw(w, "\n");
}
