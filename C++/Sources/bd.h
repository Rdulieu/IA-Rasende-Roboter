#ifndef BD_H
#define BD_H

#include "IpseityTalker.h"
#include "list.h"
#include "coordonnees.h"

class Bd
{
private:
    Stimulus m_currentStimulus;
    Coordonnees list_target[17];
    bool list_murH[15][16];
    bool list_murV[16][15];
public:
    Bd();
    Bd(Stimulus);
    ~Bd();
    void builddata();
    bool getlist_target(int);
    bool getlist_murH(int,int);
    bool getlist_murV(int,int);
};

#endif // BD_H
