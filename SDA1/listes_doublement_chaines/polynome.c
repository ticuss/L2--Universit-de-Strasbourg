/**
 * \file polynome.c
 * \brief Fonctions de manipulation de polynômes.
 */

#include "polynome.h"
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////

polynome* polynome_addition(const polynome* const P1, const polynome* const P2)
{
  liste* resultat = liste_vide();
  liste* poly1=liste_debut(P1);
  liste* poly2=liste_debut(P2);
if(liste_longueur(liste_debut(poly1)) < liste_longueur(liste_debut(poly2)))
  {
    while (poly1)
    {
      resultat=liste_inserer(resultat,liste_monome(poly1));
      resultat=liste_inserer(resultat,liste_monome(poly2));
      
      poly1=liste_suivant(poly1);
      poly2=liste_suivant(poly2);
    }
    while(poly2)
    { 
    resultat=liste_inserer(resultat,liste_monome(poly2));
    poly2=liste_suivant(poly2);
    }
  }
  else {
    
while(poly1){
  resultat=liste_inserer(resultat,liste_monome(poly1));
  poly1=liste_suivant(poly1);
}
while(poly2){
  resultat=liste_inserer(resultat,liste_monome(poly2));
  poly2=liste_suivant(poly2);
}
  }
  resultat = liste_normaliser(resultat);

  return resultat;
}



polynome* polynome_multiplication(
    const polynome* const P1, const polynome* const P2)
{
  liste* resultat = liste_vide();
  liste * poly1 = liste_debut(P1);
  liste * poly2 = NULL;
  monome reponse;
  monome poly_1;
  monome poly_2;
  if(liste_est_vide(P1) || liste_est_vide(P2))
    return NULL;
  else
  {
    while(poly1)
    {
      poly_1 = liste_monome(poly1);
      poly2 = liste_debut(P2);
      while(poly2)
      {
        poly_2 = liste_monome(poly2);
        reponse.degre = poly_1.degre + poly_2.degre;
        reponse.coefficient = poly_1.coefficient * poly_2.coefficient;
        resultat = liste_inserer(resultat,reponse);
        poly2 = liste_suivant(poly2);
      }
      poly1 = liste_suivant(poly1);
    }
  }

  return liste_normaliser(resultat);
}


polynome* polynome_derivee(const polynome* const P1)
{
  liste* resultat=liste_vide();
  liste* poly=liste_debut(P1);
  while(poly){
    monome m=liste_monome(poly);
    m.coefficient=(m.coefficient)*(m.degre);
    m.degre=m.degre-1;
    resultat=liste_inserer(resultat,m);
    poly=liste_suivant(poly);
  }
  resultat=liste_normaliser(resultat);
  return resultat;
}



////////////////////////////////////////////////////////////////////////////////
// Divers
////////////////////////////////////////////////////////////////////////////////

void polynome_free(polynome* p)
{
   //pas besoin de cette fonction car le free est fait par liste_free();
   return ;   

}

polynome* polynome_sread(const char* string)
{
  polynome* p = liste_sread(string);
  p = liste_normaliser(p);
  return p;
}

polynome* polynome_fread(FILE* const stream)
{
  polynome* p = liste_fread(stream);
  p = liste_normaliser(p);
  return p;
}

void polynome_fwrite(FILE* const stream, const polynome* const p)
{
  liste_fwrite(stream, p);
}
