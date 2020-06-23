/**
 * \file main.c
 * \brief Main.
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

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "time_helper.h"
#include "array.h"
#include "custom_sort.h"

#ifndef DEFAULT_ARRAY_SIZE
  #define DEFAULT_ARRAY_SIZE 100000
#endif

////////////////////////////////////////////////////////////////////////////////
// Static functions declarations.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Compare two long int values.
 * \param[in] a A pointer to the first long int value.
 * \param[in] b A pointer to the second long int value.
 * \return The result of the comparison.
 * \retval 0  if a == b.
 * \retval 1  if a > b.
 * \retval -1 if a < b.
 * \note We need it to use qsort().
 */
static int long_int_comparator(const void* a, const void* b);

/**
 * \brief Check command line options and modify parameters accordingly.
 * \param[in]     argc       Number of command line arguments.
 * \param[in]     argv       Command line arguments.
 * \param[in,out] array_size Desired array size.
 * \param[in,out] debug      Enable or disable debug mode.
 * \param[in,out] silent     Enable or disable silent mode.
 */
static inline void check_options(
    int argc, char* argv[argc-1], size_t* array_size, bool* debug,
    bool* silent);

/**
 * \brief Print the help for the program.
 * \param[in] stream Destination stream.
 * \param[in] argc   Number of command line arguments.
 * \param[in] argv   Command line arguments.
 * \note This function exits the program.
 */
static inline void fprint_help(FILE* stream, int argc, char* argv[argc-1]);

/**
 * \brief Print various statistics.
 */
static inline void fprint_information(FILE*, size_t, bool, double, double);

/**
 * \brief Print two arrays, side by side.
 */
static inline void fprint_arrays(
    FILE*, size_t, const long int*, const long int*);

////////////////////////////////////////////////////////////////////////////////
// Main.
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[argc-1])
{
  bool silent = false;
  bool debug = false;
  size_t array_size = DEFAULT_ARRAY_SIZE;

  /* Read command line arguments (if any). */
  check_options(argc, argv, &array_size, &debug, &silent);

  /* malloc() the arrays. */
  long int* const input_array = malloc(array_size * sizeof *input_array);
  long int* const ref_array = malloc(array_size * sizeof *input_array);

  srandom(time(NULL));

  /* To store times. */
  time_helper qsort_start, qsort_end;
  time_helper my_sort_start, my_sort_end;

  /* Randomly populate one of the arrays and copy it into the other array. */
  array_randomize(array_size, input_array);
  memcpy(ref_array, input_array, array_size * sizeof *input_array);

  /* Sort the reference array with the libc's qsort() function. */
  time_helper_get_current_time(&qsort_start);
  qsort(ref_array, array_size, sizeof *ref_array, long_int_comparator);
  time_helper_get_current_time(&qsort_end);

  /* Sort the user array with the user's sorting function. */
  time_helper_get_current_time(&my_sort_start);
  long int* const output_array = custom_sort(array_size, input_array);
  time_helper_get_current_time(&my_sort_end);

  /* Compare the two arrays. */
  const bool equals = array_equals(array_size, output_array, ref_array);

  /* Compute times. */
  const double qsort_time = time_helper_difference(&qsort_start, &qsort_end);
  const double my_sort_time = time_helper_difference(&my_sort_start,
                                                     &my_sort_end);

  if (!silent)
    fprint_information(stderr, array_size, equals, qsort_time, my_sort_time);
  if (debug)
    fprint_arrays(stderr, array_size, ref_array, output_array);

  /* Cleanup.
   * Don't free input_array: either output_array points to the same location
   * or it is custom_sort()'s job to free input_array if it decides to return
   * another array.
   */
  free(output_array);
  free(ref_array);

  return equals ? 0 : 1;
}

////////////////////////////////////////////////////////////////////////////////
// Static functions definitions.
////////////////////////////////////////////////////////////////////////////////

void check_options(
    int argc, char* argv[argc-1], size_t* size, bool* debug, bool* silent)
{
  int opt;
  char* endptr;
  unsigned long int input_size;
  while((opt = getopt(argc, argv, "dhn:s")) != -1)
  {
    switch (opt)
    {
      case 'd':
        *debug = true;
        break;
      case 'h':
        fprint_help(stderr, argc, argv);
        break;
      case 'n':
        *size = strtol(optarg, &endptr, 10);
        input_size = strtol(optarg, &endptr, 10);
        if (endptr != optarg && optarg[0] != '\0' && *endptr == '\0')
          *size = input_size;
        break;
      case 's':
        *silent = true;
        break;
      default:
        break;
    }
  }
}

int long_int_comparator(const void* const a, const void* const b)
{
  const long int* const ai = (const long int* const) a;
  const long int* const bi = (const long int* const) b;
  return *ai == *bi ? 0 : (*ai > *bi ? 1 : -1);
}

#define normal "\033[0m"
#define bold   "\033[1m"
#define dim    "\033[2m"
#define ul     "\033[4m"
#define inv    "\033[7m"

#define red    "\033[31m"
#define green  "\033[32m"
#define yellow  "\033[33m"
#define blue  "\033[34m"
#define purple  "\033[35m"
#define cyan  "\033[36m"

void fprint_help(FILE* stream, int argc, char* argv[argc-1])
{
  if (isatty(fileno(stream)))
  {
    fprintf(stream, bold "SYNOPSIS" normal "\n");
    fprintf(stream, bold "\t%s" normal " [" ul "OPTION" normal "]...\n",
            argv[0]);
    fprintf(stream, "\n" bold "DESCRIPTION" normal "\n");
    fprintf(stream,
            "    This program fills an array of a given size with random values"
            ", copies it\n"
            "    and then sorts them using two functions: " bold "qsort()"
            normal " and " bold "%s" normal ". The\n"
            "    " bold "%s" normal " is the function provided by the user"
            " while " bold "qsort()" normal " is used to\n"
            "    provide an array that is correctly sorted for reference.\n",
            custom_sort_name(), custom_sort_name());
    fprintf(stream, "\n" bold "OPTIONS" normal "\n");
    fprintf(stream, "    " bold "%s" normal "\n", "-d");
    fprintf(stream, "        %s\n", "Enable debug mode.");
    fprintf(stream, "    " bold "%s" normal "\n", "-h");
    fprintf(stream, "        %s\n", "Print this help.");
    fprintf(stream, "    " bold "%s" normal " " ul "ARRAY_SIZE" normal "\n",
            "-n");
    fprintf(stream, "        %s\n", "Change the array size (be careful, don't"
            " fill your RAM).");
    fprintf(stream, "    " bold "%s" normal "\n", "-v");
    fprintf(stream, "        %s\n", "Enable silent mode.");
  }
  else
  {
    fprintf(stream, "SYNOPSIS\n");
    fprintf(stream, "    %s [OPTION]...\n", argv[0]);
    fprintf(stream, "\nDESCRIPTION\n");
    fprintf(stream,
            "    This program fills an array of a given size with random values"
            ", copies it\n"
            "    and then sorts them using two functions: qsort() and %s. The\n"
            "    %s is the function provided by the user while qsort() is used "
            "to\n"
            "    provide an array that is correctly sorted for reference.\n",
            custom_sort_name(), custom_sort_name());
    fprintf(stream, "\nOPTIONS\n");
    fprintf(stream, "    %s\n", "-d");
    fprintf(stream, "        %s\n", "Enable debug mode.");
    fprintf(stream, "    %s\n", "-h");
    fprintf(stream, "        %s\n", "Print this help.");
    fprintf(stream, "    %s ARRAY_SIZE\n", "-n");
    fprintf(stream, "        %s\n",
            "Change the array size (be careful, don't fill your RAM).");
    fprintf(stream, "    %s\n", "-v");
    fprintf(stream, "        %s\n", "Enable silent mode.");
  }

  exit(EXIT_SUCCESS);
}

void fprint_information(
    FILE* stream, size_t array_size, bool equals, double qsort_time,
    double custom_sort_time)
{
  /* Output information. */
  if (isatty(fileno(stream)))
  {
    fprintf(stream, bold inv " Array information " normal "\n");
    fprintf(stream, "  %-24s  " yellow "%zu" normal "\n", "array size",
            array_size);
    fprintf(stream, "  %-24s  " cyan "%s" normal "\n", "array elements",
            "long int");
    fprintf(stream, "  %-24s  %s" normal "\n", "identical arrays",
            equals ? green "yes" : red "no");

    fprintf(stream, "\n" bold inv " Times " normal "\n");
    fprintf(stream, "  %-24s" normal "  " yellow "%lf" normal "\n",
            "qsort()", qsort_time);
    fprintf(stream, "  %-24s" normal "  " yellow "%lf" normal "\n",
            custom_sort_name(), custom_sort_time);
    fprintf(stream, "\n");
  }
  else
  {
    fprintf(stream, " Array information \n");
    fprintf(stream, "  %-24s  %zu\n", "array size", array_size);
    fprintf(stream, "  %-24s  %s\n", "array elements", "long int");
    fprintf(stream, "  %-24s  %s\n", "identical arrays", equals ? "yes" : "no");

    fprintf(stream, "\n Times \n");
    fprintf(stream, "  %-24s  %lf\n", "qsort()", qsort_time);
    fprintf(stream, "  %-24s  %lf\n", custom_sort_name(), custom_sort_time);
    fprintf(stream, "\n");
  }
}

void fprint_arrays(
    FILE* stream, size_t size, const long int* ref, const long int* custom)
{
  if (isatty(fileno(stream)))
  {
    fprintf(stream, bold inv " Arrays " normal "\n");
    fprintf(stream, bold "%16s  %16s  %16s" normal "\n", "index", "qsort()",
            custom_sort_name());
    for (size_t i = 0; i < size; ++i)
      fprintf(stream, "%s%16zu  %16ld  %16ld" normal "\n",
              ref[i] == custom[i] ? "" : red, i, ref[i], custom[i]);
    fprintf(stream, "\n");
  }
  else
  {
    fprintf(stream, "Arrays\n");
    fprintf(stream, "%16s  %16s  %16s\n", "index", "qsort()",
            custom_sort_name());
    for (size_t i = 0; i < size; ++i)
      fprintf(stream, "%16zu  %16ld  %16ld\n", i, ref[i], custom[i]);
    fprintf(stream, "\n");
  }
}
