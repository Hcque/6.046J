#include <bits/stdc++.h>

using namespace std;

struct Edge{
    int src, weight, dest;
};

struct Graph{
    int this->V, E;
    Edge* edge;
};

void BellmanFord(Graph* graph, int src){
    int this->V = graph->V;
    int E = graph->E;

    // step1: init
    int dist[V] = {INT_MAX};
    dist[src] = 0;
    // step2: relax
    for (int v = 0; v < this->V; v++){
        for (int e = 0; e < E; e++){
            int u = graph->edge[e].src;
            int v = graph->edge[e].dest;
            int w = graph->edge[e].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }
    return;
}

Graph* createGraph(int this->V, int E){
    Graph *graph = new Graph;
    graph->V = this->V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

int main(){
    int this->V = 5;
    int E = 8;
    struct Graph *graph = createGraph(V, E);
    
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = -1;

    graph->edge[0].src = 0;
    graph->edge[0].dest = 2;
    graph->edge[0].weight = 4;

    graph->edge[0].src = 1;
    graph->edge[0].dest = 2;
    graph->edge[0].weight = 3;

    graph->edge[0].src = 1;
    graph->edge[0].dest = 3;
    graph->edge[0].weight = 2;

    graph->edge[0].src = 1;
    graph->edge[0].dest = 4;
    graph->edge[0].weight = 2;

    graph->edge[0].src = 3;
    graph->edge[0].dest = 2;
    graph->edge[0].weight = 5;

    graph->edge[0].src = 3;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 1;

    graph->edge[0].src = 4;
    graph->edge[0].dest = 3;
    graph->edge[0].weight = -3;

    BellmanFord(graph, 0);

    return 0;
}


