//#include <QCoreApplication>
#include <iostream>
using namespace std;
#include "bd.h"
#include "global_base.h"
#include "noeud.h"
/*Bd* getBDD()
{
    return g_uniqueBase;
}*/
int main(int argc, char *argv[])
{
    Noeud *n=NULL;
    Bd* base=NULL;
    if(argc<13)return EXIT_FAILURE;
    int start_x,start_y;
    int m_CurrentStimulus[13]= {0}; //the first element is 0 so all the following will be zeroed too
    cout << "Main : Argv[0] est : "  << endl;
    cout << argv[0] <<endl;
    cout << "Main : Recuperation des arguments"  << endl;

    for(int i=1;i<14;++i)
    {
        m_CurrentStimulus[(i)-1]=atoi(argv[i]);
        cout << "Main : stimulus is : " << m_CurrentStimulus[(i)-1] << "."  << endl;
    }

    cout << "Main : stimulus is : " << m_CurrentStimulus << "."  << endl;
    //on cree la base de donne unique
    cout<<"Main : Setting up bdd"<<endl;

    base = new Bd(m_CurrentStimulus);

    cout << "Main : Trouvons les coordonees de depart du robot a bouger"  << endl;
    //trouvons quelle est le robot qui doit bouger en premier via la cible
    start_x=base->getRobot_Target_Coord().getX();
    start_y=base->getRobot_Target_Coord().getY();

    //generons le graphe
    QVector<P> discover;//position des case decouverte
    QVector<Noeud*> unicity; //stockage des noeud déjà crée
    cout << "Main : Construction du graphe"  << endl;
    n = new Noeud(0,start_x,start_y,discover,base,unicity); //unused -> bug ici
    cout <<"Main : Construction du graphe termine" << endl;

    //cherchons une solution au but et retournons là
    QVector<int> solution;
    cout <<"Main : Coordone target" << endl;
    cout << base->getTarget_Coord().getX() << endl;
    cout << base->getTarget_Coord().getY() << endl;
    cout <<"Main : Fin coordone target" << endl;
    solution = n->astar(base->getTarget_Coord().getX(),base->getTarget_Coord().getY(),base->getRobot_Target());
    //solution = n->astar(10,0,base->getRobot_Target());
    int showit;
    foreach(showit,solution)
    {
        cout << "Main : result : " << showit << endl;
    }

    return EXIT_SUCCESS;
}

