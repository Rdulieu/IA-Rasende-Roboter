
#include <iostream>
#include "global_base.h"
using namespace std;
GlobalBase GlobalBase::m_instance=GlobalBase();

GlobalBase::GlobalBase()
{
    cout<<"Creation de la base unique"<<endl;
}

GlobalBase::~GlobalBase()
{
    cout<<"Destruction de la base unique"<<endl;
}

GlobalBase& GlobalBase::Instance()
{
    return m_instance;
}

void GlobalBase::setBd(Bd *bdd_c)
{
    this->bdd=bdd_c;
}

Bd* GlobalBase::getBd()
{
    return this->bdd;
}
