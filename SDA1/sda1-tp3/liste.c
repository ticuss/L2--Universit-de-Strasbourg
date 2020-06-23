/**
 * \file liste.c
 * \brief Listes doublement chaînées de monomes
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sysexits.h>

#include "monome.h"
#include "liste.h"

/**
 * \brief Liste
 */
struct liste
{
  /** \brief Terme. */
  monome terme;
  /** \brief Élément suivant dans la liste. */
  struct liste* suivant;
  /** \brief Élément précédent dans la liste. */
  struct liste* precedent;
};

////////////////////////////////////////////////////////////////////////////////
// Constructeurs
////////////////////////////////////////////////////////////////////////////////

liste* liste_vide(void)
{
  return NULL;
}

liste* liste_inserer(liste* const l, const monome t)
{
  liste* const nouveau = malloc(sizeof *nouveau);
  if (!nouveau)
  {
    perror("malloc");
    exit(EX_OSERR);
  }

  nouveau->terme = t;
  nouveau->suivant = NULL;
  nouveau->precedent = NULL;
  liste * save = l;
  if(!save)
    return nouveau;
  else
  {
    while(save->suivant)
    {
      save = save->suivant;
    }
    save->suivant = nouveau;
    nouveau->precedent = save;
  }

  return l;
}


liste* liste_supprimer(liste* const l)
{
  liste * save = l;
  liste * del = NULL;
  if(!save)
    return NULL;
  else
  {
    if(!save->precedent && !save->suivant) 
    {
      free(save);
      return NULL;
    }
    else if(!save->precedent && save->suivant)
    {
       del = save;
       save = save->suivant;
       save->precedent = NULL;
       free(del);
       return save;
    }else if(save->precedent && !save->suivant)
    {
      del = save;
      save->precedent->suivant = NULL;
      free(del);
    }else
    {
      del = save;
      save->precedent->suivant = save->suivant;
      save->suivant->precedent = save->precedent;
      free(del);
    }
  }
  return l;
}


liste* liste_echanger(liste* const l)
{
  liste * save = l;
  monome courant;

  if(!save || !save->suivant)
    return l;
  else if(save->terme.degre < save->suivant->terme.degre)
  {
    courant = save->terme;
    save->terme = save->suivant->terme;
    save->suivant->terme = courant;
  }
  return l;
}


liste* liste_normaliser(liste* const l)
{
  if (!l || !l->suivant)
    return l;


  liste* P = l;
  bool echange = false;
  do
  {
    echange = false;
    liste* P1 = P;
    while (P1->suivant)
    {
      if(P1->terme.degre == P1->suivant->terme.degre)
      {
        liste * del;
        if(!P1->precedent)
        {
          P1->suivant->terme.coefficient += P1->terme.coefficient;
          P1=liste_supprimer(P1);
        }else if(P1->precedent)
        {
          del = P1;
          P1->suivant->terme.coefficient += P1->terme.coefficient;
          P1->suivant->precedent = P1->precedent; 
          P1->precedent->suivant = P1->suivant;
          P1=P1->suivant;
          free(del);
        }
      }else if(P1->terme.degre < P1->suivant->terme.degre)
      {
        echange = true;
        P1=liste_echanger(P1);
      }else
        P1=P1->suivant;
    }

  }
  while (echange);

  return P;
}



////////////////////////////////////////////////////////////////////////////////
// Destructeurs
////////////////////////////////////////////////////////////////////////////////

void liste_free(liste* l)
{
  liste * del = NULL;

  if(!l)
    return;
  else{
    while(l)
    {
      del = l;
      l = l->suivant;
      free(del);
    }
  }
}



////////////////////////////////////////////////////////////////////////////////
// Sélecteurs
////////////////////////////////////////////////////////////////////////////////

monome liste_monome(const liste* const l)
{
if(!l)
    exit(1);
  else
  return l->terme;
}

liste* liste_suivant(const liste* const l)
{
  /* (Peut-être) À compléter ou modifier. */
  if(!l)
    return NULL;
  else
    return l->suivant;
}

liste* liste_precedent(const liste* const l)
{
  /* (Peut-être) À compléter ou modifier. */
  if(!l)
    return NULL;
  else
    return l->precedent;
}

bool liste_est_vide(const liste* const l)
{
  /* (Peut-être) À compléter ou modifier. */
  return l == NULL;
}

bool liste_est_debut(const liste* const l)
{
  /* (Peut-être) À compléter ou modifier. */
  if(!l || (!l->precedent))
    return true;
  else
    return false;
}



liste* liste_debut(const liste* const l)
{
  if (!l)
    return 0;

  const liste* courant = l;
  while (courant->precedent)
    courant = courant->precedent;

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wcast-qual"
  return (liste*) courant;
  #pragma GCC diagnostic pop
}

liste* liste_ieme(const liste* const l, const size_t ieme)
{
  const liste* courant = liste_debut(l);

  /* (Peut-être) À compléter ou modifier. */
  size_t compteur = 0;

  if(!courant || ieme > liste_longueur(courant))
    return NULL;
  while(courant->suivant && compteur != ieme)
  {
    compteur++;
    courant = courant->suivant;
  }
  if(compteur == ieme)
  {
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wcast-qual"
    return (liste*) courant;
    #pragma GCC diagnostic pop
  }else
    return NULL;
  
}



size_t liste_longueur(const liste* const l)
{
  /* (Peut-être) À compléter ou modifier. */
  const liste * save = l;
  size_t compteur = 0;
  while(save)
  {
    compteur++;
    save = save->suivant;
  }
  return compteur;
}


////////////////////////////////////////////////////////////////////////////////
// Divers
////////////////////////////////////////////////////////////////////////////////

static inline void entree_incorrecte(
    const char* message, const char* ligne, const char* chaine_erronee,
    const size_t shifted)
{
  const bool couleurs = isatty(fileno(stderr));

  char buffers[3][2048] = { { 0 }, { 0 }, { 0 } };
  sscanf(ligne, "%2047[^\n]", buffers[0]);
  snprintf(buffers[1], shifted + 1, "%s", buffers[0]);
  sscanf(chaine_erronee, "%2047[^\n]", buffers[2]);
  const size_t size = strlen(buffers[2]);

  if (couleurs)
    fprintf(stderr, "\033[7m Avertissement \033[0m ");
  else
    fprintf(stderr, "[Avertissement] ");

  fprintf(stderr, "%s :\n", message ? message : "Entrée incorrecte");
  if (couleurs)
    fprintf(stderr, "%s\033[1m\033[33m%s\033[0m\n", buffers[1], buffers[2]);
  else
    fprintf(stderr, "%s%s\n", buffers[1], buffers[2]);
  for (size_t i = 0; i < shifted; ++i)
    fprintf(stderr, " ");
  if (size)
  {
    if (couleurs)
      fprintf(stderr, "\033[1m\033[33m^");
    else
      fprintf(stderr, "^");
    for (size_t i = 0; i < (size - 1); ++i)
      fprintf(stderr, "~");
  }
  if (couleurs)
    fprintf(stderr, "\033[0m\n");
  else
    fprintf(stderr, "\n");
}

liste* liste_sread(const char* const input)
{
  int read = 0;
  size_t shifted = 0;
  const char* remainder = input;

  liste* l = liste_vide();
  while (true)
  {
    for ( ; *remainder == ' ' || *remainder == '\t' || *remainder == '+'; ++remainder)
      ++shifted;
    if (*remainder == '\n' || *remainder == '\0')
      break;

    monome m = { .degre = 0, .coefficient = .0, };
    int scanned = sscanf(
        remainder,
        MONOME_COEFFICIENT_SCN"*%*[a-zA-Z]^"MONOME_DEGRE_SCN"%n",
        &m.coefficient, &m.degre, &read);
    if (scanned == 2)
    {
      l = liste_inserer(l, m);
      remainder += read;
      shifted += (size_t) read;
    }
    else if (scanned == 1)
    {
      entree_incorrecte("Degré non reconnu", input, remainder, shifted);
      break;
    }
    else
    {
      entree_incorrecte("Coefficient non reconnu", input, remainder, shifted);
      break;
    }
  }

  return l;
}

liste* liste_fread(FILE* const stream)
{
  char buffer[8192] = { 0 };

  liste* l = NULL;
  if (fgets(buffer, 8191, stream))
    l = liste_sread(buffer);
  else
    l = liste_vide();

  return l;
}

void liste_fwrite(FILE* const stream, const liste* const l)
{
  if (liste_est_vide(l))
  {
    monome_fprint(stream, (monome) { .coefficient = 0, .degre = 0, });
    fprintf(stream, "\n");
  }
  else
  {
    const liste* parcours = l;
    while (!liste_est_vide(liste_suivant(parcours)))
    {
      const monome m = liste_monome(parcours);
      monome_fprint(stream, m);
      fprintf(stream, " + ");
      parcours = liste_suivant(parcours);
    }
    const monome m = liste_monome(parcours);
    monome_fprint(stream, m);
    fprintf(stream, "\n");
  }
}
