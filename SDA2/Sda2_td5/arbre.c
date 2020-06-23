#include"arbre.h"




arbre arbrevide(){

    return NULL;
}

arbre nouvnoeud(int x ,arbre frere ,  arbre fils ){
      
    arbre new = (noeud*)malloc(sizeof(noeud));
     new->val = x;
     new->fils = fils;
      new->frere = frere;
    return new;

}

arbre fils(arbre a){

    return(!a)? NULL : a->fils;

}


arbre frere(arbre a ){

     return(!a)? NULL : a->fils->frere;
}

bool est_vide(arbre a) {

    if(a  == NULL){ return true;}
     else return false ;

}

bool est_feuille(arbre a) {

    if (!a)
    return false ; 
    else if (a->fils)
    return true ;
    else
    {
    return false ;
        }
    
    
   

}

bool est_fils(arbre a, int x){

    if(!a)return false ;
        else if(a->fils->val == x)
        {
        return true;}
    else return false;
}


unsigned int nb_fils(arbre a)
{
  arbre copy=a->fils;
  int i=0;
  if (a->fils==NULL) return 0;
  while(copy!=NULL){
    i++;
    copy=copy->frere;
  }
  return i;
}

void printfPrefixe(const arbre node) {

     if(!node) return;
     printf("|%d \n",node->val);
    printf("  ");
     printfPrefixe(node->fils);
  
     printfPrefixe(node->frere);
      printf(" ");
}

unsigned int hauteur(arbre a)
{
    unsigned int frere1;
    unsigned int fils1;
    
    if (a == NULL)
    return 0;
    
     frere1 = hauteur(a->frere);
     fils1 = hauteur(a->fils);
   
    if (frere1 > fils1)
     return frere1;
    else
     return fils1 + 1;
}



int etiquette(arbre a, int x ){

   
    if (a->val == x)
            return a->val;
        
     else if(a->val != x)
     {
         return etiquette(a->fils, x);    
        }

  else if(!etiquette(a->fils, x))
  {
   return etiquette(a->fils,x );
} 
    else return 0;
 }



int main(){

  arbre a1=arbrevide();
  arbre a2=arbrevide();
  arbre a3=arbrevide();
  arbre a4=arbrevide();
  arbre a5=arbrevide();
  arbre a6=arbrevide();
  a2=nouvnoeud(5,NULL,NULL);
  a1=nouvnoeud(2,a2,NULL);
  a5=nouvnoeud(3,NULL,NULL);
  a4=nouvnoeud(6,a5,NULL);
  a3=nouvnoeud(1,a4,a1);
  a6=nouvnoeud(4,NULL,a3);
  
        printf("Nombre fils  = %d\n", nb_fils(a3)  );
        printf("Hauteur = %d\n", hauteur(a6)  );
    printf("etiquette si oui alors retourne la valeur  = %d\n \n", etiquette(a6 , 2));
    printfPrefixe(a6);
}


