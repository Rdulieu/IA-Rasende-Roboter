#ifndef NOEUD_H
#define NOEUD_H

#include <QVector>
#include <QMap>
#include <algorithm>
#include "arc.h"
#include "bd.h"
#include "global_base.h"
struct P
{
    int i;
    int j;

    bool operator==(const P& a)
    {
        return (i == a.i && j == a.j);
    }
};
typedef struct P P;

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
    QVector<Noeud*> lstNoeudFils; //0 haut, 1 : bas, 2 droite, 3 gauche;
    Arc* haut; // id : 0
    Arc* bas; // id : 1
    Arc* gauche; // id : 2
    Arc* droite; // id : 3
    Bd* map;


public :
    //Noeud();
    Noeud(int, int, int, QVector<P>, Bd*, QVector<Noeud *> *unicity); // id, x, y
    Noeud(int, int, int, QVector<Noeud*>, Bd*, QVector<Noeud *> *unicity); // id, x, y, lstNoeudFils
    Noeud(const Noeud& copy);
    ~Noeud();

    bool isEqual(const Noeud b) const;

    int getId();
    void setId(int);
    int getHeuristique();
    void setHeuristique(int);
    void calcHeuristique(Noeud* final);
    int* getPosition();
    void setPosition(int x, int y);
    QVector<Noeud*>* getLstNoeudFils();
    QVector<Noeud*> getNonModifiableLstNoeudFils();
    void chercherFils(QVector<P>, Bd* bdd, QVector<Noeud *> *unicity);
    void setLstNoeudFils(QVector<Noeud*>);

    int getG();
    void setG(int);
    Arc* getArc(int);
    void setArc(int, Arc*);
    void setMap(Bd*);
    Bd* getMap();

    QVector<int> astar(int,int,int);
    Noeud* getBestNode(const QVector<Noeud*> open);
    int getIndexOfNode(const QVector<Noeud*> open, Noeud* toFind);
/*
    bool operator==(const Noeud& a);

    bool operator!=(const Noeud& a);
*/
};

QVector<int> build_path(QMap<Noeud*,Noeud*> came_from, Noeud* current,int robot);

bool member(const Noeud* node, const QVector<Noeud*> vector); //true if node is in vector, false otherwise.
#endif // NOEUD_H
