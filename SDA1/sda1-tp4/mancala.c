#include "mancala.h"

#include <inttypes.h>
#include <stdlib.h>

#include "attributes.h"

////////////////////////////////////////////////////////////////////////////////
// Struct
////////////////////////////////////////////////////////////////////////////////

struct mancala {
  liste* plateau;
  unsigned int joueur;
  size_t selection;
};

////////////////////////////////////////////////////////////////////////////////
// Fonctions locales (déclarations)
////////////////////////////////////////////////////////////////////////////////

sda1_attribute((unused)) static inline size_t
    mancala_grenier(const mancala* m, unsigned joueur);

sda1_attribute((unused)) static inline size_t
    mancala_premier_champ(const mancala* m, unsigned joueur);

sda1_attribute((unused)) static inline size_t
    mancala_dernier_champ(const mancala* m, unsigned joueur);

sda1_attribute(
    (unused,
     warn_unused_result)) static inline mancala* mancala_changer_tour(mancala*
                                                                          m);

sda1_attribute((unused)) static inline unsigned mancala_score_joueur(
    const mancala* m, unsigned joueur);

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////
mancala* mancala_init(const size_t champs, const unsigned int graines)
{
  mancala* m = malloc(sizeof *m);

  /* (Peut-être) À modifier ou compléter. */
  m->plateau = liste_vide();
  m->joueur = 0;
  m->selection = 1;
  
  //Initialisation  du plateau  selon le nombre de champs et graines
  for(size_t i = 0; i < (champs * 2 ) + 2 ; i++)
      m->plateau = liste_inserer_tete(m->plateau,graines);
  
  m->plateau = liste_modifier(m->plateau,mancala_grenier(m,0),0);
  m->plateau = liste_modifier(m->plateau,mancala_grenier(m,1),0);

  return m;
}//Done




////////////////////////////////////////////////////////////////////////////////
// Modificateurs
////////////////////////////////////////////////////////////////////////////////

mancala* mancala_egrainer(mancala* const m, const size_t i)
{
       size_t  grenier_init; // on stoque le grenier du joueur actuel
       size_t  prem_champ_j; // on stoquera le premier champ du joueur suivant 
if(mancala_joueur(m)==0 )
{
      if(mancala_coup_valide(m,i))
      {
         grenier_init= liste_ieme(m->plateau,mancala_grenier(m,mancala_joueur(m))); // on stoque le grenier du joueur actuel
         prem_champ_j=mancala_premier_champ(m,1);           //on stoque le champ suivant
         m->plateau=liste_egrainer(m->plateau,i);
         if( (liste_ieme(m->plateau,mancala_grenier(m,mancala_joueur(m))) != grenier_init) && ( mancala_premier_champ(m,1) == prem_champ_j ))     
                 m->selection=mancala_premier_champ(m,mancala_joueur(m));    
          else 
            {
                  m->joueur=1;
                  m->selection=mancala_premier_champ(m,1);
            }
      }
}

else {
 if(mancala_joueur(m)==1){
        if(mancala_coup_valide(m,i)){
          grenier_init= liste_ieme(m->plateau,mancala_grenier(m,mancala_joueur(m))); // on stoque le grenier du joueur actuel
   size_t prem_champ_j2=mancala_premier_champ(m,0);            //on stoque le champ suivant     
          m->plateau=liste_egrainer(m->plateau,i);
          if( grenier_init!=liste_ieme(m->plateau,mancala_grenier(m,mancala_joueur(m))) && (prem_champ_j2 == mancala_premier_champ(m,0)))          
                  m->selection=mancala_premier_champ(m,mancala_joueur(m));
           else { 
                  m->joueur=0;
                  m->selection=mancala_premier_champ(m,0);
                }
        }
       }
}
  return m;
}



mancala* mancala_bruler(mancala* const m, const size_t i)
{
  if(mancala_peut_bruler(m))
    m->plateau = liste_supprimer(m->plateau,i);

  return m;
}


mancala* mancala_selection_gauche(mancala* const m)
{
  if(mancala_joueur(m)==0){
    if(m->selection -1 >= mancala_premier_champ(m,mancala_joueur(m)))
        m->selection=m->selection -1;
  }
  else 
    if(mancala_joueur(m)==1){
      if(m->selection + 1 <= mancala_dernier_champ(m,mancala_joueur(m)))
        m->selection=m->selection +1;
    }

  return m;
}


mancala* mancala_selection_droite(mancala* const m)
{
  if(mancala_joueur(m)==0){
    if(m->selection +1 != mancala_grenier(m,m->joueur))
        m->selection=m->selection +1;
  }
  else 
    if(mancala_joueur(m)==1){
      if(m->selection -1 != mancala_grenier(m,m->joueur) && (m->selection -1 != mancala_grenier(m,0)))
        m->selection=m->selection -1; 
    }

  return m;
}



void mancala_free(mancala* const m)
{
  liste_detruire(m->plateau);
  free(m);

  return;
}//


////////////////////////////////////////////////////////////////////////////////
// Sélecteurs
////////////////////////////////////////////////////////////////////////////////

bool mancala_partie_finie(const mancala* const m)
{
  size_t debut = 0;

  if(m->joueur == 0)
  {
    debut = mancala_premier_champ(m,0);
    for( ; debut< mancala_dernier_champ(m,0) ; debut++)
      if(liste_ieme(m->plateau,debut) != 0)
        return false;
  }else if(m->joueur == 1)
  {
    debut = mancala_premier_champ(m,1);
    for( ; debut< mancala_dernier_champ(m,1) ; debut++)
      if(liste_ieme(m->plateau,debut) != 0)
        return false;
  }
  return true;
}


unsigned int mancala_score_joueur_1(const mancala* const m)
{
  return m->joueur == 0?liste_ieme(m->plateau,mancala_grenier(m,0)):0; 
}

unsigned int mancala_score_joueur_2(const mancala* const m)
{
  return m->joueur == 1?liste_ieme(m->plateau,mancala_grenier(m,1)):0;
}

const liste* mancala_plateau(const mancala* const m) {
  return m->plateau;
}

unsigned int mancala_joueur(const mancala* const m) {
  return m->joueur;
}

bool mancala_coup_valide(const mancala* const m, const size_t i)
{  
size_t longueur_liste=liste_longueur(m->plateau);
if(m->joueur==0) return (i<(longueur_liste/2)&& (i!=0));
else return (i>longueur_liste/2);
if(m->joueur==1) return (i<(longueur_liste/2)&& (i!=0));
else return (i>longueur_liste/2);
}



size_t mancala_selection(const mancala* const m)
{
  
  if(m->joueur == 0 && (m->selection >= mancala_premier_champ(m,0) && m->selection <= mancala_dernier_champ(m,0)))
    return m->selection;
  else if(m->joueur == 1 && (m->selection >= mancala_premier_champ(m,1) && m->selection <= mancala_dernier_champ(m,1)))
    return m->selection;
  exit(1);
}


bool mancala_peut_bruler(const mancala* const m)
{
  size_t nb_champs = 0;

  if(m->joueur == 0)
  {
    nb_champs = (mancala_dernier_champ(m,0) - mancala_premier_champ(m,0)) + 1;
  }else if(m->joueur == 1)
  {
    nb_champs = (mancala_dernier_champ(m,1) - mancala_premier_champ(m,1)) + 1;
  }

  return (nb_champs >= 4)?true:false;
}


////////////////////////////////////////////////////////////////////////////////
// Fonctions locales (définitions)
////////////////////////////////////////////////////////////////////////////////

size_t mancala_grenier(const mancala* m, const unsigned int joueur) {
  const liste* const plateau = mancala_plateau(m);
  const size_t longueur = liste_longueur(plateau);
  return joueur == 0 ? (longueur / 2) : 0;
}

size_t mancala_premier_champ(const mancala* m, const unsigned int joueur) {
  const liste* const plateau = mancala_plateau(m);
  const size_t longueur = liste_longueur(plateau);
  return joueur == 0 ? 1 : ((longueur / 2) + 1);
}

size_t mancala_dernier_champ(const mancala* m, const unsigned int joueur) {
  const liste* const plateau = mancala_plateau(m);
  const size_t longueur = liste_longueur(plateau);
  return joueur == 0 ? ((longueur / 2) - 1) : (longueur - 1);
}

mancala* mancala_changer_tour(mancala* const m) {
  const liste* const plateau = mancala_plateau(m);
  const size_t longueur = liste_longueur(plateau);
  m->joueur = m->joueur ? 0 : 1;
  m->selection = m->joueur ? (longueur - 1) : 1;
  return m;
}

unsigned int mancala_score_joueur(
    const mancala* const m, const unsigned int joueur) {
  
  return 0;
}
