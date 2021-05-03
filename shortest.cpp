#include <iostream>
using namespace std;

#define V 5
#define INF 99999


int dist[V][V];

void floydWarshell(int graph[][V]){
    int i, j, k;
    for (i = 0; i<V; i++){
        for (j = 0;j<V;j++){
            dist[i][j] = graph[i][j];
        }
    }

    for (k = 0; k < V; k++){
        for (i = 0; i< V; i++){
            for (j = 0; j < V; j++){
                cout << k << endl;
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

}

int main()
{

    int graph[V][V] = {
        {0, 3, 8, INF, -4},
        {INF, 0, INF, 1, 7},
        {INF, 4, 0, INF, INF},
        {2, INF, -5, 0, INF},
        {INF, INF, INF, 6, 0}
    };
    floydWarshell(graph);
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++){
            cout << dist[i][j];
        }
        cout << endl;
    }


    return 0;
}