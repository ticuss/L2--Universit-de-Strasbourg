#ifndef _CLI_H_
#define _CLI_H_

#include <stdio.h>
#include <unistd.h>

/**
 * \file cli.h
 * \brief Outils pour une Command Line Interface très basique.
 */

/**
 * \brief Afficher un prompt.
 * \param[in] input  Fichier d'entrée.
 * \param[in] output Fichier de sortie.
 *
 * Afficher un prompt lorsque le programme est utilisé dans un terminal.
 */
static inline void prompt(FILE* const input, FILE* const output)
{
  /* On ne souhaite afficher un prompt que si:
   * - l'entrée se fait depuis un terminal
   * - la sortie se fait dans un terminal
   */
  if (isatty(fileno(input)) && isatty(fileno(output)))
    fprintf(output, "\033[1m>>>\033[0m ");
}

/**
 * \brief Afficher un message lorsqu'une commande est incorrecte.
 * \param[in] output   Fichier de sortie.
 * \param[in] couleurs Activer ou non les couleurs.
 * \param[in] message  Message à afficher.
 * \param[in] ligne    Ligne entrée par l'utilisateur.
 */
static inline void commande_incorrecte(
    FILE* const output, const bool couleurs, const char* const message,
    const char* const ligne)
{
  if (couleurs)
  {
    char buffer2[2048] = { 0 }, buffer3[2048] = { 0 };
    sscanf(ligne, "%2047[^ \t\n]", buffer2);
    const size_t shift = strlen(buffer2);
    sscanf(ligne + shift, "%2047[^\n]", buffer3);

    fprintf(output, "\033[1mIgnoré\033[0m : %s\n", message);
    fprintf(output, "  \033[1m\033[33m");
    const int printed = fprintf(output, "%s", buffer2) - 1;
    fprintf(output, "\033[0m%s\n  \033[33m^", buffer3);
    for (int i = 0; i < printed; ++i)
      fprintf(output, "~");
    fprintf(output, "\n\033[0m");
  }
  else
    fprintf(output, "Ignoré : %s\n", message);
}

/**
 * \brief Afficher une aide.
 * \param[in] output   Fichier de sortie.
 * \param[in] couleurs Activer ou non les couleurs.
 */
static inline void aide(FILE* const output, const bool couleurs)
{
  const char* bold = couleurs ? "\033[1m" : "";
  const char* reset = couleurs ? "\033[0m" : "";

  fprintf(output, "  %s%s%s\n    %s\n", bold, "affiche", reset, "Affiche le contenu de la file.");
  fprintf(output, "  %s%s%s\n    %s\n", bold, "aide", reset, "Affiche cette aide.");
  fprintf(output, "  %s%s%s\n    %s\n", bold, "ajoute <x>", reset, "Ajoute l'entier <x> à la file.");
  fprintf(output, "  %s%s%s\n    %s\n", bold, "etat", reset, "Affiche l'état de la file et sa taille si elle n'est pas vide.");
  fprintf(output, "  %s%s%s\n    %s\n", bold, "suppr", reset, "Affiche la tête et la supprime de la file.");
  fprintf(output, "  %s%s%s\n    %s\n", bold, "quit", reset, "Détruit la file et quitte le programme.");
}

#endif
