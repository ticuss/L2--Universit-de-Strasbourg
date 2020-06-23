#include<stdio.h> 
#include<stdlib.h> 
#include "arbin.h" 


Node newNode(int key) 
{ 
    struct node* node = (struct node*) 
                        malloc(sizeof(struct node)); 
    node->key   = key; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  
    return(node); 
} 

int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

Node  enraciner(int x, Node g, Node d)
 {
           Node nouv = newNode(x);  
               nouv->key=x;  
                   nouv->left=g;    
                     nouv->right=d; 
                     nouv->height=1+max(g!=NULL ? g->height:-1, d!=NULL ? d->height:-1);
                     return nouv;
                     }


int height( Node N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 

Node getLeftChild(const Node node) {
     return (!node)? NULL:node->left;
}

Node getRightChild(const Node node) {
     return (!node)? NULL :node->right;
}


Node rightRotate( Node y) 
{ 
    Node x = y->left; 
     Node T2 = x->right; 
  
   
    x->right = y; 
    y->left = T2; 
  
    
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
  
    
    return x; 
} 

Node leftRotate(Node x) 
{ 
    Node y = x->right; 
    Node T2 = y->left; 
   
    y->left = x; 
    x->right = T2; 
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    return y; 
} 

Node  rgd(Node a)
 {
     a->left = leftRotate(a->left) ;
     
     return rightRotate(a) ;
      } 


Node  rdg(Node a)
 {
     a->right = rightRotate(a->right) ;
   
     return leftRotate(a) ;
      } 

int getBalance( Node N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 

Node insert(Node node, int key) 
{ 
   
    if (node == NULL) 
        return(newNode(key)); 
  
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else 
        return node; 
  
    /* Update height  */
    node->height = 1 + max(height(node->left), 
                           height(node->right)); 
  
    /* On obtient le facteur d'équilibre de cet ancêtre
           noeud pour vérifier si ce noeud est devenu
           déséquilibré */
        
    int balance = getBalance(node); 
  
   // Si ce noeud devient déséquilibré, alors
     // il y a 4 cas
  
    // Case gauche gauche
    if (balance > 1 && key < node->left->key) 
        return rightRotate(node); 
  
    //Right Right Case
    if (balance < -1 && key > node->right->key) 
        return leftRotate(node); 
  
    // Case gauche droite
    if (balance > 1 && key > node->left->key) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Droit gaughe 
    if (balance < -1 && key < node->right->key) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    /* retourner le pointeur de noeud (inchangé) */
    return node; 
} 

 Node  minValueNode( Node node) 
{ 
     Node current = node; 
  
   /* boucle vers le fond, pour trouver la feuille la plus à gauche */
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
} 


Node supprimeNode( Node root, int key) 
{ 
    
  
    if (root == NULL) 
        return root; 
  
    // Si la clé à supprimer est plus petite
     // que la clé de la racine, alors il se trouve
     // dans le sous-arbre gauche
    if ( key < root->key ) 
        root->left = supprimeNode(root->left, key); 
  
    // Si la clé à supprimer est supérieure à la
    // la clé de la racine, alors elle se trouve dans le sous-arbre droit
    else if( key > root->key ) 
        root->right = supprimeNode(root->right, key); 
  
    // si la clé est identique à la clé de la racine, alors c'est
    // le noeud à supprimer
    else
    { 
       // noeud avec un seul enfant ou sans enfant 
        if( (root->left == NULL) || (root->right == NULL) ) 
        { 
            Node temp = root->left ? root->left : 
                                             root->right; 
  
            // Case sans enfants
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else // Un enfant case 
             *root = *temp; // Copie le contenu de
                            // l'enfant non vide
            free(temp); 
        } 
        else
        { 
            // noeud avec deux enfants: récupère l'ordre
             // successeur (le plus petit dans le sous-arbre droit)
            Node temp = minValueNode(root->right); 
  
           // Copie les données du successeur 
            root->key = temp->key; 
  
            // Supprimer le successeur inorder
            root->right = supprimeNode(root->right, temp->key); 
        } 
    } 
  
   // Si l'arbre n'a pas qu'un seul noeud, retournez
    if (root == NULL) 
      return root; 
  
    // MISE À JOUR DE LA HAUTEUR DU NOEUD ACTUEL
    root->height = 1 + max(height(root->left), 
                           height(root->right)); 
  
    //  OBTENIR LE FACTEUR D'ÉQUILIBRE DE CE NOEUD (à
     // vérifie si ce noeud est devenu déséquilibré)
    int balance = getBalance(root); 
  
    // Si ce noeud devient déséquilibré, alors il y a 4 cas
  
    // Gauche gauche
    if (balance > 1 && getBalance(root->left) >= 0) 
        return rightRotate(root); 
  
    // gauche droit 
    if (balance > 1 && getBalance(root->left) < 0) 
    { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    //droit droit
    if (balance < -1 && getBalance(root->right) <= 0) 
        return leftRotate(root); 
  
    // droit gauche
    if (balance < -1 && getBalance(root->right) > 0) 
    { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
  
    return root; 
} 



Node reeq(Node a) {
    if (getBalance(a)==0 || getBalance(a)==-1 || getBalance(a)==1) return a;
    else if (getBalance(a)==2 && getBalance(a->left)==1)  return rightRotate(a);
    else if (getBalance(a)==-2 && getBalance(a->right)==-1) return leftRotate(a) ;
    else if (getBalance(a)==2 && getBalance(a->left)==-1) return rgd(a) ;
    else if(getBalance(a)==-2 && getBalance(a->right)==+1) return rdg(a);  
    else return a;
    } 

Node rech(int x, Node a) { 
         if (a == NULL) return a ;
              else if (a->key == x)  return a ;
              else if (a->key != x)  return rech(x, a->right);        
              else return rech(x, a->left);
               
               } 
 
void preOrder(Node root) 
{ 
    if(root != NULL) 
    { 
        printf("%d ", root->key); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 


int verifie(Node arbre , int *min,int *max){
    int i ; 
    *min = *max = arbre->key;
    if(arbre->left !=NULL)
        {
        if(!verifie(arbre->left, &i, max) || !(arbre->key > *max))
        return 0;
        } 
        if(arbre->right !=NULL)
        {
       if(!verifie(arbre->right,min,&i)||!(arbre->key <= *min))
        return 0; 
        }
    return 1;

}

int est_trie (Node arbre){
int min , max ;
return ((arbre == NULL)? 1 : verifie(arbre , &min, &max));
}


void affiche_rec (Node arbre){
    if(arbre !=NULL){
        affiche_rec(arbre->left);
        if(arbre->left != NULL)
            printf(",");
            printf("%d", arbre->key);
        if(arbre->right!=NULL)
        printf(",");
        affiche_rec(arbre->right);
    }

} 

void affiche (Node arbre){
    affiche_rec(arbre);
    printf("\n");
}


int main() 
{ 
   Node root = NULL; 
  
  root = insert(root, 10); 
  root = insert(root, 20); 
  root = insert(root, 30); 
  root = insert(root, 40); 
  root = insert(root, 50); 
  root = insert(root, 25); 
  
  
  printf("Preorder affichage de AVL \n"); 
  preOrder(root); 
   root = supprimeNode(root, 20); 
     printf("\nApres la suppresion\n");
     preOrder(root);
    
   printf("\n" );
   printf("\nrenvoie 1 si l'arbre est trié := %d\n", est_trie(root));
   printf("\nAffiche en ordre croissant\n" );
      affiche(root);
  return 0; 
} 