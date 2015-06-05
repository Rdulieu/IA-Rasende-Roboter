#ifndef ARC_H
#define ARC_H
#include "noeud.h"


class Arc
{
private :
    int poids;
    Noeud* cible;

public :
    int getPoids();
    void setPoids(int);

    Noeud* getCible();
    void setCible(Noeud*);
    Arc();
    Arc(int,Noeud*);
};

#endif // ARC_H
