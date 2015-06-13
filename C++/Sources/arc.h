#ifndef ARC_H
#define ARC_H
#include "noeud.h"
class Noeud;
// La classe arc pointe vers un noeud cible et a un poids qui sert à calculer les coûts de déplacement
class Arc
{
private :
    int poids;
    Noeud* cible;

public :
    Arc();
    Arc(int,Noeud*);
    Arc(const Arc& copy);

    int getPoids();
    void setPoids(int);

    Noeud* getCible();
    void setCible(Noeud*);

};

#endif // ARC_H
