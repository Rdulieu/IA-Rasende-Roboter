#include <queue>
#include "noeud.h"

class Graph
{
private:
    Noeud* start;
public:
    Graph();
    Graph(Noeud* init);
    Graph(int x, int y, int id);
    Graph(const Graph& copy);
    ~Graph();

    Noeud* getStart();

    void init();
};

void addAll(std::vector<Noeud*> cont, std::queue<Noeud*>& q, std::vector<P>& v);
void link(Noeud* start, Noeud* target);
