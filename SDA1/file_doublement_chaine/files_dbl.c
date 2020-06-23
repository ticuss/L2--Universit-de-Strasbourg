//author BOGDANAS CONSTANTIN 
// fichier files_dbl.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "files_dbl.h"
#include <errno.h>
void raler(char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}


// pre : vrai
// post : retourne FILE_VIDE
// modif : aucune
file    file_vide()
{
    return FILE_VIDE;
}

// pre : vrai
// post : retourne la file modifiée par adjonction en queue
//        attention, cette adresse peut être différente de celle donnée
// modif : la structure pointée par f est modifiée, allocation d'une nouvelle cellule
file    file_adjq(S x, file f)
{
    
    file res = (file) malloc(sizeof(Strfile));
    res-> val = x;
    if(file_estvide(f)) 
    {
        res->next = res->prev = res;
    }
    else
    {
         res->prev = f;
         res->next = f->next;
         res->next->prev = res;
         f->next = res;
    }
    
    return res; 
}


// pre file_supt(f) = ! file_estvide(f) 
// post : retourne la file modifiée par la suppression de la tête
// modif : la structure pointée f est modifiée, désallocation d'une cellule

file file_supt(file f){
 
    if(!f){
        raler("1: SUPP");
    }
    if ((f == NULL) || (f->next == f->prev)) return NULL;   //prec
file save = f->next , save2 = f;

do{f=f->next;} while (f->next!=save);

    f->next = save->next;
    save->prev->prev = f;
    free(save);

    return save2;

}

// pre file_tete(f) = ! file_estvide(f)
// post : retourne la tête de la file
// modif : aucune
S file_tete(file f)
{
   return f->next->val;
}

// pre : vrai
// post : test de vacuité
// modif : aucune
bool    file_estvide(file f)
{
    return f == FILE_VIDE; 
}

// pre : vrai
// post : retourne le nombre d'élement dans la file
// modif : aucune
Nat file_lgr(file f)
{
    if(!f) return 0;
   unsigned int i =0;
   file fil = f ; 
   do {
     fil =   fil ->prev ;
     i++;

   } while(f!=fil);
   return i;

}



// pre : si place > lgr(l) on prend la la derniere valeur possible  
// post : 
// modif : 
file file_ins(file f, Nat place, S x)
{
   file save = f;

    if(place >= file_lgr(f)) 
    return file_adjq(x,f);
    if(place <=1 ) return file_adjq(x,f);

    do {
        f=f->next;
        place--;
    }
    while(place!=0);
        
        file_adjq(x,f);
       
        return save;
    }


// pre : vrai
// post : 
// modif : 
file file_dd(file f, Nat decD)
{
    
    decD = decD % file_lgr(f);
    for(unsigned int i= 0; i < decD; i++) f = f-> prev;
    return f; 
}

// pre : vrai
// post : 
// modif : 
file file_gg(file f, Nat decG)
{
    
    decG = decG % file_lgr(f);
    for(unsigned int i= 0; i < decG; i++) f = f-> next;
    return f;  
}
