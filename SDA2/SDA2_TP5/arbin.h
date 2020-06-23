#ifndef _arbin_h_
#define _arbin_h_

typedef struct node  { 
    int key; 
    struct node *left; 
    struct node *right; 
    int height; 
} *Node ; 

/**
 * \brief Fonction d'assistance qui alloue un
    nouveau noeud avec la clé donnée et
    Pointeurs NULL gauche et droit.
 **/
Node newNode(int key) ;


/**
 * \brief Une fonction utilitaire pour obtenir le maximum
 * de deux entiers
 **/
int max(int a, int b) ;


/**
 * \brief créer un arbre  à partir du fils gauche et droit
 * \return Node
 **/
Node  enraciner(int x, Node g, Node d);


/**
 * \brief Une fonction utilitaire pour obtenir la hauteur de l'arbre
 * \return int
 **/
int height( Node N) ;

/**
 * \brief Acces au enfant gauche
 **/
Node getLeftChild(const Node node) ;


/**
 * \brief Acces au enfant droit
 **/
Node getRightChild(const Node node) ;

/**
 * \brief Rotation a droite avec sous arbre enraciné avec y
 **/
Node rightRotate(Node y);


/**
 * \brief Rotation a gauche avec sous arbre enraciné avec x
 **/
Node leftRotate(Node x) ;


/**
 * \brief Rotation a gauche et droite avec sous arbre enraciné avec a
 **/
Node  rgd(Node a) ;

/**
 * \brief Rotation a droit et gauche avec sous arbre enraciné avec a
 **/
Node  rdg(Node a);

/**
 * \brief indicateur de déséquilibrage qui veriefie la 
 * difference entre hauteur gauche et droite
 **/
int getBalance( Node N) ;

/**
 * \brief fonction qui fait insertion d'un element en preservent l'equilibrage de l'arbre 
 * j'ai detaillé le code de cette fonction dans le fichier source.
 **/
Node insert(Node node, int key) ;

/**
 * \brief  Étant donné un arbre de recherche binaire non vide,
 * retourner le nœud avec la valeur de clé minimale
 * trouvé dans cet arbre. On n'a pas besoin parcourir tout l'arbre.
 **/
 Node  minValueNode( Node node) ;

 /**
 * \brief  Fonction récursive pour supprimer un nœud
 * avec la clé donnée du sous-arbre avec la racine donnée. 
 * Il renvoie la racine du sous-arbre modifié.
 **/
Node supprimeNode( Node root, int key) ;

/**
 * \brief  Fonction de reequilibrage.
 **/
Node reeq(Node a) ;

/**
 * \brief  Fonction de recherche d'un element.
 **/
Node rech(int x, Node a) ;

/**
 * \brief  Fonction classique d'affichage'
 **/
void preOrder(Node root) ;



/**
 * \brief  Fonction qui verifie  si l'arbre binaire passé en
 *  parametre est un arbre binaire de recherche
 **/
int verifie(Node arbre , int *min,int *max);
/**
 * \brief  Appel de la fonction verifie();
 **/
int est_trie (Node arbre);



/**
 * \brief  Fonction qui affiche les valeurs des noeuds d'un ABR par ordre croissant
 * ici il fallait choisir bien le parcours des noeuds.
 **/
void affiche_rec (Node arbre);
/**
 * \brief  appel de la fonction.
 **/
void affiche (Node arbre);


#endif