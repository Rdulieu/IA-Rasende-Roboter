#include <iostream>
#include <fstream>
using namespace std;
#include "bd.h"
#include "global_base.h"
#include "noeud.h"
#include "stdio.h"
int main(int argc, char *argv[])
{
    ofstream logmain;
    logmain.open ("logmain.log");
    Noeud *n=NULL;
    Bd* base=NULL;
    if(argc<13)
    {
        logmain << "Argument inferieur à 13 \n";
        return EXIT_FAILURE;
    }
    int start_x,start_y;
    int m_CurrentStimulus[13]= {0}; //the first element is 0 so all the following will be zeroed too
    logmain << "Main : Argv[0] est : "  << endl;
    logmain << argv[0] <<endl;
    logmain << "Main : Recuperation des arguments"  << endl;

    for(int i=1;i<14;++i)
    {
        m_CurrentStimulus[(i)-1]=atoi(argv[i]);
        logmain << "Main : case "<< i-1 << " du stimulus est  is : " << m_CurrentStimulus[(i)-1] << "."  << endl;
    }

    logmain << "Main : stimulus is : " << m_CurrentStimulus << "."  << endl;
    //on cree la base de donne unique
    logmain <<"Main : Setting up bdd"<<endl;

    base = new Bd(m_CurrentStimulus);
    //trouvons quelle est le robot qui doit bouger en premier via la cible
    start_x=base->getRobot_Target_Coord().getX();
    start_y=base->getRobot_Target_Coord().getY();

    //generons le graphe
    QVector<P> discover;//position des case decouverte
    QVector<Noeud*> unicity; //stockage des noeud déjà crée

    logmain << "Main : Construction du graphe"  << endl;
    n = new Noeud(0,start_x,start_y,discover,base,&unicity);
    logmain <<"Main : Construction du graphe termine" << endl;

    //cherchons une solution au but et retournons là
    QVector<int> solution;
    solution = n->astar(base->getTarget_Coord().getX(),base->getTarget_Coord().getY(),base->getRobot_Target());
    int showit;
    //preparation de la string de retour
    if(solution.size()>0)
    {
        //on traduis d'abord le vector de retour
        /*
         *vect  dir     ipseity
            0 ->haut      2

            1 ->bas       4

            2 ->droite    1

            3 ->gauche    3
        */
        for(showit =1;showit<solution.size();showit=2+showit)
        {
            switch (solution[showit]) {
            case 0:
                solution[showit]=2;
                break;
            case 1:
                solution[showit]=4;
                break;
            case 2:
                solution[showit]=1;
                break;
            /*case 3:
                solution[showit]=3;
                break;*/
            }
        }
        logmain << "Reponse donne est : " << endl;
        cout << ">";
        logmain  << ">";
        for(showit =0;showit<solution.size();++showit)
        {
            cout << solution[showit];
            logmain  << solution[showit];
            if(showit!=solution.size()-1)
                cout << ";";
                logmain  << ";";
        }
        logmain << "<";
        cout << "<";
    }
    else
    {
        logmain << "Aucune reponse \n";
        cout << "Fail" << endl;
    }
    //on nettoie la mémoire
    foreach(n,unicity)
    {
        delete n;
    }
    delete base;
    logmain.close();
    return EXIT_SUCCESS;
}

