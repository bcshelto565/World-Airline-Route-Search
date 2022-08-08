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

/*
 * Graph class: defines the adjacency list as an unordered map of source city and its neighbours
 */
class Graph {
    unordered_map<string, City*> graph; //graph list <string, City type pointer>

private:

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

            //if cityB is found at the front of the queue
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

    int shortestPathBFS(City* cityA, City* cityB) {
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

            //if cityB is found at the front of the queue
            if(temp == cityB) {
                int countPath = 0;

                //start at our leaf, stop when we've found the root, crawl back up until we reach root
                for(City* childNode = temp; childNode != cityA; childNode = childNode->parentCity) {
                    countPath++;
                }

                return countPath;
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

        //if failed to find source city, add to graph
        if(search == graph.end()) {
            City* newCity = new City(sourceCity);
            graph.insert(make_pair(sourceCity, newCity));
        }

        search = graph.find(destinationCity);

        //failed to find destination city, add to graph
        if(search == graph.end()) {
            City* newCity = new City(destinationCity);
            graph.insert(make_pair(destinationCity, newCity));
        }

        //create edge list
        graph[sourceCity]->edgeList.insert(make_pair(graph[destinationCity], weight));

    }

    //print graph function
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

    //function to address problem 1
    void testOne(string cityAName, string cityBName, int numConnections) {
        auto search = graph.find(cityAName);

        //failed to find source city
        if(search == graph.end()) {
            cout << cityAName << " not found." << endl;
            return;
        }

        search = graph.find(cityBName);

        //failed to find source city
        if(search == graph.end()) {
            cout << cityBName << " not found." << endl;
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

    //function to address problem 2
    void testTwo(string cityAName, string cityBName, string cityCName, string cityDName) {
        auto search = graph.find(cityAName);

        //failed to find source city
        if(search == graph.end()) {
            cout << cityAName << " not found." << endl;
            return;
        }

        search = graph.find(cityBName);

        //failed to find source city
        if(search == graph.end()) {
            cout << cityBName << " not found." << endl;
            return;
        }

        search = graph.find(cityCName);

        //failed to find source city
        if(search == graph.end()) {
            cout << cityBName << " not found." << endl;
            return;
        }

        search = graph.find(cityDName);

        //failed to find source city
        if(search == graph.end()) {
            cout << cityBName << " not found." << endl;
            return;
        }

        City* cityA = graph[cityAName];
        City* cityB = graph[cityBName];
        City* cityC = graph[cityCName];
        City* cityD = graph[cityDName];

        //shortest path from A->B;
        int pathAB = shortestPathBFS(cityA, cityB);
        cout << "A->B: " << pathAB << " " << endl;

        //shortest path from B->C
        int pathBC = shortestPathBFS(cityB, cityC);
        cout << "B->C: " << pathBC << " " << endl;

        //shortest path from C->D
        int pathCD = shortestPathBFS(cityC, cityD);
        cout << "C->D: " << pathCD << " " << endl;

        int totalPathDist = pathAB + pathBC + pathCD;

        //reporting to user if connection exists
        if(pathAB == -1) {
            cout << "No route exists." << endl;
        }
        else if(pathBC == -1) {
            cout << "No route exists." << endl;
        }
        else if(pathCD == -1) {
            cout << "No route exists." << endl;
        }
        else {
            cout << cityA->name << " to " << cityD->name << " through "
                 << cityB->name << " and " << cityC->name << endl;
            cout << "Total connections: " << totalPathDist << endl;
        }

    }

};


int main() {

    ifstream inputFile;
    inputFile.open("flight.txt", ios::in);
    char lineArr[256];
    Graph worldAirline;
    string line, node1, node2, cityA, cityB, cityC, cityD;
    int userChoice = -1;
    int userNumConnects = 0;

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

    do {
        cout << "\nPlease choose a program to run or enter 0 to exit: " << endl;
        cout << "Program 1: I am in city “A”, can I fly to city  “B”  with less than x connections? Give me the\n"
                "route with the smallest number of connections or tell me there is no such a route.\n"
                "\nProgram 2: Give me the route with the smallest number of connections from city “A” to city\n"
                "“D” through city “B” and “C”. (the order of  “B” and “C” is not important). Or\n"
                "tell me there is no such a route\n"
                "\nProgram 3: Print adjacency list"<< endl;

        cout << "\nFOR ALL CITY INPUTS: Format is: City Name, Country Name" << endl;
        cout << "EXAMPLE CITY: New York City, United States" << endl;

        cout << "\nEnter either a 1, 2, 3, or 0: ";
        cin >> userChoice;

        if(userChoice == 1) {
            cin.ignore();
            cout << "Enter city A: ";
            getline(cin, cityA);
            cout << "Enter city B: ";
            getline(cin, cityB);
            cout << "Enter number of connections: ";
            cin >> userNumConnects;

            cout << endl << "PRINTING RESULT --------------------------------" << endl;
            worldAirline.testOne(cityA, cityB, userNumConnects);
            cout << "------------------------------------------------" << endl;

        }
        else if(userChoice == 2){
            cin.ignore();
            cout << "Enter city A: ";
            getline(cin, cityA);
            cout << "Enter city B: ";
            getline(cin, cityB);
            cout << "Enter city C: ";
            getline(cin, cityC);
            cout << "Enter city D: ";
            getline(cin, cityD);

            cout << endl << "PRINTING RESULT --------------------------------" << endl;
            worldAirline.testTwo(cityA, cityB, cityC, cityD);
            cout << "------------------------------------------------" << endl;
        }
        else if(userChoice == 3) {
            cout << endl << "PRINTING RESULT --------------------------------" << endl;
            worldAirline.printAdjList();
            cout << "------------------------------------------------" << endl;
        }
        else {
            if(userChoice > 3) {
                cout << "Incorrect choice, try again." << endl;
            }
        }

    }while(userChoice != 0);


    return 0;
}
