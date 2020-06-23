#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>

#ifndef __EXPR_H_
#define __EXPR_H_

#define A1 1 // +
#define A2 2 // -
#define A3 3 // *
#define A4 4 // /
#define A5 5 // min
#define A6 6 // max
#define B1 7 // sqrt
#define B2 8 // exp 
#define B3 9 // ln
#define B4 10 // abs
#define B5 11 // floor
#define B6 12 // ceil
#define BADKEY 13 // autres
#define NBCLE 12



typedef struct {
	
	 char *cle;
	  int val; 
	 
	 } t_symcle;

typedef struct abin {
	/* signi => 0 = opérande, 1 = opérateur */
	int descri;		// descripteur
	double val;  // la valeur stockée dans le node
	struct abin* fd;  //fils droit
	struct abin* fg; //fils gauche
} *expr;


/**
 *  \param[in] *char = pointeur vers char qui stocke la constante
 * \return  int qui est la clé de la constante définie plus haut. 
 * **/
int keyfromstring(char* cle);

/**
 *
 *  \param[in] *str = pointeur vers string qu'on veut convertir un double
 * \param[in]  *a = pointeur vers un double qu'on veut obtenir
 * \param[in] arbre fils = pointeur vers le fils 
 * \brief Cette fonction fait la conversion de string en double utilisant la fonction atof 
 * aussi j'ai fait attention au signe " - " et " . "
 * \return int = un nombre 0 ou 1, si c'est 0 la conversion est finie.
 * */
int convert_type(char* str, double* a);

/**
 * \param[in] **str = pointeur vers string qu'on a introduit dans le terminal
 *  \param[in] *pos = int position
 * \param[in] *err = int 0 ou 1 qu'on utilise pour la gestion d'erreur.
 * \brief Initiation de l'arbre binaire classique qu'on a appris en cours, choix d'opérande utilisant 
 * le switch, la gestion des erreurs: d'introduction d'un opérande inconnu et le nombre des arguments.
 * aussi les adjonctions dans l'arbre .(la préparation pour le calcul de l'expression)
**/
expr initial(char** str,int* pos,int* err);

/**
 * \param[in] *str = pointeur vers string qu'on a introduit dans le terminal
 * \brief cette fonction prépare l'expression qu'on a introduit dans le terminal en utilisant les fonctions strcpy
 * et strtok.
**/
expr creation(char* str);


/**
 * \param[in] expr e  l'expression qui est stockée dans l'arbre 
 * \param[in] int * err int 0 ou 1 pour la gestion d'erreur 
 * \brief Dans cette fonction j'ai fait les calculs pour chaque constante utilisant un switch 
**/
double calcul_expr(expr e,int* err);

/**
 * \param[in] expr e = expression qui est stockée dans l'arbre 
 * \brief libère la mémoire, pour être plus précis liberation de fg et fd de l'arbre binaire.
 * \return void
**/
void free_expr(expr e);

/**
 * \param[in] **str = pointeur vers string qu'on a introduit dans le terminal
 *  et qui est stocké dans la mémoire
 * \brief libère la mémoire
**/
void free_mem(char** str);

#endif
