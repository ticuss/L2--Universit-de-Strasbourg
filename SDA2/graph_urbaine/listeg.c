#include "listeg.h"

listeg nouvlg() { return NULL; }

listeg adjtetelg(listeg l, void *x, void* (*fclone)(void *x))
{
	listeg n = (listeg)malloc(sizeof(struct s_maillong));
	if (n == NULL) { printf("fatal error: no memory allocation possible.\n"); abort(); }
	n->succ = l;
	n->data = fclone(x);
	return n;
}

listeg rechlg(listeg l, void *x, fcomp comp)
{
	if (l == NULL) return NULL;
	if (comp(x, l->data) == 0) return l;
	return rechlg(l->succ, x, comp);
}

int ranglg(listeg l, void *x, fcomp comp)
{
	if (l == NULL) return -1;
	if (comp(x, l->data) == 0) return 0;
	int r = ranglg(l->succ, x, comp);
	if (r == -1) return -1; else return r+1;
}

listeg supkiemelg(listeg l, unsigned int k, fdestroy destr)
{
	if (l == NULL) return NULL; // this should never happen
	if (k == 0)
	{
		destr(l->data);
		listeg n = l->succ;
		free(l);
		return n;
	}
	l->succ = supkiemelg(l->succ, k - 1, destr);
	return l;
}

void destroylg(listeg l, fdestroy destr)
{
	while (l != NULL)
	{
		listeg n = l->succ;
		destr(l->data);
		free(l);
		l = n;
	}
}
// selecteurs
void *kiemelg(listeg l, unsigned int k)
{
	if (l == NULL) return NULL; // this should never happen
	if (k == 0) return l->data;
	return kiemelg(l->succ, k - 1);
}

bool videlg(listeg l) { return l == NULL; }

unsigned int longueur(listeg l)
{
	if (l == NULL) return 0; else return 1 + longueur(l->succ);
}
