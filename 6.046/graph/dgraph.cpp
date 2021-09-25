#pragma once

#include "graph.cpp"
#include <cassert>
using namespace std;

template<typename N, typename E>
class DiGraph : public Graph<N, E> {

public:
    bool addEdge(int uid, int vid, E& e) ;
    vector<int> tolopologySort();
    void dijsktra(int src);
};

template<typename N, typename E>
bool DiGraph<N,E>::addEdge(int uid, int vid, E& e)  {
    assert (this->V.find(uid) != this->V.end() );
    assert (this->V.find(vid) != this->V.end() );

    if ( this->V[uid]->adj.find(vid) != this->V[uid]->adj.end() ) return false;
    this->V[uid]->adj[vid] = e;
    this->num_edges++;
    return true;
}

template<typename N, typename E>
vector<int> DiGraph<N,E>::tolopologySort(){
    Graph<N,E>::DFS();
    return this->buf;
}

template<typename N, typename E>
void DiGraph<N, E>::dijsktra(int src){
    Graph<N,E>::searchInit(src);
    priority_queue<Vertex<N,E>, vector<Vertex<N,E>>, greater<Vertex<N,E>>> Q;
    Q.push(*(this->V[src]));
    while (! Q.empty()){
       auto u = Q.top();
       Q.pop();
       for (auto n: u.adj){
           int vid = n.first;
           if (u.dist + u.adj[vid]->data < this->V[vid]->dist){
                this->V[vid]->dist = u.dist + u.adj[vid]->data;
                this->V[vid]->pie = 1;
           }
       }
    }

}

int main()
{
    DiGraph<int, int> *G = new DiGraph<int, int>();
    for (int i = 0; i <= 6; i++)
        G->addNode(i, 0);
    int d = 0;
    G->addEdge(0,3,d);
    G->addEdge(0,1,d);
    G->addEdge(0,2,d);
    G->addEdge(1,2,d);
    G->addEdge(1,4,d);
    G->addEdge(2,4,d);
    G->addEdge(2,5,d);
    G->addEdge(3,5,d);
    G->addEdge(4,5,d);
    G->addEdge(5,6,d);

    //see buf 
    vector<int> bu = G->tolopologySort();

    G->dijsktra(0);
    for (int i = 0; i <= 6; i++){
        cout << G->V[i]->pie  << endl;
    }



    return 0;
}

