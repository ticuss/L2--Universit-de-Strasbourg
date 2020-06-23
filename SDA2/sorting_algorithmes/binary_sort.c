/**
 * \file binary_sort.c
 * \brief Binary sort.
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

#include <string.h>
#include "array.h"

////////////////////////////////////////////////////////////////////////////////
// Your implementation.
////////////////////////////////////////////////////////////////////////////////
int binarySearch(long int* const array, int item, int low, int high);

long int* custom_sort(size_t size, long int* const array)
{
  
  size_t i;
  int k, j, selected;

  for(i = 1; i < size; i++)
  {
    j = i - 1;
    selected = array[i];

    k = binarySearch(array, selected, 0, j);

    while(j >= k)
    {
      array[j + 1] = array[j];
      j--;
    }
    array[j+1] = selected;
  }
  return array;
}

////////////////////////////////////////////////////////////////////////////////
// Other required functions.
////////////////////////////////////////////////////////////////////////////////

const char* custom_sort_name(void)
{
  return "binary_sort()";
}

int binarySearch(long int* const array, int item, int low, int high)
{
  if(high <= low)
    return (item > array[low]) ? (low + 1) : low;

  int mid = (low + high)/2;

  if(item == array[mid])
    return (mid + 1);

  if(item > array[mid])
    return binarySearch(array, item, mid + 1, high);
  return binarySearch(array, item, low, mid - 1);
}