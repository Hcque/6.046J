#include <iostream>
using namespace std;

typedef int Vertex;

template <class Weight, int graph_size>
class Digraph
{
public:
    void set_distance(Vertex source, Weight distance[]) const;
protected:
    int count;
    Weight adj[graph_size][graph_size];
};

template <class Weight, int graph_size>
class Network: public Digraph<Weight, graph_size>
{
public:
    void minimal_spanning(Vertex source, Network<Weight, graph_size> &tree) const;
};


template<class Weight, int graph_size>
void Digraph<Weight, graph_size>:: set_distance(Vertex source, Weight distance[]) const
{
    Vertex v, w;
    bool found[graph_size];

}