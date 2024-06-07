#include <iostream>
#include <list>
#include <stack>
using namespace std;

struct WeightedEdge
{
    int endvertex;
    int weight;
    int activity_num;
    WeightedEdge(int endvertex = -1, int weight = -1, int activity_num = -1)
        :endvertex(endvertex), weight(weight), activity_num(activity_num){}
};


class LinkedDigraph 
{
public:
    LinkedDigraph(const int vertices = 0, int edges = 0);
    ~LinkedDigraph() {}
    bool IsEmpty() {return adjLists == 0;}
    void InsertEdge(int u, int v, int act = -1, int w = 1);
    void TopologicalOrder(bool print = true);
    void EarliestEventTime();
    void LatestEventTime();
    void ActivityTime();

    void PrintChart();

    void Setup1();
    void Setup2();
    
private:
    int n; // number of vertices
    int e; // number of edges
    list<WeightedEdge> *adjLists;
    int *count; // count[i] is the number of predecessors of vertex i (indegree)
    int *ee, *le;
    int *ea, *la;
    int *slack;
    bool *criticality;
    int *topologicalOrder;
};

LinkedDigraph::LinkedDigraph(const int vertices, int edges)
{
    n = vertices;
    e = edges;
    adjLists = new list<WeightedEdge>[n]; 

    count = new int[n]; fill(count, count + n, 0);

    ee = new int[n]; fill(ee, ee + n, 0);
    le = new int[n]; fill(le, le + n, 0);

    ea = new int[e]; fill(ea, ea + e, 0);
    la = new int[e]; fill(la, la + e, 0);
    slack = new int[e]; fill(slack, slack + e, 0);

    criticality = new bool[e]; fill(criticality, criticality + e, false);

    topologicalOrder = new int[n];
}

void LinkedDigraph::InsertEdge(int u, int v, int act, int w)
{
    // if (u > n || v > n) throw invalid_argument("At least one of the two vertices is too large.");
    adjLists[u].push_back(WeightedEdge(v, w, act));
    count[v]++;
}

void LinkedDigraph::Setup1()
{
    LinkedDigraph Gout(9, 11);
    Gout.InsertEdge(0, 1, 1, 6);
    Gout.InsertEdge(0, 2, 2, 4);
    Gout.InsertEdge(0, 3, 3, 5);

    Gout.InsertEdge(1, 4, 4, 1);
    Gout.InsertEdge(2, 4, 5, 1);
    Gout.InsertEdge(3, 5, 6, 2);

    Gout.InsertEdge(4, 6, 7, 9);
    Gout.InsertEdge(4, 7, 8, 7);
    Gout.InsertEdge(5, 7, 9, 4);

    Gout.InsertEdge(6, 8, 10, 2);
    Gout.InsertEdge(7, 8, 11, 4);

    Gout.InsertEdge(8, -1); // dummy vertex for the vertex without outdegree
    *this = Gout;
}

void LinkedDigraph::Setup2()
{
    LinkedDigraph Gout(10, 14);
    Gout.InsertEdge(0, 1, 1, 5);
    Gout.InsertEdge(0, 2, 2, 6);

    Gout.InsertEdge(1, 3, 3, 3);
    Gout.InsertEdge(2, 3, 4, 6);
    Gout.InsertEdge(2, 4, 5, 3);

    Gout.InsertEdge(3, 4, 6, 3);

    Gout.InsertEdge(3, 5, 7, 4);
    Gout.InsertEdge(3, 6, 8, 4);
    Gout.InsertEdge(4, 6, 9, 1);
    Gout.InsertEdge(4, 7, 10, 4);

    Gout.InsertEdge(6, 8, 11, 5);
    Gout.InsertEdge(7, 8, 12, 2);
    Gout.InsertEdge(5, 9, 13, 4);
    Gout.InsertEdge(8, 9, 14, 2);

    Gout.InsertEdge(9, -1); // dummy vertex for the vertex without outdegree
    *this = Gout;
}

void LinkedDigraph::TopologicalOrder(bool print)
{
    stack<int> s; // A stack holds 0-indegree vertices
    // Any container is good for this algorithm
    for (int i = 0; i < n; i++) 
        if (count[i] == 0) s.push(i);

    for (int i = 0; i< n; i++) {
        if (s.empty()) {
            // throw "Network has a cycle.";
            return;
        }
        int j = s.top(); s.pop();
        if (print)
            cout << j << " ";
        topologicalOrder[i] = j;
    
        list<WeightedEdge>::iterator ji = adjLists[j].begin();
        while (ji != adjLists[j].end()) {
            count[(*ji).endvertex]--;
            if (count[(*ji).endvertex] == 0) s.push((*ji).endvertex);
            ji++;
        }
    }
    cout << endl;
}

void LinkedDigraph::EarliestEventTime()
{
    // TopologicalOrder(false);
    for (int i = 0; i < n; i++) {
        int j = topologicalOrder[i];
        list<WeightedEdge>::iterator ji = adjLists[j].begin();
        while (ji != adjLists[j].end()) {
            if (ee[j] + (*ji).weight > ee[(*ji).endvertex]) {
                ee[(*ji).endvertex] = ee[j] + (*ji).weight;
            }
            ji++;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ee[i] << " ";
    }
    cout << endl;
}

void LinkedDigraph::LatestEventTime()
{
    // TopologicalOrder(false);
    for (int i = 0; i < n; i++) {
        le[i] = ee[n-1];
    }
    for (int i = n - 2; i >= 0; i--) {
        int j = topologicalOrder[i];
        list<WeightedEdge>::iterator ji = adjLists[j].begin();
        while (ji != adjLists[j].end()) {
            if (le[(*ji).endvertex] - (*ji).weight < le[j]) {
                le[j] = le[(*ji).endvertex] - (*ji).weight;
            }
            ji++;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << le[i] << " ";
    }
    cout << endl;
}

void LinkedDigraph::ActivityTime()
{
    for (int i = 0; i < n; i++) {
        list<WeightedEdge>::iterator ji = adjLists[i].begin();
        while (ji != adjLists[i].end()) {
            ea[(*ji).activity_num - 1] = ee[i];
            la[(*ji).activity_num - 1] = le[(*ji).endvertex] - (*ji).weight;
            ji++;
        }
    }
    // for (int i = 0; i < e; i++) {
    //     cout << ea[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < e; i++) {
    //     cout << la[i] << " ";
    // }
    // cout << endl;
    for (int i = 0; i < e; i++) {
        slack[i] = la[i] - ea[i];
        if (slack[i] == 0) {
            criticality[i] = true;
        }
    }
}

void LinkedDigraph::PrintChart()
{
    cout << "Activity  Earliest  Latest  Slack  Criticality" << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i < e; i++) {
        cout << "  " << i + 1 << "\t" << ea[i] << "\t" << la[i] << "\t" << slack[i] << "\t" << criticality[i] << endl;
    }
    cout << endl;
}

int main()
{
    LinkedDigraph G1(9, 11), G2(10, 14);
    
    G1.Setup1();
    cout << "Fig 6.39:" << endl;
    G1.TopologicalOrder();
    G1.EarliestEventTime();
    G1.LatestEventTime();
    G1.ActivityTime();

    cout << "activity table:\n";
    G1.PrintChart();
    // --------------------------------------------------
    cout << "--------------------------------------------------" << endl;
    cout << "--------------------------------------------------" << endl;
    
    G2.Setup2();
    cout << "Fig 6.44:" << endl;
    cout << "Topological order:\n";
    G2.TopologicalOrder();

    G2.EarliestEventTime();
    G2.LatestEventTime();

    G2.ActivityTime();

    cout << "activity table:\n";
    G2.PrintChart();

    return 0;
}