/**
 * \file custom_sort.h
 * \brief Custom sort.
 * \date 2017
 * \author Harenome Razanajato
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
#ifndef _CUSTOM_SORT_H_
#define _CUSTOM_SORT_H_

#include <stdlib.h>

/**
 * \brief A custom sort function you have to implement.
 * \param[in] size  Size of the input array.
 * \param[in] array Input array to sort.
 * \return A pointer to a sorted (if your implementation is correct!) array.
 * \note the return value may point to the same location as the input array
 */
long int* custom_sort(size_t size, long int* const array);

/**
 * \brief Get the name of the implemented sort algorithm.
 * \return The name of the sort algorithm you implemented.
 */
const char* custom_sort_name(void);

#endif
