
% ------------------
%  Corrig� du TP 3
% ------------------

 
% Exo 1) ==========================================================================

% 1- 

animal(caribou).
animal(bouquetin).
animal(ours).
animal(tigre).
animal(grenouille).
animal(hibou).
animal(singe).
animal(alligator).
animal(lama).
animal(marmotte).
animal(pelican).
animal(hippocampe).
animal(canard).

concat([],L2,L2). 
concat([X|R],L2,[X|L]) :- concat(R,L2,L).

mutant(X) :- animal(A1), animal(A2),
	name(A1,L1), name(A2,L2),
	concat(_,Mil, L1), Mil \== [], L1 \= Mil,
	concat(Mil, Lfin, L2),
	concat(L1, Lfin, LX),
	name(X,LX).

:- mutant(caribouquetin).

% 2-
     
d(N,N1,N2) :- NN is N-1,
	enum(N1,0,NN),
	N2 is NN-N1.
	
enum(I,I,_).
enum(I,A,B) :- A <B, AA is A+1, enum(I,AA,B).

gmutant(X,0) :- animal(X).

gmutant(X,N) :- N>0, 
	d(N, N1, N2),
	gmutant(A1,N1), gmutant(A2,N2),
	name(A1,L1), name(A2,L2),
	concat(_,Mil, L1), Mil \== [], L1 \= Mil,
	concat(Mil, Lfin, L2),
	concat(L1, Lfin, LX),
	name(X,LX).

% 3-

enum_inf(I,I).
enum_inf(I,A) :- AA  is A+1, enum_inf(I,AA).

gmutant(X) :- enum_inf(I,0), gmutant(X,I).


% Exo 2) ==========================================================================

d1_9(1).
d1_9(2).
d1_9(3).
d1_9(4).
d1_9(5).
d1_9(6).
d1_9(7).
d1_9(8).
d1_9(9).
 
digit(0).
digit(X) :- d1_9(X).
 
distinct([]).
distinct([X|Xs]) :- not(member(X, Xs)), distinct(Xs).
 
sendmoremoney :-
   d1_9(S), digit(E), digit(N), digit(D), d1_9(M), digit(O), digit(R), digit(Y),
   distinct([S, E, N, D, M, O, R, Y]),
   SEND is 1000*S + 100*E + 10*N + D,
   MORE is 1000*M + 100*O + 10*R + E,
   MONEY is 10000*M + 1000*O + 100*N + 10*E + Y,
   MONEY is SEND + MORE,
   print([[S, E, N, D], [M, O, R, E], [M, O, N, E, Y]]).
 
% ?- sendmoremoney.
% [[9,5,6,7],[1,0,8,5],[1,0,6,5,2]]

tentenfortysixty :-
   d1_9(T), digit(E), digit(N), d1_9(F), digit(O), digit(R), digit(Y), d1_9(S), digit(I), digit(X),
   distinct([T, E, N, F, O, R, Y, S, I, X]),
   TEN is 100*T + 10*E + N,
   FORTY is 10000*F + 1000*O + 100*R + 10*T + Y,
   SIXTY is 10000*S + 1000*I + 100*X + 10*T + Y,
   SIXTY is TEN + TEN + FORTY,
   print([[T, E, N], [T, E, N], [F, O, R, T, Y], [S, I, X, T, Y]]).

% ?-  tentenfortysixty.
% [[8,5,0],[8,5,0],[2,9,7,8,6],[3,1,4,8,6]] 





