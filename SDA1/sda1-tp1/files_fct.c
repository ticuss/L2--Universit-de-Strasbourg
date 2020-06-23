/**
 * \file files_fct.c
 * \brief Source pour les files fonctionnelles.
 */
#include "files_fct.h"

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////

file file_nouv(void)
{
  file f;
  f.taille = 0;
  f.debut = 0 ;
  return f ;
}

file file_adjq(file f, S x)
{
  f.elements[(f.taille)% TAILLE_MAX ] = x;
  f.taille++;
  return f;
}

file file_supt(file f)
{
  f.debut=(f.debut +1 )%TAILLE_MAX;

for (size_t i = 0; i < f.taille-1%TAILLE_MAX; i++)
{
  f.elements[i]=f.elements[i+1];
}
f.taille--;

  return f;
}

////////////////////////////////////////////////////////////////////////////////
// Destructeurs
////////////////////////////////////////////////////////////////////////////////

// j'ai changé le type de retour de la fonction car ca m'affiche un warning que f est pas utilise si j'assigne f = file_nouv() sans return;

file file_detruit(file f)
{
   f = file_nouv();
  return f;
}

////////////////////////////////////////////////////////////////////////////////
// Selecteurs
////////////////////////////////////////////////////////////////////////////////

S file_tete(file f)
{
  return f.elements[f.debut];
}

bool file_estvide(file f)
{
if (f.taille == 0)
  return true ;
else 
  return false;
}

size_t file_taille(file f)
{
  return f.taille;
}

S file_ieme(file f, size_t i)
{
  if(i>=TAILLE_MAX) 
  exit(-1);
  return f.elements[i];
}

////////////////////////////////////////////////////////////////////////////////
// Divers
////////////////////////////////////////////////////////////////////////////////

int file_affiche(FILE* const stream, file f)
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
