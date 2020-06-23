#ifndef _SORTE_H_
#define _SORTE_H_

/**
 * \file sorte.h
 * Définition de la sorte S
 */

#include <inttypes.h>

/**
 * \defgroup S_module S
 * \brief Sorte S.
 *
 * \copydetails S
 */


#ifndef TYPE_S
  #define TYPE_S intmax_t
  #ifndef PRI_S
    #define PRI_S PRIdMAX
  #endif
  #ifndef SCN_S
    #define SCN_S SCNdMAX
  #endif
  #ifndef S_C
    #define S_C(x) INTMAX_C(x)
  #endif
#endif

/*
 * PRI_S et SCN_S ont une valeur par défaut si et seulement si
 * TYPE_S est défini à sa valeur par défaut.
 * On exige que PRI_S et SCN_S soient manuellement définis
 * lorsque TYPE_S est manuellement défini, car ces deux macros doivent
 * être adaptées à TYPE_S.
 */
#ifndef PRI_S
  #error "Aucune définition trouvée pour PRI_S."
#endif
#ifndef SCN_S
  #error "Aucune définition trouvée pour SCN_S."
#endif


/**
 * \typedef S
 * \brief Sorte S
 *
 * # Introduction
 *
 * La sorte ::S est utilisée pour abstraire la représentation d'élements d'un
 * type arbitrairement choisi.
 *
 * Une expression constante dans le bon type peut être obtenue avec la macro
 * ::S_C.
 *
 * Les macros présentées dans le tableau ci-dessous peuvent être utilisées pour
 * obtenir la bonne chaîne de conversion à utiliser dans une chaîne de
 * formattage pour les fonctions de la famille \c \b printf(3).
 *
 * Macro   | Conversion
 * -----   | ----------
 * ::PRI_S | écrire une valeur de type S
 * ::SCN_S | scanner une valeur de type S
 *
 * # Exemple
 *
 * \code
 * S entree;
 * printf("Veuillez entrer un nombre :\n> ");
 * const int lu = scanf("%"SCN_S, &entree);
 * if (lu != 1)
 *   exit(1);
 * printf("Valeur lue : %"PRI_S"\n", entree);
 *
 * const S x = S_C(42);
 * const S resultat = x + entree;
 * printf("%"S_PRIdS" + %"PRI_S" = %"PRI_S"\n", entree, x, resultat);
 * \endcode
 *
 * \ingroup S_module
 */
typedef TYPE_S S;

/**
 * \brief Expression constante de type S.
 * \ingroup S_module
 */
#define S_C(x) INTMAX_C(x)

/**
 * \brief Écrire une valeur de type S sur la sroite standard.
 * \param[in] x La valeur à afficher.
 * \return Nombre de caractères écrits (voir printf(3)).
 */
static inline int S_ecrire(const S x) {
  return printf("%"PRI_S, x);
}

/**
 * \brief Écrire une valeur de type S sur la sroite standard.
 * \param[in,out] x Un pointeur vers une sorte S
 * \return Nombre de caractères écrits (voir scanf(3)).
 * \retval 1 en cas de lecture réussie
 * \pre x est un pointeur valide.
 */
static inline int S_lire(S* const x) {
  return scanf("%"SCN_S, x);
}

#endif
