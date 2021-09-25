#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// num of vertices
#define n 10
#define p pair<int, int>
#define pa pair<int , p>
vector<pa> edges;
int pie[n], rank_[n], graph_pie[n] = {0};

int find_set(int x){
    if (pie[x] == x) return x;
    pie[x] = find_set(pie[x]);
    return pie[x];
}

bool union_set(int x, int y){
    int i = find_set(x);
    int j = find_set(y);
    if (i == j) return false;
    if (rank_[i] > rank_[j]) pie[j] = i;
    else if (rank_[i] < rank_[j]) pie[i] = j;
    else {
        pie[j] = i;
        rank_[i]++;
    }        
    return true;
}

void init(){
    edges.push_back(pa(2, p(0,1)));
    edges.push_back(pa(3, p(0,2)));
    edges.push_back(pa(3, p(0,3)));
    edges.push_back(pa(4, p(1,2)));
    edges.push_back(pa(3, p(1,4)));
    edges.push_back(pa(1, p(2,4)));
    edges.push_back(pa(6, p(2,5)));
    edges.push_back(pa(7, p(3,5)));
    edges.push_back(pa(8, p(4,5)));
    edges.push_back(pa(9, p(5,6)));
}
int main()
{
    init();
    // make set
    for (int i = 0; i < n; i++){
        pie[i] = i;
        rank_[i] = 0;
        graph_pie[i] = -1;
    }
    // -------------------------
    int mst = 0;
    sort(edges.begin(), edges.end());
    for (int i = 0; i < edges.size(); i ++){
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        int w = edges[i].first;

        // cout << u << "-" << v << endl;
        if (find_set(u) != find_set(v)){
            union_set(u, v);
            cout << u << "-" << v << endl;
            graph_pie[v] = u;
            mst += w;
        }
    }

    // for (int i = 0; i < 10; i++)
        // cout << graph_pie[i] << endl;
    cout << mst << endl;
    return 0;
}