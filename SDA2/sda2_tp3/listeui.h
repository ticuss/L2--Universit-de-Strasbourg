#ifndef _listeui_h_

/**
 * \file listeui.h
 * \brief Stupid wrappers for time measurement.
 * \date 2017
 * \author 
 * \copyright WTFPLv2
 */

/* Copyright © 2018 JM Dischler
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


typedef struct s_maillonui {
	unsigned int		data; // the data
	struct s_maillonui	*succ; // next link
} *listeui;

// Operations
listeui nouvlui();
listeui adjtetelui(listeui l, unsigned int x);
listeui rechlui(listeui l, unsigned int x);
int ranglui(listeui l, unsigned int x);
listeui supkiemelui(listeui l, unsigned int k);
unsigned int kiemelui(listeui l, unsigned int k);
bool videlui(listeui l);
unsigned int longlui(listeui l);
void destroylui(listeui l);

#endif