/*
 * Copyright (c) 2019 Bogdanas Constantin <ticu369@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "jeu.h"
/**
 * \fn void paint_square(cairo_surface_t *surface, grille* g,int showlife);
 * The cairo_paint() operation uses a mask that transfers the entire source
 * to the destination. Some people consider this an infinitely large mask,
 *  and others consider it no mask; the result is the same. The related operation
 */

void paint_square(cairo_surface_t *surface, grille* g,int showlife);
/**
 * \fn void print_string(cairo_surface_t *surface, char* str,double pos_xt,double pos_yt, double t_size);
 * prints the strings from the file
 */

void print_string(cairo_surface_t *surface, char* str,double pos_xt,double pos_yt, double t_size);
/**
 * \fn void paint_background(cairo_surface_t *surface);
 * Paint the background
 */
void paint_background(cairo_surface_t *surface);
/**
 *\fn void corp_jeu(grille *g, grille *gc, cairo_surface_t *cs, XEvent e, Display *dpy);
 * \brief Implementation du jeu dans cairo avec tous le buttons et avec tous le fonction
 *
 */
void corp_jeu(grille *g, grille *gc, cairo_surface_t *cs, XEvent e, Display *dpy);
#endif
