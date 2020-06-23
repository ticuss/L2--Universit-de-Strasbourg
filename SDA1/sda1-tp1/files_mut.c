/**
 * \file files_mut.c
 * \brief Source pour les files par mutation.
 */

#include "files_mut.h"

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

////////////////////////////////////////////////////////////////////////////////
// struct
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief File
 *
 * La struct pour le type opaque ::file.
 *
 */
struct file
{
  /** \brief Tableau d'éléments de type ::S et de taille #TAILLE_MAX. */
  S elements[TAILLE_MAX];
  /** \brief Position du premier élément dans le tableau file::x. */
  size_t debut;
  /** \brief Nombre d'éléments dans la file. */
  size_t taille;
};

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////

file* file_nouv(void)
{
  file *f=(file*)malloc(sizeof(file));
  f->taille=0;
  f->debut=0;

  return f;
}

file* file_adjq(file* const f, S x)
{
  f->elements[(f->debut + f->taille) % TAILLE_MAX] = x ;
  f->taille++;
  return f;
}

file* file_supt(file* const f)
{
  for (size_t i = 0; i < (f->taille-1)%TAILLE_MAX; i++)
  {
    f->elements[i]=f->elements[i+1];
  }
  f->debut =f->debut+1 %TAILLE_MAX;
  f->taille--;

  
  return f;
}

////////////////////////////////////////////////////////////////////////////////
// Destructeurs
////////////////////////////////////////////////////////////////////////////////

void file_detruit(file* const f)
{
  free(f);
  return;
}

////////////////////////////////////////////////////////////////////////////////
// Selecteurs
////////////////////////////////////////////////////////////////////////////////

S file_tete(const file* const f)
{
  return f->elements[f->debut];
}

bool file_estvide(const file* const f)
{
  if( f->taille==0)
    return true;
  else
    return false;

}

size_t file_taille(const file* const f)
{
  return f->taille;
}

S file_ieme(const file* const f, size_t i)
{
  if(i>=TAILLE_MAX -1)
  exit(-1);
  return f->elements[i];

}

////////////////////////////////////////////////////////////////////////////////
// Divers
////////////////////////////////////////////////////////////////////////////////

int file_affiche(FILE* const stream, const file* const f)
{
  /*
   * Pas besoin de modifier cette fonction.
   * Mais l'affichage sera étrange si file_ieme() ou file_taille() sont
   * incorrectes ou si la file n'a pas bien été construite (si les autres
   * fonctions sont fausses).
   */
  int total = 0, code = 0;

  for (size_t i = 0; i < file_taille(f); ++i)
  {
    const S ieme = file_ieme(f, i);
    code = fprintf(stream, "%"PRI_S" ", ieme);
    if (code >= 0)
      total += code;
    else
      return code;
  }
  code += fprintf(stream, "\n");
  return code >= 0 ? total + code : code;
}
