#ifndef NOEUD_H
#define NOEUD_H
#include <List>
#include <Map>
#include <map>
#include <list>
#include "arc.h"
#include "bd.h"
class Arc;
class Bd;
class Noeud
//La classe Noeud représente un noeud du graphe sur lequel on souhaite appliquer notre algorithme Astar.
{
private :
    int id;
    int position[2];  // position[0] : coordX  position[1] : coordY
    int heuristique;
    std::list<Noeud*> lstNoeudFils;
    Arc* haut;
    Arc* bas;
    Arc* gauche;
    Arc* droite;

public :
    std::list<std::pair<Noeud*,int> > astar(Noeud&); // 0 : haut 1: bas 2 : gauche 3 : droite
    Noeud();
    Noeud(int,int,int); // id, x, y
    Noeud(int,int,int,std::list<Noeud*>); // id, x, y, lstNoeudFils
    ~Noeud();

    int getId();
    void setId(int);
    int getHeuritisque();
    void setHeuristique(int);
    int* getPosition();
    void setPosition(int x, int y);
    std::list<Noeud*> getLstNoeudFils();
    void chercherFils();
    void setLstNoeudFils(std::list<Noeud*>);

};

#endif // NOEUD_H
