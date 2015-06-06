#include "arc.h"
#include "noeud.h"

Arc::Arc():poids(0)
{

}

Arc::Arc(int p, Noeud* n)
{
    this->poids = p;
    this->cible = n;
}

void Arc::setCible(Noeud* n)
{
    this->cible = n;
}

Noeud* Arc::getCible()
{
    return this->cible;
}

void Arc::setPoids(int p)
{
    this->poids = p;
}

int Arc::getPoids()
{
    return this->poids;
}

