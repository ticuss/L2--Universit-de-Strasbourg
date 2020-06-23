

// TP 1
// Objectifs : 
// Découverte, Calcul Matriciel, Application fonction sur échantillon, Plot, Régression Linéaire en 3 façons.

//**************************************************************** Découverte affichage
//Exercice 1 : Découverte de Scilab
// Exemple Plot

// Création abscisses
x = [0:1:10];
// ou linspace(0,10,100) va jusqu'à 10 avec 100-1 "intervalles" mais 100 points en finissant sur 10
// Observation lien intervalles/distances à parcourir
// Regarder les x obtenus

scf(0)
clf(0)
plot(x, sqrt(x))

// Pour effacer la fenêtre du graphe avant de tracer un nouveau graphe
// Sinon superposition
// clf()
// Ouverture d'une nouvelle fenêtre
// scf()
// Ces fonctions acceptent un numéro de figure entre leurs parenthèses pour effacer ou être plus précis.

// Si superposition voulue
scf(1)
clf(1)
plot(x, sqrt(x), x, x^2)

// Si dans la même figure on veut plusieurs petits graphes
// subplot(nbr subdivisions verticales, nbe subdivisions horizontales, n° de position)
scf(2)
clf(2)
subplot(121)
plot(x, x^2)
subplot(122)
plot(x, sqrt(x))

// Jeu sur le style de trait et style de points : aller voir la doc !
// Noter le fait qu'une fonction peut avoir un nombre de paramètres variables en entrée
scf(3)
clf(3)
plot(x, sqrt(x), 'gs-', x, x^2, 'm^-.', x, x^3, 'bp:')
xtitle("Des courbes colorées", "abscisse", "ordonnée")
// Attention aux titres ! pour une apostrophe : ''. L'écriture peut se faire via commandes LateX en encadrant par $ $.
// exemple : $mbox{la fréquence } \nu 

// Exporter graph 
// Utiliser la fonction d'export dans la fenêtre d'affichage ou 
// xs2png(0,"Nom_Fichier.png")

//**************************************************************** Syntaxe Création Fonction 

// function <arguments_sortie>=<nom_de_la_fonction><arguments_entrée>
// <instructions>
// endfunction

function [a]=somme(x, y)
    a = x + y ; 
endfunction
a = somme(1,2)

//**************************************************************** Partie Calcul Matriciel

// Ecrire des matrices
A = [1 2 3; 4 5 6; 7 8 9] ;
B = [1 1 1; 10 10 10; 20 20 20] ;

// Chargement d'un fichier de données
// Pour stocker dans une matrice 
//A = fscanfMat("blablubli.dat")

// Remarque : besoins de tailles cohérentes pour les opérations entre matrices sinon erreur !
// Attention quand on manipule des matrices de tailles différentes
// On peut toujours vérifier la taille d'une matrice 
size(A)
C1 = A + B
C2 = A - B

// Calcul Matriciel classique
C3 = A*B
// Calcul terme à terme
C4 = A.*B
// Idem puissance
C5 = A^3
C6 = A.^3

// Inverse de matrice 
det(A)
det(B)
// Déterminant de A et B nul, non inversible : message d'erreur
D = [50 200 20; 50 30 60; 1 2 3]
DET = det(D)
C7 = inv(D)
// On devrait obtenir la matrice identité mais il y a déjà des problèmes d'arrondis
// Fonction pour nettoyer : clean() mais contre-productive dans le cadre du tp ?
// Problèmes numériques
C8 = D*C7
// Attention pour obtenir une division termes à termes, ajouter un espace sinon nombre à virgule
C9 = 1 ./D

//**************************************************************** Fonctions sur Matrices
// Somme des éléments d'une ligne
C10 = sum(A(1,:))
C101 = sum(A, 'c')

// Eviter les boucles ! Fonctions adaptées disponibles
// Comment faire la somme de la racine carré de tous les éléments de la matrice ?
C11 = sum(sqrt(A))

//Exercice 2 Manipulation de donneìes

//**************************************************************** Régression Linéaire
//question 1
// Données : taille de nez d'un kangourou gris (longueur en X, largeur en Y) en mm
K = fscanfMat("/Users/pham/Scilab-2020/Kangourous.txt")
//question 2
scf(4)
clf(4)
plot(K(:,1),K(:,2))
// Classer les données
Ktri = gsort(K, "lr", "i")
scf(4)
clf(4)
plot(Ktri(:,1),Ktri(:,2), 'gs')
//question 3+4
X = Ktri(:,1)';
Y = Ktri(:,2)';
// Utilisation librairie
// régression linéaire selon les moindres carrés
[a, b, sig] = reglin(X, Y)
Xc = [450:10:900]
plot(Xc, a*Xc+b)

//question 5
// Calcul via variance et covariance à la main 
cov = corr(X, Y, 1)
[s, mc] = variance(X)
a2 = cov/s

b2 = mean(Y) - a2 * mean(X)

//question 6
// Ecriture système linéaire
// Introduction du "backslash" ou du slash
Xlin = [X', ones(X')]
A3 = Xlin\Y' ;
A4 = Y/[X; ones(X)]
//question 7 + 8
// Coefficient corrélation / Résidus
co = correl(X, Y)
Residus = Y' - Xlin*[a; b]
res = sum(Residus)
//conclusion

