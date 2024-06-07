#include <iostream>
#include <list>
#include <stack>
using namespace std;


class LinkedDigraph 
{
public:
    LinkedDigraph(const int vertices = 0):n(vertices)
        {adjLists = new list<int>[n]; 
         count = new int[n]; fill(count, count + n, 0);}
    ~LinkedDigraph(){}
    bool IsEmpty() {return adjLists == 0;}
    void InsertEdge(int u, int v);
    void TopologicalOrder();
    void Setup1();
    void Setup2();
    // void Setup3();
    
private:
    int n; // number of vertices
    list<int> *adjLists;
    int *count; // count[i] is the number of predecessors of vertex i (indegree)
};

void LinkedDigraph::InsertEdge(int u, int v)
{
    // if (u > n || v > n) throw invalid_argument("At least one of the two vertices is too large.");
    adjLists[u].push_back(v);
    count[v]++;
}

void LinkedDigraph::Setup1()
{
    LinkedDigraph Gout(9);
    Gout.InsertEdge(0, 1);
    Gout.InsertEdge(0, 2);
    Gout.InsertEdge(0, 3);

    Gout.InsertEdge(1, 4);
    Gout.InsertEdge(2, 4);
    Gout.InsertEdge(3, 5);

    Gout.InsertEdge(4, 6);
    Gout.InsertEdge(4, 7);
    Gout.InsertEdge(5, 7);

    Gout.InsertEdge(6, 8);
    Gout.InsertEdge(7, 8);

    Gout.InsertEdge(8, -1); // dummy vertex for the vertex without outdegree
    *this = Gout;
}

void LinkedDigraph::Setup2()
{
    LinkedDigraph Gout(10);
    Gout.InsertEdge(0, 1);
    Gout.InsertEdge(0, 2);

    Gout.InsertEdge(1, 3);
    Gout.InsertEdge(2, 3);
    Gout.InsertEdge(2, 4);

    Gout.InsertEdge(3, 4);

    Gout.InsertEdge(3, 5);
    Gout.InsertEdge(3, 6);
    Gout.InsertEdge(4, 6);
    Gout.InsertEdge(4, 7);

    Gout.InsertEdge(5, 9);
    Gout.InsertEdge(6, 8);
    Gout.InsertEdge(7, 8);
    Gout.InsertEdge(8, 9);

    Gout.InsertEdge(9, -1); // dummy vertex for the vertex without outdegree
    *this = Gout;
}

// void LinkedDigraph::Setup3()
// {
//     LinkedDigraph Gout(6);
//     Gout.InsertEdge(0, 1);
//     Gout.InsertEdge(0, 2);
//     Gout.InsertEdge(0, 3);

//     Gout.InsertEdge(1, 4);
//     Gout.InsertEdge(2, 4);
//     Gout.InsertEdge(2, 5);
//     Gout.InsertEdge(3, 4);
//     Gout.InsertEdge(3, 5);

//     Gout.InsertEdge(4, 6);
//     Gout.InsertEdge(5, 6);
//     *this = Gout;
// }


// void LinkedDigraph::TopologicalOrder()
// { //the n vertices are listed in topological order
//     int top = -1; // stack top
//     for(int i = 0; i<n; i++) // create a linked stack of vertices with no
//         if(count[i] == 0) { 
//             count[i] = top; top = i;
//         } // no predecessors
//     for (i = 0; i< n; i++){
//         if (top ==-1) throw "Network has a cycle.";
//         int j = top; top = count[top]; // unstack a vertex
//         cout << j <<endl;
//         list<int>::iterator ji = adjLists[j].begin();
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
    for (int i = 0; i < n; i++) 
        if (count[i] == 0) s.push(i);

    for (int i = 0; i < n; i++) {
        if (s.empty()) {
            throw "Network has a cycle.";
            // return;
        }
        int j = s.top(); s.pop();
        cout << j << " "; 

        list<int>::iterator ji = adjLists[j].begin();
        while (ji != adjLists[j].end()) {
            count[*ji]--;
            if (count[*ji] == 0) s.push(*ji);
            ji++;
        }
    }
    cout << endl;
}


int main()
{
    LinkedDigraph G1(9), G2(10);
    // LinkedDigraph G3(6);

    G1.Setup1();
    G1.TopologicalOrder();

    G2.Setup2();
    G2.TopologicalOrder();

    // G3.Setup3();
    // G3.TopologicalOrder();
    return 0;
}
