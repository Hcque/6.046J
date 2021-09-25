#include <iostream>
#include <cmath>
using namespace std;

#define high(x) ((int) (x/sqrt(u)))
#define low(x) ((int) (x%(int)sqrt(u)))

const int u = 16;

class vebTree{
    // int u;
    int min_, max_, w;
    int *summary;
    int **clusters;
    vebTree() {
        this->w = sqrt(u);
        min_ = max_ = -1;
        summary = nullptr;
        clusters = new int*[w];
        for (int i = 0; i < w; i++){
            clusters[i] = nullptr;
        }
    }
    void insert(int * V, int x){

        if (this->clusters[high(x)] == nullptr)
            insert(this->summary, high(x));
        insert(this->clusters[high(x)], low(x));
    }
    int successor(int x){

    }
    
};








int main()
{
    return 0;
}