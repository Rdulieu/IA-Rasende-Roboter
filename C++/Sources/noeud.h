#ifndef NOEUD_H
#define NOEUD_H
#include <List>
#include <Map>
#include <map>
#include <list>
#include "arc.h"

class Arc;
class Noeud
{
private :
    int id;
    int position[2];  // position[0] : coordX  position[1] : coordY
    std::list<Noeud*> lstNoeudFils;
    Arc* haut;
    Arc* bas;
    Arc* gauche;
    Arc* droite;

public :
    std::list<std::pair<Noeud*,int> > astar(Noeud&); // 0 : haut 1: bas 2 : gauche 3 : droite
    Noeud();
    Noeud(int,int,int);
    Noeud(int,int,int,std::list<Noeud*>);
    ~Noeud();

    int getId();
    void setId(int);
    int* getPosition();
    void setPosition(int x, int y);
    std::list<Noeud*> getLstNoeudFils();
    void setLstNoeudFils(std::list<Noeud*>);
};

#endif // NOEUD_H
