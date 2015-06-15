#include "noeud.h"
#include "global_base.h"
#include <vector>
#include <QMap>

// Constructeurs & Destructeurs
/* ULTRA DANGEREUSE UTILISE UNE BD NON EXISTENTE
Noeud::Noeud() : map(new Bd())
{
    this->map = new Bd();
}
*/
Noeud::~Noeud()
{
    delete haut;
    delete bas;
    delete gauche;
    delete droite;
    delete map;
}

Noeud::Noeud(int _id, int x, int y, std::vector<P> discover)
{
    cout << "Debut de Noeud" << endl;
    GlobalBase& g_uniqueBase=GlobalBase::Instance(); //singleton
    cout << "Etape 1 de Noeud" << endl;
    this->id = _id;
    this->position[0] = x;
    this->position[1] = y;
    cout << "Etape 2 de Noeud" << endl;
    this->map = g_uniqueBase.getBd(); //a tester si g nest init recupere la bdd unique gener� dans ipseity tazlker
    cout << "Etape 3 de Noeud" << endl;
    chercherFils(discover);
    cout << "Etape 4 de Noeud" << endl;
}

Noeud::Noeud(int _id, int x, int y, std::vector<Noeud*> _lst)
{
        cout << "OMG" << endl;
    GlobalBase& g_uniqueBase=GlobalBase::Instance(); //singloton
    this->id = _id;
    this->position[0]=x;
    this->position[1]=y;
    this->lstNoeudFils = _lst;
    this->map = g_uniqueBase.getBd(); //a tester si g nest init recupere la bdd unique gener� dans ipseity tazlker
}

Noeud::Noeud(const Noeud& copy)
{
    if(*this !=  copy)
    {
        this->id = copy.id;
        this->position[1] = copy.position[1];
        this->position[2] = copy.position[2];
        this->heuristique = copy.heuristique;
        this->gCost = copy.gCost;
        this->getLstNoeudFils() = copy.lstNoeudFils;
        this->haut = new Arc(*(copy.haut));
        this->bas = new Arc(*(copy.bas));
        this->gauche = new Arc(*(copy.gauche));
        this->droite = new Arc(*(copy.droite));
        this->map = new Bd(*map);
    }
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

void Noeud::setLstNoeudFils(std::vector<Noeud*> _lst)
{
    this->lstNoeudFils = _lst;
}

std::vector<Noeud*> Noeud::getLstNoeudFils()
{
    return this->lstNoeudFils;
}

// On cherche tous les noeuds fils, ce sont les cases qui sont accessibles partir de la case actuelle (Noeud parent)
void Noeud::chercherFils(std::vector<P> discover)
{
        cout << "Debut de chercherFils" << endl;
    int i,j;
    int pos[4]={0,0,0,0};// : 0 haut 1 bas 2 gauche 3 droite, si pos[0]==1 alors il y a un obstacle horizontale au-dessus de notre case
    int count=0; // nombre de fils partir du noeud parent 15/06 9h41 ajout de l'initialisation
    P p; // anciennement int p[2];
    GlobalBase& g_uniqueBase=GlobalBase::Instance(); //singloton
    map = g_uniqueBase.getBd(); //a tester si g nest init recupere la bdd unique gener� dans ipseity tazlker;
    cout << "Etape 1 de chercherFils" << endl;
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
    cout << "Etape 2 de chercherFils" << endl;
    if(pos[0]==0) // On cherche la position d'un noeud fils s'il n'y a pas d'obstacle collé au-dessus de notre case actuelle
    {
        cout << "Etape 2 : IF de chercherFils et j:" << j << " i:" << i << endl;
        while(map->getlist_murH(i,j-1)==false && j>0) // On monte dans la grille tant qu'on ne rencontre pas de mur
        {
            cout << "Etape 2 : WHILE de chercherFils et j:" << j << " i " << i << endl;
            j--;
        }
        count++;
        //Si la position n'est pas encore découverte :
        p.i = i;
        p.j = j;
        if(!(std::find(discover.begin(), discover.end(),p) != discover.end()))
        {
            cout << "Etape 2 : IF nb2 de chercherFils" << endl;
            discover.push_back(p);
            Noeud *filsHaut = new Noeud(count,i,j, discover);

            this->getLstNoeudFils().push_back(filsHaut); // On ajoute le noeud fils la vectore des noeuds fils
            Arc up(1, filsHaut);
            this->setArc(0, &up);
        }
    }
    else
    {
        cout << "Etape 2 : ELSE de chercherFils" << endl;
        this->getLstNoeudFils().push_back(NULL);
        this->setArc(0, NULL);
    }
        cout << "Etape 3 de chercherFils" << endl;
    // On revient sur notre case de départ
    i = this->getPosition()[0];
    j = this->getPosition()[1];

    if(pos[1]==0) // Libre en bas
    {
        while(map->getlist_murH(i,j)==false && j<=15) // On descend dans la grille tant qu'on ne rencontre pas de mur
        {
            j++;
        }
        count++;
        //Si la position n'est pas encore découverte :
        p.i = i;
        p.j = j;
        if(!(std::find(discover.begin(), discover.end(),p) != discover.end()))
        {
            discover.push_back(p);
            Noeud *filsBas = new Noeud(count,i,j,discover);

            this->getLstNoeudFils().push_back(filsBas); // On ajoute le noeud fils la vectore des noeuds fils
            Arc down(1, filsBas);
            this->setArc(1, &down);
        }
    }
    else
    {
        this->getLstNoeudFils().push_back(NULL);
        this->setArc(1, NULL);

    }
        cout << "Etape 4 de chercherFils" << endl;
    i = this->getPosition()[0];
    j = this->getPosition()[1];

    if(pos[2]==0) //Libre gauche
    {
        while(map->getlist_murH(i-1,j)==false && i>0) // On va gauche dans la grille tant qu'on ne rencontre pas de mur
        {
            i--;
        }
        count++;

        //Si la position n'est pas encore découverte :
        p.i = i;
        p.j = j;
        if(!(std::find(discover.begin(), discover.end(),p) != discover.end()))
        {
            discover.push_back(p);
            Noeud *filsGauche = new Noeud(count,i,j, discover);

            this->getLstNoeudFils().push_back(filsGauche); // On ajoute le noeud fils la vectore des noeuds fils
            Arc left(1, filsGauche);
            this->setArc(2, &left);
        }
    }
    else
    {
        this->getLstNoeudFils().push_back(NULL);
        this->setArc(2, NULL);

    }
    cout << "Etape 5 de chercherFils" << endl;
    i = this->getPosition()[0];
    j = this->getPosition()[1];

    if(pos[3]==0) // Libre droite
    {
        while(map->getlist_murH(i,j)==false && i<=14) // On va droite dans la grille tant qu'on ne rencontre pas de mur
        {
            i++;
        }
        count++;
        //Si la position n'est pas encore découverte :
        p.i = i;
        p.j = j;
        if(!(std::find(discover.begin(), discover.end(),p) != discover.end()))
        {
            discover.push_back(p);
            Noeud *filsDroite = new Noeud(count,i,j,discover);

            this->getLstNoeudFils().push_back(filsDroite); // On ajoute le noeud fils la vectore des noeuds fils
            Arc right(1, filsDroite);
            this->setArc(3, &right);
        }
    }
    else
    {
        this->getLstNoeudFils().push_back(NULL);
        this->setArc(3, NULL);

    }
        cout << "Etape 6 de chercherFils" << endl;
    i = this->getPosition()[0];
    j = this->getPosition()[1];

            cout << "fin de chercherFils" << endl;
  // inutile  return;
}

int Noeud::getG()
{
    return gCost;
}

void Noeud::setG(int val)
{
    gCost = val;
}

Arc* Noeud::getArc(int option)
{
    switch(option)
    {
    case 1:
        return bas;
        break;
    case 2:
        return gauche;
        break;
    case 3:
        return droite;
        break;
    case 0:
        return haut;
        break;
    default:
        return NULL;
    }
}

void Noeud::setArc(int option, Arc* val)
{
    switch(option)
    {
    case 0:
        haut = val;
        break;
    case 1:
        bas = val;
        break;
    case 2:
        gauche = val;
        break;
    case 3:
        droite = val;
        break;
    default :
        printf("Bad option.\n");
    }
}

Response Noeud::astar(int final_x,int final_y)
{
    std::vector<Noeud*> open, closed, origin;
    open.push_back(this);

    int f,tempG;
   // calcHeuristique(final_x,final_y); //a  corriger pour ne plus recevoir un noeud mais des coordon�
    setHeuristique(0); //en attendant de calculer l'heuristique
    f = getHeuristique();
    setG(0);

    //Tant qu'on est pas au noeud final.
    while(!(open.empty()))
    {
        //On récupère le meilleurs noeud selon f
        //On rest s'il est le noeud final.
        Noeud* cur = getBestNode(open);
        if(cur->getPosition()[0] == final_x && cur->getPosition()[1] == final_y)
        {
            return build_path(origin, cur); //On retourne le chemin parcouru.
        }
        open.erase(open.begin()); // open.remove(cur)
        closed.push_back(cur);
        Noeud* temp;
        //S'il ne l'est pas on met dans open tout les noeuds fils qui ne sont ni dans open,
        //ni dans closed et qui possède un coût de déplacement inférieur au noeud courrant.
        int i = 0;
        for(std::vector<Noeud*>::iterator it = lstNoeudFils.begin(); it != lstNoeudFils.end(); it++)
        {
            if(!(member(*it, closed)))
            {
                tempG = cur->getG() + cur->getArc(i)->getPoids();
                temp = *it;
                if(!(member(*it, open)) || tempG < temp->getG())
                {
                    origin.push_back(cur);
                    temp->setG(tempG);
                    temp->setHeuristique(tempG + 0); //Add calcHeuritique.

                    if(!(member(*it, open))) open.push_back(*it);

                }
            }
        }
    }
    //Si échec on retourne null.
    return NULL;
}


Noeud* Noeud::getBestNode(const std::vector<Noeud*> open)
{
    Noeud* res = open[0];
    int f(res->getHeuristique() + res->getG());

    //On parcours la vectore des fils et on recupère le meilleurs noeuds selon f.
    for(int i = 1; i<open.size(); i++) //warning here
    {
        if (f > open[i]->getG() + open[i]->getHeuristique()) res = open[i];
    }

    return res;
}

Response build_path(const std::vector<Noeud*> origin, Noeud* final)
{
    Response path(2*(origin.size()+1)); //On alloue un tableau de 2 fois la taille de origin + final
    int j(0);

    for(int i = 0, k = 0; i < 2*(origin.size()+1); i+=2, k++) //warning here
    {
        path[i] = 0;
        //On cherche la direction
        while(origin[k]->getLstNoeudFils()[j] != origin[k+1])
        {
            j++;
        }
        path[i+1] = j;

    }
    return path;
}

bool member(const Noeud* node, const std::vector<Noeud*> vector)
{
    for(int i = 0; i < vector.size(); i++) //warning here
    {
        if(vector[i] == node) return true;
    }
    return false;
}

bool Noeud::isEqual(const Noeud b) const
{
    return (id == b.id && position[1] == b.position[1] && position[2] == b.position[2] && heuristique == b.heuristique && gCost == b.gCost && lstNoeudFils == b.lstNoeudFils && haut == b.haut && bas == b.bas && gauche == b.gauche && droite == b.droite && map == b.map);
}

bool Noeud::operator==(const Noeud a)
{
    return this->isEqual(a);
}

bool Noeud::operator!=(const Noeud a)
{
    return !(this->isEqual(a));
}
