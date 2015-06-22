#ifndef GLOBAL_BASE_H
#define GLOBAL_BASE_H
class Bd;
class global_base
{
public:
    static void setUniqueBase(Bd *bdd);
    static Bd *getUniqueBase();
private:
    Bd *g_uniqueBase;
};
#endif // GLOBAL_BASE_H
