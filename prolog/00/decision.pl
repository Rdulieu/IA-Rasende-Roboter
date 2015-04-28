/*


  Définition de l'IA du joueur artificiel de Rasende Roboter


*/


:- module( decision, [
	init/1,
	move/2
] ).


init(_).


/*
  move( +L, -ActionId )
*/

% Examples
move( [0,0,0,0,  1, 4,0 | _], [0,4,0,1,0,4,0,1,0,2,0,3,0,2,0,3] ) :- !.
move( [0,0,0,0,  2, 6,1 | _], [0,1,0,4] ) :- !.
move( [0,0,0,0, 14, _,_, _,_, _,_, 5,15], [3,3,3,2,3,3,3,4] ) :- !.

move( _, [] ) :- !.
%        ^
%        |
%        Action: next configuration
