#include "noeud.h"
#include <QList>
#include <QMap>

// Constructeurs & Destructeurs
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

// Accesseurs et mutateurs
void Noeud::setId(int _id)
{
    this->id = _id;
}

int Noeud::getId()
{
    return this->id;
}

void Noeud::setHeuristique(int _h)
{
    this->heuristique=_h;
}

int Noeud::getHeuristique()
{
    return this->heuristique;
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

// On cherche tous les noeuds fils, ce sont les cases qui sont accessibles à partir de la case actuelle (Noeud parent)
void Noeud::chercherFils()
{
    int pos[4]; // : 0 haut 1 bas 2 gauche 3 droite, si pos[0]==1 alors il y a un obstacle horizontale au-dessus de notre case
    int countFils; // nombre de fils à partir du noeud parent

    // On cherche à quel(s) bords notre case est collée
    if(Bd::getlist_murV(this->getPosition(0),this->getPosition(1))) // est-ce qu'il y a un mur vertical à droite
        pos[3]=1;
    else if(Bd::getlist_murV(this->getPosition(0)-1,this->getPosition(1))) // est-ce qu'il y a un mur vertical à gauche
        pos[2]=1;
    else if(Bd::getlist_murH(this->getPosition(0),this->getPosition(1))) // est-ce qu'il y a un mur horizontal en bas
        pos[1]=1;
    else if(Bd::getlist_murH(this->getPosition(0),this->getPosition(1)-1)) // est-ce qu'il y a un mur horizontal en haut
        pos[0]=1;

    // On cherche la position des noeuds fils possibles dans chaque direction
    i = this->getPosition(0);
    j = this->getPosition(1);

    if(tab[0]==0) // On cherche la position d'un noeud fils s'il n'y a pas d'obstacle collé au-dessus de notre case actuelle
    {
        while(Bd::getlist_murH(this->getPosition(i),this->getPosition(j)-1)==false) // On monte dans la grille tant qu'on ne rencontre pas de mur
        {
            j--;
        }
        count++;
        Noeud filsHaut = new Noeud(count,i,j);
        this->getLstNoeudFils().push_back(filsHaut); // On ajoute le noeud fils à la liste des noeuds fils
    }
    else this->getLstNoeudFils().push_back(NULL);

    // On revient sur notre case de départ
    i = this->getPosition(0);
    j = this->getPosition(1);

    if(tab[1]==0) // Libre en bas
    {
        while(Bd::getlist_murH(this->getPosition(i),this->getPosition(j))==false) // On descend dans la grille tant qu'on ne rencontre pas de mur
        {
            j++;
        }
        count++;
        Noeud filsBas = new Noeud(count,i,j);
        this->getLstNoeudFils().push_back(filsBas); // On ajoute le noeud fils à la liste des noeuds fils
    }
    else this->getLstNoeudFils().push_back(NULL);

    i = this->getPosition(0);
    j = this->getPosition(1);

    if(tab[2]==0) // Libre à gauche
    {
        while(Bd::getlist_murH(this->getPosition(i)-1,this->getPosition(j))==false) // On va à gauche dans la grille tant qu'on ne rencontre pas de mur
        {
            i--;
        }
        count++;
        Noeud filsGauche = new Noeud(count,i,j);
        this->getLstNoeudFils().push_back(filsGauche); // On ajoute le noeud fils à la liste des noeuds fils
    }
    else this->getLstNoeudFils().push_back(NULL);

    i = this->getPosition(0);
    j = this->getPosition(1);

    if(tab[3]==0) // Libre à droite
    {
        while(Bd::getlist_murH(this->getPosition(i),this->getPosition(j))==false) // On va à droite dans la grille tant qu'on ne rencontre pas de mur
        {
            i++;
        }
        count++;
        Noeud filsDroite = new Noeud(count,i,j);
        this->getLstNoeudFils().push_back(filsDroite); // On ajoute le noeud fils à la liste des noeuds fils
    }
    else this->getLstNoeudFils().push_back(NULL);

    i = this->getPosition(0);
    j = this->getPosition(1);

    return;
}

int* astar(const Noeud& final)
{
    std::list<Noeud*> open, closed, origin;
    open.push_back(this);

    int g(0), f(g + heuristique), tempG;

    while(!(open.empty()))
    {
        Noeud* cur = getBestNode(open);
        if(cur == final)
        {
            return build_path(origin, final);
        }
        open.remove(cur);
        closed.push_back(cur);

        for(int i = 0; i<lstNoeudFils.size(); i++)
        {
            if(!(member(lstNoeudFils[i], closed)))
            {
                tempG = cur->getG() + cur->getArc(i)->getWeight();

                if(!(member(lstNoeudFils[i], open)) || tempG < lstNoeudsFils[i]->getG())
                {
                    origin.push_back(cur);
                    lstNoeudFils[i].setG(tempG);
                    lstNoeudFils[i].setHeuristique(tempG + 0); //Add calcHeuritique.

                    if(!(member(lstNoeudFils[i], open))) open.push_back(lstNoeudsFils[i]);

                }
            }
        }
    }
    return NULL;
}

Noeud* getBestNode(const std::list<Noeud*>& open);

int* build_path(const std::list<Noeud*>& origin, const Noeud& final);

bool member(const std::list<Noeud*>& list, const Noeud* node)
{
    for(int i = 0; i < list.size(); i++)
    {
        if(list[i] == node) return true;
    }
    return false;
}
