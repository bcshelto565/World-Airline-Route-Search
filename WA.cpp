#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <stack>
#include <set>

using namespace std;

class Node{
    public:
        int val;
        Node *next;
        Node();
        Node(Node* previous, int data);
        void newNode(Node** previous, int data);    
};

Node::Node(Node* head, int data){
    Node* newN = new Node();
    newN->val = data;
    head->next = newN;
};

void Node::newNode(Node** previous, int data){                  // code here causes compilation issues. need to fix pointer problems
    if(previous == NULL){
        cout << "Previous node cannot be NULL \n";
        return;
    }
    Node* newnode = new Node();
    newnode->val = data;
    newnode->next = previous->next;
    previous->next = newnode;
    return;
};

class Graph{
     public:
          Graph(int d);
          ~Graph(){};

          void print();
          void addEdge(int node1, int node2){ adj[node1][node2] = 1; };
          bool adjChck(string n1, string n2);
          int routeFinder(Node* head, int in, int out, stack<int> stack, set<int> set);
          void task3(map<const string, int> map1, Graph g);
          static int adj[140][140];
     private: 
          int n;
           // You may want to use adjacent list implementation for sparse graph instead
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

/* int Graph::routeFinder(Node* head, int in, int out, stack<int> stack, set<int> set){
    if(adj[in][out]){
        if(set.find(out) != set.end()){
            cout << stack.top() << " is being popped as the top element for being in the stack\n";
            stack.pop();
        }
        return 0;
    }
    else{
        for(int e=0; e<140; e++){
            if(adj[in][e] && adj[e][out]){
                head->next = Node(head, e);
                cout << e << " is a connection between " << in << " and " << out << endl;
                return e;
            }
            else{
                continue;
            }
        }
    }
} */

// 

void Graph::task3(map<const string, int> map1, Graph g){
    
} 

/* int routefinder(int in, int out, stack<int> stack){
    
}*/

bool searchStck(stack<int> stck, int a){
    stack<int> stck2 = stck;
    int size = stck2.size();
    for(int i=0; i<size; i++){
        if(stck2.top() == a){
            return true;
        }
        else{
            stck2.pop();
            continue;
        }
        return false;
    }
}


struct strCmp {
    bool operator()( const string s1, const string s2 ) const {
      return s1 <s2;
    }
  };


/*to map a city name with an unique integer */


int main(int argc, char *argv[]){
   int i, j, node1, node2, n, ptask;
   string line, n3, task;
    map<const string, int> city;

   cout << "Please enter the number of cities in your graph: " << endl;
   cout << "---------------------------------------------------" << endl;
   getline(cin, n3);
   n = stoi(n3);
   cout << "What task are we currently testing for? (1-4): ";
   getline(cin, task);
   ptask = stoi(task);
   //cin >> n;
   //n = 140;
    Graph graph(n);
    /*string cityg1, cityg2, test;
    cout << "test test\n";
    getline(cin, test);
    //cin >> test;
    cout << "What are your two cities? city 1: ";
    getline(cin, cityg1);
    //cin >> cityg1;
    cout << "What are your two cities? city 2: ";
    getline(cin, cityg2);
    //cin >> cityg2; */
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
	  	//cout << "locate!" << line <<  line.length() << endl;
	  }
	  else{
	  	//cout << "NO!" << line <<  line.length() << endl;
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
   if(ptask = 3){
        // graph.task3(city, graph); this line won't work due to an issue with the "graph." part
        cout << "What is the origin city to be used for task 3? (case sensitive): ";
        string origin;
        getline(cin, origin);
        int originI, destCnt, minConn;
        originI = city[origin];
        Node* head;
        head->val = originI;
        head->next = NULL;
        stack<int> destinations;
        for(int d=0; d<140; d++){
            if(Graph::adj[originI][d]){
                destinations.push(d);
            }
        }
        // vector<int>::iterator itr;
        int e = destinations.top();
        // head->next = 
        newNode(*head, e);
        // head->next = nexNode;
        int f = destinations.size();
        for(int g=0; g<f; g++){
            for(int h=0; h<140; h++){
                if(Graph::adj[g][h]){
                    if(searchStck(destinations, h)){
                        cout << "Connection found between destinations " << g << " and " << h << endl;
                        cout << "Popping " << h << " out of the stack and moving forward\n";
                        destinations.pop();
                    }
                }
            }
        }
   }
   /*if(graph.adjChck(cityg1, cityg2)){
        cout << cityg1 << " and " << cityg2 << " are adjacent!! True!!\n";
   }
   else{
        cout << cityg1 << " and " << cityg2 << " are not adjacent!! False!!\n";
   }
   /* print the graph */

    // --------------------------------------------------------------------------------
   // graph printout is below, this should be uncommented out for the final submission
   // ----------------------------------------------------------------------------------

   cout << endl << "The graph generated can be represented by the following adjacent matrix : " << endl;
   cout << "-----------------------------------------------------------------------------------" << endl;
   // graph.print();
}
