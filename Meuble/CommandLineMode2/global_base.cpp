#include "global_base.h"
/*
namespace
{
    Bd *g_uniqueBase;
}*/

void global_base::setUniqueBase(Bd *bdd)
{
    g_uniqueBase=bdd;
}

Bd* global_base::getUniqueBase(){return g_uniqueBase;}
