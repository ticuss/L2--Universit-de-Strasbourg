/**
 * \file merge_sort.c
 * \brief Merge sort.
 * \date 2017
 * \author YOU
 * \copyright WTFPLv2
 */

/* Copyright © 2017 YOU <you@etu.unistra.fr>
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
#include "custom_sort.h"
#include "array.h"

////////////////////////////////////////////////////////////////////////////////
// Your implementation.
////////////////////////////////////////////////////////////////////////////////
void merge(long int *const a, int i1, int j1, int i2, int j2);
void mergesort(long int *const a, int i, int j);

long int *custom_sort(size_t size, long int *const array)
{
  mergesort(array, 0, size - 1);
  return array;
}

////////////////////////////////////////////////////////////////////////////////
// Other required functions.
////////////////////////////////////////////////////////////////////////////////

const char *custom_sort_name(void)
{
  return "merge_sort()";
}

void mergesort(long int *const a, int i, int j)
{
  int mid;
  if (i < j)
  {
    mid = (i + j) / 2;
    mergesort(a, i, mid);
    mergesort(a, mid + 1, j);
    merge(a, i, mid, mid + 1, j);
  }
}

void merge(long int *const a, int i1, int j1, int i2, int j2)
{
  int temp[900000];
  int i, j, k;
  i = i1;
  j = i2;
  k = 0;

  while (i <= j1 && j <= j2)
  {
    if (a[i] < a[j])
      temp[k++] = a[i++];
    else
      temp[k++] = a[j++];
  }

  while (i <= j1)
    temp[k++] = a[i++];

  while (j <= j2)
    temp[k++] = a[j++];

  for (i = i1, j = 0; i <= j2; i++, j++)
    a[i] = temp[j];
}