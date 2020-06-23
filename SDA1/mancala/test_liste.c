/**
 * \file main.c
 * \brief Main.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>

#include "attributes.h"
#include "but.h"
#include "liste.h"

sda1_attribute((unused)) static inline void info(
    FILE* const stream, const char* const message) {
  if (isatty(fileno(stream)))
    fprintf(stream, "\033[1m%s\033[0m", message);
  else
    fprintf(stream, "%s", message);
}

but_test_start(test_liste_vide, "Test liste_vide()") {
  liste* l = liste_vide();
  but_assert(liste_longueur(l) == 0);
  but_assert(liste_est_vide(l) == true);
  liste_detruire(l);
}
but_test_end

but_test_start(test_liste_inserer_tete, "Test liste_inserer_tete()") {
  liste* l[8] = {0};

  /*
   * Création de 8 listes, de tailles 0 à 7.
   * Attention : ajouts en tête !
   * (Donc éléments dans l'ordre décroissant dans la liste finale !)
   */
  for (size_t i = 0; i < 8; ++i) {
    l[i] = liste_vide();
    for (size_t j = 0; j < i; ++j)
      l[i] = liste_inserer_tete(l[i], (unsigned int) j);
  }

  for (size_t i = 0; i < 8; ++i) {
    but_assert(liste_longueur(l[i]) == i);
    but_assert(liste_est_vide(l[i]) == (i ? false : true));
    for (size_t j = 0; j < i; ++j)
      but_assert(liste_ieme(l[i], j) == (i - j - 1));
  }

  /* Nettoyage. */
  for (size_t i = 0; i < 8; ++i)
    liste_detruire(l[i]);
}
but_test_end

but_test_start(test_liste_supprimer, "Test liste_supprimer()") {
  liste* l[8] = {0};

  //////////////////////////////////////////////////////////////////////////////
  // Test : suppression du premier élément.
  //////////////////////////////////////////////////////////////////////////////
  for (size_t i = 0; i < 8; ++i) {
    l[i] = liste_vide();
    for (size_t j = 0; j < i; ++j)
      l[i] = liste_inserer_tete(l[i], (unsigned int) j);

    if (i)
      l[i] = liste_supprimer(l[i], 0);
  }
  for (size_t i = 0; i < 8; ++i) {
    but_assert(liste_longueur(l[i]) == (i ? (i - 1) : 0));
    if (i > 1) {
      but_assert(liste_ieme(l[i], 0) == (i - 2));
      but_assert(liste_ieme(l[i], i - 2) == 0);
    }
  }
  /* Nettoyage. */
  for (size_t i = 0; i < 8; ++i)
    liste_detruire(l[i]);

  //////////////////////////////////////////////////////////////////////////////
  // Test : suppression du dernier élément.
  //////////////////////////////////////////////////////////////////////////////
  for (size_t i = 0; i < 8; ++i) {
    l[i] = liste_vide();
    for (size_t j = 0; j < i; ++j)
      l[i] = liste_inserer_tete(l[i], (unsigned int) j);

    if (i)
      l[i] = liste_supprimer(l[i], i - 1);
  }
  for (size_t i = 0; i < 8; ++i) {
    but_assert(liste_longueur(l[i]) == (i ? (i - 1) : 0));
    if (i > 1) {
      but_assert(liste_ieme(l[i], 0) == (i - 1));
      but_assert(liste_ieme(l[i], i - 2) == 1);
    }
  }
  /* Nettoyage. */
  for (size_t i = 0; i < 8; ++i)
    liste_detruire(l[i]);

  //////////////////////////////////////////////////////////////////////////////
  // Test : suppression de n'importe quel élément.
  //////////////////////////////////////////////////////////////////////////////
  for (size_t i = 0; i < 8; ++i) {
    l[i] = liste_vide();
    for (size_t j = 0; j < i; ++j)
      l[i] = liste_inserer_tete(l[i], (unsigned int) j);

    if (i)
      l[i] = liste_supprimer(l[i], i - 1);
  }
  for (size_t i = 0; i < 8; ++i) {
    but_assert(liste_longueur(l[i]) == (i ? (i - 1) : 0));
    if (i > 1) {
      but_assert(liste_ieme(l[i], 0) == (i - 1));
      but_assert(liste_ieme(l[i], i - 2) == 1);
    }
  }
  /* Nettoyage. */
  for (size_t i = 0; i < 8; ++i)
    liste_detruire(l[i]);
}
but_test_end

but_test_start(test_liste_est_vide, "Test liste_est_vide()") {
  liste* l[8] = {0};
  for (size_t i = 0; i < 8; ++i) {
    l[i] = liste_vide();
    for (size_t j = 0; j < i; ++j)
      l[i] = liste_inserer_tete(l[i], (unsigned int) j);
  }

  for (size_t i = 0; i < 8; ++i)
    but_assert(liste_est_vide(l[i]) == (i ? false : true));

  /* Nettoyage. */
  for (size_t i = 0; i < 8; ++i)
    liste_detruire(l[i]);
}
but_test_end

but_test_start(test_liste_longueur, "Test liste_longueur()") {
  liste* l[8] = {0};
  for (size_t i = 0; i < 8; ++i) {
    l[i] = liste_vide();
    for (size_t j = 0; j < i; ++j)
      l[i] = liste_inserer_tete(l[i], (unsigned int) j);
  }

  for (size_t i = 0; i < 8; ++i)
    but_assert(liste_longueur(l[i]) == i);

  /* Nettoyage. */
  for (size_t i = 0; i < 8; ++i)
    liste_detruire(l[i]);
}
but_test_end

but_test_start(test_liste_ieme, "Test liste_ieme()") {
  liste* l[8] = {0};
  for (size_t i = 0; i < 8; ++i) {
    l[i] = liste_vide();
    for (size_t j = 0; j < i; ++j)
      l[i] = liste_inserer_tete(l[i], (unsigned int) j);
  }

  for (size_t i = 0; i < 8; ++i)
    for (size_t j = 0; j < i; ++j)
      but_assert(liste_ieme(l[i], j) == (i - j - 1));

  /* Nettoyage. */
  for (size_t i = 0; i < 8; ++i)
    liste_detruire(l[i]);
}
but_test_end

but_test_start(test_liste_egrainer, "Test liste_egrainer()") {
  liste* l[3] = {0};

  for (size_t i = 0; i < 3; ++i)
    for (size_t j = 0; j < 14; ++j)
      l[i] = liste_inserer_tete(l[i], 3);

  /* l[0][0] = 0, l[0][1:3] = 4, l[0][4:13] = 3 */
  l[0] = liste_egrainer(l[0], 0);
  /* l[1][0:4] = 3, l[1][5] = 0, l[1][6:8] = 4, l[1][9:13] = 3 */
  l[1] = liste_egrainer(l[1], 5);
  /* l[2][2:11] = 3, l[2][12] = 0, l[2][13] = l[2][0:1] = 4 */
  l[2] = liste_egrainer(l[2], 12);

  /* Vérification que la longueur n'a pas changé (?!) */
  for (size_t i = 0; i < 3; ++i)
    but_assert(liste_longueur(l[i]) == 14);

  /* l[0][0] = 0, l[0][1:3] = 4, l[0][4:13] = 3 */
  but_assert(liste_ieme(l[0], 0) == 0);
  but_assert(liste_ieme(l[0], 1) == 4);
  but_assert(liste_ieme(l[0], 2) == 4);
  but_assert(liste_ieme(l[0], 3) == 4);
  for (size_t i = 4; i < 14; ++i)
    but_assert(liste_ieme(l[0], i) == 3);

  /* l[1][0:4] = 3, l[1][5] = 0, l[1][6:8] = 4, l[1][9:13] = 3 */
  for (size_t i = 0; i < 5; ++i)
    but_assert(liste_ieme(l[1], i) == 3);
  but_assert(liste_ieme(l[1], 5) == 0);
  but_assert(liste_ieme(l[1], 6) == 4);
  but_assert(liste_ieme(l[1], 7) == 4);
  but_assert(liste_ieme(l[1], 8) == 4);
  for (size_t i = 9; i < 14; ++i)
    but_assert(liste_ieme(l[1], i) == 3);

  /* l[2][2:11] = 3, l[2][12] = 0, l[2][13] = l[2][0:1] = 4 */
  but_assert(liste_ieme(l[2], 12) == 0);
  but_assert(liste_ieme(l[2], 13) == 4);
  but_assert(liste_ieme(l[2], 0) == 4);
  but_assert(liste_ieme(l[2], 1) == 4);
  for (size_t i = 2; i < 11; ++i)
    but_assert(liste_ieme(l[2], i) == 3);

  for (size_t i = 0; i < 3; ++i)
    liste_detruire(l[i]);
}
but_test_end

but_test_start(test_liste_modifier, "Test liste_modifier()") {
  liste* l[8] = {0};
  for (size_t i = 0; i < 8; ++i) {
    l[i] = liste_vide();
    for (size_t j = 0; j < i; ++j)
      l[i] = liste_inserer_tete(l[i], (unsigned int) j);
  }
  for (size_t i = 0; i < 8; ++i)
    for (size_t j = 0; j < i; ++j)
      l[i] = liste_modifier(l[i], j, (unsigned int) j);

  for (size_t i = 0; i < 8; ++i) {
    /* Vérification que la longueur n'a pas changé (?!) */
    but_assert(liste_longueur(l[i]) == i);
    for (size_t j = 0; j < i; ++j)
      but_assert(liste_ieme(l[i], j) == j);
  }

  /* Nettoyage. */
  for (size_t i = 0; i < 8; ++i)
    liste_detruire(l[i]);
}
but_test_end

    int
    main(int argc, char* argv[argc + 1]) {
  (void) argc;
  (void) argv;
  but_runtime runtime;
  but_runtime_init(&runtime);

  // runtime.verbose = true;

  but_register_test(&runtime, test_liste_vide);
  but_register_test(&runtime, test_liste_inserer_tete);
  but_register_test(&runtime, test_liste_supprimer);
  but_register_test(&runtime, test_liste_est_vide);
  but_register_test(&runtime, test_liste_longueur);
  but_register_test(&runtime, test_liste_ieme);
  but_register_test(&runtime, test_liste_egrainer);
  but_register_test(&runtime, test_liste_modifier);

  but_run_tests(&runtime);
  const int exit_code = runtime.failed_tests ? 1 : 0;
  but_runtime_clean(&runtime);

  return exit_code;
}
