#ifndef _FILE_H_
#define _FILE_H_

/**
 * \file file.h
 * \brief Header pour les files par mutation.
 */
 
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "sorte.h"
#include "util.h"

/**
 * \defgroup file_module File
 * \copydetails file
 */

/**
 * \struct file
 * \brief Files FIFO d'éléments ::S par mutation.
 *
 * # Introduction
 * 
 * ::file représente des files de type FIFO. Les élements dans une ::file sont
 * de type ::S.
 *
 * # Constructeurs
 * \see \ref file_constructeurs
 *
 * \copydetails file_constructeurs
 *
 * # Destructeurs
 * \see \ref file_destructeurs
 *
 * \copydetails file_destructeurs
 *
 * # Sélecteurs
 * \see \ref file_selecteurs
 *
 * \copydetails file_selecteurs
 *
 * # Divers
 * \see \ref file_divers
 *
 * \copydetails file_divers
 *
 * # Exemple
 *
 * \code
 * file* f = file_nouv();
 * f = file_adjq(f, S_C(0));
 * f = file_adjq(f, S_C(1));
 * f = file_adjq(f, S_C(2));
 * f = file_affiche(f);
 * file_detruit(f);
 * \endcode
 *
 * \ingroup file_module
 */
struct file;
typedef struct file file;

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup file_constructeurs Constructeurs
 * \brief Constructeurs pour ::file.
 *
 * La création d'une nouvelle ::file se fait à l'aide de la fonction file_nouv().
 * Un élément peut être ajouté en fin de ::file en utilisant file_adjq() tandis
 * que file_supt() supprime l'élément en tête de ::file.
 *
 * \ingroup file_module
 */

/**
 * \brief Construire une ::file vide.
 * \return Une nouvelle ::file vide.
 *
 * \post \code file_taille(f) == 0 \endcode
 * \post \code file_estvide(f) == true \endcode
 * \warning Après utilisation, la ::file retournée devra être détruite avec
 *          la fonction file_detruit().
 * \see file_detruit
 *
 * \memberof file
 * \ingroup file_constructeurs
 */
file* file_nouv(void);

/**
 * \brief Ajouter un élément en queue de ::file 
 * \param[in,out] f File à modifier.
 * \param[in]     x Élément à ajouter
 * \return la ::file \a f + (\a x)
 *
 * \post \code file_ieme(file_taille(f)) == x \endcode
 *
 * \memberof file
 * \ingroup file_constructeurs
 */
file* file_adjq(file* f, S x);

/**
 * \brief Supprimer l’élément de tête de ::file.
 * \param[in,out] f File à modifier.
 * \return La ::file privée de son premier élément.
 *
 * \pre \code file_estvide(f) == false \endcode
 *
 * \memberof file
 * \ingroup file_constructeurs
 */
file* file_supt(file* f);

////////////////////////////////////////////////////////////////////////////////
// Destructeurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup file_destructeurs Destructeurs
 * \brief Destructeurs pour ::file.
 *
 * Une ::file peut être détruite avec file_detruit().
 *
 * \ingroup file_module
 */

/**
 * \brief Détruire la ::file f.
 * \param[in] f File à détruire.
 * \see file_nouv
 *
 * \memberof file
 * \ingroup file_destructeurs Destructeurs
 */
void file_detruit(file* f);

////////////////////////////////////////////////////////////////////////////////
// Selecteurs
////////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup file_selecteurs Sélecteurs
 * \brief Sélecteurs pour ::file.
 *
 * file_estvide() permet de vérifier si une ::file est vide tandis que
 * file_taille() retourne la taille d'une ::file. L'élément en tête de ::file
 * peut être obtenu avec la fonction file_tete() et le i-ième élément d'une
 * ::file peut être récupéré avec file_ieme().
 *
 * \ingroup file_module
 */

/**
 * \brief Obtenir l'élément en tête de ::file.
 * \param[in] f File à inspecter.
 * \return Une valeur de type S.
 *
 * \pre \code file_estvide(f) == false \endcode
 *
 * \memberof file
 * \ingroup file_selecteurs
 */
S file_tete(const file* f);

/**
 * \brief Tester si une ::file est vide.
 * \param[in] f File à inspecter.
 * \return Un booléen indiquant si la ::file est vide.
 * \retval true  si la ::file \a f est vide.
 * \retval false si la ::file \a f n'est pas vide.
 *
 * \memberof file
 * \ingroup file_selecteurs
 */
bool file_estvide(const file* f);

/**
 * \brief Obtenir la taille de la ::file
 * \param[in] f File à inspecter.
 * \return Nombre d'éléments de la ::file \a f
 *
 * \memberof file
 * \ingroup file_selecteurs
 */
size_t file_taille(const file* f);

/**
 * \brief Obtenir le i-ième élément d’une ::file
 * \param[in] f File à inspecter.
 * \param[in] i Position de l'élément dans la ::file.
 * \return une valeur de type \c S
 *
 * \pre \a f est un pointeur non nul.
 * \pre \code file_estvide(f) == false \endcode
 * \pre 0 <= \a i < file_taille(\a f)
 *
 * \memberof file
 * \ingroup file_selecteurs
 */
S file_ieme(const file* f, size_t i);

////////////////////////////////////////////////////////////////////////////////
// Divers
////////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup file_divers Divers
 * \brief Fonctions diverses pour ::file.
 *
 * Une ::file peut-être affichée à l'aide de la fonction file_affiche().
 *
 * \ingroup file_module
 */

/**
 * Affichage du contenu d'une ::file dans le fichier passé en paramètre
 * \param[in] stream Fichier de sortie.
 * \param[in] f      File à afficher.
 * \return Nombre de caractères écrits dans \a stream.
 *
 * \memberof file
 * \ingroup file_divers
 */
int file_affiche(FILE* stream, const file* f);

#endif
