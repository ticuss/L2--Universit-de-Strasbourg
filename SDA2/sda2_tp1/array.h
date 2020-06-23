/**
 * \file array.h
 * \brief Arrays.
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
#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * \brief Fill an array with random values.
 * \param[in]     size  Size of the array.
 * \param[in,out] array Input (and output) array.
 * \pre Initialize a seed with srandom()
 */
static inline void array_randomize(size_t size, long int* const array)
{
  for (size_t i = 0; i < size; ++i)
    array[i] = random();
}

/**
 * \brief Print an array into a stream
 * \param[in] stream Destination stream.
 * \param[in] size   Size of the array.
 * \param[in] array  Input array.
 */
static inline void array_fprint(
    FILE* const stream, size_t size, const long int* const array)
{
  for (size_t i = 0; i < size; ++i)
    fprintf(stream, "%ld ", array[i]);
  fprintf(stream, "\n");
}

/**
 * \brief Determine whether two arrays are equal.
 * \param[in] size Size of the arrays.
 * \param[in] a    First array.
 * \param[in] b    Second array.
 * \retval true if the two arrays are equal.
 * \retval false otherwise.
 */
static inline bool array_equals(
    size_t size, const long int* const a, const long int* const b)
{
  bool equals = true;
  for (size_t i = 0; i < size; ++i)
    equals = equals && a[i] == b[i];
  return equals;
}

/**
 * \brief Swap two elements in an array.
 * \param[in,out] array Input (and output) array.
 * \param[in]     i     Index of the first element to swap.
 * \param[in]     j     Index of the second element to swap.
 */
static inline void swap_elements(long int* const array, size_t i, size_t j)
{
  const long int tmp = array[j];
  array[j] = array[i];
  array[i] = tmp;
}

#endif
