#include <stdio.h> 
#include <stdlib.h> 
#include "base.h"

typedef struct strarc 
{
    int v;
    struct strarc *suc;
    }Strarc, *ListeSom; 

typedef struct {
    int v; 
    ListeSom ls;
    } Couple;
 
 typedef struct strsom 
 {
     Couple c; 
    struct strsom *suiv;
 } Strsom, *Graphe; 





 Graphe createGraphe() {
   
     Graphe new  = ((Graphe*)malloc(sizeof(Graphe)));

     new->suiv = ((Couple*)malloc(sizeof(Couple)));

     int i;
     for(i=0;i< new->c.v ;i++) {
        new->suiv[i].c.v=NULL;}

        return new;

}
Nat isSommetPresent(Graphe graf, int sommet) {
    if (graf) {
        for (Nat i = 0; i < graf->c.v; i++)
        {
            if (graf->suiv[i].c.v == sommet)
                return i;
        }
    }
    return -1;
}

Graphe createListe(Nat elmt) {
     Graphe new = NULL;
     if(new = MALLOC(Graphe) == NULL);
     new->c.v = elmt;
     new->suiv = NULL;
     return new;
}


void addEdge( Graphe graph, int src, int dest) 
{ 
    
    struct strarc* newNode = createListe(dest); 
    newNode->suc = graph->suiv[src].c.v; 
    graph->suiv[src].c.v = newNode; 
  
  
    newNode = createListe(src); 
    newNode->suc = graph->suiv[dest].c.v; 
    graph->suiv[dest].c.v = newNode; 
} 

void printGraph(Graphe graph) 
{ 
    int v; 
    for (v = 0; v < graph->c.v; ++v) 
    { 
        struct strarc* pCrawl = graph->suiv[v].c.v; 
        printf("\n Adjacency list of vertex %d\n head ", v); 
        while (pCrawl) 
        { 
            printf("-> %d", pCrawl->v); 
            pCrawl = pCrawl->suc; 
        } 
        printf("\n"); 
    } 
} 


int main() 
{ 
   
    int V = 5; 
     Graphe graph = createGraphe(V); 
    addEdge(graph, 0, 1); 
    addEdge(graph, 0, 4); 
    addEdge(graph, 1, 2); 
    addEdge(graph, 1, 3); 
    addEdge(graph, 1, 4); 
    addEdge(graph, 2, 3); 
    addEdge(graph, 3, 4); 
  
    printGraph(graph); 
  
    return 0; 
} 