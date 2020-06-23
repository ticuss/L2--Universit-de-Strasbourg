/**
 * \file files_ch.c
 * \brief Source pour les files chaînées alternatives.
 */

#include "file.h"

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

////////////////////////////////////////////////////////////////////////////////
// struct
////////////////////////////////////////////////////////////////////////////////

struct chainon
{
  /** \brief Élément de type S */
  S element;
  /** \brief Pointeur sur le suivant */
  struct chainon* suivant;
};
typedef struct chainon chainon;

struct file
{
  /** \brief Tête de file chainée */
  chainon* tete;
  /** \brief Queue de file chainée */
  chainon* queue;
  /** \brief Nombre d'éléments dans la file */
  size_t taille;
};

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////

file* file_nouv(void)
{
  file* const f = malloc(sizeof *f);
  if (!f)
    ERREUR("malloc");
    
  f->queue = NULL;
  f->taille = 0;
  f->tete=NULL;
  
  return f;

}

file* file_adjq(file* const f, const S x)
{
  
  chainon* const nouveau_chainon = malloc(sizeof *nouveau_chainon);
  if (!nouveau_chainon)
    ERREUR("malloc");
  
  nouveau_chainon->element = x;
  nouveau_chainon->suivant = NULL;

  file * save = f;

  if(!save->tete )
  {
    save->tete = nouveau_chainon;
    save->queue = nouveau_chainon;
  }else
  {
    save->queue->suivant = nouveau_chainon;
    save->queue = nouveau_chainon;
  }
  save->taille++;
  return f;
}


file* file_supt(file* const f)
{
  
  file * save = f;
  chainon *del = NULL;

  if(save->taille == 0)// ou if(!save->tete)
    return NULL;
  else if((save->tete) == (save->queue))
  {
    del = save->tete;
    save->tete = NULL;
    save->queue =NULL;
  }else
  {
    del = save->tete;
    save->tete = save->tete->suivant;
  }
  save->taille--;
  free(del);
  return f;
}

////////////////////////////////////////////////////////////////////////////////
// Destructeurs
////////////////////////////////////////////////////////////////////////////////

void file_detruit(file* const f)
{
  file * save = f;
  chainon * del  = NULL;

  if(save->taille == 0) // ou if(!save->tete)
  { 
    exit(-1);
  }
  else
  {
    while(save->tete )
    {
      del = save->tete;
      save->tete = save->tete->suivant;
      free(del);
      save->taille--;
    }
  }
  
}

////////////////////////////////////////////////////////////////////////////////
// Sélecteurs
////////////////////////////////////////////////////////////////////////////////

S file_tete(const file* const f)
{
  /* (Peut-être) À modifier ou compléter. */
  const file * save = f;
  if(save->taille==0) // ou  if(!save->tete)
    exit(-1);
  
  return save->tete->element;
}


bool file_estvide(const file* const f)
{
   return f->taille==0;
}

size_t file_taille(const file* const f)
{
  return f->taille;
}
/*
S file_ieme(const file* const f, const size_t ieme)
{
  
   file * const save = f;
  size_t compteur = 0;
  if(!save->tete || ieme >= save->taille)
    exit(3);

  while(save->tete &&  compteur != ieme )
  {
    save->tete = save->tete->suivant;
    compteur++;
  }
  if(compteur == ieme)
    return save->tete->element;
  else
    exit(-1);
}*/
// II variante 
S file_ieme(const file* const f, const size_t ieme)
{
  file *save = f;
  for (size_t i = 0; i < ieme; i++) {
      save->tete = save->tete->suivant;
  }
  return save->tete->element;
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

  for (const chainon* courant = f->tete; courant; courant = courant->suivant)
  {
    const S ieme = courant->element;
    code = fprintf(stream, "%"PRI_S" ", ieme);
    if (code >= 0)
      total += code;
    else
      return code;
  }
  code += fprintf(stream, "\n");
  return code >= 0 ? total + code : code;
}
