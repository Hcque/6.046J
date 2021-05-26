#pragma once

// #ifndef GRAPH_H
// #define GRAPH_H
#include <unordered_map>
#include <queue>
#include <vector>
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

    Vertex(N& d) : data(d), pie(-1), dist(-1), dtime(-1), ftime(-1) {}
    E operator [] (int i) { return adj[i]; }

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
    unordered_map<int, Vertex<N, E>*> V;
    int num_edges;    
    int time;

    vector<int> buf;
    void searchInit(int id);
    void relax(int uid, int vid);
public:
    bool addNode(int id, const N& data);
    // virtual bool addEdge(int uid, int vid, E& e) = 0;
    // virtual bool removeNode(int id) = 0;
    // virtual bool removeEdge(int uid, int vid) = 0;
    void BFS(int id);
    void DFS();
    void DFSVisit(int id);

};

template <typename N, typename E>
void Graph<N, E>::searchInit(int id){
    for (auto v: V){
        v->pie = -1;
        v->dist = -1;
        v->status = UNDISCOVER;
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
        for (auto& elem: V[id]->adj){
            if (V[elem->first]->status == UNDISCOVER){
                V[elem->first]->status = DISCOVER;
                V[elem->first]->dist = V[id]->dist + 1;
                V[elem->first]->pie = id;
                Q.push(elem->first);
            }
        }
        V[id]->status = VISITED;
    }
}
template <typename N, typename E>
void Graph<N, E>::DFS(){
    searchInit();
    time = 0;
    for (auto u: V){
        DFSVisit(u.first);
    }
}
template <typename N, typename E>
void Graph<N, E>::DFSVisit(int id){
    V[id]->status = DISCOVER;
    V[id]->dtime = ++time;
    for (auto v: V[id]->adj){
        if (v.first->status == UNDISCOVER){
            v.first->pie = id;
            DFSVisit(v.first);
        }
    }
    buf.push_back(id); // for tolopology
    V[id]->status = VISITED;
    V[id]->ftime = ++time;
}


template <typename N, typename E>
bool Graph<N, E>::addNode(int id, const N& data){
    if (this->V.find(id) == this->V.end()) return false;
    V[id] = new Vertex<N, E>(data);
    return true;
}

template <typename N, typename E>
void Graph<N, E>::relax(int uid, int vid){
    if (V[uid]->dist + V[uid]->adj[vid]->data < V[vid]->dist)
        V[vid]->dist = V[uid]->dist + V[uid]->adj[vid]->data;
        V[vid]->pie = uid;
}




// #endif