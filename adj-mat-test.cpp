#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include "graph-test.h"

using namespace std;

map<const string, int> place;

int main(){
    int j, k, node, node1, num;
    string Line;
    cout << "Number of places?: ";
    cin >> num;
    graph g(num);
    char lineC[256];
    ifstream placeFile;
    placeFile.open("city.name", ifstream::in);
    for(int i=0; i<num; i++){
        getline(placeFile, Line);
        Line.erase(prev(Line.end()));
        place[Line] = i;
    }
    placeFile.close();
    ifstream routesFile;
    routesFile.open("flight.txt", ifstream::in);
    while(routesFile.getline(lineC, 256)){
        Line = lineC;
        if(Line.find("From:", 0) == 0 ){
            Line.erase(0,7);
            // cout << Line.c_str();
            if(place.find(Line) != place.end()){
                cout << "located " << Line << " " << Line.length() << endl;
            }
            else{
                cout << "Nope " << Line << " " << Line.length() << endl;
            }
            node = place[Line];
        }
        else{
            Line.erase(0,7);
            node1 = place[Line];
            g.addEdge(node, node1);
        }
    }
    routesFile.close();
    cout << "file finished\n";
    g.gPrint();
}