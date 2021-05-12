#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
using namespace std;

#define n 7
#define INF 30000
#define p pair<int, int>
#define pa pair<int, p>

int W[n][n] = {
    {0,2,3,3,0,0,0},
                    {2,0,4,0,3,0,0},
                    {3,4,0,0,1,6,0},
                    {3,0,0,0,0,7,0},
                    {0,3,1,0,0,8,0},
                    {0,0,6,7,8,0,9},
                    {0,0,0,0,0,9,0}
};
unordered_set<int> S;
priority_queue<pa, vector<pa>, greater<pa>> minE;
vector<int> pie, keys;

void prim(int start = 0)
{
    for (int i = 0; i < n; i++){
        pie.push_back(INF);
        keys.push_back(INF);
    }
    int v = start;
    keys[v] = 0;
    S.insert(v);
    do {
        // add to queue
        for (int i = 0; i < n; i++){
            if (W[v][i] && S.find(i) == S.end())
                minE.push(pa(W[v][i], p(v, i)));
        }
        // extract min edge
        int c = minE.top().first;
        int u = minE.top().second.first;
        v = minE.top().second.second;
        minE.pop();

        if (c < keys[v]){
            keys[v] = c;
            pie[v] = u;
            S.insert(v);
        }
    } while (! minE.empty());
    
}

int main ()
{
    prim();
    for (int i = 0; i < n; i++){
        cout << pie[i];
    }
    return 0;
}