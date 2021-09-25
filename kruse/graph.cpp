#include <iostream>
#include <queue>
#include <list>

using namespace std;
// template <int max_size>
// struct Set
// {
//     bool iselement[max_size];
// };


// template <int max_size>
// class Digraph
// {
//     int count;
//     Set<max_size> neibours[max_size];
// };


// ################################################
// template <int max_size>
// class Digraph 
// {
//     bool adj[max_size][max_size];
// };


typedef int Vertex;
template <int max_size>
class Digraph
{
public:
    // search
    void depth_search(void (*visit)(Vertex&));
    void breath_search(void (*visit)(Vertex&));

    std::list<Vertex> neibours[max_size];

private:

    void traversal(Vertex v, bool visited[], void(*visit)(Vertex&));

};


template <int max_size>
void Digraph<max_size>::traversal(Vertex v, bool visited[], void(*visit)(Vertex&))
{
    visited[v] = true;
    visit(v);
    for (Vertex w: neibours[v]) if (!visited[w])
        traversal(w, visited, visit);
}

template <int max_size>
void Digraph<max_size>::depth_search(void (*visit)(Vertex&))
{
    bool visited[max_size] = {false};
    Vertex v;
    for (Vertex v = 0; v < neibours->size(); v++) if (!visited[v])
        traversal(v, visited, visit);
}

template <int max_size>
void Digraph<max_size>::breath_search(void (*visit)(Vertex&))
{
    bool visited[max_size] = {false};
    for (int v = 0; v < neibours->size(); v++) if (!visited[v]) {
        std::queue<Vertex> Q; Q.push(v); 
        while (!Q.empty()){
            Vertex w = Q.front(); Q.pop();
            visited[w] = true;
            visit(w);

            for (Vertex x: neibours[w]) if (!visited[x]){
                cout << "x" << x << endl;
                Q.push(x);
            }
        }
    }
}

// ################################

// class Edge;
// class Vertex
// {
//     Vertex* next;
//     Edge* firstE;
// };

// class Edge
// {
//     Edge* next_E;
//     Vertex* to;
// };

// class Digraph
// {
//     Vertex* firstV;
// };
void p(Vertex& v)
{
    cout << v << endl;
}

int main()
{

    Digraph<4> G;

    list<int> L1;
    L1.push_back(1); 
    L1.push_back(2); 
    G.neibours[0] = L1;

    list<int> L2;
    L2.push_back(2); 
    L2.push_back(3); 
    G.neibours[1] = L2;

    list<int> L4;
    G.neibours[2] = L4;

    list<int> L3;
    L3.push_back(0); 
    L3.push_back(1); 
    L3.push_back(2); 
    G.neibours[3] = L3;

    // G.depth_search(p);
    G.breath_search(p);

    return 0;
}


