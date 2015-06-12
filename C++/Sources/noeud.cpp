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

void Noeud::calcHeuristique(Noeud* final)
{
    setHeuristique(0);
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

// On cherche tous les noeuds fils, ce sont les cases qui sont accessibles partir de la case actuelle (Noeud parent)
void Noeud::chercherFils()
{
    int i,j;
    int pos[4]={0,0,0,0}; // : 0 haut 1 bas 2 gauche 3 droite, si pos[0]==1 alors il y a un obstacle horizontale au-dessus de notre case
    int count; // nombre de fils partir du noeud parent
    map = new Bd();
   // Bd *t=new Bd();

    // On cherche quel(s) bords notre case est collée
    if(map->getlist_murV(this->getPosition()[0],this->getPosition()[1])) // est-ce qu'il y a un mur vertical droite
        pos[3]=1;
    else if(map->getlist_murV(this->getPosition()[0]-1,this->getPosition()[1])) // est-ce qu'il y a un mur vertical gauche
        pos[2]=1;
    else if(map->getlist_murH(this->getPosition()[0],this->getPosition()[1])) // est-ce qu'il y a un mur horizontal en bas
        pos[1]=1;
    else if(map->getlist_murH(this->getPosition()[0],this->getPosition()[1]-1)) // est-ce qu'il y a un mur horizontal en haut
        pos[0]=1;

    // On cherche la position des noeuds fils possibles dans chaque direction
    i = this->getPosition()[0];
    j = this->getPosition()[1];

    if(pos[0]==0) // On cherche la position d'un noeud fils s'il n'y a pas d'obstacle collé au-dessus de notre case actuelle
    {
        while(map->getlist_murH(this->getPosition()[i],this->getPosition()[j]-1)==false) // On monte dans la grille tant qu'on ne rencontre pas de mur
        {
            j--;
        }
        count++;
        Noeud *filsHaut = new Noeud(count,i,j);

        this->getLstNoeudFils().push_back(filsHaut); // On ajoute le noeud fils la liste des noeuds fils
        Arc up(getPosition()[1]-j, filsHaut);
        this->setArc(0, &up);
    }
    else
    {
        this->getLstNoeudFils().push_back(NULL);
        this->setArc(0, NULL);
    }

    // On revient sur notre case de départ
    i = this->getPosition()[0];
    j = this->getPosition()[1];

    if(pos[1]==0) // Libre en bas
    {
        while(map->getlist_murH(this->getPosition()[i],this->getPosition()[j])==false) // On descend dans la grille tant qu'on ne rencontre pas de mur
        {
            j++;
        }
        count++;
        Noeud *filsBas = new Noeud(count,i,j);

        this->getLstNoeudFils().push_back(filsBas); // On ajoute le noeud fils la liste des noeuds fils
        Arc down(j-getPosition()[1], filsBas);
        this->setArc(1, &down);
    }
    else
    {
        this->getLstNoeudFils().push_back(NULL);
        this->setArc(1, NULL);

    }

    i = this->getPosition()[0];
    j = this->getPosition()[1];

    if(pos[2]==0) //Libre gauche
    {
        while(map->getlist_murH(this->getPosition()[i]-1,this->getPosition()[j])==false) // On va gauche dans la grille tant qu'on ne rencontre pas de mur
        {
            i--;
        }
        count++;
        Noeud *filsGauche = new Noeud(count,i,j);

        this->getLstNoeudFils().push_back(filsGauche); // On ajoute le noeud fils la liste des noeuds fils
        Arc left(i-getPosition()[0], filsGauche);
        this->setArc(1, &left);
    }
    else
    {
        this->getLstNoeudFils().push_back(NULL);
        this->setArc(2, NULL);

    }

    i = this->getPosition()[0];
    j = this->getPosition()[1];

    if(pos[3]==0) // Libre droite
    {
        while(map->getlist_murH(this->getPosition()[i],this->getPosition()[j])==false) // On va droite dans la grille tant qu'on ne rencontre pas de mur
        {
            i++;
        }
        count++;
        Noeud *filsDroite = new Noeud(count,i,j);

        this->getLstNoeudFils().push_back(filsDroite); // On ajoute le noeud fils la liste des noeuds fils
        Arc right(j-getPosition()[0], filsDroite);
        this->setArc(1, &right);
    }
    else
    {
        this->getLstNoeudFils().push_back(NULL);
        this->setArc(3, NULL);

    }

    i = this->getPosition()[0];
    j = this->getPosition()[1];

    return;
}

Response Noeud::astar(Noeud* final)
{
    std::list<Noeud*> open, closed, origin;
    open.push_back(this);

    int f,tempG;
    calcHeuristique(final);
    f = getHeuristique();
    setG(0);

    //Tant qu'on est pas au noeud final.
    while(!(open.empty()))
    {
        //On récupère le meilleurs noeud selon f
        //On rest s'il est le noeud final.
        Noeud* cur = getBestNode(open);
        if(cur == final)
        {
            return build_path(origin, final); //On retourne le chemin parcouru.
        }
        open.remove(cur);
        closed.push_back(cur);

        //S'il ne l'est pas on met dans open tout les noeuds fils qui ne sont ni dans open,
        //ni dans closed et qui possède un coût de déplacement inférieur au noeud courrant.
        int i = 0;
        for(std::list<Noeud*>::iterator it = lstNoeudFils.begin(); it != lstNoeudFils.end(); it++)
        {
            if(!(member(*it, closed)))
            {
                tempG = cur->getG() + cur->getArc(i)->getPoids();

                if(!(member(*it, open)) || tempG < *it->getG())
                {
                    origin.push_back(cur);
                    *it->setG(tempG);
                    *it->setHeuristique(tempG + 0); //Add calcHeuritique.

                    if(!(member(*it, open))) open.push_back(*it);

                }
            }
            i++;
        }
    }
    //Si échec on retourne null.
    return VoidResponse;
}

Noeud* getBestNode(const std::list<Noeud*>& open)
{
    Noeud* res = open[0];
    int f(res->getHeuritisque() + res->getG());

    //On parcours la liste des fils et on recupère le meilleurs noeuds selon f.
    for(int i = 1; i<open.size(); i++)
    {
        if (f > open[i]->getG() + open[i]->getHeuristique()) res = open[i];
    }

    return res;
}

Response build_path(const std::list<Noeud*>& origin, Noeud* final)
{
    Response path(2(origin.size()+1)); //On alloue un tableau de 2 fois la taille de origin + final
    int j(0);
    for(int i = 0, k = 0; i < 2(origin.size()+1); i+=2, k++)
    {
        path[i] = 0;
        //On cherche la direction
        while(origin[k].getLstNoeudFils()[j] != origin[k+1])
        {
            j++;
        }
        path[i+1] = j;

    }

}

bool member(const std::list<Noeud*>& list, const Noeud* node)
{
    for(int i = 0; i < list.size(); i++)
    {
        if(list[i] == node) return true;
    }
    return false;
}
