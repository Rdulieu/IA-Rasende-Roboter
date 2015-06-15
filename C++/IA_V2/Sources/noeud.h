#ifndef NOEUD_H
#define NOEUD_H
#include <map>
#include <vector>
#include <vector>
#include <algorithm>
#include "arc.h"
#include "bd.h"
#include"IpseityTalker.h"
#include"global_base.h"
struct P
{
    int i;
    int j;

    bool operator==(const P& a)
    {
        return (i == a.i && j == a.j);
    }

    bool operator!=(const P& a)
    {
        return (this->operator ==(a));
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
    //Qvector<Noeud*> lstNoeudFils;
    std::vector<Noeud*> lstNoeudFils;
    Arc* haut; // id : 0
    Arc* bas; // id : 1
    Arc* gauche; // id : 2
    Arc* droite; // id : 3
    Bd* map;


public :
    //Noeud();
    Noeud(int,int,int); // id, x, y
    Noeud(int,int,int,std::vector<Noeud*>); // id, x, y, lstNoeudFils
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
    std::vector<Noeud*> getLstNoeudFils();
    void chercherFils(std::vector<P>&);
    void setLstNoeudFils(std::vector<Noeud*>&);
/* -> INUTILE
    std::vector<std::pair<Noeud*, int> > astar(const Noeud& final);
};
std::vector<std::pair<Noeud*, int> > build_path(const std::vector<Noeud*>& origin, const Noeud& final);*/
    int getG();
    void setG(int);
    Arc* getArc(int);
    void setArc(int, Arc*);

    Response astar(int,int);
    Noeud* getBestNode(const std::vector<Noeud*>& open);

    bool operator==(const Noeud a);

    bool operator!=(const Noeud a);

    ostream& display(ostream& stream) const;

};

Response build_path(const std::vector<Noeud*>& origin, Noeud* final);

bool member(const Noeud* node, const std::vector<Noeud*>& vector); //true if node is in vector, false otherwise.

ostream& operator<<(const Noeud& a, ostream& stream);
#endif // NOEUD_H
