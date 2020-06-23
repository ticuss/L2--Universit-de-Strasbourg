#include "ia.h"

#include "liste.h"
#include "mancala.h"

static inline size_t _premier_champ(size_t longueur, unsigned int joueur) {
  return joueur == 0 ? 1 : ((longueur / 2) + 1);
}

static inline size_t _dernier_champ(size_t longueur, unsigned int joueur) {
  return joueur == 0 ? ((longueur / 2) - 1) : (longueur - 1);
}

static inline size_t _grenier(size_t longueur, unsigned int joueur) {
  return joueur == 0 ? (longueur / 2) : 0;
}

mancala* mancala_ia(mancala* m, const unsigned int joueur) {
  /*
   * IA très stupide.
   *
   * Pistes:
   * - Coup qui permet de rejouer.
   * - Vol de graines.
   * - Incendie d'une colonne avec un champ moins rempli chez le joueur
   *   que chez l'adversaire (cas extrême : obligatoirement vide chez le
   *   joueur).
   * - Minimiser le nombre de graines qui passe chez l'adversaire.
   * - Minimiser le nombre de graines par champ (en cas d'incendie).
   * - Incendie qui force l'adversaire à passer des graines chez soi ?
   * - Incendie qui empêche l'adversaire de rejouer.
   */

  /* Cas étranges. */
  if (mancala_partie_finie(m)) {
    return m;
  }

  /* Cas étranges. */
  const unsigned int tour = mancala_joueur(m);
  if (tour != joueur) {
    return m;
  }

  const liste* plateau = mancala_plateau(m);
  const size_t longueur = liste_longueur(plateau);
  const size_t grenier = _grenier(longueur, joueur);
  const size_t debut = _premier_champ(longueur, joueur);
  const size_t fin = _dernier_champ(longueur, joueur);

  /* Sélectionner un coup qui permet de rejouer. */
  for (size_t i = debut; i <= fin; ++i) {
    const unsigned int graines = liste_ieme(plateau, i);
    const size_t dernier = (i + graines) % longueur;
    if (dernier == grenier && mancala_coup_valide(m, i)) {
      return mancala_egrainer(m, i);
    }
  }

  /* Sélectionner le premier coup possible... */
  // for (size_t i = debut; i < fin; ++i)
  for (size_t i = fin; i <= fin; --i) {
    if (mancala_coup_valide(m, i)) {
      return mancala_egrainer(m, i);
    }
  }

  /* ??? */
  return m;
}
