#include <iostream>
#include <list>
#include <stack>
using namespace std;

struct WeightedEdge
{
    int endvertex;
    int weight;
    WeightedEdge(int endvertex = -1, int weight = -1):endvertex(endvertex), weight(weight){}
};


class LinkedDigraph 
{
public:
    LinkedDigraph(const int vertices = 0):n(vertices)
        {adjLists = new list<int>[n]; count = new int[n];}
        // {adjLists = new list<WeightedEdge>[n];}
    ~LinkedDigraph(){}
    bool IsEmpty(){return adjLists == 0;}
    void InsertEdge(int u, int v, int w = 1);
    void TopologicalOrder();
    void Setup1();
    void Setup2();
    
private:
    int n; // number of vertices
    list<int> *adjLists;
    // list<WeightedEdge> *adjLists;
    int *count; // count[i] is the number of predecessors of vertex i (indegree)
};

void LinkedDigraph::InsertEdge(int u, int v, int w = 1)
{
    if (u > n || v > n) throw invalid_argument("At least one of the two vertices is too large.");
    // adjLists[u].push_back(WeightedEdge(v, w));
    adjLists[u].push_back(v);
    // adjLists[v].push_back(u);
}

void LinkedDigraph::Setup1()
{
    LinkedDigraph Gout(8);
    Gout.InsertEdge(0, 1);
    Gout.InsertEdge(0, 2);
    Gout.InsertEdge(1, 3);
    Gout.InsertEdge(2, 3);
    Gout.InsertEdge(4, 5);
    Gout.InsertEdge(5, 6);
    Gout.InsertEdge(6, 7);
    *this = Gout;
}

void LinkedDigraph::Setup2()
{
    LinkedDigraph Gout(8);
    Gout.InsertEdge(0, 1);
    Gout.InsertEdge(0, 2);
    Gout.InsertEdge(1, 3);
    Gout.InsertEdge(1, 4);
    Gout.InsertEdge(2, 5);
    Gout.InsertEdge(2, 6);
    Gout.InsertEdge(3, 7);
    Gout.InsertEdge(4, 7);
    Gout.InsertEdge(5, 7);
    Gout.InsertEdge(6, 7);
    *this = Gout;
}

// void LinkedDigraph::TopologicalOrder()
// { //the n vertices are listed in topological order
//     int top =-1; // stack top
//     for(int i = 0; i<n; i++) // create a linked stack of vertices with no
//         if(count[i] == 0) { 
//             count[i] = top; top = i;
//         } // no predecessors
//     for (i = 0; i< n; i++){
//         if (top ==-1) throw "Network has a cycle.";
//         int j = top; top = count[top]; // unstack a vertex
//         cout << j <<endl;
//         Chain<int>::ChainIterator ji = adjLists[j].begin();
//         while (ji) { // decrease the count of the successor vertices of j
//             count[*ji]--;
//             if(count[*ji]==0){count[*ji]=top; top=*ji;}// add *ji to stack
//             ji++;
//         }
//     }
// }

void LinkedDigraph::TopologicalOrder()
{
    stack<int> s; // A stack holds 0-indegree vertices
    // Any container is good for this algorithm
    for (int i = 0; i < n; i++) {
        if (count[i] == 0) s.push(i);
        for (i = 0; i< n; i++) {
            if (s.empty() ) throw "Network has a cycle.";
            int j = s.top(); s.pop();
            cout << j <<endl;
            // Chain<int>::ChainIterator ji = adjLists[j].begin();
            list<int>::iterator ji;
            // list<WeightedEdge>::iterator ji;
            ji = adjLists[j].begin();
            while (*ji) {
                count[*ji]--;
                if (count[*ji] == 0) s.push(*ji);
                ji++;
            }
        }
    }
}

