/******************************************/
/*
// grapheurbain.c
*/

#include "grapheurbain.h"

// operations internes
grapheurbain rechCarrefour(grapheurbain g, unsigned int icar)
{
	if (g == NULL) return NULL;
	if (g->c.icf == icar) return g;
	return rechCarrefour(g->suiv, icar);
}
ListeSom rechArc(ListeSom ls, unsigned int icar)
{
	if (ls == NULL) return NULL;
	if (ls->icf == icar) return ls;
	return rechArc(ls->suc, icar);
}
ListeSom rechArcVal(ListeSom ls, unsigned int irue)
{
	if (ls == NULL) return NULL;
	if (ls->irue == irue) return ls;
	return rechArcVal(ls->suc, irue);
}
ListeSom supArc(ListeSom ls, unsigned int icar)
{
	if (ls == NULL) return NULL;
	if (ls->icf == icar) { ListeSom n = ls->suc;  free(ls);  return n; }
	ls->suc = supArc(ls->suc, icar);
	return ls;
}
ListeSom adjArc(ListeSom ls, unsigned int icar, unsigned int irue)
{
	ListeSom n = (ListeSom)malloc(sizeof(Strarc));
	if (n == NULL) abort();
	n->icf = icar;
	n->irue = irue;
	n->suc = ls;
	return n;
}

// creation et destruction
grapheurbain grapheurbainNouv()
{
	return NULL;
}
void grapheurbainFree(grapheurbain g)
{
	while(g!=NULL)
	{ 
		grapheurbain cur = g;
		ListeSom ls = cur->c.lsucc;
		while (ls != NULL) { ListeSom n = ls->suc; free(ls); ls = n; }
		ls = cur->c.lpred;
		while (ls != NULL) { ListeSom n = ls->suc; free(ls); ls = n; }
		g = g->suiv;
		free(cur);
	}
}

// operations usuelles sur les graphes
void addCarrefour(grapheurbain *g, unsigned int icar)
{
	if (existeCarrefour(*g, icar)) return; // already exists
	grapheurbain n = (grapheurbain)malloc(sizeof(Strsom));
	if (n == NULL) abort(); // not enough memory
	n->c.icf = icar;
	n->c.lpred = NULL; // isolated node
	n->c.lsucc = NULL;
	n->suiv = *g;
	*g = n;
}

//version recursive
void supCarrefour(grapheurbain *g, unsigned int icar)
{
	// only possible if there is no connection
	grapheurbain f = *g;
	if (f == NULL) return; // carrefour icar does not exist
	if (f->c.icf != icar) { f = f->suiv;  supCarrefour(&f, icar); (*g)->suiv = f; return; }
	if (f->c.lpred != NULL || f->c.lsucc != NULL) return; // carrefour must be isolated
	*g = f->suiv;
	free(f);
}

void addRue(grapheurbain *g, unsigned int ico, unsigned int ice, unsigned int irue)
{
	grapheurbain f = *g;
	grapheurbain fco = rechCarrefour(f,ico);
	grapheurbain fce = rechCarrefour(f,ice);
	if (fco == NULL || fce == NULL) return; // carrefour does not exist
	if (rechArc(fco->c.lsucc, ice) == NULL) // add only if arc does not already exists
	{
		fco->c.lsucc = adjArc(fco->c.lsucc, ice, irue);
	}
	if (rechArc(fce->c.lpred, ico) == NULL) // add only if arc does not already exists
	{
		fce->c.lpred = adjArc(fce->c.lpred, ico, irue);
	}
}

void addRueDoubleSens(grapheurbain *g, unsigned int ico, unsigned int ice, unsigned int irue)
{
	addRue(g, ico, ice, irue);
	addRue(g, ice, ico, irue);
}

void supRue(grapheurbain *g, unsigned int ico, unsigned int ice)
{
	grapheurbain f = *g;
	grapheurbain fco = rechCarrefour(f, ico);
	grapheurbain fce = rechCarrefour(f, ice);
	if (fco == NULL || fce == NULL) return; // carrefour does not exist
	fco->c.lsucc = supArc(fco->c.lsucc, ice);
	fce->c.lpred = supArc(fce->c.lpred, ico);
}

bool existeArc(grapheurbain g, unsigned int ico, unsigned int ice)
{
	grapheurbain fco = rechCarrefour(g, ico);
	grapheurbain fce = rechCarrefour(g, ice);
	if (fco == NULL || fce == NULL) abort(); // carrefour does not exist
	return rechArc(fco->c.lsucc, ice) != NULL;
}
bool existeCarrefour(grapheurbain g, unsigned int icar)
{
	return rechCarrefour(g, icar) != NULL;
}

// operations sur les liste de succ et pred
// les carrefours associes a une rue
listeui carrefoursDeRue(grapheurbain g, unsigned int irue)
{
	listeui res = nouvlui();
	while (g != NULL)
	{
		if (rechArcVal(g->c.lsucc, irue) != NULL)
		{
			if (ranglui(res, g->c.icf) == -1) res = adjtetelui(res, g->c.icf);
		}
		g = g->suiv;
	}
	return res;
}
// les rues incidentes en un carrefour
listeui ruesDeCarrefour(grapheurbain g, unsigned int icar)
{
	listeui res = nouvlui();
	grapheurbain f = rechCarrefour(g, icar);
	ListeSom ls = f->c.lsucc;
	while (ls != NULL)
	{
		if (ranglui(res, ls->irue) == -1) res = adjtetelui(res, ls->irue);
		ls = ls->suc;
	}
	ListeSom lp = f->c.lpred;
	while (lp != NULL)
	{
		if (ranglui(res, lp->irue) == -1) res = adjtetelui(res, lp->irue);
		lp = lp->suc;
	}
	return res;
}

listeui ruesCroisement(grapheurbain g, unsigned int irue)
{
	listeui res = nouvlui();
	listeui lc = carrefoursDeRue(g, irue);
	for (int i = 0; i < longlui(lc); i++)
	{
		unsigned int icar = kiemelui(lc, i);
		listeui lr = ruesDeCarrefour(g, icar);
		for (int j = 0; j < longlui(lr); j++)
		{
			unsigned int jrue = kiemelui(lr, j);
			if (jrue!=irue && ranglui(res, jrue) == -1) res = adjtetelui(res, jrue);
		}
		destroylui(lr);
	}
	destroylui(lc);
	return res;
}