// fichier base.h

#ifndef BASE
#define BASE 
#define N 128
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <stdbool.h>
typedef bool Bool;
#define faux false
#define vrai true
//#define vrai 1
//#define faux 0
//typedef unsigned char Bool;

typedef unsigned int Nat;
typedef int Ent;
typedef float Reel;
typedef float Rat;
typedef char Car;
typedef Car * Chaine;

#define MALLOC(type)        ((type*)malloc(sizeof(type)))
#define MALLOCN(type, n)    ((type*)malloc(n * sizeof(type)))
#define CALLOCN(type, n)    ((type*)calloc(n, sizeof(type)))
#define REALLOC(t, type, n) ((type*)realloc(t, n * sizeof(type)))
#define FREE(t) free(t)

#endif
