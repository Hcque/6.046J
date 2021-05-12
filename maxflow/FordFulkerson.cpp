#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>
#include <vector>
#include "FlowEdge.cpp"
#include "FlowNetwork.cpp"

using namespace std;

class FordFulkerson{

    bool *marked; // for bfs 
    FlowEdge *edgeto; // store path, similar to parents
    double value;

    double excess(FlowNetwork G, int v){
        double ans = 0.0;
        for (FlowEdge e: G.adj[v]){
            if (e.from() == v) ans -= e.getFlow();
            else ans += e.getFlow();
        }
        return ans;
    }

    bool hasAugmentingPath( FlowNetwork G, int s, int t){

        marked = new bool[G.getV()];
        edgeto = new FlowEdge[G.getV()];
        fill(marked, marked + G.getV(), false);

        // bfs
        queue<int> Q;
        Q.push(s);
        marked[s] = true;
        while (!Q.empty() && !marked[t]) {
            int v = Q.front();
            Q.pop();
            for (FlowEdge e: G.adj[v]){
                int w = e.other(v);
                if ( e.residueCapacityTo(v) > 0 ){
                    if (!marked[w]){
                        edgeto[w] = e;
                        marked[w] = true;
                        Q.push(w);
                    }
                }
            }
        }
        return marked[t];
    }

    FordFulkerson ( FlowNetwork G, int s, int t ) {

        value = excess(G, t);
        while (hasAugmentingPath(G, s, t)){
            // calculate bottleneck capacity
            double bottle = INT64_MAX;
            for (int v = t; v != s; v = edgeto[v].other(v))
                bottle = min(bottle, edgeto[v].residueCapacityTo(v));

            // augment flow
            for (int v = t; v != s; v = edgeto[v].other(v))
                G.addResidueFlowTo(edgeto[v], v, bottle);

            value += bottle;
        }

    }

};

int main() 
{
    int V = 6;
    int E = 10;
    int s = 0, t = V - 1;

    ifstream in("input");
    FlowNetwork G(in);

    FordFulkerson maxflow(G, s, t);

}