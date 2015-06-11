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
    int gCost;
    std::list<Noeud*> lstNoeudFils;
    Arc* haut;
    Arc* bas;
    Arc* gauche;
    Arc* droite;

public :
    Noeud();
    Noeud(int,int,int); // id, x, y
    Noeud(int,int,int,std::list<Noeud*>); // id, x, y, lstNoeudFils
    ~Noeud();

    int getId();
    void setId(int);
    int getHeuritisque();
    void setHeuristique(int);
    void calcHeuristique(Noeud*);
    int* getPosition();
    void setPosition(int x, int y);
    std::list<Noeud*> getLstNoeudFils();
    void chercherFils();
    void setLstNoeudFils(std::list<Noeud*>);
    int getG();
    int setG(int);
    Arc* getArc(int);
    void setArc(int, Arc*);

    int* astar(const Noeud& final);

};
Noeud* getBestNode(const std::list<Noeud*>& open);

int* build_path(const std::list<Noeud*>& origin, const Noeud& final);

bool member(const std::list<Noeud*>& list, const Noeud* node); //true if node is in list, false otherwise.
#endif // NOEUD_H
