#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <stack>
#include <set>
#include <list>
#include <algorithm>
#include <random>

using namespace std;

class Node{
    public:
        int val;
        Node *next;
        Node();
        Node(Node* previous, int data);
        void newNode(Node* previous, int data);    
};

Node::Node(){
    val=0;
    next=NULL;
}

Node::Node(Node* head, int data){
    Node* newN = new Node();
    newN->val = data;
    head->next = newN;
};

void printList(Node *node) { 
    while (node != NULL) 
    { 
        cout << " " << node->val; 
        node = node->next; 
    } 
} 

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
          void BFS(int l);
          void bfsRoute(int ol, stack<int> placesToGo, Node* head);
          void DFS(int st);
          void dfsRoute(int st, stack<int> placesToGo, Node* head);
          bool bFs(int ori, int dst, int route[], int dist[]);
          void printRte(int ori, int dst);
          int rteFinder(int ori, int dst, Node* head);
          void Task3(int orig, stack<int> places2Go, Node* head);
     private: 
          int n;

           // You may want to use adjacent list implementation for sparse graph instead
};

int Graph::adj[140][140];

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
};



void Graph::BFS(int l){
    vector<bool> visits;
    visits.resize(140, false);
    list<int> Que;
    visits[l] = true;
    Que.push_back(l);
    int visi;
    while(!Que.empty()){
        l = Que.front();
        cout << l << " ";
        Que.pop_front();
        for(int i=0; i<140;i++){
            if(adj[l][i] == 1 && (!visits[i])){
                Que.push_back(i);
                visits[i] = true;
            }
        }
    }
};

void Append(Node* head, int p){
    if(head->next != NULL){
        Append(head->next, p);
    }
    else{
        Node* temp = new Node();
        temp->val = p;
        head->next = temp;
    }
}

void Graph::bfsRoute(int ol, stack<int> placesToGo, Node* head){
    vector<bool> visits;
    visits.resize(140, false);
    list<int> Que;
    int l;
    visits[ol] = false;
    bool visi = false;
    Que.push_back(ol);
    // placesToGo.push(ol);
    // int visi;
    while(!Que.empty()){
        l = Que.front();
        // cout << l << " ";
        Que.pop_front();
        for(int i=0; i<140;i++){
            /* stack<int> placCopy = placesToGo;
            while(!placCopy.empty()){
                cout << " " << placCopy.top();
                placCopy.pop();
            } */
            if(placesToGo.empty() && visi == false){
                // break;
                placesToGo.push(ol);
                visi = true;
            }
            else if(placesToGo.empty() && visi == true){
                break;
            }
            else if(i == ol && !placesToGo.empty() && visi == false){
                continue;
            }
            if(adj[l][i] == 1 && (!visits[i])){
                    // cout << l << " and " << i << endl;
                    if(searchStck(placesToGo, i)){
                        Append(head, l);
                        Append(head, i);
                        if(placesToGo.top() == i){
                            placesToGo.pop();
                        }
                        else{
                            stack<int> copyPlaces;
                            stack<int> copyPlaces1 = placesToGo;
                            while(!copyPlaces1.empty()){
                                if(copyPlaces1.top() != i){
                                    copyPlaces.push(copyPlaces1.top());
                                    copyPlaces1.pop();
                                    placesToGo = copyPlaces;
                                    l = i;
                                    continue;
                                }
                                else{
                                    copyPlaces1.pop();
                                    l = i;
                                    continue;
                                }
                            }
                        }
                    }
                    /* else{
                        for(int q=0; q<140; q++){
                            if(adj[i][q] && searchStck(placesToGo, q) && visits[q] != true){
                                Que.push_back(q);
                                visits[q] = true;
                                Append(head, i);
                                Append(head, q);
                                if(placesToGo.top() == i){
                                    placesToGo.pop();
                                    l = q;
                                    continue;
                                }
                                else{
                                    stack<int> copyPlaces;
                                    stack<int> copyPlaces1 = placesToGo;
                                    while(!copyPlaces1.empty()){
                                        if(copyPlaces1.top() != i){
                                            copyPlaces.push(copyPlaces1.top());
                                            copyPlaces1.pop();
                                            placesToGo = copyPlaces;
                                            l = q;
                                            continue;
                                        }
                                        else{
                                            copyPlaces1.pop();
                                            l = q;
                                            continue;
                                        }
                                    }
                                }
                            }
                            /* else{
                                for(int r=0; r<140; r++){
                                    if(adj[q][r] && searchStck(placesToGo, r) && visits[r] != true){
                                        Que.push_back(r);
                                        visits[r] = true;
                                        Append(head, q);
                                        Append(head, r);
                                        if(placesToGo.top() == q){
                                            placesToGo.pop();
                                        }
                                        else{
                                            stack<int> copyPlaces;
                                            stack<int> copyPlaces1 = placesToGo;
                                            while(!copyPlaces1.empty()){
                                                if(copyPlaces1.top() != q){
                                                    copyPlaces.push(copyPlaces1.top());
                                                    copyPlaces1.pop();
                                                    placesToGo = copyPlaces;
                                                    l = r;
                                                    continue;
                                                }
                                                else{
                                                    copyPlaces1.pop();
                                                    l = r;
                                                    continue;
                                                }
                                            }
                                        }
                                    }
                                    /* else{
                                        for(int s=0; s<140; s++){
                                            if(adj[r][s] && searchStck(placesToGo, s) && visits[s] != true){
                                                Que.push_back(s);
                                                visits[s] = true;
                                                Append(head, r);
                                                Append(head, s);
                                                if(placesToGo.top() == r){
                                                    placesToGo.pop();
                                                }
                                                else{
                                                    stack<int> copyPlaces;
                                                    stack<int> copyPlaces1 = placesToGo;
                                                    while(!copyPlaces1.empty()){
                                                        if(copyPlaces1.top() != r){
                                                            copyPlaces.push(copyPlaces1.top());
                                                            copyPlaces1.pop();
                                                            placesToGo = copyPlaces;
                                                            l = s;
                                                            continue;
                                                        }
                                                        else{
                                                            copyPlaces1.pop();
                                                            l = s;
                                                            continue;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    } */
                           //     }
                         //   } 
                       // }
                    // } 
                    Que.push_back(i);
                    visits[i] = true;
            }
        }
    }
    // printList(head);
}

/* void Graph::DFS(int st){
    cout << st << " ";
    vector<bool> visits;
    visits[st] = true;
    for(int i=0; i<140; i++){
        if(adj[st][i] == 1 && (!visits[i])){
            DFS(i, visits);
        }
    }
} */

/* void Graph::dfsRoute(int st, int ol, stack<int> placesToGo, Node* head){
    vector<bool> visits;
    bool foo = false;
    if(placesToGo.empty() && foo == false){
        placesToGo.push(ol);
    }
    else if(placesToGo.empty() && foo == true){
        return;
    }
    visits[st] = true;
    for(int i=0; i<140; i++){
        if(adj[st][i] == 1 && (!visits[i])){
            if(searchStck(placesToGo, i)){
                append(head, i);
                dfsRoute(i, ol, placesToGo, head);
            }
            
        }
    }
} */

bool Graph::bFs(int ori, int dst, int route[], int dist[]){
    list<int> queue;
    bool visited[140];
    for(int i=0; i<140; i++){
        visited[i] = false;
        dist[i] = INT8_MAX;
        route[i] = -1;
    }
    visited[ori] = true;
    dist[ori] = 0;
    queue.push_back(ori);
    while(!queue.empty()){
        int t = queue.front();
        // cout << t << " ";
        queue.pop_front();
        for(int i=0; i<140; i++){
            if(visited[adj[t][i]] == false){
                visited[adj[t][i]] = true;
                dist[adj[t][i]] = dist[t] + 1;
                route[adj[t][i]] = t;
                queue.push_back(adj[t][i]);
                if(adj[t][i] == dst){
                    return true;
                }
            }
        }
    }
    return false;
}

void Graph::printRte(int ori, int dst){
    int route[140], dist[140];
    if(bFs(ori, dst, route, dist) == false){
        cout << "No connection found between " << ori << " and " << dst << endl;
        return;
    }
    vector<int> path;
    int crawl = dst;
    path.push_back(crawl);
    while (route[crawl] != -1) {
        path.push_back(route[crawl]);
        crawl = route[crawl];
    }
    cout << "Shortest path length is : " << dist[dst];
    cout << "\nPath is::\n";
    for (int i = path.size() - 1; i >= 0; i--){
        cout << path[i] << " ";
    }
}


void stackShffle(stack<int> stackman){
    int GoatSize = stackman.size();
    stack<int> sacrifice;
    for(int g=0; g<GoatSize; g++){
        int temp = stackman.top();
        sacrifice.push(temp);
        stackman.pop();
    }
    stackman = sacrifice;
    return;
}

int Graph::rteFinder(int ori, int dst, Node* head){
    int route[140], dist[140];
    if(bFs(ori, dst, route, dist) == false){
        cout << "No connection found between " << ori << " and " << dst << endl;
        // cout << "Skipping set\n";
        return 0;
    }
    vector<int> path;
    int crawl = dst;
    path.push_back(crawl);
    cout << crawl << " is crawl." << endl;
    while (route[crawl] != -1) {
        path.push_back(route[crawl]);
        crawl = route[crawl];
    }
    for(int v=0; v<path.size(); v++){
        Append(head, path[v]);
    }
    return dist[dst];
}

void Graph::Task3(int orig, stack<int> places2Go, Node* head){
    int pop1 = places2Go.top();
    places2Go.pop();
    int size = places2Go.size();
    int length = rteFinder(orig, pop1, head);
    if(length == 0){
        for(int i=0; i<size; i++){
            // places2Go.push(pop1);
            // pop1 = places2Go.top();
            // places2Go.pop();
            stackShffle(places2Go);
            pop1 = places2Go.top();
            length = rteFinder(orig, pop1, head);
            if(length != 0){
                break;
            }
        }
    }
    cout << " ";
    if(length == 0){
        cout << "No route can be found for the supplied values. Try again with new input.\n";
        return;
    }
    int top;
    int connects;
    int pop;
    while(!places2Go.empty()){
        top = places2Go.top();
        places2Go.pop();
        if(places2Go.empty()){
            int length1;
            length1 = rteFinder(top, orig, head);// + length;
            if(length1 == 0){
                cout << "No route can be found for the supplied values of destinations back to the origin point. Try again with new input.\n";
                cout << "Disconnect occurs between " << top << " and " << orig << endl;
                // return;
                return;
            }
            length = length + length1;
            break;
        }
        else{
            pop = places2Go.top();
            places2Go.pop();
            int length1;
            length1 = rteFinder(top, pop, head); //+ length;
            if(length1 == 0){
                for(int i=0; i<size; i++){
                    stackShffle(places2Go);
                    pop = places2Go.top();
                    length1 = rteFinder(orig, pop, head);
                    if(length1 != 0){
                        break;
                    }
                }
            }
            cout << " ";
            if(length1 == 0){
                cout << "No route can be found for the supplied values of destinations. Try again with new input city.\n";
                cout << "The destinations fail for the city at int " << orig << endl;
                return;
            }
            continue;
        }
    }
    cout << "Route in circular fashion with shortest amount of connections is: \n";
    printList(head);
    cout << "\nConnection count is " << length << " including main destinations.\n";
    connects = length - size;
    cout << "Not including main destinations the connection count is " << connects << endl;
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
	  // printf("%s\n", line.c_str());
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
        Node* head = new Node();
        Node* nexNode = new Node();
        head->val = originI;
        // head->next = NULL;
        stack<int> destinations;
        for(int d=0; d<140; d++){
            if(Graph::adj[originI][d]){
                destinations.push(d);
            }
        }
        int e = destinations.top();
        head->next = nexNode;
        nexNode->val = e;
        int f = destinations.size();
        vector<bool> visited(140, false);

        /*
        cout << "Destinations size is " << destinations.size() << endl;
        stack<int> desCopy1 = destinations;
        stack<int> desCopy = destinations;
        cout << "These are the destination integers: ";
        while(!desCopy.empty()){
            cout << desCopy.top();
            desCopy.pop();
            cout << ", ";
            continue;
        }
        cout << endl;
        stackShffle(desCopy1);
        cout << "These are the destination integers 'shuffled': ";
        while(!desCopy1.empty()){
            cout << desCopy1.top();
            desCopy1.pop();
            cout << ", ";
            continue;
        }
        cout << "\n---------------------------------------------\n";
        */

        // graph.BFS(originI);
        // graph.bfsRoute(originI, destinations, nexNode);
        // graph.Task3(originI, destinations, head);
        graph.rteFinder(1, 88, head);
        printList(head);
        // graph.DFS(originI, visited);
        // graph.printRte(88, 1);
        
       //* if(ptask == 5){
       /* while(!destinations.empty()){
            for(int h=0; h<140; h++){
                // cout << "For loop 1 is starting...\n";
                if(graph.adj[destinations.top()][h]){
                    if(searchStck(destinations, h) && destinations.top() != h){
                        cout << "Connection found between destinations " << destinations.top() << " and " << h << endl;
                        cout << "Popping " << h << " out of the stack and moving forward\n";
                        destinations.pop();
                    }
                }
                // continue;
            }
            if(!destinations.empty()){
                cout << "There is no direct path only including origin and destinations... running recursive check\n";
                destinations.pop();
                // routeFinder(nexNode->val, destinations.top(), nexNode, graph);
            } */
        // }
    //}
   //}
   /* print the graph */
   }
    // --------------------------------------------------------------------------------
   // graph printout is below, this should be uncommented out for the final submission
   // ----------------------------------------------------------------------------------

   cout << endl << "The graph generated can be represented by the following adjacent matrix : " << endl;
   cout << "-----------------------------------------------------------------------------------" << endl;
   // graph.print();
}
