#include <unordered_set>
#include <iostream>
#include <queue>
#include <vector>
#define INF 32766
#define NIL 32766
#define p pair<int, int>
#define pa pair<int, pair <int, int>>
using namespace std;
bool debug;
const int vertex = 7;

unordered_set<int> S;
vector<int> V, keys, pare;
priority_queue<pa, vector<pa>, greater<pa>> minE;
int G[vertex][vertex] = {0};
int W[vertex][vertex] = {
                    {0,2,3,3,0,0,0},
                    {2,0,4,0,3,0,0},
                    {3,4,0,0,1,6,0},
                    {3,0,0,0,0,7,0},
                    {0,3,1,0,0,8,0},
                    {0,0,6,7,8,0,9},
                    {0,0,0,0,0,9,0}
};

void init(){
    for (int i = 0; i < 7; i++){
        V.push_back(i);
        keys.push_back(INF);
        pare.push_back(INF);
    }
    // G[0][1] = 1; W[0][1] = 2;
    // G[0][2] = 1; W[0][2] = 3;
    // G[0][3] = 1;W[0][3] = 3;
    // G[1][2] = 1;W[1][2] = 4;
    // G[1][4] = 1;W[1][4] = 3;
    // G[2][5] = 1;W[2][5] = 6;
    // G[2][4] = 1;W[2][4] = 1;
    // G[3][5] = 1;W[3][5] = 7;
    // G[4][5] = 1;W[4][5] = 8;
    // G[5][6] = 1;W[5][6] = 9;
}
void add_queue(int x){
    for (int y = 0; y < 7; y++){
        if (W[x][y] != 0 && S.find(y) == S.end()){
            // cout << "x-y:" << x << y << endl;
            minE.push(pa(W[x][y], p(x, y)));
        }
    }
}

void MST_PRIM(int r = 0){
    // init
    keys[r] = 0;
    add_queue(r);
    S.insert(r);
    while ( ! minE.empty() ) {
        int u = minE.top().second.first;
        int v = minE.top().second.second;
        int c = minE.top().first;
        // cout << u << v << c << endl;
        minE.pop();

        if (c < keys[v]) {
            keys[v] = c;
            pare[v] = u;
            S.insert(u);
            add_queue(v);
        }
    }
}

int main()
{
    init();
    MST_PRIM();
    for (int i = 0; i < pare.size(); i++)
        cout << pare[i] << endl;
    return 0;
}

