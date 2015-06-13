#ifndef NOEUD_H
#define NOEUD_H
#include <map>
#include <QList>
#include "arc.h"
#include "bd.h"
#include"IpseityTalker.h"
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
    QList<Noeud*> lstNoeudFils;
    Arc* haut; // id : 0
    Arc* bas; // id : 1
    Arc* gauche; // id : 2
    Arc* droite; // id : 3
    Bd* map;

public :
    Noeud();
    Noeud(int,int,int); // id, x, y
    Noeud(int,int,int,QList<Noeud*>); // id, x, y, lstNoeudFils
    ~Noeud();

    int getId();
    void setId(int);
    int getHeuristique();
    void setHeuristique(int);
    void calcHeuristique(Noeud* final);
    int* getPosition();
    void setPosition(int x, int y);
    QList<Noeud*> getLstNoeudFils();
    void chercherFils();
    void setLstNoeudFils(QList<Noeud*>);
/* -> INUTILE
    std::list<std::pair<Noeud*, int> > astar(const Noeud& final);
};
std::list<std::pair<Noeud*, int> > build_path(const std::list<Noeud*>& origin, const Noeud& final);*/
    int getG();
    int setG(int);
    Arc* getArc(int);
    void setArc(int, Arc*);

    Response astar(Noeud* final);

};
Noeud* getBestNode(const QList<Noeud*>& open);

Response build_path(const QList<Noeud*>& origin, Noeud* final);

bool member(const Noeud* node, const QList<Noeud*>& list); //true if node is in list, false otherwise.

#endif // NOEUD_H
