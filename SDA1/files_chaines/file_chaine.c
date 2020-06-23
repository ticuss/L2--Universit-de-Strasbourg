/**
 * \file files_ch.c
 * \brief Source pour les files chaînées.
 */

#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "util.h"

////////////////////////////////////////////////////////////////////////////////
// struct
////////////////////////////////////////////////////////////////////////////////

struct file
{
  S element;
  struct file* suivant;
};

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////

file* file_nouv(void)
{
  return NULL;
}

file* file_adjq(file* const f, const S x)
{
  file* const nouveau_chainon = malloc(sizeof *nouveau_chainon);
  if (!nouveau_chainon)
    ERREUR("malloc");
file * save = f;
  nouveau_chainon->element = x;
  nouveau_chainon->suivant = NULL;

 if(!save)
    return nouveau_chainon;

  while(save->suivant)
  {
    save = save->suivant;
  }
  save->suivant = nouveau_chainon;

  return f;
}


file* file_supt(file* const f)
{

     file * save = f;
   if(!save)
    return NULL;
  file * del = save;
  save = save->suivant;
  free(del);

  return save;

}

////////////////////////////////////////////////////////////////////////////////
// Destructeurs
////////////////////////////////////////////////////////////////////////////////

void file_detruit(file* const f)
{
    file * save = f;
  file * del = NULL;

  if(!save)
    exit(-1);

  while(save)
  {
    del = save;
    save = save->suivant;
    free(del);
  }
  return;
}


////////////////////////////////////////////////////////////////////////////////
// Sélecteurs
////////////////////////////////////////////////////////////////////////////////

S file_tete(const file* const f)
{
  const file * save = f;

  if(!save)
    exit(2);
  
  return save->element;

}

bool file_estvide(const file* const f)
{
  return f == NULL;
}

size_t file_taille(const file* const f)
{
  const file * save = f;
  size_t compteur = 0;

  while(save)
  {
    compteur++;
    save = save->suivant;
  }

  return compteur;
}

S file_ieme(const file* const f, const size_t ieme)
{
  const file * save = f;
  size_t compteur = 0;

  if(!save || ieme >= file_taille(f))
    exit(-1);

  while(save && compteur != ieme)
  {
      compteur++;
      save = save->suivant;
  }
  if(compteur==ieme)
    return save->element;
  else
    exit(-1);
}

////////////////////////////////////////////////////////////////////////////////
// Divers
////////////////////////////////////////////////////////////////////////////////

int file_affiche(FILE* const stream, const file* const f)
{
  /*
   * Pas besoin de modifier cette fonction.
   * Mais l'affichage sera étrange si certaines fonctions sont incorrectes ou
   * si la file n'a pas bien été construite (si les autres fonctions sont
   * fausses).
   */
  int total = 0, code = 0;

  for (const file* courant = f; courant; courant = courant->suivant)
  {
    const S ieme = file_tete(courant);
    code = fprintf(stream, "%"PRI_S" ", ieme);
    if (code >= 0)
      total += code;
    else
      return code;
  }
  code += fprintf(stream, "\n");
  return code >= 0 ? total + code : code;
}
