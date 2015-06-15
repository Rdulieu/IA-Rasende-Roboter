#ifndef BD_H
#define BD_H

#include "IpseityTalker.h"
#include "coordonnees.h"

class Bd
{
private:
    Stimulus m_CurrentStimulus;
    Coordonnees list_target[17];
    bool list_murH[15][16];
    bool list_murV[16][15];

    int robot_target;
    int target;
    Coordonnees robot_target_coord;
    Coordonnees target_coord;


public:
    Bd();
    Bd(Stimulus);
    ~Bd();
    void builddata();
    Coordonnees getlist_target(int);
    bool getlist_murH(int,int);
    bool getlist_murV(int,int);
    Coordonnees getRobot_Target_Coord();
    Coordonnees getTarget_Coord();
    int getRobot_Target();
    int getTarget();
};

#endif // BD_H
