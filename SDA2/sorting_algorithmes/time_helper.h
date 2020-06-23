/**
 * \file time_helper.h
 * \brief Stupid wrappers for time measurement.
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
#if _OPENMP
  #include <omp.h>

  typedef double time_helper;
  /**
   * \brief Get the current time
   * \param[out] time Pointer to the location where to store the current time.
   */
  static inline void time_helper_get_current_time(time_helper* const time)
  {
    *time = omp_get_wtime();
  }

  /**
   * \brief Compute the difference between two time_helper values.
   * \param[in] t0 First time.
   * \param[in] t1 Second time.
   * \return The difference in seconds.
   * \pre t0 < t1
   */
  static inline double time_helper_difference(
      const time_helper* const t0, const time_helper* const t1)
  {
    return *t1 - *t0;
  }
#else
  #include <time.h>

  typedef struct timespec time_helper;

  /**
   * \brief Get the current time
   * \param[out] time Pointer to the location where to store the current time.
   */
  static inline void time_helper_get_current_time(time_helper* const time)
  {
    #ifdef CLOCK_MONOTONIC_RAW
      clock_gettime(CLOCK_MONOTONIC_RAW, time);
    #else
      clock_gettime(CLOCK_MONOTONIC, time);
    #endif
  }

  /**
   * \brief Compute the difference between two time_helper values.
   * \param[in] t0 First time.
   * \param[in] t1 Second time.
   * \return The difference in seconds.
   * \pre t0 < t1
   */
  static inline double time_helper_difference(
      const time_helper* const t0, const time_helper* const t1)
  {
    double secdiff = difftime(t1->tv_sec, t0->tv_sec);
    if (t1->tv_nsec < t0->tv_nsec)
    {
      long val = 1000000000l - t0->tv_nsec + t1->tv_nsec;
      secdiff += (double) val / 1e9 - 1.;
    }
    else
    {
      long val = t1->tv_nsec - t0->tv_nsec;
      secdiff += (double) val / 1e9;
    }

    return secdiff;
  }
#endif /* _OPENMP */
