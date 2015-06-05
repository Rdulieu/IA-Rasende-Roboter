#ifndef NOEUD_H
#define NOEUD_H
#include <List>
#include <Map>
#include <map>
#include <list>

class Noeud
{
private :
    int id;
    int position[2];  // position[0] : coordX  position[1] : coordY
    std::list<Noeud*> lstNoeudFils;

public :
    std::map<Noeud*,int> astar(Noeud&);
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
