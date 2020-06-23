
#ifndef _LISTEUI_H_
#include "listeui.h"

listeui nouvlui() { return NULL; }

listeui adjtetelui(listeui l, unsigned int x)
{
	listeui n = (listeui)malloc(sizeof(struct s_maillonui));
	if (n == NULL) { printf("fatal error: no memory allocation possible.\n"); abort(); }
	n->succ = l;
	n->data = x;
	return n;
}

listeui rechlui(listeui l, unsigned int x)
{
	if (l == NULL) return NULL;
	if (x==l->data) return l;
	return rechlui(l->succ, x);
}

int ranglui(listeui l, unsigned int x)
{
	if (l == NULL) return -1;
	if (x == l->data) return 0;
	int r = ranglui(l->succ, x);
	if (r == -1) return -1; else return r+1;
}

listeui supkiemelui(listeui l, unsigned int k)
{
	if (l == NULL) return NULL; // this should never happen
	if (k == 0)
	{
		listeui n = l->succ;
		free(l);
		return n;
	}
	l->succ = supkiemelui(l->succ, k - 1);
	return l;
}

void destroylui(listeui l)
{
	while (l != NULL)
	{
		listeui n = l->succ;
		free(l);
		l = n;
	}
}
// selecteurs
unsigned int kiemelui(listeui l, unsigned int k)
{
	if (l == NULL) abort(); // this should never happen
	if (k == 0) return l->data;
	return kiemelui(l->succ, k - 1);
}

bool videlui(listeui l) { return l == NULL; }

unsigned int longlui(listeui l)
{
	if (l == NULL) return 0; else return 1 + longlui(l->succ);
}
#endif