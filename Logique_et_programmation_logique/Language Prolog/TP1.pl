
% ------------------
%  Corrig� du TP 1
% ------------------


% [etudiants].

% [geographie].

% Exo 1) ==========================================================================

% 1-

aff_etudiant(X) :- etudiant(X), write(X), write('\n').
aff_etudiant(X) :- etudiante(X), write(X), write('\n').

:- findall(X,aff_etudiant(X),L).

etud(X) :- etudiant(X).
etud(X) :- etudiante(X).

% 2- 

:- habite('Eric Hochaud',X,Y).

% 3-

habite_rue(X) :- etud(X),habite(X,Y,_),Y\==0.
 
:- habite_rue(X).

% 4-

voisins(X,Y) :- habite(X,N,R),N\==0,habite(Y,M,R),N is M+1.
voisins(X,Y) :- habite(X,N,R),N\==0,habite(Y,M,R),M is N+1.

:- voisins('Kent Bowie',Y).
:- voisins('Paul Bonvoisin',Y).


% Exo 2) ==========================================================================

% 1-

est_dans_region(paris,'�le-de-France').
est_dans_region(strasbourg,'Alsace').
est_dans_region(colmar,'Alsace').
est_dans_region(toulouse,'Midi-Pyr�n�es').
est_dans_region(orleans,'Centre-Val de Loire').
est_dans_region(mulhouse,'Alsace').
est_dans_region(nancy,'Lorraine').
est_dans_region(grenoble,'Rh�ne-Alpes').

:- est_dans_region(grenoble,X).
:- est_dans_region(X,'Alsace').

% 2-

se_trouve_dans(X,Y) :- est_dans(X,Y).
se_trouve_dans(X,Z) :- est_dans(X,Y), est_dans(Y,Z).

est_dans_ville(X,Y) :- habite(X,_,Y),ville(Y).
est_dans_ville(X,Y) :- habite(X,_,Z),ville(Y),se_trouve_dans(Z,Y).

:- est_dans_ville('Hans-Hubert Worm',Y).

% 3-

habite_alsace(X) :- est_dans_ville(X,Y),est_dans_region(Y,'Alsace').

:- habite_alsace(X).

% 4-

meme_ville(X,Y) :- est_dans_ville(X,Z),est_dans_ville(Y,Z), not(X = Y).

meme_region(X,Y) :- est_dans_ville(X,XR),est_dans_region(XR,R),est_dans_ville(Y,YR),est_dans_region(YR,R), not(X = Y).


 





