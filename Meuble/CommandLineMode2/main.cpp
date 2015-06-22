#include <QCoreApplication>
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
    Bd* base;
    base = new Bd(m_CurrentStimulus);
    cout << "Main : Trouvons les coordonees de depart du robot a bouger"  << endl;
    //trouvons quelle est le robot qui doit bouger en premier via la cible
    start_x=base->getRobot_Target_Coord().getX();
    start_y=base->getRobot_Target_Coord().getY();

    //generons le graphe
    QVector<P> discover;
    cout << "Main : Construction du graphe"  << endl;
    Noeud *n = new Noeud(0,start_x,start_y,discover,base); //unused -> bug ici

    cout <<"Main : Construction du graphe termine" << endl;

    //cherchons une solution au but et retournons là
    QVector<int> solution;
    solution = n->astar(base->getTarget_Coord().getX(),base->getTarget_Coord().getY(),base->getRobot_Target());
    int showit;
    foreach(showit,solution)
    {
        cout << "Main : result : " << showit << endl;
    }
    return EXIT_SUCCESS;
}
