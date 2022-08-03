#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>

using namespace std;

class gNode{
    public:
        int id;
        vector <int> connectionCnt;
};

string place[200];

int rando(int low, int high){
    int random_int;
    float rnge = (high - low) + 1;
    random_int = int(low + (rnge*rand()/(RAND_MAX + 1.0)));
    return random_int;
};

int main(int argc, char *argv[]){
    int j, k, neighNum, nodeCnt;
    vector <Node> grph;
    char line1[256];
    if(argc < 2){
        cout << "Using: " << argv[0] << " nodes" << endl;
        return 0;
    }
    ifstream placeFile;
    placeFile.open("city.name", ifstream::in);
    for(j=0; j<200; j++){
        placeFile.getline(line1, 256);
        place[j] = line1;
    }
    placeFile.close();
    nodeCnt = atoi(argv[1]);
    srand((unsigned) time(0));
    for(j=0; j<nodeCnt; j++){
        gNode node1;
        node1.id = j;
        neighNum = myRand(0,10);
        for(k=0; k<neighNum; k++){
            int neigh = myRand(0, nodeCnt-1);
            int f = 0;
            if(neigh == j){
                f = 1;
            }
            else{
                for(l=0; l<node1.neighbors.size(); l++){
                    if(node1.neighbors[l] == neigh){
                        f = 1;
                    }
                }
            }
            if(!f){
                node1.neighbors.push_back(neigh);
            }
        }
        grph.push_back(node1);
    }
    for(j=0; j<nodeCnt; j++){
        if(!grph[j].neighbors.size()){
            continue;
        }
        for(k=0; k<grph[j].neighbors.size(); k++){
            if(k){
                cout << "   " << place[grph[j].neigbors[k]] << endl;
            }
            else{
                cout << " " << place[grph[j].neighbors[k]] << endl;
            }
        }
    }
}