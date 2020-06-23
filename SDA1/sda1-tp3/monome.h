#ifndef _MONOME_H_
#define _MONOME_H_

/**
 * \file monome.h
 * \brief Header pour les monomes.
 */


#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <inttypes.h>

#include "util.h"

/**
 * \defgroup monome_module Monôme
 * \copydetails monome
 */

////////////////////////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////////////////////////

/*
 * Définitions par défaut pour monome_degre_type.
 */
#ifndef MONOME_DEGRE_TYPE
  #define MONOME_DEGRE_TYPE unsigned int
  #ifndef MONOME_DEGRE_SCN
    #define MONOME_DEGRE_SCN "%u"
  #endif
  #ifndef MONOME_DEGRE_PRI
    #define MONOME_DEGRE_PRI "%u"
  #endif
#endif

/*
 * Dans le cas où MONOME_DEGRE_TYPE a été manuellement défini, MONOME_DEGRE_SCN
 * et MONOME_DEGRE_PRI doivent impérativement avoir été également définis
 * manuellement (car ils doivent correspondre à MONOME_DEGRE_TYPE)
 */
#ifndef MONOME_DEGRE_SCN
  #error "MONOME_DEGRE_SCN macro not found"
#endif
#ifndef MONOME_DEGRE_PRI
  #error "MONOME_DEGRE_PRI macro not found"
#endif

/**
 * \brief Degrés de monomes.
 * \ingroup monome_module
 */
typedef MONOME_DEGRE_TYPE monome_degre_type;

/*
 * Définitions par défaut pour monome_coefficient_type.
 */
#ifndef MONOME_COEFFICIENT_TYPE
  #define MONOME_COEFFICIENT_TYPE double
  #ifndef MONOME_COEFFICIENT_SCN
    #define MONOME_COEFFICIENT_SCN "%lf"
  #endif
  #ifndef MONOME_COEFFICIENT_PRI
    #define MONOME_COEFFICIENT_PRI "%.2lf"
  #endif
#endif

/*
 * Dans le cas où MONOME_COEFFICIENT_TYPE a été manuellement défini,
 * MONOME_COEFFICIENT_SCN et MONOME_COEFFICIENT_PRI doivent impérativement
 * avoir été également définis manuellement (car ils doivent correspondre à
 * MONOME_COEFFICIENT_TYPE)
 */
#ifndef MONOME_COEFFICIENT_SCN
  #error "MONOME_COEFFICIENT_SCN macro not found"
#endif
#ifndef MONOME_COEFFICIENT_PRI
  #error "MONOME_COEFFICIENT_PRI macro not found"
#endif

/**
 * \brief Coefficients de monomes.
 * \ingroup monome_module
 */
typedef MONOME_COEFFICIENT_TYPE monome_coefficient_type;

/**
 * \brief Monôme
 * \ingroup monome_module
 */
struct monome
{
  /** \brief Degré du monome. */
  monome_degre_type degre;
  /** \brief Coefficient du monome. */
  monome_coefficient_type coefficient;
};
typedef struct monome monome;

////////////////////////////////////////////////////////////////////////////////
// Macros diverses
////////////////////////////////////////////////////////////////////////////////

#ifndef MONOME_TEXT_COEFFICIENT_PREFIX
  #define MONOME_TEXT_COEFFICIENT_PREFIX UTIL_TEXT_BOLD UTIL_TEXT_BLUE
#endif
#ifndef MONOME_TEXT_DEGRE_PREFIX
  #define MONOME_TEXT_DEGRE_PREFIX UTIL_TEXT_BOLD UTIL_TEXT_CYAN
#endif

////////////////////////////////////////////////////////////////////////////////
// Opérations arithmétiques
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Additionner deux monômes.
 * \param[in] m1 Premier monôme.
 * \param[in] m2 Second monôme.
 * \return Le monôme \a m1 + \a m2.
 *
 * \pre \code m1.degre == m2.degre \endcode
 *
 * \memberof monome
 */
static inline monome monome_addition(const monome m1, const monome m2)
{
  const monome_degre_type degre = m1.degre;
  const monome_coefficient_type coefficient = m1.coefficient + m2.coefficient;
  return (monome) { .degre = degre, .coefficient = coefficient, };
}

/**
 * \brief Multiplier deux monômes.
 * \param[in] m1 Premier monôme.
 * \param[in] m2 Second monôme.
 * \return Le monôme \a m1 * \a m2.
 *
 * \memberof monome
 */
static inline monome monome_multiplication(const monome m1, const monome m2)
{
  const monome_degre_type degre = m1.degre + m2.degre;
  const monome_coefficient_type coefficient = m1.coefficient * m2.coefficient;
  return (monome) { .degre = degre, .coefficient = coefficient, };
}

////////////////////////////////////////////////////////////////////////////////
// I/O
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Scanner un monôme depuis une chaîne de caractères.
 * \param[in] string Chaîne d'entrée.
 * \param[in,out] m Monôme de destination.
 * \return Un entier indiquant le statut.
 * \retval 0 Aucun monome lu.
 * \retval 1 Un monome a été lu.
 *
 * \memberof monome
 */
static inline int monome_sscan(const char* const string, monome* const m)
{
  int scanned = sscanf(
      string, MONOME_COEFFICIENT_SCN" "MONOME_DEGRE_SCN, &(m->coefficient),
      &(m->degre));

  if (scanned < 0)
    return scanned;
  else  if (scanned == 2)
    return 1;
  else
    return 0;
}

/**
 * \brief Scanner un monôme depuis un fichier.
 * \param[in] stream Fichier d'entrée.
 * \param[in,out] m Monôme de destination.
 * \return Un entier indiquant le statut.
 * \retval 0 Aucun monome lu.
 * \retval 1 Un monome a été lu.
 *
 * \memberof monome
 */
static inline int monome_fscan(FILE* const stream, monome* const m)
{
  int scanned = fscanf(
      stream, MONOME_COEFFICIENT_SCN" "MONOME_DEGRE_SCN, &(m->coefficient),
      &(m->degre));

  if (scanned < 0)
    return scanned;
  else  if (scanned == 2)
    return 1;
  else
    return 0;
}

/**
 * \brief Écrire un monôme dans un fichier.
 * \param[in] stream Fichier de destination.
 * \param[in] m Monôme à écrire.
 * \return Nombre de caractères écrits dans \a stream.
 *
 * \memberof monome
 */
static inline int monome_fprint(FILE* const stream, const monome m)
{
  /* Utilisation de couleurs sur la sortie. */
  const bool colours = isatty(fileno(stream));
  const char* const coefficient_prefix = colours ? MONOME_TEXT_COEFFICIENT_PREFIX : "";
  const char* const coefficient_suffix = colours ? UTIL_TEXT_RESET: "";
  const char* const degre_prefix = colours ? MONOME_TEXT_DEGRE_PREFIX: "";
  const char* const degre_suffix = colours ? UTIL_TEXT_RESET: "";
  const char* const x_prefix = "";
  const char* const x_suffix = "";
  /* 
   * const char* const x_prefix = colours ? UTIL_TEXT_DIM : "";
   * const char* const x_suffix = colours ? UTIL_TEXT_RESET : "";
   */

  const monome_coefficient_type c = m.coefficient;
  const monome_degre_type d = m.degre;
  int printed = 0;
  if (!d)
  {
    printed = fprintf(
        stream, "%s"MONOME_COEFFICIENT_PRI"%s", coefficient_prefix, c,
        coefficient_suffix);
  }
  else
  {
    printed = fprintf(
        stream, "%s"MONOME_COEFFICIENT_PRI"%s%s*X^%s%s"MONOME_DEGRE_PRI"%s",
        coefficient_prefix, c, coefficient_suffix, x_prefix, x_suffix,
        degre_prefix, d, degre_suffix);
  }
  return printed;
}

#endif
