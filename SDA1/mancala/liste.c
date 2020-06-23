/**
 * \file liste.c
 * \brief Listes doublement chaînées de monomes
 */

#include "liste.h"

#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

/**
 * \brief Liste
 */
struct liste {
  /** \brief Feves. */
  unsigned int graines;
  /** \brief Élément suivant dans la liste. */
  struct liste* suivant;
};

////////////////////////////////////////////////////////////////////////////////
// Fonctions locales
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Retourne le ième maillon d'une liste.
 * \param[in] l Liste d'entrée.
 * \param[in] i Indice du maillon recherché.
 * \return ième maillon de la liste.
 *
 * \pre liste_est_vide(l) == false
 * \pre 0 <= i < liste_longueur(l)
 */
static inline liste* liste_ieme_maillon(const liste* const l, const size_t i) {
  const liste* courant = l;
  for (size_t j = 0; j < i; ++j)
    courant = courant->suivant;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
  return (liste*) courant;
#pragma GCC diagnostic pop
}

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////

liste* liste_vide(void) {
  
  return NULL;
}

liste* liste_inserer_tete(liste* const l, const unsigned int graines)
{
  liste* const nouveau_maillon = malloc(sizeof *nouveau_maillon);
  liste* debut=l;
  nouveau_maillon->graines=graines;
  nouveau_maillon->suivant=debut;

  if (!l)
      nouveau_maillon->suivant=nouveau_maillon; 

  else { 
      liste* x=l->suivant; 
  while(x->suivant != debut)
      x=x->suivant;
  x->suivant=nouveau_maillon; 
  
  }
  return nouveau_maillon;
}


liste* liste_supprimer(liste* const l, const size_t i)
{

  if(!l)
    return NULL;
  else
  { liste* debut=l;
    liste* asupprimer = liste_ieme_maillon(l,i);
    if(liste_longueur(l) == 1)
    {
        free(l);
        return NULL;
    }
    else if(asupprimer->suivant == debut)
    {
        liste* precedent = liste_ieme_maillon(l,i-1); 
        precedent->suivant = debut; 
        free(asupprimer);
    }
    else if(asupprimer == debut) 
    {
        liste* next = asupprimer->suivant;

       
        liste* courant = l;
        while(courant->suivant != debut) 
            courant= courant->suivant;
        courant->suivant = next;

        free(asupprimer);

        return next;
    }
    else
    {
        liste* precedent = liste_ieme_maillon(l,i-1);
        asupprimer = precedent->suivant;
        precedent->suivant = asupprimer->suivant;
        free(asupprimer);
    }
  }

  return l;
}



liste* liste_egrainer(liste* const l, const size_t ieme)
{ 
        liste* debut=l;
         liste* amod= liste_ieme_maillon(l,ieme); 
      while(debut->suivant != l) {
            if(debut==amod){
            liste* next = debut->suivant; 
            size_t g=debut->graines;
             debut->graines=0;      
              for(size_t i=g;i!=0;i--){  
                      next->graines=next->graines+1;  
                      next=next->suivant;
              }
            }
              debut=debut->suivant;    
            }

  return l;
}


liste* liste_modifier(liste* const l, const size_t i, const unsigned int graines)
{
  liste* li = liste_ieme_maillon(l, i);
  li->graines = graines;
  return l;
}

////////////////////////////////////////////////////////////////////////////////
// Destructeurs
////////////////////////////////////////////////////////////////////////////////

void liste_detruire(liste* const l) 
 {
  if (liste_est_vide(l))
    return;

  liste * courant = l;
  liste * Asup = NULL;
  for( size_t i = liste_longueur(l); i !=0 ; i--)
  {
    Asup =  courant;
    courant = courant->suivant;
    free(Asup);
  }

}


////////////////////////////////////////////////////////////////////////////////
// Sélecteurs
////////////////////////////////////////////////////////////////////////////////

bool liste_est_vide(const liste* const l) {
  return l ? false : true;
}

unsigned int liste_ieme(const liste* const l, const size_t ieme)
{
 
  if(!liste_ieme_maillon(l,ieme))
    return 0;
  else 
    return liste_ieme_maillon(l,ieme)->graines;
}


size_t liste_longueur(const liste* l)
{
  if (liste_est_vide(l))
    return 0;

  size_t compteur = 1;
  const liste * copy = l;
  while(l != copy->suivant)
  {
    compteur++;
    copy =  copy->suivant;
  }
  return compteur;
}


////////////////////////////////////////////////////////////////////////////////
// Divers
////////////////////////////////////////////////////////////////////////////////

void liste_afficher(FILE* const stream, const liste* const l) {
  if (liste_est_vide(l)) {
    fprintf(stream, "graines:\n");
    fprintf(stream, "index:\n");
    return;
  }

  fprintf(stream, "graines: ");
  fprintf(stream, "%2u", l->graines);
  for (const liste* p = l->suivant; p != l; p = p->suivant) {
    fprintf(stream, "  %2u", p->graines);
  }
  fprintf(stream, "\n");

  if (isatty(fileno(stream))) {
    fprintf(stream, "\033[2m");
  }
  fprintf(stream, "index: ");
  size_t i = 0;
  fprintf(stream, "%2zu", i);
  for (const liste* p = l->suivant; p != l; p = p->suivant) {
    ++i;
    fprintf(stream, "  %2zu", i);
  }
  fprintf(stream, "\n");
  if (isatty(fileno(stream))) {
    fprintf(stream, "\033[0m");
  }
}
