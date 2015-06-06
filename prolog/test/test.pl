

recupere(L,N,X):- recupere(L,N,X,1).
recupere([X|_],N,X,N):-!.
recupere([_|R],N,X,N2):- recupere(R,N,X,N3),N3 is N2+1.