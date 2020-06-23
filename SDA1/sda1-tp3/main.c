/**
 * \file main.c
 * \brief Main.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sysexits.h>

#include "util.h"
#include "polynome.h"

static inline bool line_is_comment(const char* line)
{
  if (!line)
    return false;

  const char* current = line;
  for ( ; *current == ' ' || *current == '\t'; ++current)
    ;

  return *current == '#';
}

static inline polynome* polynome_from_input(
    FILE* const input, const char* const name, const bool interactive,
    FILE* const output)
{
  const char* const prefix = UTIL_TEXT_BOLD UTIL_TEXT_DIM;
  const char* const suffix = UTIL_TEXT_RESET;

  polynome* result = NULL;
  while (true)
  {
    char buffer[8192] = { 0 };
    if (interactive)
      fprintf(output, "%s%s(X) =%s ", prefix, name, suffix);
    if (!fgets(buffer, 8191, input))
      return liste_vide();
    if (line_is_comment(buffer))
      continue;
    result = polynome_sread(buffer);
    break;
  }

  return result;
}

int main(int argc, char* argv[argc + 1])
{
  FILE* input = stdin;
  FILE* output = stdout;

  /* Basic CLI check. */
  if (argc > 3)
  {
    fprintf(stderr, "Too many arguments.\n");
    fprintf(stderr, "Usage: %s [input] [output]\n", argv[0]);
    exit(EX_USAGE);
  }

  /* Open I/O files. */
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

  const bool interactive_input = isatty(fileno(input));
  const bool interactive_output = isatty(fileno(output));
  const bool interactive = interactive_input && interactive_output;
  const char* const prefix = interactive_output ? UTIL_TEXT_BOLD UTIL_TEXT_DIM : "";
  const char* const suffix = interactive_output ? UTIL_TEXT_RESET : "";

  /* Read the input. */
  polynome* const P1 = polynome_from_input(input, "P1", interactive, output);
  polynome* const P2 = polynome_from_input(input, "P2", interactive, output);
  if (interactive)
    fprintf(output, "\n");

  /* Print the input. */
  fprintf(output, "%s%-8s= %s", prefix, "P1(X)", suffix);
  polynome_fwrite(output, P1);
  fprintf(output, "%s%-8s= %s", prefix, "P2(X)", suffix);
  polynome_fwrite(output, P2);

  {
    polynome* const somme = polynome_addition(P1, P2);
    fprintf(output, "%s%-8s= %s", prefix, "P1 + P2", suffix);
    polynome_fwrite(output, somme);
    polynome_free(somme);
  }

  {
    polynome* const produit = polynome_multiplication(P1, P2);
    fprintf(output, "%s%-8s= %s", prefix, "P1 * P2", suffix);
    polynome_fwrite(output, produit);
    polynome_free(produit);
  }

  {
    polynome* const derivee = polynome_derivee(P1);
    fprintf(output, "%s%-8s= %s", prefix, "P1'(X)", suffix);
    polynome_fwrite(output, derivee);
    polynome_free(derivee);
  }

  {
    polynome* const derivee = polynome_derivee(P2);
    fprintf(output, "%s%-8s= %s", prefix, "P2'(X)", suffix);
    polynome_fwrite(output, derivee);
    polynome_free(derivee);
  }

  polynome_free(P1);
  polynome_free(P2);

  return 0;
}
