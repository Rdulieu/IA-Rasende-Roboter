#include "noeud.h"
#include "global_base.h"
#include <iostream>
using namespace std;
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

Noeud::Noeud(int _id, int x, int y, QVector<P> discover,Bd * bdd, QVector<Noeud*> unicity)
{
    //cout << "Debut de Noeud" << endl;
    //GlobalBase& g_uniqueBase=GlobalBase::m_instance; //singleton
    //GlobalBase *g_uniqueBase=new GlobalBase();
    //cout << "Etape 1 de Noeud" << endl;
    this->id = _id;
    this->position[0] = x;
    this->position[1] = y;
    //cout << "Etape 2 de Noeud" << endl;
    this->map = bdd; //a tester si g nest init recupere la bdd unique generé dans ipseity tazlker
    //cout << "Etape 3 de Noeud" << endl;
    P coor;
    coor.i = x;
    coor.j = y;

    discover.append(coor);
    unicity.append(this);
    chercherFils(discover,this->map,unicity);
    //cout << "Noeud :Etape 4 de Noeud" << endl;

}

Noeud::Noeud(int _id, int x, int y, QVector<Noeud*> _lst,Bd * bdd,  QVector<Noeud*> unicity)
{
        cout << "OMG" << endl;
    //GlobalBase *g_uniqueBase=new GlobalBase();
    this->id = _id;
    this->position[0]=x;
    this->position[1]=y;
    this->lstNoeudFils = _lst;
    this->map = bdd; //a tester si g nest init recupere la bdd unique generé dans ipseity tazlker
    unicity.append(this);
}
/*
Noeud::Noeud(const Noeud& copy)
{
    if(*this !=  copy)
    {
        this->id = copy.id;
        this->position[0] = copy.position[0];
        this->position[1] = copy.position[1];
        this->heuristique = copy.heuristique;
        this->gCost = copy.gCost;
        *(this->getLstNoeudFils()) = copy.lstNoeudFils;
        this->haut = new Arc(*(copy.haut));
        this->bas = new Arc(*(copy.bas));
        this->gauche = new Arc(*(copy.gauche));
        this->droite = new Arc(*(copy.droite));
        this->map = copy.map;
    }
}
*/
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

void Noeud::setLstNoeudFils(QVector<Noeud*> _lst)
{
    this->lstNoeudFils = _lst;
}

QVector<Noeud*>* Noeud::getLstNoeudFils()
{
    return &lstNoeudFils;
}

QVector<Noeud*> Noeud::getNonModifiableLstNoeudFils()
{
    return lstNoeudFils;
}

// On cherche tous les noeuds fils, ce sont les cases qui sont accessibles partir de la case actuelle (Noeud parent)
void Noeud::chercherFils(QVector<P> discover,Bd* bdd, QVector<Noeud*> unicity)
{
    cout << "Noeud : ChercherFils" << endl;
    int i,j;
    int pos[4]={0,0,0,0};// : 0 haut 1 bas 2 gauche 3 droite, si pos[0]==1 alors il y a un obstacle horizontale au-dessus de notre case
    int count=0; // nombre de fils partir du noeud parent 15/06 9h41 ajout de l'initialisation
    P p; // anciennement int p[2];
    map = bdd;

    //cout << "Etape 1 de chercherFils" << endl;
    // On cherche quel(s) bords notre case est collÃ©e
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
    //cout << "Etape 2 de chercherFils" << endl;
    if(pos[0]==0) // On cherche la position d'un noeud fils s'il n'y a pas d'obstacle collÃ© au-dessus de notre case actuelle
    {
        //cout << "Etape 2 : IF de chercherFils et j:" << j << " i:" << i << endl;
        //cout << "Target is : " << map->getlist_murH(1,1) << endl;
        while(map->getlist_murH(i,j-1)==false && j>0) // On monte dans la grille tant qu'on ne rencontre pas de mur
        {
            //cout << "Etape 2 : WHILE de chercherFils et j:" << j << " i " << i << endl;
            j--;
        }
        count++;
        //Si la position n'est pas encore dÃ©couverte :
        p.i = i;
        p.j = j;
        if(!(std::find(discover.begin(), discover.end(),p) != discover.end()))
        {
            //cout << "Etape 2 : IF nb2 de chercherFils" << endl;
            discover.push_back(p);
            Noeud *filsHaut = new Noeud(count,i,j, discover,map,unicity);
            this->getLstNoeudFils()->push_back(filsHaut); // On ajoute le noeud fils la vectore des noeuds fils
            Arc *up = new Arc(1, filsHaut);
            this->setArc(0, up);
        }
        else
        {
            Noeud *n_searched;
            foreach (n_searched, unicity)
            {
                if(n_searched->getPosition()[0]==i && n_searched->getPosition()[1]==j)
                {
                    Arc *arcToSet = new Arc(1, n_searched);
                    this->setArc(0,arcToSet);
                    break; //to go out from the foreach statement because "life"
                }
            }
        }

    }
    else
    {
        //cout << "Etape 2 : ELSE de chercherFils" << endl;
        this->getLstNoeudFils()->push_back(NULL);
        this->setArc(0, NULL);
    }
        //cout << "Etape 3 de chercherFils" << endl;
    // On revient sur notre case de dÃ©part
    i = this->getPosition()[0];
    j = this->getPosition()[1];

    if(pos[1]==0) // Libre en bas
    {
        while(map->getlist_murH(i,j)==false && j<=15) // On descend dans la grille tant qu'on ne rencontre pas de mur
        {
            j++;
        }
        count++;
        //Si la position n'est pas encore dÃ©couverte :
        p.i = i;
        p.j = j;
        if(!(std::find(discover.begin(), discover.end(),p) != discover.end()))
        {
            discover.push_back(p);
            Noeud *filsBas = new Noeud(count,i,j,discover,map,unicity);

            this->getLstNoeudFils()->push_back(filsBas); // On ajoute le noeud fils la vectore des noeuds fils
            Arc *down= new Arc(1, filsBas);
            this->setArc(1, down);
        }
        else
        {
            Noeud *n_searched;
            foreach (n_searched, unicity)
            {
                if(n_searched->getPosition()[0]==i && n_searched->getPosition()[1]==j)
                {
                    Arc *arcToSet = new Arc(1, n_searched);
                    this->setArc(1,arcToSet);
                    break; //to go out from the foreach statement because "life"
                }
            }
        }
    }
    else
    {
        this->getLstNoeudFils()->push_back(NULL);
        this->setArc(1, NULL);

    }
        //cout << "Etape 4 de chercherFils" << endl;
    i = this->getPosition()[0];
    j = this->getPosition()[1];

    if(pos[2]==0) //Libre gauche
    {
        while(map->getlist_murH(i-1,j)==false && i>0) // On va gauche dans la grille tant qu'on ne rencontre pas de mur
        {
            i--;
        }
        count++;

        //Si la position n'est pas encore dÃ©couverte :
        p.i = i;
        p.j = j;
        if(!(std::find(discover.begin(), discover.end(),p) != discover.end()))
        {
            discover.push_back(p);
            Noeud *filsGauche = new Noeud(count,i,j, discover,map,unicity);

            this->getLstNoeudFils()->push_back(filsGauche); // On ajoute le noeud fils la vectore des noeuds fils
            Arc *left = new Arc(1, filsGauche);
            this->setArc(2, left);
        }
        else
        {
            Noeud *n_searched;
            foreach (n_searched, unicity)
            {
                if(n_searched->getPosition()[0]==i && n_searched->getPosition()[1]==j)
                {
                    Arc *arcToSet = new Arc(1, n_searched);
                    this->setArc(2,arcToSet);
                    break; //to go out from the foreach statement because "life"
                }
            }
        }
    }
    else
    {
        this->getLstNoeudFils()->push_back(NULL);
        this->setArc(2, NULL);

    }
    //cout << "Etape 5 de chercherFils" << endl;
    i = this->getPosition()[0];
    j = this->getPosition()[1];

    if(pos[3]==0) // Libre droite
    {
        while(map->getlist_murH(i,j)==false && i<=14) // On va droite dans la grille tant qu'on ne rencontre pas de mur
        {
            i++;
        }
        count++;
        //Si la position n'est pas encore dÃ©couverte :
        p.i = i;
        p.j = j;
        if(!(std::find(discover.begin(), discover.end(),p) != discover.end()))
        {
            discover.push_back(p);
            Noeud *filsDroite = new Noeud(count,i,j,discover,map,unicity);

            this->getLstNoeudFils()->push_back(filsDroite); // On ajoute le noeud fils la vectore des noeuds fils
            Arc *right = new Arc(1, filsDroite);
            this->setArc(3, right);
        }
        else
        {
            Noeud *n_searched;
            foreach (n_searched, unicity)
            {
                if(n_searched->getPosition()[0]==i && n_searched->getPosition()[1]==j)
                {
                    Arc *arcToSet = new Arc(1, n_searched);
                    this->setArc(3,arcToSet);
                    break; //to go out from the foreach statement because "life"
                }
            }
        }
    }
    else
    {
        this->getLstNoeudFils()->push_back(NULL);
        this->setArc(3, NULL);

    }
        //cout << "Etape 6 de chercherFils" << endl;
    i = this->getPosition()[0];
    j = this->getPosition()[1];

      //      cout << "fin de chercherFils" << endl;
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
        cout << "Bad option.\n";
    }
}

Bd* Noeud::getMap()
{
    return map;
}

void Noeud::setMap(Bd* bdd)
{
    this->map=bdd;
}

QVector<int> Noeud::astar(int final_x,int final_y, int robot)
{
    QVector<Noeud*> open, closed, origin;
    open.push_back(this);

    int f,tempG;
   // calcHeuristique(final_x,final_y); //a  corriger pour ne plus recevoir un noeud mais des coordoné
    setHeuristique(0); //en attendant de calculer l'heuristique
    f = getHeuristique();
    setG(0);

    //Tant qu'on est pas au noeud final.
    while(!(open.empty()))
    {
        //On récupére le meilleurs noeud selon f
        //On rest s'il est le noeud final.
        Noeud* cur = getBestNode(open);
        cout << "Noeud : Astar : Point de depart x :" << cur->getPosition()[0] << endl;
        cout << "Noeud : Astar : Point de depart y :" << cur->getPosition()[1] << endl;
        if(cur->getPosition()[0] == final_x && cur->getPosition()[1] == final_y)
        {
            cout << "Noeud : Astar : le noeud cibl a ete atteint"  << endl;
            origin.append(cur);
            return build_path(origin, cur, robot); //On retourne le chemin parcouru.
        }
        open.erase(open.begin()); // open.remove(cur)
        closed.push_back(cur);
        //Noeud* temp;
        //S'il ne l'est pas on met dans open tout les noeuds fils qui ne sont ni dans open,
        //ni dans closed et qui possede un coout de deplacement inferieur au noeud courrant.
        int i = 0;
        cout << "Noeud : Astar : avant le for" << endl;
        if(this->lstNoeudFils.begin() == this->lstNoeudFils.end())
            cout << "Noeud : Astar : begin et end de noeud fils sont egaux" << endl;
        /*for(QVector<Noeud*>::iterator it = lstNoeudFils.begin(); it != lstNoeudFils.end(); it++)*/
        if(this->lstNoeudFils.isEmpty())
            cout << "Noaud : Astar : lstNoeudFils est vide" << endl;
        Noeud* it;
        foreach(it , this->lstNoeudFils)
        {
            if(it!=NULL)
            {
                cout << "Noeud : Astar : iterations a travers les lstNoeudFils" << endl;
                if(!(member(it, closed)))
                {
                    cout << "Noeud : Astar : it  n est pas un membre de closed" << endl;
                    if(cur->getArc(i)!=NULL)
                    {
                        tempG = cur->getG() + cur->getArc(i)->getPoids();
                    }
                    else
                    {
                        tempG= cur->getG();
                    }
                    //temp = it;
                    if(!(member(it, open)) || tempG < cur->getG())
                    {
                        cout << "Noeud : Astar : it  n est pas membre de open ou son G est sup au g temporaore" << endl;
                        origin.push_back(cur);
                        cout << "Noeud : Astar : tempG vaut : " << tempG << endl;
                        it->setG(tempG);
                        it->setHeuristique(tempG + 0); //Add calcHeuritique.

                        if(!(member(it, open))) open.push_back(it);
                        cout << "Noeud : Astar : open est de taille : " << open.size() << endl;
                    }
                }
            }
            ++i;
        }
    }
    cout << "Noeud : Astar : Rien trouve" << endl;
    //Si échec on retourne null.
    QVector<int> fail;
    return fail;
}


Noeud* Noeud::getBestNode(const QVector<Noeud*> open)
{
    Noeud* res = open[0];
    int f(res->getHeuristique() + res->getG());

    //On parcours la vectore des fils et on recupere le meilleurs noeuds selon f.
    for(int i = 1; i<open.size(); i++) //warning here
    {
        if (f > open[i]->getG() + open[i]->getHeuristique()) res = open[i];
    }

    return res;
}

QVector<int> build_path(QVector<Noeud*> origin, Noeud* final, int robot)
{
    QVector<int> path/*(">")*/; //On alloue un tableau de 2 fois la taille de origin + final
    int j=0,i = 0;
    /*
    for(int k = 0; k < origin.size(); k++) //warning here
    {
        cout << "k vaut :" << k << endl;
        cout << "origin.size() vaut : "<< origin.size() <<endl;
        cout << "i vaut : "<< i <<endl;
        path.append(robot);
        ++i;
        //On cherche la direction
        while(j<origin[k]->getNonModifiableLstNoeudFils().size() && (k+1)<origin.size() && origin[k]->getNonModifiableLstNoeudFils()[j] != origin[k+1])
        {
            //j++;
            ++j;
        }
        cout << "CCCCCC" << endl;
        path.push_back(j);
        j=0;
        ++i;

    }
    cout << "BBBBBB" << endl;
    path.append(robot);
    while(origin[origin.size()-1]->getNonModifiableLstNoeudFils()[j] != final)
    {
        j++;
    }
    path.push_back(j);

    return path;


*/
    for(i=0; i<(origin.size()-1); ++i)
    {
        for(j=0; j<origin[i]->getNonModifiableLstNoeudFils().size();++j)
        {
            if(origin[i]->getNonModifiableLstNoeudFils()[j]!=NULL)
            {
                cout << origin[i]->getNonModifiableLstNoeudFils()[j]->getPosition()[0] << endl;
                if(origin[i]->getNonModifiableLstNoeudFils()[j]->getPosition()[0] == origin[i+1]->getPosition()[0]
                        && origin[i]->getNonModifiableLstNoeudFils()[j]->getPosition()[1] == origin[i+1]->getPosition()[1])
                {
                    path.append(robot);
                    path.append(j);
                }
            }
            cout << "j vaut"<< j << endl;
            cout << "i vaut"<< i << endl;
            cout << "path est de taille"<< path.size() << endl;
        }
    }
    return path;

}

bool member(const Noeud* node, const QVector<Noeud*> vector)
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
/*
bool Noeud::operator==(const Noeud& a)
{
    return this->isEqual(a);
}

bool Noeud::operator!=(const Noeud& a)
{
    return !(this->isEqual(a));
}*/
