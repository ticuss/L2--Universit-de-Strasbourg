
% ------------------
%  Corrig� du TP 2
% ------------------


% Exo 1) ==========================================================================

% 3-

concat([],L2,L2). 
concat([X|R],L2,[X|L]) :- concat(R,L2,L).

rev([],[]).
rev([X|R],LX) :- rev(R,L), concat(L,[X],LX).

:- rev([1,2,3],X).

rev2(L,Lr) :- revacc(L, [], Lr).
revacc([], L, L).
revacc([X|L1], L2, Lr) :- revacc(L1, [X|L2], Lr).

:- rev2([1,2,3],X).

% 4-

aplat([],[]).
aplat([X|L],La) :-
	aplat(X,L1),
	aplat(L,L2),
	concat(L1,L2,La).

aplat(X,[X]) :- not(liste(X)).

liste([]).
liste([_|_]).

:- aplat([[1,2],[5,[1]],3],X).

 
% Exo 2) ==========================================================================

% 1-

epelle :- read(X),
          name(X,L),
	  epelle(L).
	  
epelle([]):-nl.
epelle([X|L]) :- put(X), nl, epelle(L).

% 2-

concat([],L2,L2). 
concat([X|R],L2,[X|L]) :- concat(R,L2,L).

aconcat(A1,A2,A) :-
	name(A1,L1), name(A2,L2), concat(L1,L2,L), name(A,L).

:- aconcat(ceci,cela,X).

% 3-

substring(L,1, Nb, Le) :-
     substring(L,Nb,Le).
substring([_|L],Nd,Nb,Le) :- Nd>1,
       NN is Nd-1,
       substring(L, NN, Nb, Le).
       
 substring(_,0,[]).
 substring([X|L], N, [X|Le]) :-
 	N > 0, NN is N-1, substring(L,NN,Le).

subatom(A,Nd,Nb,Ae) :- name(A,L),
		substring(L,Nd,Nb,Le),
		name(Ae,Le).

% 4-

rev([],[]).
rev([X|R],LX) :- rev(R,L), concat(L,[X],LX).

palin(A) :- name(A,L), rev(L,LR), name(AR,LR), A == AR.

:- palin(ericacire).

 
% Exo 3) ==========================================================================

% -

% t(t(t(nil,8,nil),2,nil),4,t(t(nil,2,nil),7,t(nil,3,nil)))

estarbin(nil).
estarbin(t(AG,X,AD)) :- estarbin(AG),estarbin(AD).

:- estarbin(t(t(t(nil,8,nil),2,nil),4,t(t(nil,2,nil),7,t(nil,3,nil)))).

ag(t(AG,X,AD),AG).
ad(t(AG,X,AD),AD).
rac(t(AG,X,AD),X).

dans(X,t(AG,X,AD)).
dans(X,t(AG,Y,AD)) :- not(X = Y), dans(X,AG), !.
dans(X,t(AG,Y,AD)) :- not(X = Y), dans(X,AD), !.

:- dans(8,t(t(t(nil,8,nil),2,nil),4,t(t(nil,2,nil),7,t(nil,3,nil)))).

nn(nil,0).
nn(t(AG,X,AD),N) :- nn(AG,NG), nn(AD,ND), N is NG+ND+1.

:- nn(t(t(t(nil,8,nil),2,nil),4,t(t(nil,2,nil),7,t(nil,3,nil))),N).

% La hauteur d'un arbre binaire est �gale � la plus grande des distances des feuilles � la racine.

hauteur(nil,0).
hauteur(t(AG,X,AD),N) :- hauteur(AG,NG), hauteur(AD,ND), N is max(NG,ND)+1.
 
:- hauteur(t(t(t(nil,8,nil),2,nil),4,t(t(nil,2,nil),7,t(nil,3,nil))),N).

affiche_aux(nil,S) :- name(AS,S), write(AS), write('nil').
affiche_aux(t(AG,X,AD),S) :- concat(S,"   ",SS),
                             affiche_aux(AD,SS),nl,
                             name(AS,S),write(AS),write(X),nl,
                             affiche_aux(AG,SS).

affiche(A) :- affiche_aux(A,[]).

:- affiche(t(t(nil,8,nil),2,nil)).
:- affiche(t(t(t(nil,8,nil),2,nil),4,t(t(nil,2,nil),7,t(nil,3,nil)))).



