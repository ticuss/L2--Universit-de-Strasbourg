/**
 * \file main.c
 * \brief Main.
 */

////////////////////////////////////////////////////////////////////////////////
// features required by this implemetation
////////////////////////////////////////////////////////////////////////////////

/*
 * Be sure to define all required macros before including any header!
 * See also the feature_test_macros(7) manpage for further information.
 */

/* To enable extended features in ncurses */
#ifndef _XOPEN_SOURCE_EXTENDED
  #define _XOPEN_SOURCE_EXTENDED
#endif

/* Various Mancala related macros */
#ifndef MANCALA_NCURSES
  #define MANCALA_NCURSES 1
#endif

#ifndef MANCALA_IA
  #define MANCALA_IA 1

  #ifndef MANCALA_IA_DEFAULT
    #define MANCALA_IA_DEFAULT false
  #endif
#endif

#ifndef MANCALA_TAILLE
  #define MANCALA_TAILLE 6
#endif
#ifndef MANCALA_GRAINES
  #define MANCALA_GRAINES 3
#endif

////////////////////////////////////////////////////////////////////////////////
// headers
////////////////////////////////////////////////////////////////////////////////

/* C library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

/* ncurses */
#include <ncurses.h>

/* local headers */
#include "attributes.h"
#include "ia.h"
#include "io.h"
#include "liste.h"
#include "mancala.h"

////////////////////////////////////////////////////////////////////////////////
// local functions decalarations
////////////////////////////////////////////////////////////////////////////////

sda1_attribute((unused)) static mancala* simple_ui(mancala* m, const bool ia);

sda1_attribute((unused)) static mancala* curses_ui(mancala* m, const bool ia);

////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[argc + 1]) {
#if MANCALA_IA == 1
  bool ia = MANCALA_IA_DEFAULT;
  for (int i = 0; i < argc; ++i)
    if (!strcmp(argv[i], "--ia"))
      ia = true;
    else if (!strcmp(argv[i], "--no-ia"))
      ia = false;
#else
  bool ia = false;
#endif

  mancala* m = mancala_init(MANCALA_TAILLE, MANCALA_GRAINES);
#if MANCALA_NCURSES == 1
  m = curses_ui(m, ia);
#else
  m = simple_ui(m, ia);
#endif
  mancala_free(m);

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// local function definitions
////////////////////////////////////////////////////////////////////////////////

mancala* simple_ui(mancala* m, const bool ia) {
  while (!mancala_partie_finie(m)) {
#if MANCALA_IA == 1
    if (ia) {
      /* IA. */
      while (mancala_joueur(m)) {
        m = mancala_ia(m, mancala_joueur(m));
        mancala_afficher(stdout, m);
      }
      if (mancala_partie_finie(m)) {
        break;
      }
    }
#endif

    mancala_afficher(stdout, m);
    printf("\n> ");

    size_t champ = 0;
    if (scanf("%zu", &champ) != 1) {
      printf("\n");
      break;
    }

    if (mancala_coup_valide(m, champ)) {
      m = mancala_egrainer(m, champ);
    }
    printf("\n");
  }

  const unsigned int scores[2] = {
      [0] = mancala_score_joueur_1(m),
      [1] = mancala_score_joueur_2(m),
  };

  printf("Joueur 1 : %u\n", scores[0]);
  printf("Joueur 2 : %u\n", scores[1]);

  return m;
}

mancala* curses_ui(mancala* m, const bool ia) {
  initscr();
  noecho();
  curs_set(0);
  if (has_colors()) {
    start_color();

    short fg, bg;
    pair_content(0, &fg, &bg);
#ifdef NCURSES_VERSION
    bg = use_default_colors() == OK ? -1 : bg;
#endif

    init_pair(1, COLOR_RED, bg);
    init_pair(2, COLOR_GREEN, bg);
    init_pair(3, COLOR_YELLOW, bg);
    init_pair(4, COLOR_BLUE, bg);
    init_pair(5, COLOR_MAGENTA, bg);
    init_pair(6, COLOR_CYAN, bg);
    init_pair(7, COLOR_WHITE, bg);
  }

  int input;
  bool quit = false;
  while (!mancala_partie_finie(m) && !quit) {
    /* Affichage. */
    mancala_curses(stdscr, m);

#if MANCALA_IA == 1
    /* IA. */
    if (ia) {
      while (mancala_joueur(m)) {
        m = mancala_ia(m, mancala_joueur(m));
        mancala_curses(stdscr, m);
      }
      if (mancala_partie_finie(m)) {
        break;
      }
    }
#endif

    mancala_curses(stdscr, m);
    input = getch();

    switch (input) {
      case 'q':
        quit = true;
        break;
      case 'e':
      case ' ':
        if (mancala_coup_valide(m, mancala_selection(m)))
          m = mancala_egrainer(m, mancala_selection(m));
        break;
      case 'b':
        if (mancala_peut_bruler(m))
          m = mancala_bruler(m, mancala_selection(m));
        break;
      case 68:
      case 'h':
      case '4':
        // gauche
        m = mancala_selection_gauche(m);
        break;
      case 67:
      case 'l':
      case '6':
        // droite
        m = mancala_selection_droite(m);
        break;
      default:
        break;
    }
  }

  /* Fin! */
  mancala_curses(stdscr, m);
  wprintw(stdscr, "\n");
  for (size_t i = 0; i < MANCALA_TAILLE * 2 + 2; ++i) {
    wprintw(stdscr, " ");
  }
  wattron(stdscr, A_BOLD | A_REVERSE | COLOR_PAIR(1));
  wprintw(stdscr, " FIN ");
  wattroff(stdscr, A_BOLD | A_REVERSE | COLOR_PAIR(1));
  wprintw(stdscr, "\n");
  getch();

  endwin();

  return m;
}
