
#ifndef _dico_h_
/**
 * \file dico.h
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

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "listeg.h"
#include "listeui.h"

#define OMEGA 0
#define N 100

typedef struct s_dico {
	char				*mots[N]; // all the strings
	unsigned int		ident[N]; // identifier

	 listeui		ident_collid[N];
	 listeg			mots_collid[N];
} *Dico;

// Operations
Dico newDico();
void freeDico(Dico t);
char  *getStr(Dico t, unsigned int strid);
unsigned int getIdent(Dico t, char *mot);
void adj(Dico t, char *mot, unsigned int id);
void supStr(Dico t, char *mot);

// only for internal use, if necessary
unsigned int hash(char *s);

#endif
