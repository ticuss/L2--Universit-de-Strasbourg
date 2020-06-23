#ifndef _BASIC_UNIT_TESTING_H
#define _BASIC_UNIT_TESTING_H

/**
 * \file but.h
 * \brief Very basic single-header unit testing framework.
 * \author Harenome Ranaivoarivony-Razanajato
 *
 * BUT (Basic Unit Testing) is a single-file unit testing framework. It is
 * intended to be used in situations where dropping a single header is the most
 * convenient solution.
 * Thus, BUT provides a rather small number of features.
 *
 * Chances are you should *not* use this header and would be better off with one
 * of the following libraries:
 * - libcheck (https://libcheck.github.io/check/)
 * - cmocka (https://cmocka.org/)
 *
 * This program is free software. It comes without any warranty, to the extent
 * permitted by applicable law. You can redistribute it and/or modify it under
 * the terms of the Do What The Fuck You Want To Public License, Version 2, as
 * published by Sam Hocevar. See http://www.wtfpl.net/ for more details.
 */

/*
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
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

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////////////////////////

struct but_runtime;
typedef int (*but_test)(struct but_runtime*, void*);

struct but_runtime {
  but_test* tests;
  size_t test_count;
  size_t test_max;

  bool verbose;
  bool silent;
  bool compact;

  intmax_t total_tests;
  intmax_t passed_tests;
  intmax_t failed_tests;
};
typedef struct but_runtime but_runtime;

////////////////////////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////////////////////////

static const size_t but_test_count_step = 1lu;

////////////////////////////////////////////////////////////////////////////////
// Behaviour-related macros
////////////////////////////////////////////////////////////////////////////////

#ifdef but_nocolours
  #undef but_colours
#else
  #define but_colours
#endif

////////////////////////////////////////////////////////////////////////////////
// Text printing macros
////////////////////////////////////////////////////////////////////////////////

#ifdef but_colours
  #define but_text_reset "\033[0m"
  #define but_text_bold "\033[1m"
  #define but_text_dim "\033[2m"
  #define but_text_inv "\033[7m"

  #define but_text_red "\033[31m"
  #define but_text_green "\033[32m"
  #define but_text_yellow "\033[33m"
  #define but_text_blue "\033[34m"
  #define but_text_magenta "\033[35m"
  #define but_text_cyan "\033[36m"
  #define but_text_lightgray "\033[37m"

  #define but_text_padding " "

  /* U+2714 Heavy Check Mark. */
  #define but_text_success "✔"
  /* U+2718 Heavy Ballot X. */
  #define but_text_failure "✘"
#else
  #define but_text_reset ""
  #define but_text_bold ""
  #define but_text_dim ""
  #define but_text_inv ""

  #define but_text_red ""
  #define but_text_green ""
  #define but_text_yellow ""
  #define but_text_blue ""
  #define but_text_magenta ""
  #define but_text_cyan ""
  #define but_text_lightgray ""

  #define but_text_padding " "

  #define but_text_success " OK "
  #define but_text_failure "FAIL"
#endif

////////////////////////////////////////////////////////////////////////////////
// Time utilities
////////////////////////////////////////////////////////////////////////////////

#ifndef but_clock
  #ifdef CLOCK_MONOTONIC_RAW
    #define but_clock CLOCK_MONOTONIC_RAW
  #else
    #define but_clock CLOCK_MONOTONIC
  #endif
#endif

static inline double timespec_diff(
    const struct timespec t0, const struct timespec t1) {
  const long t0_nsec = t0.tv_nsec;
  const long t1_nsec = t1.tv_nsec;

  double result = difftime(t1.tv_sec, t0.tv_sec);
  if (t1_nsec < t0_nsec) {
    const long nsec = 1000000000l - t0_nsec + t1_nsec;
    result += (double) nsec / 1e9 - 1.;
  } else {
    const long nsec = t1_nsec - t0_nsec;
    result += (double) nsec / 1e9;
  }
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// Test writing macros
////////////////////////////////////////////////////////////////////////////////

#define but_test_prelude(test_name) \
  do { \
    clock_gettime(but_clock, &but_local_time_start); \
    if (runtime->verbose) { \
      fprintf( \
          stderr, \
          "\n" but_text_bold but_text_inv but_text_padding \
          "%s" but_text_padding but_text_reset "\n", \
          (test_name)); \
    } \
  } while (0)

#define but_test_postlude(test_name) \
  do { \
    clock_gettime(but_clock, &but_local_time_end); \
    but_local_time_total = \
        timespec_diff(but_local_time_start, but_local_time_end); \
    runtime->total_tests += but_local_test_count; \
    runtime->passed_tests += but_local_test_count - but_local_errors; \
    runtime->failed_tests += but_local_errors; \
    if (runtime->verbose) { \
      if (but_local_errors) { \
        fprintf( \
            stderr, \
            "\n" \
            "\t%-16s" but_text_bold "%4d\n" but_text_reset \
            "\t%-16s" but_text_bold "%4d\n" but_text_reset \
            "\t%-16s" but_text_bold \
            "%4d\n" but_text_reset but_text_bold but_text_red \
            "\tFAILURE\n" but_text_reset, \
            "Test count:", but_local_test_count, \
            "Passed tests:", but_local_test_count - but_local_errors, \
            "Failed tests:", but_local_errors); \
      } else { \
        fprintf( \
            stderr, \
            "\t%-16s" but_text_bold "%4d\n" but_text_reset \
            "\t%-16s" but_text_bold "%4d\n" but_text_reset \
            "\t%-16s" but_text_bold \
            "%4d\n" but_text_reset but_text_bold but_text_green \
            "\tSUCCESS\n" but_text_reset, \
            "Test count:", but_local_test_count, \
            "Passed tests:", but_local_test_count - but_local_errors, \
            "Failed tests:", but_local_errors); \
      } \
    } else if (!runtime->silent) { \
      if (but_local_errors) \
        fprintf( \
            stderr, \
            but_text_padding but_text_bold but_text_red but_text_failure \
                but_text_reset but_text_padding but_text_bold \
            "%s" but_text_reset " (%d errors, %d tests, %lf seconds)\n", \
            __func__, but_local_errors, but_local_test_count, \
            but_local_time_total); \
      else \
        fprintf( \
            stderr, \
            but_text_padding but_text_bold but_text_green but_text_success \
                but_text_reset but_text_padding but_text_bold \
            "%s" but_text_reset " (%d errors, %d tests, %lf seconds)\n", \
            __func__, but_local_errors, but_local_test_count, \
            but_local_time_total); \
    } \
  } while (0)

#define but_test_start(function_name, test_name) \
  static int function_name(struct but_runtime* runtime, void* user) { \
    (void) user; \
    const char* const but_local_test_name = test_name; \
    int but_local_errors = 0; \
    int but_local_test_count = 0; \
    struct timespec but_local_time_start, but_local_time_end; \
    double but_local_time_total = .0; \
    but_test_prelude(but_local_test_name);

#define but_test_end \
  but_test_postlude(but_local_test_name); \
  return but_local_errors; \
  }

#define but_assert(expression) \
  do { \
    but_local_test_count++; \
    const bool assertion = (expression); \
    if (!assertion) { \
      but_local_errors++; \
      if (runtime->verbose || !runtime->compact) { \
        fprintf( \
            stderr, \
            "\t" but_text_bold but_text_red \
            "error:" but_text_reset but_text_bold \
            " %s:%d:" but_text_reset but_text_bold but_text_cyan \
            " %s" but_text_reset "(): " but_text_bold but_text_red \
            "%s" but_text_reset "\n", \
            __FILE__, __LINE__, __func__, #expression); \
      } \
    } \
  } while (0)

////////////////////////////////////////////////////////////////////////////////
// Runtime functions
////////////////////////////////////////////////////////////////////////////////

static inline void but_runtime_init(struct but_runtime* const runtime) {
  if (!runtime)
    return;

  runtime->tests = malloc(sizeof *runtime->tests * but_test_count_step);
  runtime->test_count = 0;
  runtime->test_max = but_test_count_step;
#ifdef but_verbose
  runtime->verbose = true;
#else
  runtime->verbose = false;
#endif
  runtime->silent = false;
  runtime->compact = false;

  runtime->total_tests = 0;
  runtime->passed_tests = 0;
  runtime->failed_tests = 0;
}

static inline void but_runtime_clean(struct but_runtime* const runtime) {
  if (!runtime)
    return;

  free(runtime->tests);
}

static inline void but_runtime_grow(struct but_runtime* const runtime) {
  if (runtime->test_count >= runtime->test_max) {
    const size_t new_size = runtime->test_max + but_test_count_step;
    but_test* const tests = realloc(runtime->tests, new_size * sizeof *tests);
    if (tests) {
      runtime->tests = tests;
      runtime->test_max = new_size;
    }
  }
}

static inline void but_register_test(
    struct but_runtime* const runtime, but_test const test) {
  but_runtime_grow(runtime);
  if (runtime->test_count < runtime->test_max)
    runtime->tests[runtime->test_count++] = test;
}

static inline int but_run_tests(struct but_runtime* const runtime) {
  const size_t count = runtime->test_count;
  int failed_tests = 0;
  for (size_t i = 0; i < count; ++i)
    failed_tests += runtime->tests[i](runtime, NULL) ? 1 : 0;
  return failed_tests;
}

#endif
