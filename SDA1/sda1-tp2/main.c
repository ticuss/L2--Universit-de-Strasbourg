/**
 * \file main.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sysexits.h>

#include "cli.h"
#include "sorte.h"
#include "file.h"

/**
 * \mainpage Files chaînées
 *
 * Le programme permet de tester l'implémentation d'une ::file chaînée
 * d'éléments de sorte ::S. Voir la documentation d'une ::file pour plus
 * d'informations.
 *
 * Un \c \b Makefile est disponible pour faciliter la compilation :
 *
 * \code{.sh}
 * $ make
 * \endcode
 *
 * Une aide peut-être affichée lors de l'éxécution du programme :
 *
 * \code{.sh}
 * $ rlwrap ./fonctionnel
 * >>> aide
 *   affiche
 *    Affiche le contenu de la file.
 *  aide
 *    Affiche cette aide.
 *  ajoute <x>
 *    Ajoute l'entier <x> à la file.
 *  etat
 *    Affiche l'état de la file et sa taille si elle n'est pas vide.
 *  suppr
 *    Affiche la tête et la supprime de la file.
 *  quit
 *    Détruit la file et quitte le programme.
 * >>> quit
 * \endcode
 */

/**
 * \brief Programme principal
 * \param[in] argc Nombre d'arguments.
 * \param[in] argv Arguments de la ligne de commande.
 * \return Retour du programme.
 * \retval 0 en cas de succès.
 * 
 * Lit le contenu de l'entrée standard, et modifie une file de la manière
 * suivante :
 *
 * Commande       | Effet
 * --------       | -----
 * `aide`         |  Afficher une aide
 * `ajoute <x>`   |  Ajoute l'entier x à la file.
 * `suppr`        |  Affiche l'entier en tête de file et le supprime de la file.
 * `etat`         |  Affiche "vide" ou "non-vide" selon l'état de la file, et sa taille si elle n'est pas vide.
 * `affiche`      |  Affiche le contenu de la file.
 * `quit` ou `^D` |  Détruit la file et termine le programme.
 */
int main(int argc, char* argv[argc + 1])
{
  FILE* input = stdin;
  FILE* output = stdout;
  if (argc > 1)
  {
    input = fopen(argv[1], "r");
    if (!input)
    {
      perror("fopen");
      exit(EX_NOINPUT);
    }
  }
  if (argc > 2)
  {
    output = fopen(argv[2], "w");
    if (!output)
    {
      perror("fopen");
      fclose(input);
      exit(EX_CANTCREAT);
    }
  }

  const bool couleurs = isatty(fileno(output));
  char buffer[2048] = { 0 };
  file* f = file_nouv();

  for (prompt(input, output); fgets(buffer, 2047, input); prompt(input, output))
  {
    const char* ligne = 0;
    for (ligne = buffer; *ligne == ' '; ++ligne)
      ;

    /* Commentaire ou ligne vide. */
    if (*ligne == '#' || *ligne == '\n')
      continue;

    if (!strncmp(ligne, "ajoute", 6))
    {
      /* "ajoute <x>" : ajoute l'entier x à la file ; */
      S x;
      const int lu = sscanf(ligne, "ajoute %"SCN_S, &x);
      if (lu != 1)
        commande_incorrecte(output, couleurs, "argument manquant ou incorrect", ligne);
      else
        f = file_adjq(f, x);
    }
    else if (!strncmp(ligne, "suppr", 5))
    {
      /* "suppr" : affiche l'entier en tête de file et le supprime de la file */
      if (!file_estvide(f))
      {
        const S tete = file_tete(f);
        fprintf(output, "%"PRI_S"\n", tete);
        f = file_supt(f);
      }
      else
        commande_incorrecte(output, couleurs, "file vide", ligne);
    }
    else if (!strncmp(ligne, "etat", 4))
    {
      /*
       * "etat" : affiche "vide" ou "non-vide" selon l'état de la file, et sa
       * taille si elle n'est pas vide ;
       */
      if (file_estvide(f))
        fprintf(output, "File vide.\n");
      else
      {
        const size_t taille = file_taille(f);
        const char* const elements = taille > 1 ? "éléments" : "élément";
        fprintf(output, "File non vide, contient %zu %s.\n", taille, elements);
      }
    }
    else if (!strncmp(ligne, "affiche", 7))
      /* "affiche" : affiche le contenu de la file ;*/
      file_affiche(output, f);
    else if (!strncmp(ligne, "quit", 4))
      /* "quit" : détruit la file et termine le programme.*/
      break;
    else if (!strncmp(ligne, "aide", 4))
      aide(output, couleurs);
    else
      commande_incorrecte(output, couleurs, "commande inconnue:", ligne);
  }
  file_detruit(f);

  return 0;
}
