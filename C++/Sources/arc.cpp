#include "arc.h"
#include "noeud.h"
//test

// Constructeurs
Arc::Arc(): poids(0)
{

}

Arc::Arc(int p, Noeud* n)
{
    if(p<0) this->poids = p-2*p;
    else this->poids = p;
    this->cible = n;
}

Arc::Arc(const Arc& copy)
{
    this->poids = copy.poids;
    this->cible = copy.cible;
}

Arc::~Arc()
{
    delete cible;
}

// Accesseurs & Mutateurs
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

