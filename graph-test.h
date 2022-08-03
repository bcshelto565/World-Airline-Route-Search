#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>

using namespace std;

class graph{
    public:
        graph();
        graph(int num1);
        ~graph(){};
        void gPrint();
        void addEdge(int node1, int node2){ adj[node1][node2] = 1; };
        bool rConnectd(int node1, int node2);
    private:
        int num2;
        int adj[200][200];
};

graph::graph(){
};

graph::graph(int num1){
    for(int i=0; i<num1; i++){
        for(int j=0; j<num1; j++){
            adj[i][j] = 0;
        }
    }
    num2 = num1;
};

void graph::gPrint(){
    for(int i=0; i<num2; i++){
        cout << i << " -> ";
        for(int j=0; j<num2; j++){
            if(adj[i][j]){
                cout << j << " ";
            }
        }
        cout << endl;
    }
};

bool graph::rConnectd(int node1, int node2){
    if(adj[node1][node2]){
        return true;
    }
    else{
        return false;
    }
};