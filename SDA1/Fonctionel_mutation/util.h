#ifndef _UTIL_H_
#define _UTIL_H_

/**
 * \file util.h
 * \brief Utilitaires divers.
 */

#include <stdio.h>
#include <unistd.h>

/**
 * \defgroup util_module Divers
 * \brief Utilitaires divers.
 */

/**
 * Macro d'affichage d'un msg d'erreur et exit.
 * utilisée en cas de non respect d'une précondition
 * \ingroup util_module
 */
#define ERREUR(message) \
  do \
{ \
  if (isatty(fileno(stderr))) \
    fprintf(stderr, "\033[1m%s\033[0m: %s\n", __func__, message); \
  else \
    fprintf(stderr, "%s: %s\n", __func__, message); \
  exit(1); \
} while(0)

#endif
