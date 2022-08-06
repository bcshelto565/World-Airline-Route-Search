#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>

using namespace std;

class Graph{
     public:
          Graph(int d);
          ~Graph(){};

          void print();
          void addEdge(int node1, int node2){ adj[node1][node2] = 1; };
          bool adjChck(string n1, string n2);
     private: 
          int n;
          int adj[140][140]; // You may want to use adjacent list implementation for sparse graph instead
};

Graph::Graph(int d){
    for (int i=0; i < d; i++){
        for (int j=0; j < d; j++){
            adj[i][j] = 0;
        }
    }
    n = d;
};

void Graph::print(){
    for (int i=0; i < n; i++){
        cout << i << " -> ";
        for (int j=0; j < n; j++){
            if (adj[i][j]){
                cout << j << " ";
            }
        }
        cout << endl;
    }

};

bool Graph::adjChck(string n1, string n2){
    map<const string, int> city1;
    ifstream cities;
    string line1;
    int o1, o2;
    cities.open("city.name", ios::in);
    for(int a=0; a<140; a++){
        getline(cities, line1);
        line1.erase(prev(line1.end()));
        city1[line1] = a;
    }
    if(!city1[n1]){
        cout << "city 1 not found! search term: " << n1 << endl;
        return false;
    }
    else if(!city1[n2]){
        cout << "city 2 not found! search term: " << n2 << endl;
        return false;
    }
    else{
        o1 = city1[n1];
        o2 = city1[n2];
        if(adj[o1][o2] = 1){
            return true;
        }
        else{
            return false;
        }
    }
    
}


struct strCmp {
    bool operator()( const string s1, const string s2 ) const {
      return s1 <s2;
    }
  };


/*to map a city name with an unique integer */
map<const string, int> city;

int main(int argc, char *argv[]){
   int i, j, node1, node2, n;
   string line, n3;


   cout << "Please enter the number of cities in your graph: " << endl;
   cout << "---------------------------------------------------" << endl;
   getline(cin, n3);
   n = stoi(n3);
   //cin >> n;
   //n = 140;
    Graph graph(n);
    string cityg1, cityg2, test;
    cout << "test test\n";
    getline(cin, test);
    //cin >> test;
    cout << "What are your two cities? city 1: ";
    getline(cin, cityg1);
    //cin >> cityg1;
    cout << "What are your two cities? city 2: ";
    getline(cin, cityg2);
    //cin >> cityg2; 
   char lineChar[256];

   ifstream cityFile;
   cityFile.open("city.name", ios::in);

   for (i = 0; i < n; i++){
      std::getline(cityFile, line);
      line.erase(std::prev(line.end()));
      // printf("The city %s\n", line.c_str());
      //fflush(stdout);
      // line = lineChar;
      city[line] = i;
      //city.insert({line, i});
      // printf(" is numbered as %d\n", i);
      // printf(" is numbered as %d\n", city[line]);
      //fflush(stdout);
      //cout << line << " is numbered as city " << city[line]<< endl;
   }

   cityFile.close();
   ifstream flightFile;
   flightFile.open("flight.txt", ios::in);

   while (flightFile.getline(lineChar, 256)){
      /* if line constains From: */
      line = lineChar;

      if (line.find("From:", 0) == 0 ){
          line.erase(0,7);
	  printf("%s\n", line.c_str());
          if(city.find(line) != city.end()){
	  	cout << "locate!" << line <<  line.length() << endl;
	  }
	  else{
	  	cout << "NO!" << line <<  line.length() << endl;
	  }
	  //cout << line << " " << city[line] << endl;
          node1 = city[line];
      } else {
          line.erase(0,7);
          node2 = city[line];
          graph.addEdge(node1,node2);
      }
   }
   flightFile.close();
   if(graph.adjChck(cityg1, cityg2)){
        cout << cityg1 << " and " << cityg2 << " are adjacent!! True!!\n";
   }
   else{
        cout << cityg1 << " and " << cityg2 << " are not adjacent!! False!!\n";
   }
   /* print the graph */
   cout << endl << "The graph generated can be represented by the following adjacent matrix : " << endl;
   cout << "-----------------------------------------------------------------------------------" << endl;
   graph.print();
}
