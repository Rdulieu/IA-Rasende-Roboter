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

Noeud::Noeud(int _id, int x, int y, QVector<P> discover,Bd * bdd, QVector<Noeud*> *unicity)
{
    this->id = _id;
    this->position[0] = x;
    this->position[1] = y;

    this->map = bdd; //a tester si g nest init recupere la bdd unique generé dans ipseity tazlker
    P coor;
    coor.i = x;
    coor.j = y;

    discover.append(coor);
    unicity->append(this);
    chercherFils(discover,this->map,unicity);
    //cout << "Noeud :Etape 4 de Noeud" << endl;

}

//le noeud de queu?
Noeud::Noeud(int _id, int x, int y, QVector<Noeud*> _lst,Bd * bdd,  QVector<Noeud*> *unicity)
{
        cout << "OMG" << endl;
    //GlobalBase *g_uniqueBase=new GlobalBase();
    this->id = _id;
    this->position[0]=x;
    this->position[1]=y;
    this->lstNoeudFils = _lst;
    this->map = bdd; //a tester si g nest init recupere la bdd unique generé dans ipseity tazlker
    unicity->append(this);
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

void Noeud::chercherFils(QVector<P> discover,Bd* bdd, QVector<Noeud*>* unicity)
{
    int i=0,j=0;
//verifier les bord et ceux plein les mettre a nul
    //verifions qu'en haut il y a un mur ou une sortie du tableau
    //unicity->append(this);
    if((this->getPosition()[1]-1)>=0
            && bdd->getlist_murV(this->getPosition()[0],this->getPosition()[1]-1) != true)
    {
        //il faut parcourir vers le haut
        j=this->getPosition()[1];
        while((j-1)>=0
              && bdd->getlist_murV(this->getPosition()[0],j-1) != true)
        {
            j--;
        }
        //tester si le noeud n'existe pas déjà dans la liste des noeud decouvert et si oui le racorder
            //FOREACH
        Noeud *n_searched=NULL;
        QVector<Noeud*> tobesearched=*unicity;
        foreach (n_searched, tobesearched)
        {
            if(n_searched->getPosition()[0]==this->getPosition()[0]  //si on est sur la mêm colonne
                    && n_searched->getPosition()[1]==j) //et si le j quon a cocgé et identique
            {//alors c'est que ce noeud la pointe vers un noeud déjà decouvert
                //en ce cas on casse le foreach car on est au bons endroit
                break; //to go out from the foreach statement because "life"
            }
            n_searched=NULL;
        }
        if(n_searched==NULL) //alors c'est que le noeud na pas encore été decouvert
        {
            this->lstNoeudFils.push_back(new Noeud(0 /*id inutile*/,getPosition()[0],j,discover,bdd,unicity));
            this->haut = new Arc(0,this->lstNoeudFils[0]);
        }
        else
        {
            this->lstNoeudFils.push_back(n_searched);
            this->haut = new Arc(0,n_searched);
        }

    }
    else
    {
        //passer a nul l'arc et la lsite des neud fils
        //vers la haut c'est l'indice 0 donc le premier à ajouter
        this->haut=NULL;
        this->lstNoeudFils.push_back(NULL);
    }

    //verifions qu'en bas il y a un mur ou une sortie du tableau
    if(((this->getPosition()[1])+1)<16 //ce test sert vraimetn le tableau n'étant pas delimité
            && bdd->getlist_murV(this->getPosition()[0],this->getPosition()[1]) != true)
    {
            //il faut parcourir vers le bas
                j=this->getPosition()[1];
                while((j+1)<16
                      && bdd->getlist_murV(this->getPosition()[0],j) != true)
                {
                    j++;
                }
                //tester si le noeud n'existe pas déjà dans la liste des noeud decouvert et si oui le racorder
                    //FOREACH
                Noeud *n_searched=NULL;
                QVector<Noeud*> tobesearched=*unicity;
                foreach (n_searched, tobesearched)
                {
                    if(n_searched->getPosition()[0]==this->getPosition()[0]  //si on est sur la mêm colonne
                            && n_searched->getPosition()[1]==j) //et si le j quon a cocgé et identique
                    {//alors c'est que ce noeud la pointe vers un noeud déjà decouvert
                        //en ce cas on casse le foreach car on est au bons endroit
                        break; //to go out from the foreach statement because "life"
                    }
                    n_searched=NULL;
                }
                if(n_searched==NULL) //alors c'est que le noeud na pas encore été decouvert
                {
                    this->lstNoeudFils.push_back(new Noeud(0 /*id inutile*/,getPosition()[0],j,discover,bdd,unicity));
                    this->bas = new Arc(0,this->lstNoeudFils[1]);
                }
                else
                {
                    this->lstNoeudFils.push_back(n_searched);
                    this->bas = new Arc(0,n_searched);
                }

    }
    else
    {
        //passer a nul l'arc et la lsite des neud fils
        //vers la haut c'est l'indice 0 donc le premier à ajouter
        this->bas=NULL;
        this->lstNoeudFils.push_back(NULL);
    }


    //verifions qu'a droite il y a un mur ou une sortie du tableau
    if((this->getPosition()[0]+1) <16 //ce test sert vraimetn le tableau n'étant pas delimité
            && bdd->getlist_murH(this->getPosition()[0],this->getPosition()[1]) != true)
    {
                //il faut parcourir vers la droite
                j=this->getPosition()[0];
                while((j+1)<16
                      && bdd->getlist_murH(j,this->getPosition()[1]) != true)
                {
                    j++;
                }
                //tester si le noeud n'existe pas déjà dans la liste des noeud decouvert et si oui le racorder
                    //FOREACH
                Noeud *n_searched=NULL;
                QVector<Noeud*> tobesearched=*unicity;
                foreach (n_searched, tobesearched)
                {
                    if(n_searched->getPosition()[0]==j  //si le j quon a cocgé et identique
                            && n_searched->getPosition()[1]==this->getPosition()[1]) //si on est sur la même ligne
                    {//alors c'est que ce noeud la pointe vers un noeud déjà decouvert
                        //en ce cas on casse le foreach car on est au bons endroit
                        break; //to go out from the foreach statement because "life"
                    }
                    n_searched=NULL;
                }
                if(n_searched==NULL) //alors c'est que le noeud na pas encore été decouvert
                {
                    this->lstNoeudFils.push_back(new Noeud(0 /*id inutile*/,j,getPosition()[1],discover,bdd,unicity));
                    this->droite = new Arc(0,this->lstNoeudFils[2]);
                }
                else
                {
                    this->lstNoeudFils.push_back(n_searched);
                    this->droite = new Arc(0,n_searched);
                }

    }
    else
    {
        //passer a nul l'arc et la lsite des neud fils
        //vers la droite c'est l'indice 2 donc l'avant dernier à ajouter
        this->droite=NULL;
        this->lstNoeudFils.push_back(NULL);
    }

    //verifions qu'a gauche il y a un mur ou une sortie du tableau
    if((this->getPosition()[0]-1) >=0
            && bdd->getlist_murH(this->getPosition()[0]-1,this->getPosition()[1]) != true)
    {
        //ilfaut parcourir vers la gauche
        j=this->getPosition()[0];
        while((j-1)>=0
              && bdd->getlist_murH(j-1,this->getPosition()[1]) != true)
        {
            j--;
        }

        //tester si le noeud n'existe pas déjà dans la liste des noeud decouvert et si oui le racorder
            //FOREACH
        Noeud *n_searched=NULL;
        QVector<Noeud*> tobesearched=*unicity;
        foreach (n_searched, tobesearched)
        {
            if(n_searched->getPosition()[0]==j
                    && n_searched->getPosition()[1]==this->getPosition()[1])
            {//alors c'est que ce noeud la pointe vers un noeud déjà decouvert
                //en ce cas on casse le foreach car on est au bons endroit
                break; //to go out from the foreach statement because "life"7
            }
            n_searched=NULL;
        }
        if(n_searched==NULL) //alors c'est que le noeud na pas encore été decouvert
        {
            this->lstNoeudFils.push_back(new Noeud(0 /*id inutile*/,j,getPosition()[1],discover,bdd,unicity));
            this->gauche = new Arc(0,this->lstNoeudFils[3]);

        }
        else
        {
            this->lstNoeudFils.push_back(n_searched);
            this->gauche = new Arc(0,n_searched);
        }

    }
    else
    {
        //passer a nul l'arc et la lsite des neud fils
        //vers la gauche c'est l'indice 3 donc le dernier à ajouter
        this->gauche=NULL;
        this->lstNoeudFils.push_back(NULL);
    }

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
        //open.erase(open.begin()); // open.remove(cur)
        open.remove(this->getIndexOfNode(open,cur));
        closed.push_back(cur);
        //Noeud* temp;
        //S'il ne l'est pas on met dans open tout les noeuds fils qui ne sont ni dans open,
        //ni dans closed et qui possede un coout de deplacement inferieur au noeud courrant.
        int i = 0;
        cout << "Noeud : Astar : avant le for" << endl;
        Noeud* it;
        foreach(it , cur->lstNoeudFils)
        {
            if(it!=NULL)
            {
                cout << "Noeud : Astar : iterations a travers les lstNoeudFils" << endl;
                if(!(member(it, closed)))
                {
                    cout << "Noeud : Astar : it  n est pas un membre de closed" << endl;
                    tempG = cur->getG() + 1;
                    if(!(member(it, open)) || tempG <= cur->getG())
                    {
                        cout << "Noeud : Astar : it  n est pas membre de open ou son G est sup au g temporaore" << endl;
                        origin.push_back(cur);
                        cout << "Noeud : Astar : tempG vaut : " << tempG << endl;
                        it->setG(tempG);
                        it->setHeuristique(0); //Add calcHeuritique. SALE!
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

int Noeud::getIndexOfNode(const QVector<Noeud*> open, Noeud* toFind)
{
    int i=0;
    Noeud* it;
    foreach (it, open)
    {
        if(it->position[0]==toFind->position[0]
                && it->position[1]==toFind->position[1])
           return i;
        ++i;
    }
    return -1; //si on est là in peut se pendre
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
