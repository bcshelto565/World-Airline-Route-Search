/*
 * Samantha Fisher, sjc0208
 * Group #14
 * Adjacency List
 */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

/*
 * City class: defines a city's: name, edges, parent, and holds a bool for discovery
 */
class City {
public:
    City(string newName) {              //constructor
        name = newName;
    }
    unordered_map<City*, int> edgeList; //edge list <City type pointer, int for weight>
    string name;                        //name of city
    bool discovered;                    //discovery bool for marking a node as discovered or not
    City* parentCity;                   //city type pointer to point at city's parent node
};


class Graph {
    unordered_map<string, City*> graph; //graph list <string, City type pointer>

private:
    int countConnectionsDepthFirst(City* cityA, City* cityB, int numConnections, int recursionDepth) {
        auto search = cityA->edgeList.find(cityB);

        //we have found our destination, so return the number of connections
        if(search != cityA->edgeList.end()) {
            return recursionDepth + 1;
        }
        else if(recursionDepth < numConnections - 1){
            for(auto i: cityA->edgeList) {
               int temp = countConnectionsDepthFirst(i.first, cityB, numConnections, recursionDepth + 1);

               if(temp != -1) {
                   return temp;
               }
            }
        }
        //no route found
        return -1;
    }

    int countConnectionsBreadthFirst(City* cityA, City* cityB, int numConnections) {
        queue<City*> q;

        //make all cities undiscovered
        for(auto city: graph) {
            city.second->discovered = false;
        }

        //make first city discovered
        cityA->discovered = true;

        //push onto stack
        q.push(cityA);

        while(!q.empty()) {
            City* temp = q.front();
            if(temp == cityB) {
                int countPath = 0;

                //start at our leaf, stop when we've found the root, crawl back up until we reach root
                for(City* childNode = temp; childNode != cityA; childNode = childNode->parentCity) {
                    countPath++;
                }

                if(countPath < numConnections) {
                    return countPath;
                }
                else {
                    return -1;
                }
            }

            q.pop();

            for(auto nbr: temp->edgeList) {
                if(!nbr.first->discovered) {
                    nbr.first->discovered = true;
                    nbr.first->parentCity = temp;
                    q.push(nbr.first);
                }
            }
        }

        return -1;
    }

public:
    void addEdge(string sourceCity, string destinationCity, int weight) {

        auto search = graph.find(sourceCity);

        //failed to find source city
        if(search == graph.end()) {
            City* newCity = new City(sourceCity);
            graph.insert(make_pair(sourceCity, newCity));
        }

        search = graph.find(destinationCity);

        //failed to find destination city
        if(search == graph.end()) {
            City* newCity = new City(destinationCity);
            graph.insert(make_pair(destinationCity, newCity));
        }

        graph[sourceCity]->edgeList.insert(make_pair(graph[destinationCity], weight));

    }

    //print list function
    void printAdjList() {
        for(auto p: graph) {
            string cityName = p.first;
            City* city = p.second;

            cout << "Source: " << city->name << " --> " << endl;
            for(auto nbr: city->edgeList) {
                City* destinationCity = nbr.first;
                int weight = nbr.second;

                cout << destinationCity->name << " " << weight << endl;
            }
            cout << endl;
        }
    }

    void testOne(string cityAName, string cityBName, int numConnections) {
        auto search = graph.find(cityAName);

        //failed to find source city
        if(search == graph.end()) {
            cout << cityAName << "not found." << endl;
            return;
        }

        search = graph.find(cityBName);

        //failed to find source city
        if(search == graph.end()) {
            cout << cityBName << "not found." << endl;
            return;
        }

        City* cityA = graph[cityAName];
        City* cityB = graph[cityBName];

        //call the BFS function to count connections between cityA and cityB
        int jumps = countConnectionsBreadthFirst(cityA, cityB, numConnections);

        //reporting to user if connection is in x or less connections
        if(jumps == -1) {
            cout << "No route exists." << endl;
        }
        else {
            cout << cityA->name << " to " << cityB->name << endl;
            cout << "Total connections: " << jumps << endl;
        }
    }

    void testTwo() {

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

    //worldAirline.printAdjList();

    worldAirline.testOne("Seoul, South Korea", "Seattle, United States", 10);
    worldAirline.testOne("Seoul, South Korea", "Panama City, Panama", 10);
    worldAirline.testOne("Osaka, Japan", "Pittsburgh, United States", 20);

    //worldAirline.testTwo("Osaka, Japan", "Detroit, United States","Vienna, Austria","Harare, Zimbabwe");

    //worldAirline.testTwo("Osaka, Japan", "Caracas, Venezuela","Vienna, Austria","Harare, Zimbabwe");


    return 0;
}
