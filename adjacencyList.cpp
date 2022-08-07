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

        //sourceCity -> destinationCity, weight; pushback the pair of destin and weight at the source
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

    void testOne(string cityA, string cityB, int numConnections) {
        int countWeight = 1; //countWeight starts at 1 because all edges have weight = 1

        //checking if city was found or not
        if(cityAdjList.find(cityA) == cityAdjList.end()) {
            cout << cityA << " was not found" << endl;
        }
        //walking through graph to find cityA and cityB
        else {
            for (auto key: cityAdjList) {
                string city = key.first;
                list<pair<string, int>> neighbors = key.second;

                if (city == cityA) {
                    for (auto nbr: neighbors) {
                        string destination = nbr.first;
                        int weight = nbr.second;

                        //count weight until destination is reached
                        if(destination == cityB) {
                            break;
                        }
                        else {
                            countWeight = weight + countWeight;
                        }
                    }
                }
            }
        }

        //reporting to user if connection is in x or less connections
        if(numConnections >= countWeight) {
            cout << cityA << " to " << cityB << endl;
            cout << "Total connections: " << countWeight << endl;
        }
        else {
            cout << "No route exists." << endl;
        }

    }

    void testTwo() {
        //check to see if key even has those cities?
        //count edges
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

    worldAirline.testOne("Seoul, South Korea", "Seattle, United States", 7);
    worldAirline.testOne("Osaka, Japan", "Harare, Zimbabwe", 10);


    return 0;
}
