#include "noeud.h"
#include <QList>
#include <QMap>

Noeud::Noeud()
{

}

Noeud::~Noeud()
{
}

Noeud::Noeud(int _id, int x, int y)
{
    this->id = _id;
    this->position[0] = x;
    this->position[1] = y;
}

Noeud::Noeud(int _id, int x, int y, std::list<Noeud*> _lst)
{
    this->id = _id;
    this->position[0]=x;
    this->position[1]=y;
    this->lstNoeudFils = _lst;
}

void Noeud::setId(int _id)
{
    this->id = _id;
}

int Noeud::getId()
{
    return this->id;
}

void Noeud::setPosition(int x, int y)
{
    this->position[0] = x;
    this->position[1] = y;
}

int* Noeud::getPosition()
{
    return this->position;
}

void Noeud::setLstNoeudFils(std::list<Noeud*> _lst)
{
    this->lstNoeudFils = _lst;
}

std::list<Noeud*> Noeud::getLstNoeudFils()
{
    return this->lstNoeudFils;
}
