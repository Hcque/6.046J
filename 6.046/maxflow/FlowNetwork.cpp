#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include "FlowEdge.cpp"
using namespace std;

class FlowNetwork{
public: 
   int V; 
   int E; 
   vector< list<FlowEdge> > adj;

    FlowNetwork(ifstream& in){

    }

    int getV() {return V;}
    int getE() {return E;}
   
   list< FlowEdge > getadj(int v){
       return adj[v];
   }

   list< FlowEdge > edges(){
       list< FlowEdge > ans;
       for (int i = 0; i < V; i++){
           for (FlowEdge e: adj[i]){
               if (e.to() != i)
                   ans.push_back( e );
           }
       }
       return ans;
   }

    void addEdge(FlowEdge e){
        int v = e.from();
        int w = e.to();
        adj[v].push_back(e);
        adj[w].push_back(e);
        E++;
    }

    void addResidueFlowTo(FlowEdge e, int v, int bottle){
        for (list<FlowEdge>::iterator it = adj[v].begin(); it != adj[v].end(); it++ ){
            if (e.from() == it->from() && e.to() == it->to()){
                e.addResidueFlowTo(v, bottle);
                break;
            }
        }


    }




};