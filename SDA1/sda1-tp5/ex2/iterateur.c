#include "iterateur.h"

#include <stdlib.h>

typedef enum iterateur_type {
  ITERATEUR_LISTE,
  ITERATEUR_TABLEAU,
  ITERATEUR_INCONNU,
} iterateur_type;

struct iterateur {
  iterateur_type type;
  union {
    const liste *l;
    struct {
      const tableau *t;
      size_t position;
    };
  };
};

iterateur *liste_iterateur_debut(const liste *l){
  iterateur* it = malloc(sizeof *it);
  if (!it)
    return it;

  it->type=ITERATEUR_LISTE;
  it->l=liste_debut(l);

  return it;
}

iterateur* liste_iterateur_fin(const liste* l)
{
  iterateur* it = malloc(sizeof *it);
  if (!it)
    return it;
 
   it->type=ITERATEUR_LISTE;
   it->l=liste_fin(l);
  return it;
}

iterateur* tableau_iterateur_debut(const tableau* t)
{
  iterateur* it = malloc(sizeof *it);
  if (!it)
    return it;
 
  it->type=ITERATEUR_TABLEAU;
  it->t=t;
  it->position=0;
  return it;
}


iterateur* tableau_iterateur_fin(const tableau* t)
{
  iterateur* it = malloc(sizeof *it);
  if (!it)
    return it;
 
  it->type=ITERATEUR_TABLEAU;
  it->t=t;
  it->position=tableau_longueur(it->t);
  return it;
}


iterateur* iterateur_suivant(iterateur* it)
{
 
  if(it->type==ITERATEUR_TABLEAU)
    it->position++;
  else
       if(it->type==ITERATEUR_LISTE)
          it->l=liste_suivant(it->l);

return it;
}

iterateur* iterateur_precedent(iterateur* it)
{
 
   if(it->type==ITERATEUR_TABLEAU)
    it->position--;
  else
       if(it->type==ITERATEUR_LISTE)
          it->l=liste_precedent(it->l);

return it;
}

bool iterateur_egal(const iterateur* a, const iterateur* b)
{
 
  if (a->type ==  b->type )
  {
    if(a->type==ITERATEUR_TABLEAU)
    {
      if( (b->position==a->position) && (a->t==b->t) )
      {
        return true;
      }
      else return false;
    }

    else if(a->type==ITERATEUR_LISTE)
          {
            if(a->l==b->l)
              return true;
            else return false;       
          }
          else return false;
  }
  else 
  return false;
}

S iterateur_valeur(const iterateur* it)
{
 
  if(it->type==ITERATEUR_TABLEAU)
        return tableau_element(it->t,it->position);
  else 
    if(it->type==ITERATEUR_LISTE)
         return liste_element(it->l);
    else return (S) {0};
}

void iterateur_free(iterateur* i)
{
 
  free(i);
}
