#ifndef GLOBAL_BASE_H
#define GLOBAL_BASE_H
class Bd;
class GlobalBase
{
public:
    static GlobalBase& Instance();
    Bd* getBd();
    void setBd(Bd *bdd_c);
private:
    GlobalBase& operator= (const GlobalBase&){}
    GlobalBase (const GlobalBase&){}
    Bd *bdd;
    static GlobalBase m_instance;
    GlobalBase();
    ~GlobalBase();
};

#endif // GLOBAL_BASE_H
