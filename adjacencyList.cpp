/*
 * Samantha Fisher, sjc0208
 * Group ###
 * Adjacency List
 */
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <cstdlib>
#include <ctime>
using namespace std;

string city[140]; //global array to store raw city data

class Graph {
    unordered_map<string, list<pair<string, int>>> cityAdjList; //adjacency list using stl unordered_map
                                                                //it is of key <<string> -> list<string, int>>

public:
    void addEdge(string sourceCity, string destinationCity, int ID) {

        //preventative measure to avoid dupes (though this is not full-proof)
        if(sourceCity == destinationCity) {
            return;
        }
        //sourceCity -> destinationCity, ID; pushback the pair of destin and ID at the source
        else {
            cityAdjList[sourceCity].push_back(make_pair(destinationCity, ID));
        }

    }

    //print list function
    void printAdjList() {
        for(auto p: cityAdjList) {
            string city = p.first;
            list<pair<string, int>> neighbors = p.second;

            cout << "from: " << city << "-> ";
            for(auto nbr: neighbors) {
                string destination = nbr.first;
                int ID = nbr.second;

                cout << "to: " << destination << " " << ID << " || ";
            }
            cout << endl;
        }
    }
};

//generates a random number between 0-140
int genRand() {
    int myRand;

    myRand = rand() % 140;

    return myRand;
}

int main() {

    ifstream inputFile;
    inputFile.open("city.name", ios::in);
    char line[256];
    Graph worldAirline;
    srand(unsigned (time(0)));

    //get the lines of the city file and store in city[i]
    for (int i = 0; i < 140; i++){
        inputFile.getline(line,256);
        city[i] = line;
    }

    inputFile.close();

    //add cities to adjacency list to make a directed graph
    for(int i = 0; i < 140; i++) {

        worldAirline.addEdge(city[genRand()], city[genRand()], i);

    }

    worldAirline.printAdjList();

    return 0;
}
