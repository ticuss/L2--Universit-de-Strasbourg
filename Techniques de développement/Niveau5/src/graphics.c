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

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <string.h>

#include "jeu.h"
#include "grille.h"
#include "graphics.h"
#include "settings.h"





void print_life(cairo_t *cr, char* str,double pos_xt,double pos_yt, double t_size){
	cairo_set_source_rgb(cr, 1, 0.87451, 0.87451);
	const char *utf8 =str;
	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, t_size);
	cairo_text_extents_t extents;
	cairo_text_extents(cr, utf8, &extents);
	cairo_move_to(cr, pos_xt+t_size, pos_yt+t_size);
	cairo_show_text(cr, utf8);

}
void paint_square(cairo_surface_t *surface, grille* g,int showlife)
{
	paint_background(surface);
	int gl=g->nbl;
	int gc=g->nbc;
	cairo_t *cr;
	cr=cairo_create(surface);
	double square_w;
	if(((STAGEX-GAP*(gc+1))/(gc))>((STAGEY-GAP*(gl+1))/(gl))){
		square_w=(STAGEY-GAP*(gl+1))/(gl);
	}

	else{

		square_w=(STAGEX-GAP*(gc+1))/(gc);
	}
	double marge_x=(SIZEX-(square_w+GAP)*gc+GAP)/2;
	double marge_y=(SIZEY-(square_w+GAP)*gl+GAP)/2;



for (int i=0;i<gl;i++){
	for (int j=0;j<gc;j++){
		cr=cairo_create(surface);
		if(est_vivante(i,j,*g)){
			double pos_x=j*(GAP+square_w)+marge_x;
			double pos_y=i*(GAP+square_w)+marge_y;

			cairo_set_source_rgb (cr, 0.6, 0.5, 0.7);
			cairo_rectangle(cr,pos_x,  pos_y,square_w,square_w);
			cairo_fill(cr);
			if(showlife==1){
			char life[4]="\0";
			sprintf(life,"%d",g->cellules[i][j]);
			print_life(cr,life,pos_x,pos_y,square_w/3);
			}
			cairo_destroy(cr);

		}
		else if(g->cellules[i][j]<0){
			double pos_x=j*(GAP+square_w)+marge_x;
			double pos_y=i*(GAP+square_w)+marge_y;
			cairo_set_source_rgb (cr, 0.68235 ,0.87059, 0.98824);
			cairo_rectangle(cr,pos_x,  pos_y,square_w,square_w);
			cairo_fill(cr);
			cairo_destroy(cr);
		}

		else{
			double pos_x=j*(GAP+square_w)+marge_x;
			double pos_y=i*(GAP+square_w)+marge_y;
			cairo_set_source_rgb(cr, 1, 0.87451, 0.87451);
			cairo_rectangle(cr,pos_x,  pos_y,square_w,square_w);
			cairo_fill(cr);
			cairo_destroy(cr);
		}


	}
}
char S[]="Essayer les TOUCHES ( C / V / N ) ";
			print_string(surface,S, 10.0, SIZEY-13, 20);
}

void print_string(cairo_surface_t *surface, char* str,double pos_xt,double pos_yt, double t_size){
	cairo_t *cr;
	cr=cairo_create(surface);
	cairo_set_source_rgb(cr, 0.999, 0.999, 0.9999);
	const char *utf8 =str;
	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, t_size);
	cairo_text_extents_t extents;
	cairo_text_extents(cr, utf8, &extents);
	cairo_move_to(cr, pos_xt, pos_yt);
	cairo_show_text(cr, utf8);
	cairo_destroy(cr);

}

void paint_background(cairo_surface_t *surface){
	cairo_t *cr;
	cr=cairo_create(surface);
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.1);
	cairo_paint(cr);
	cairo_destroy(cr);
}

void corp_jeu(grille *g, grille *gc, cairo_surface_t *cs, XEvent e, Display *dpy){
	int etape=0;
	int showlife=0;
	char cylique[20]="Mode: cyclique    ";
	char non_cylique[30]="Mode: non-cyclique";
	char turn[20]="\0";
	char const  etape_str[10]="Etape: ";
	char number_string[5]="\0";
	int (*compte_voisins_vivants)(int,int,grille);
  	compte_voisins_vivants=compte_voisins_vivants_cyclique;
	while(1) {
		XNextEvent(dpy, &e);

		if(e.type==Expose && e.xexpose.count<1) {
			paint_square(cs,g,showlife);
			sprintf(number_string,"%d",etape);
			strcpy(turn,etape_str);
			strcat(turn,number_string);
			if(compte_voisins_vivants==compte_voisins_vivants_cyclique){
				print_string(cs,cylique,150,20,20);
			}
		else {
				print_string(cs,non_cylique,300,20,20);
			}
			print_string(cs,turn, 20.0, 20.0, 20.0);


		}
		 else if(e.type==ButtonPress && e.xbutton.button==1) {
			evolue(g,gc,compte_voisins_vivants);
			etape++;
			sprintf(number_string,"%d",etape);
			strcpy(turn,etape_str);
			strcat(turn,number_string);
			paint_square(cs,g,showlife);
			print_string(cs,turn, 20.0, 20.0, 20.0);
		if(compte_voisins_vivants==compte_voisins_vivants_cyclique){
				print_string(cs,cylique,150,20,20);
			}
		else {
				print_string(cs,non_cylique,300,20,20);
			}
		 }

		 else if (e.type==KeyPress && e.xkey.keycode==55){
				showlife=showlife==0? 1: 0;
				paint_square(cs,g,showlife);
				if(compte_voisins_vivants==compte_voisins_vivants_cyclique){
				print_string(cs,cylique,150,20,20);
				}
				else {
				print_string(cs,non_cylique,300,20,20);
				}
				print_string(cs,turn, 20.0, 20.0, 20.0);
		 }
		 else if (e.type==KeyPress && e.xkey.keycode==54){

		 			 if(compte_voisins_vivants==compte_voisins_vivants_cyclique){
		 				compte_voisins_vivants=compte_voisins_vivants_non_cyclique;
		 				paint_square(cs,g,showlife);
		 				print_string(cs,non_cylique,300,20,20);
		 				print_string(cs,turn, 20.0, 20.0, 20.0);

		 			}
		 			else {
		 				compte_voisins_vivants=compte_voisins_vivants_cyclique;
		 				paint_square(cs,g,showlife);
		 				print_string(cs,cylique,150,20,20);
		 				print_string(cs,turn, 20.0, 20.0, 20.0);

		 			}
		 		 }
		 else if (e.type==KeyPress && e.xkey.keycode==57){
				etape=0;
				showlife=0;
				char c[180];
				compte_voisins_vivants=compte_voisins_vivants_cyclique;

      			printf("Saisissez le nom du dossier à charger.   \n");
      			scanf("%s",c);
      			libere_grille(g);
		    	libere_grille(gc);
      			init_grille_from_file(c,g);
      			alloue_grille(g->nbl, g->nbc, gc);

				sprintf(number_string,"%d",etape);
				strcpy(turn,etape_str);
				strcat(turn,number_string);
				paint_square(cs,g,showlife);
				print_string(cs,cylique,150,20,20);
				print_string(cs,turn, 20.0, 20.0, 20.0);
		 }

		 else if (e.type==ButtonPress && e.xbutton.button==3)
			break;
	}

}
