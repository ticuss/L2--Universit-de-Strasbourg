#include "liste_avancee.h"

#include <stdlib.h>

liste* liste_range(S debut, S fin, S pas)
{
  /* (Peut-être) À modifier ou compléter.*/ //done
  liste* l=liste_vide();
  if(pas>0)
  {
    S i;
    for(i=debut; i<fin;i+=pas)
    {
    l=liste_insertion_queue(l,i);
    }
  } 
  else 
          { S i;
             for(i=debut;i>fin;i+=pas)
              {
                l=liste_insertion_queue(l,i);   
              }
          }
  
  return liste_debut(l);
}






liste* liste_reverse(const liste* l)
{
  
  liste* lrev=liste_vide();
  for(size_t i=0;i<liste_longueur(l);i++)
  {
      lrev=liste_insertion_tete(lrev,liste_element(liste_ieme(l,i)));
  }
  return lrev;
}

liste* liste_map(const liste* l, S (*f)(S))
{
  
  liste* lmap=liste_vide();
  for(size_t i=0;i<liste_longueur(l);i++)
  { S func = f(liste_element(liste_ieme(l,i)));
    lmap=liste_insertion_queue(lmap,func);
  }
  return liste_debut(lmap);
}

liste* liste_filter(const liste* l, bool (*f)(S))
{
  
  liste* lfiltre= liste_vide();
  for(size_t i=0;i<liste_longueur(l);i++)
  {
    if(f(liste_element(liste_ieme(l,i))))
      lfiltre=liste_insertion_queue(lfiltre,liste_element(liste_ieme(l,i)));
  }
  return liste_debut(lfiltre);
}



S liste_reduce(const liste* l, S (*f)(S, S))
{
  

 S x=liste_element(l);
    
    l=liste_suivant(l);
 while(l !=NULL)
 {
   x=f(x,liste_element(l));
   l=liste_suivant(l);
 }

  return x;
}

void liste_fold_left(const liste* l, void (*f)(void*, S), void* resultat)
{
  
  liste* lfl = liste_debut(l);
  while(lfl != NULL)
  {
    f(resultat,liste_element(lfl));
    lfl=liste_suivant(lfl);
  }
}

void liste_fold_right(const liste* l, void (*f)(S, void*), void* resultat)
{
  
    liste* lfl = liste_fin(l);
  while(lfl != NULL)
  {
    f(liste_element(lfl),resultat);
     lfl=liste_precedent(lfl);
  }
}

S add(S x, S y)  {return x+y; }

S liste_somme(const liste* l)
{
return liste_reduce(l,add);
}

S produit(S x, S y){ return x*y ;}

S liste_produit(const liste* l)
{
  return liste_reduce(l,produit);
}

S min(S x,S y){ if (x<y) return x ;else return y; }

S liste_minimum(const liste* l)
{
  
  return liste_reduce(l,min);
}

S max(S x,S y){ if (x>y) return x ;else return y; }

S liste_maximum(const liste* l)
{
  
  return liste_reduce(l,max);
}

S carre(S x){return x*x;}

liste* liste_carre(const liste* l)
{
   
 return liste_map(l,carre);

}

bool liste_any(const liste* l, bool (*f)(S))
{
  
  if(liste_longueur(liste_filter(l,f))>=1)
  return true;
  else 
  return false;
}

bool liste_all(const liste* l, bool (*f)(S))
{
  
  if(liste_longueur(liste_filter(l,f))==liste_longueur(l))
  return true;
  else
  return false;
}




