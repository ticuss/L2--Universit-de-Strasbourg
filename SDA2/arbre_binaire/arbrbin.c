#include "arbrbin.h"
#include "base.h"

// Désolé Monsieur j'ai pas reussi de documenter le code et de l'organiser comme il faut.

void raler(char *msg, int returnCode){
     if(returnCode > 0){
          perror(msg);
          exit(returnCode);
     }else
     {
          fprintf(stderr,"%s\n",msg);
          EXIT_SUCCESS;
     }
}



abin emptyNode(){
     return NULL;
}


abin createNode(int elemt){
     abin new = NULL;
     if((new = MALLOC(noeud)) == NULL) raler("Erreur de Malloc arbre",3);

     new->elmt = elemt;
     new->FilsDroit = NULL;
     new->FilsGauche = NULL;
     
     return new;
}


 abin enraciner(abin left, int elt, abin right) {
     abin new = NULL;
     new = createNode(elt);
     new->FilsGauche = left;
     new->FilsDroit = right;
     if(left) left = new;
     if(right) right = new;
     return new;
}


bool isPresente(const abin binaire, int elemt) {

     abin copy = binaire;
     if (copy){
          if(copy->elmt == elemt)
               return true;     
          else if (copy->FilsGauche && (elemt < copy->elmt))
               return isPresente(copy->FilsGauche,elemt);
          else
               return isPresente(copy->FilsDroit, elemt);
     }
     return false;
}
int racine(const abin node) {
     return (node)?node->elmt:-1;
}

Nat nombreNode(abin node) {
     if(!node) return 0;
     if(!node->FilsGauche && !node->FilsDroit) return 1;
     else return 1 + (nombreNode(node->FilsDroit) + nombreNode(node->FilsGauche));
}


Nat nombreFeuille(abin node) {
     if(!node) return 0;
     if(!node->FilsDroit && !node->FilsGauche) return 1;
     else return nombreFeuille(node->FilsDroit) + nombreFeuille(node->FilsGauche);
}

abin extremeLeft(const abin node) {
     if (node){
          //Fin
          if(!node->FilsDroit && !node->FilsGauche) 
               return node;
          return extremeLeft(node->FilsGauche);
     }
     return NULL;
}

abin extremeRight(const abin node) {
     if (node){
          //Fin
          if(!node->FilsDroit && !node->FilsGauche) 
               return node;
          return extremeRight(node->FilsDroit);
     }
     return NULL;
}

void printfPrefixe(const abin node) {

     if(!node) return;
     printf("%d ",node->elmt);
     printfPrefixe(node->FilsGauche);
     printfPrefixe(node->FilsDroit);
}

void freeAllNodes(abin new1) {
     if (new1) {
          if (!new1->FilsDroit && !new1->FilsGauche)
               free(new1);
          else
          {
               freeAllNodes(new1->FilsDroit);
               freeAllNodes(new1->FilsGauche);
               free(new1);
          }
     }
}

int getAleatInt(int min, int max){
     return (rand() % (max - min + 1)) + min;
}


int main(int argc, char const *argv[])
{
     srand(time(NULL));
     abin new1 = createNode(getAleatInt(1,5));
     abin new2 = createNode(getAleatInt(1,5));
     abin new3 = createNode(getAleatInt(1,5));
     abin new4 = createNode(getAleatInt(1,5));
     abin new5 = createNode(getAleatInt(1,20));
     abin new6 = createNode(getAleatInt(1,20));
     abin new7 = createNode(getAleatInt(1,20));
     abin new8 = createNode(getAleatInt(1,20));
     
     //Connection de noeud
     //1
     new1->FilsGauche = new2;
     new1->FilsDroit  = new3;

     //3
     new3->FilsGauche = new6;
     new3->FilsDroit  = new7;

     //2
     new2->FilsGauche = new4;
     new2->FilsDroit  = new5;

     //4
     new4->FilsGauche = new8;

     
     printf("1 : %d\n",new1->elmt);
     printf("2 : %d\n",new2->elmt);
     printf("3 : %d\n",new3->elmt);
     printf("4 : %d\n",new4->elmt);
     printf("5 : %d\n",new5->elmt);
     printf("6 : %d\n",new6->elmt);
     printf("7 : %d\n",new7->elmt);
     printf("8 : %d\n",new8->elmt);

     printf("\nRacine : %d\n",racine(new1));
     printf("Extreme Gauche : %d\n",extremeLeft(new1)->elmt);
     printf("Extreme Droit : %d\n",extremeRight(new1)->elmt);
    
     

     
     free(new1);
     free(new2);
     free(new3);
     free(new4);
     free(new5);
     free(new6);
     free(new7);
     free(new8);

     (void) argc;
     (void) argv;
     return 0;
}
