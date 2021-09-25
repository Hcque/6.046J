#pragma once

#include <unordered_map>
#include <queue>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;



enum Status {UNDISCOVER, DISCOVER, VISITED};

template <typename N, typename E>
struct Vertex
{
    N data;
    unordered_map<int, E> adj;
    int pie, dist;
    int dtime, ftime;
    Status status;

    Vertex(const N& d) : data(d), pie(-1), dist(-1), dtime(-1), ftime(-1) {}

    E operator [] (int i) { return adj[i]; }
    bool operator < (Vertex v2) { return this->data < v2->data; }

};

template <typename E>
struct Edge{
    int uid, vid;
    E data;
    Edge(int u, int v, E& e) : uid(u), vid(v), data(e) {}
};

template <typename N, typename E>
class Graph{

protected:
    int num_edges;    
    int time;

    vector<int> buf;
    void searchInit(int id);
    void relax(int uid, int vid);
public:
    unordered_map<int, Vertex<N, E>*> V;

    bool addNode(int id, const N& data);
    bool addEdge(int uid, int vid, E& e);
    // virtual bool removeNode(int id) = 0;
    // virtual bool removeEdge(int uid, int vid) = 0;
    void BFS(int id);
    void DFS();
    void DFSVisit(int id);

};

template <typename N, typename E>
void Graph<N, E>::searchInit(int id){
    for (auto elem: V){
        elem.second->pie = -1;
        elem.second->dist = -1;
        elem.second->status = UNDISCOVER;
    }
    V[id]->dist = 0;
}
template <typename N, typename E>
void Graph<N, E>::BFS(int id){
    searchInit(id);

    queue<int> Q;
    Q.push(id);
    while ( ! Q.empty()){
        id = Q.front(), Q.pop();
        for (auto& elem: V[id]->adj){ // elem: intV ->  Edata
            if (V[elem.first]->status == UNDISCOVER){
                V[elem.first]->status = DISCOVER;
                V[elem.first]->dist = V[id]->dist + 1;
                V[elem.first]->pie = id;
                // cout << elem.first  << endl;
                Q.push(elem.first);
            }
        }
        V[id]->status = VISITED;
    }
}
template <typename N, typename E>
void Graph<N, E>::DFS(){
    searchInit(0);
    time = 0;
    for (auto u: V){
        if (V[u.first]->status == UNDISCOVER )
            DFSVisit(u.first);
    }
}
template <typename N, typename E>
void Graph<N, E>::DFSVisit(int id){
    V[id]->status = DISCOVER;
    V[id]->dtime = ++time;
    for (auto v: V[id]->adj){
        if (V[v.first]->status == UNDISCOVER){
            V[v.first]->pie = id;
            // cout << v.first << endl;
            DFSVisit(v.first);
        }
    }
    buf.push_back(id); // for tolopology
    V[id]->status = VISITED;
    V[id]->ftime = ++time;
            cout << id << endl;
}


template <typename N, typename E>
bool Graph<N, E>::addNode(int id, const N& data){
    if (this->V.find(id) != this->V.end()) return false;
    V[id] = new Vertex<N, E>(data);
    return true;
}

template<typename N, typename E>
bool Graph<N,E>::addEdge(int uid, int vid, E& e){
    assert (this->V.find(uid) != this->V.end() );
    assert (this->V.find(vid) != this->V.end() );

    if ( this->V[uid]->adj.find(vid) != this->V[uid]->adj.end() ) return false;
    this->V[uid]->adj[vid] = e;
    this->V[vid]->adj[uid] = e;
    this->num_edges++;
    return true;
}


template <typename N, typename E>
void Graph<N, E>::relax(int uid, int vid){
    if (V[uid]->dist + V[uid]->adj[vid]->data < V[vid]->dist)
        V[vid]->dist = V[uid]->dist + V[uid]->adj[vid]->data;
        V[vid]->pie = uid;
}


int amain()
{
    Graph<int, int> *G = new Graph<int, int>();
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

    // ----------------------------------
    // G->BFS(0);
    G->DFS();

    return 0;
}


