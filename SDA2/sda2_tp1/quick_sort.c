/**
 * \file quick_sort.c
 * \brief Quick sort.
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
void quicksort(long int *const array, int first, int last);
long int *custom_sort(size_t size, long int *const array)
{
  /* TO DO. */
  quicksort(array, 0, size - 1);

  return array;
}

////////////////////////////////////////////////////////////////////////////////
// Other required functions.
////////////////////////////////////////////////////////////////////////////////

const char *custom_sort_name(void)
{
  return "quick_sort()";
}

void quicksort(long int *const array, int first, int last)
{
  int i, j, pivot, temp;

  if (first < last)
  {
    pivot = first;
    i = first;
    j = last;

    while (i < j)
    {
      while (array[i] <= array[pivot] && i < last)
        i++;
      while (array[j] > array[pivot])
        j--;
      if (i < j)
      {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }

    temp = array[pivot];
    array[pivot] = array[j];
    array[j] = temp;
    quicksort(array, first, j - 1);
    quicksort(array, j + 1, last);
  }
}