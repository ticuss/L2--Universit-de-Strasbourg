/**
 * \file dico.c
 * \brief Stupid wrappers for time measurement.
 * \date 2017
 * \author 
 * \copyright WTFPLv2
 */

/* Copyright © 2017 Harenome Razanajato <hrazanajato@unistra.fr>
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar.
 *
 * See http://www.wtfpl.net/ or read below for more details.
 */
/* DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 * Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */


#include "dico.h"

Dico newDico()
{
	Dico t = (Dico)malloc(sizeof(struct s_dico));
	int i;
	for (i = 0; i < N; i++)
	{
		t->mots[i] = NULL;
		t->ident[i] = OMEGA;
		t->ident_collid[i] = nouvlui();
		t->mots_collid[i] = nouvlg();
	}
	return t;
}

void freeDico(Dico t)
{
     int i;
     for (i = 0; i < N; i++)
     {
         destroylui(t->ident_collid[i]);
         destroylg(t->mots_collid[i], &free);
         if (t->mots[i] != NULL) free(t->mots[i]);
     }
     free(t);
}

// compute hash code
unsigned int hash(char *s)
{
	unsigned long h = 0;
	unsigned long r = 1;
	while (*s != 0) { h += r*(*s - 'a' + 1); r++; s++;  }
	return (((22695477 * h + 1)  >> 16) % N);
}


// returns the pointer to the string that has strid as identifier
char  *getStr(Dico t, unsigned int strid)
{
	unsigned int i;
	for (i = 0; i < N; i++)
	{
		if (t->ident[i] == strid) return t->mots[i];
		if (t->ident[i] != OMEGA)
		{
			// search in the liste
			int r = ranglui(t->ident_collid[i], strid);
			if (r != -1) return kiemelg(t->mots_collid[i], r);
		}
	}
	return NULL;
}

// for comparing
int scomp(void *s1, void *s2) { return strcmp(s1, s2); }

// returns the identifier of the string str, or OMEGA if not in database
unsigned int getIdent(Dico t, char *str)
{
	unsigned int h = hash(str);
	if (t->mots[h] == NULL) return OMEGA;
	if (strcmp(t->mots[h], str) == 0) return t->ident[h];
	int r = ranglg(t->mots_collid[h], str, &scomp);
	if (r == -1) return OMEGA;
	return kiemelui(t->ident_collid[h], (unsigned int)r);
}

// clone a string
void *sclone(void *str)
{
	void *n = malloc(strlen(str) + 1);
	strcpy((char *)n, str);
	return n;
}

// adds a string str to the database, returns its unique identifier
void adj(Dico t, char *str, unsigned int id)
{
	unsigned int h = hash(str);
	if (t->mots[h] == NULL)
	{
		t->mots[h] = sclone(str);
		t->ident[h] = id;
		return;
	}
	t->mots_collid[h] = adjtetelg(t->mots_collid[h], str, &sclone);
	t->ident_collid[h] = adjtetelui(t->ident_collid[h], id);
}

void supStr(Dico t, char *str)
{
	unsigned int h = hash(str);
	if (t->mots[h] == NULL) abort(); // should not happen
	if (strcmp(t->mots[h], str) == 0)
	{
		if (videlg(t->mots_collid[h]))
		{
			free(t->mots[h]);
			t->mots[h] = NULL;
			t->ident[h] = OMEGA;
		}
		else
		{
			free(t->mots[h]);
			t->mots[h] = sclone(kiemelg(t->mots_collid[h], 0));
			t->ident[h] = kiemelui(t->ident_collid[h], 0);
			t->mots_collid[h] = supkiemelg(t->mots_collid[h], 0, free);
			t->ident_collid[h] = supkiemelui(t->ident_collid[h], 0);
		}
		return;
	}
	int r = ranglg(t->mots_collid[h], str, &scomp);
	if (r == -1) abort(); // should not happen
	t->mots_collid[h] = supkiemelg(t->mots_collid[h], (unsigned int)r, free);
	t->ident_collid[h] = supkiemelui(t->ident_collid[h], (unsigned int)r);
}


  
