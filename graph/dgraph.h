#pragma once

#include "graph.h"
#include <cassert>
using namespace std;

template<typename N, typename E>
class DiGraph : public Graph<N, E> {

public:
    virtual bool addEdge(int uid, int vid, E& e);
    vector<int> tolopologySort();

    void dijsktra(int src);
};

template<typename N, typename E>
bool DiGraph<N,E>::addEdge(int uid, int vid, E& e){
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
    Q.push(this->V[src]);
    while (! Q.empty()){
       int uid = Q.top().first;
       Q.pop();

       for (auto n: this->V[uid]->adj){
           int vid = n.first;
           if (this->V[uid]->dist + this->V[uid]->adj[vid]->data < this->V[vid]->dist){
                this->V[vid]->dist = this->V[uid]->dist + this->V[uid]->adj[vid]->data;
                this->V[vid]->pie = uid;
           }
       }

    }


}

