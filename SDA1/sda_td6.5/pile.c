#include <stdio.h>
#include "base.h"
#define N 100000

typedef struct strpile{
  Nat h;
  float tab[N];
} strPile, *Pile;

Pile pileNouv() {
  Pile p1 = MALLOC (strPile);
  p1->h=0;
  return p1;
}

Bool vide(Pile p){
  return p->h==0;
}

Pile empiler(Pile p, float x){
  p->tab[p->h]= x;
  p->h++;
  return p;
}

Pile depiler(Pile p){
  p->h--;
  return p;
}


Nat hauteur(Pile p){
  return p->h;
} 

void afficher(Pile p){
  for (int i = p->h-1; i>=0 ; i--){
    printf("[%f]\n", p->tab[i]);
  }
}

float acces (Pile p) {
    return p->tab[p->h-1];
    

}
/*
int main(){
Pile p=pileNouv();
empiler (p,4);
empiler (p,3);
empiler (p,2);
empiler (p,1);
  printf("Vide?: %d\n",vide(p));
  printf("Hauteur?: %d\n",hauteur(p));
  afficher(p);
  depiler(p);
  acces(p);
  printf("\n\n");
  printf("Hauteur?: %d\n",hauteur(p));
  afficher(p);
}*/