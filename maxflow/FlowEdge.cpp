#include <iostream>
using namespace std;

class FlowEdge {
private:
    int v, w;
    int capacity;
    int flow;
public:
    FlowEdge() {}
    FlowEdge(int v, int w, int cap, int f) : v(v), w(w), capacity(cap), flow(f) {}

    int from(){ return v; }
    int to(){ return w; }
    int getFlow(){ return flow; }
    int other(int vertice){
         if (v == vertice ) return w; 
         else if (w == vertice) return v;
         else return -1;
    }

    int residueCapacityTo(int vertice){
        if (v == vertice) return flow; // backward edge
        else if (w == vertice) return (capacity - flow); // forward edge
    }

    void addResidueFlowTo(int vertice, int delta){
        if (vertice == w) flow += delta; // forward edge 
        else if (vertice == v) flow -= delta; // backward edge
    }

    // friend bool operator== ( const FlowEdge& lhs, const FlowEdge& rhs){
    //     return lhs.from() == rhs.from() && lhs.from() == rhs.to();
    // }

    friend ostream& operator << (ostream& out, FlowEdge& fe){
        out << fe.v << " - " << fe.w << "\t" 
        << "cap: " << fe.capacity << " " << fe.flow << endl;
        return out;
    } 


};


// int main () 
// {
//     // test FlowEdge
//     FlowEdge e(12, 23, 3,2);
//     cout << e;

//     return 0;
// }