#include "graph.h"


Graph::Graph()
{
    start = NULL;
}

Graph::Graph(Noeud* init)
{
    start = init;
}

Graph::Graph(int x, int y, int id)
{
    start = new Noeud(id, x, y);
	init();
}

Graph::Graph(const Graph& copy)
{
    start = copy.start;
}

Graph::~Graph()
{
    delete start;
}

void Graph::init()
{
	std::queue<Noeud*> toSearch;
	std::vector<P> discover;
    start->chercherFils(discover);
    addAll(start->getLstNoeudFils(), toSearch, discover);
	
    while(!(toSearch.empty()))
    {
        toSearch.front()->chercherFils(discover);
		addAll(toSearch.front()->getLstNoeudFils(), toSearch, discover);
		toSearch.pop();
	}
}

void addAll(std::vector<Noeud*> cont, std::queue<Noeud*>& q, std::vector<P> v)
{
	P temp;
	for(int k = 0; k<cont.size(); k++)
	{
		temp.i = cont[k]->getPosition()[0];
		temp.j = cont[k]->getPosition()[1];
        if((*(std::find(v.begin(), v.end(), temp)) == v.back()) && (temp != v.back())) q.push(cont[k]);
	}
}

void link(Noeud* start, Noeud* target)
{
    Arc* temp = new Arc(1, target);
	for (int i = 0; i<4; i++)
	{
		if(target->getArc(i)->getCible() == target)
		{
            start->getLstNoeudFils()[i] = target;
			switch(i)
			{
                case 0:
                    start->setArc(1, temp);
					break;
                case 1:
                    start->setArc(0, temp);
					break;
                case 2:
                    start->setArc(3, temp);
					break;
                case 3:
                    start->setArc(2, temp);
						
			}
		}
	}
}
