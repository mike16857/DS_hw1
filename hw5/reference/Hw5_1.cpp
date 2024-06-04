#include <iostream>
#include <list>
#include <queue>

using namespace::std;

class Graph {
public:
    Graph(const int vertices = 0):n(vertices), e(0)
        {adjLists = new list<int>[n];}
    ~Graph(){}
    bool IsEmpty(){return adjLists == 0;}
    void InsertEdge(int u, int v);
    void DFS(int vbegin);
    void BFS(int v);
    void Components();
    void DfnLow(const int x);
    void Setup1();
    void Setup2();
    void Setup3();

    void hDFS(const int v);
    void DfnLow(const int u, const int v);
private:
    int n; // number of vertices
    int e; // number of edges
    list<int> *adjLists;
    bool *visited;
    int num;
    int* dfn;
    int* low;
};

void Graph::InsertEdge(int u, int v)
{
    if (u > n || v > n) throw invalid_argument("At least one of the two vertices is too large.");
    adjLists[u].push_back(v);
    adjLists[v].push_back(u);
}

void Graph::Setup1()
{
    Graph Gout(8);
    Gout.InsertEdge(0, 1);
    Gout.InsertEdge(0, 2);
    Gout.InsertEdge(1, 3);
    Gout.InsertEdge(2, 3);
    Gout.InsertEdge(4, 5);
    Gout.InsertEdge(5, 6);
    Gout.InsertEdge(6, 7);
    *this = Gout;
}

void Graph::Setup2()
{
    Graph Gout(8);
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

void Graph::Setup3()
{
    Graph Gout(10);
    Gout.InsertEdge(0, 1);
    Gout.InsertEdge(1, 2);
    Gout.InsertEdge(1, 3);
    Gout.InsertEdge(2, 4);
    Gout.InsertEdge(3, 4);
    Gout.InsertEdge(3, 5);
    Gout.InsertEdge(5, 6);
    Gout.InsertEdge(5, 7);
    Gout.InsertEdge(6, 7);
    Gout.InsertEdge(7, 8);
    Gout.InsertEdge(7, 9);
    *this = Gout;
}

void Graph::DFS(int vbegin)
{
    visited = new bool[n];
    fill(visited, visited + n, false);
    hDFS(vbegin);
    cout << endl;
    delete [] visited;
}

void Graph::hDFS(const int v)
{
    cout << v << " ";
    visited[v] = true;
    list<int>::iterator it;
    for (it = adjLists[v].begin(); it != adjLists[v].end(); it++)
        if (!visited[*it]) hDFS(*it);
}

void Graph::BFS(int v)
{
    visited = new bool [n];
    fill(visited, visited + n, false);
    cout << v << " ";
    visited[v] = true;
    queue<int> q;
    q.push(v);
    while (!q.empty()) {
        v = q.front();
        q.pop();
        list<int>::iterator it;
        for (it = adjLists[v].begin(); it != adjLists[v].end(); it++)
            if (!visited[*it]) {
                q.push(*it);
                cout << *it << " ";
                visited[*it] = true;
            }
    }
    cout << endl;
    delete [] visited;
}

void Graph::Components()
{
    visited = new bool [n];
    fill(visited, visited + n, false);
    for (int i = 0; i < n; i++)
        if (!visited[i]) {
            hDFS(i);
            cout << endl;
        }
    delete [] visited;
}

void Graph::DfnLow(const int x)
{
    num = 1;
    dfn = new int[n];
    low = new int[n];
    fill(dfn, dfn + n, 0);
    fill(low, low + n, 0);
    DfnLow(x, -1);
    cout << "    i : ";
    for (int i = 0; i < n; i++) cout << i << " ";
    cout << "\ndfn[i]: ";
    for (int i = 0; i < n; i++)
        cout << dfn[i] << " ";
    cout << "\nlow[i]: ";
    for (int i = 0; i < n; i++)
        cout << low[i] << " ";
    cout << endl;
    delete [] dfn;
    delete [] low;
}

void Graph::DfnLow(const int u, const int v)
{
    dfn[u] = low[u] = num++;
    list<int>::iterator it;
    for (it = adjLists[u].begin(); it != adjLists[u].end(); it++)
        if (dfn[*it] == 0) {
            DfnLow(*it, u);
            low[u] = min(low[u], low[*it]);
        }
        else if (*it != v) low[u] = min(low[u], dfn[*it]);
}

int main()
{
    Graph g1(8), g2(8), g3(10);

    g1.Setup1();
    cout << "For G1:\n";
    //BFS
    cout << "BFS:\n";
    cout << "Begin at vertex 0:\n";
    g1.BFS(0);
    cout << "Begin at vertex 3:\n";
    g1.BFS(3);
    cout << "Begin at vertex 7:\n";
    g1.BFS(7);
    cout << endl;

    // DFS
    cout << "DFS:\n";
    cout << "Begin at vertex 0:\n";
    g1.DFS(0);
    cout << "Begin at vertex 3:\n";
    g1.DFS(3);
    cout << "Begin at vertex 7:\n";
    g1.DFS(7);
    cout << endl;

    cout << "Components:\n";
    g1.Components();
    cout << endl;

    cout << "DfnLow:\n";
    cout << "Begin at vertex 3:\n";
    g1.DfnLow(3);
    cout << "-------------------------------\n";
    //------------------------------------
    g2.Setup2();
    cout << "For G2:\n";
    //BFS
    cout << "BFS:\n";
    cout << "Begin at vertex 0:\n";
    g2.BFS(0);
    cout << "Begin at vertex 3:\n";
    g2.BFS(3);
    cout << "Begin at vertex 7:\n";
    g2.BFS(7);
    cout << endl;

    // DFS
    cout << "DFS:\n";
    cout << "Begin at vertex 0:\n";
    g2.DFS(0);
    cout << "Begin at vertex 3:\n";
    g2.DFS(3);
    cout << "Begin at vertex 7:\n";
    g2.DFS(7);
    cout << endl;

    cout << "Components:\n";
    g2.Components();
    cout << endl;

    cout << "DfnLow:\n";
    cout << "Begin at vertex 1:\n";
    g2.DfnLow(1);
    cout << "-------------------------------\n";
    //------------------------------------
    g3.Setup3();
    cout << "For G3:\n";
    //BFS
    cout << "BFS:\n";
    cout << "Begin at vertex 0:\n";
    g3.BFS(0);
    cout << "Begin at vertex 3:\n";
    g3.BFS(3);
    cout << "Begin at vertex 7:\n";
    g3.BFS(7);
    cout << endl;

    // DFS
    cout << "DFS:\n";
    cout << "Begin at vertex 0:\n";
    g3.DFS(0);
    cout << "Begin at vertex 3:\n";
    g3.DFS(3);
    cout << "Begin at vertex 7:\n";
    g3.DFS(7);
    cout << endl;

    cout << "Components:\n";
    g3.Components();
    cout << endl;

    cout << "DfnLow:\n";
    cout << "Begin at vertex 3:\n";
    g3.DfnLow(3);

    return 0;
}
