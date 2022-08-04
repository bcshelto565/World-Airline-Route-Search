/*
 * Samantha Fisher, sjc0208
 * Group #14
 * Adjacency List
 */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
using namespace std;

class Graph {

    unordered_map<string, list<pair<string, int>>> cityAdjList; //adjacency list using stl unordered_map
                                                                //it is of key <<string> -> list<string, int>>

public:
    void addEdge(string sourceCity, string destinationCity, int weight) {

        //sourceCity -> destinationCity, weight; pushback the pair of destin and ID at the source
        cityAdjList[sourceCity].push_back(make_pair(destinationCity, weight));

    }

    //print list function
    void printAdjList() {
        for(auto p: cityAdjList) {
            string city = p.first;
            list<pair<string, int>> neighbors = p.second;

            cout << "Source: " << city << " --> " << endl;
            for(auto nbr: neighbors) {
                string destination = nbr.first;
                int weight = nbr.second;

                cout << destination << " " << weight << endl;
            }
            cout << endl;
        }
    }
};


int main() {

    ifstream inputFile;
    inputFile.open("flight.txt", ios::in);
    char lineArr[256];
    Graph worldAirline;
    string line, node1, node2;

    while(inputFile.getline(lineArr, 256)) {
        line = lineArr;

        //if line contains From: erase the leading From: and spaces and save source city into node1
        if(line.find("From:", 0) == 0) {
            line.erase(0,7);
            node1 = line;
        }
        //else it is the To: cities, save those in node2 and add both to graph
        else {
            line.erase(0,7);
            node2 = line;
            worldAirline.addEdge(node1, node2, 1);
        }
    }

    inputFile.close();

    worldAirline.printAdjList();

    return 0;
}
