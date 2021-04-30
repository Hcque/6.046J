#include <iostream>
using namespace std;

struct node {
    int *min, *max;
    node* summary;
    node* clusters[];
    node() : min(nullptr), max(nullptr) {};
};

node* vebTree(){
    return new node;
}


void insert(node* V, int x){
    if (V->min == nullptr)
        V->min =
    
}
int successor(){

}




int main()
{
    return 0;
}