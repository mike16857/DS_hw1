#include <iostream>
#include <malloc.h>

using namespace::std;

#define LARGE 99999
#define UNKNOWN 999
#define SELF 555

class MatrixWDigraph
{
public:
    MatrixWDigraph(const int verNum = 0);
    ~MatrixWDigraph(){}
    void SetWeight(int u, int v, int wei) {length[u][v] = wei;}
    void SetupG1();
    void SetupG1_1();
    void SetupG1_2();
    void SetupG2();
    void SetupG2_1();
    void SetupG3();

    void Dijkstra(const int n, const int v);
    void BellmanFord(const int n, const int v);
    void Floyd(const int n);

    int Choose(const int n);
    void PrintPath(const int u);
    void PrintBellman(const int n);
    void PrintFloyd(const int n);
private:
    int num;          // number of vertices
    int **length;
    int *dist;      // the shortest path length from beginning vertex to vertex i
    int *pre;       // the previous vertex on Shortest path
    bool *s;        // if the vertex is in set S
    int **chart;    // output chart
};

MatrixWDigraph::MatrixWDigraph(const int verNum):num(verNum)
{
    length = new int*[num];
    chart = new int*[num];
    for (int i = 0; i < num; i++) {
        length[i] = new int[num];
        chart[i] = new int[num];
        for (int j = 0; j < num; j++) {
            if (i == j) length[i][j] = 0;
            else length[i][j] = LARGE;
            chart[i][j] = LARGE;
        }
    }
    dist = new int[num];
    pre = new int[num];
    s = new bool[num];
}

void MatrixWDigraph::SetupG1()
{
    MatrixWDigraph Mout(8);
    Mout.SetWeight(1, 0, 300);
    Mout.SetWeight(2, 0, 1000);
    Mout.SetWeight(2, 1, 800);
    Mout.SetWeight(3, 2, 1200);
    Mout.SetWeight(4, 3, 1500);
    Mout.SetWeight(4, 5, 250);
    Mout.SetWeight(5, 3, 1000);
    Mout.SetWeight(5, 6, 900);
    Mout.SetWeight(5, 7, 1400);
    Mout.SetWeight(6, 7, 1000);
    Mout.SetWeight(7, 0, 1700);
    *this = Mout;
}

void MatrixWDigraph::SetupG1_1()
{
    MatrixWDigraph Mout(6);
    Mout.SetWeight(0, 1, 50);
    Mout.SetWeight(0, 2, 45);
    Mout.SetWeight(0, 3, 10);
    Mout.SetWeight(1, 2, 10);
    Mout.SetWeight(1, 3, 15);
    Mout.SetWeight(2, 4, 30);
    Mout.SetWeight(3, 0, 20);
    Mout.SetWeight(3, 4, 15);
    Mout.SetWeight(4, 1, 20);
    Mout.SetWeight(4, 2, 35);
    Mout.SetWeight(5, 4, 3);
    *this = Mout;
}

void MatrixWDigraph::SetupG1_2()
{
    MatrixWDigraph Mout(6);
    Mout.SetWeight(0, 1, 20);
    Mout.SetWeight(0, 2, 15);
    Mout.SetWeight(1, 0, 2);
    Mout.SetWeight(1, 4, 10);
    Mout.SetWeight(1, 5, 30);
    Mout.SetWeight(2, 3, 4);
    Mout.SetWeight(2, 5, 10);
    Mout.SetWeight(4, 3, 15);
    Mout.SetWeight(5, 3, 4);
    *this = Mout;
}

void MatrixWDigraph::SetupG2()
{
    MatrixWDigraph Mout(7);
    Mout.SetWeight(0, 1, 6);
    Mout.SetWeight(0, 2, 5);
    Mout.SetWeight(0, 3, 5);
    Mout.SetWeight(1, 4, -1);
    Mout.SetWeight(2, 1, -2);
    Mout.SetWeight(2, 4, 1);
    Mout.SetWeight(3, 2, -2);
    Mout.SetWeight(3, 5, -1);
    Mout.SetWeight(4, 6, 3);
    Mout.SetWeight(5, 6, 3);
    *this = Mout;
}

void MatrixWDigraph::SetupG2_1()
{
    MatrixWDigraph Mout(3);
    Mout.SetWeight(0, 1, 7);
    Mout.SetWeight(0, 2, 5);
    Mout.SetWeight(1, 2, -5);
    *this = Mout;
}

void MatrixWDigraph::SetupG3()
{
    MatrixWDigraph Mout(3);
    Mout.SetWeight(0, 1, 4);
    Mout.SetWeight(0, 2, 11);
    Mout.SetWeight(1, 0, 6);
    Mout.SetWeight(1, 2, 2);
    Mout.SetWeight(2, 0, 3);
    *this = Mout;
}

void MatrixWDigraph::Dijkstra(const int n, const int v)
{
    for (int i = 0; i < n; i++) {
        s[i] = false;
        dist[i] = length[v][i];
        if (length[v][i] != LARGE) pre[i] = v;
        else pre[i] = UNKNOWN;
    }
    s[v] = true;
    dist[v] = 0;
    pre[v] = SELF;

    int u = v;
    for (int i = 0; i < n - 1 && dist[u] < LARGE; i++) {
        u = Choose(n);
        if (dist[u] < LARGE) {
            s[u] = true;
            PrintPath(u);
            for (int w = 0; w < n && i != n - 1; w++) {
                if (!s[w] && dist[u] + length[u][w] < dist[w]) {
                    dist[w] = dist[u] + length[u][w];
                    pre[w] = u;
                }
            }
        }
    }
}

void MatrixWDigraph::BellmanFord(const int n, const int v)
{
    for (int i = 0; i < n; i++) {
        dist[i] = length[v][i];
        chart[0][i] = dist[i];
        if (i < n - 1) chart[i][v] = 0;
    }

    for (int k = 2; k <= n - 1; k++)
        for (int u = 0; u < n; u++) {
            for (int i = 0; u != v && i < n; i++)
                if (i != u && chart[k - 2][i] < LARGE && length[i][u] < LARGE && dist[u] > chart[k - 2][i] + length[i][u])
                    dist[u] = chart[k - 2][i] + length[i][u];
            chart[k - 1][u] = dist[u];
        }
    PrintBellman(n);
}

void MatrixWDigraph::Floyd(const int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            chart[i][j] = length[i][j];
    cout << "A(-1) ";
    PrintFloyd(n);
    cout << endl;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (chart[i][k] < LARGE && chart[k][j] < LARGE && (chart[i][k] + chart[k][j]) < chart[i][j])
                    chart[i][j] = chart[i][k] + chart[k][j];
        cout << "A" << k << "    ";
        PrintFloyd(n);
        cout << endl;
    }
}

int MatrixWDigraph::Choose(const int n)
{
    int minVert = UNKNOWN, minDist = LARGE + 10;
    for (int i = 0; i < n; i++)
        if (!s[i] && dist[i] < minDist) {
            minDist = dist[i];
            minVert = i;
        }
    return minVert;
}

void MatrixWDigraph::PrintPath(const int u)
{
    if (pre[u] == SELF) cout << "Path: " << u << "; Distance: 0\n";
    else {
        int curr = u;
        int capacity = 5;
        int *path = new int[10];
        for (int i = 0; curr != SELF; i++) {
            if (!path[i + 1]) path = (int*)realloc(path, sizeof(int) * capacity * 2);
            path[i] = curr;
            curr = pre[curr];
            if (curr == SELF) {
                cout << "Path: ";
                for (int j = i; j >= 0; j--) {
                    cout << path[j];
                    if (j != 0) cout << "->";
                    else cout << "; Distance: " << dist[u] << endl;
                }
            }
        }
    }
}

void MatrixWDigraph::PrintBellman(const int n)
{
    cout << "k   ";
    for (int i = 0; i < n; i++) {
        cout << i << "   ";
    }
    cout << "\n-------------------------------\n";
    for (int i = 0; i < n - 1; i++) {
        cout << i + 1 << "   ";
        for (int j = 0; j < n; j++) {
            if (chart[i][j] >= LARGE) cout << "i   ";
            else cout << chart[i][j] << "   ";
        }
        cout << endl;
    }
}

void MatrixWDigraph::PrintFloyd(const int n)
{
    for (int i = 0; i < n; i++) cout << i << "   ";
    cout << endl;
    cout << "---------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << i << "     ";
        for (int j = 0; j < n; j++) {
            if (chart[i][j] >= LARGE) cout << "i   ";
            else if (chart[i][j] < 0 || chart[i][j] >= 10) cout << chart[i][j] << "  ";
            else cout << chart[i][j] << "   ";
        }
        cout << endl;
    }
}

int main()
{
    cout << "'i' means infinte" << endl;
    cout << endl;
    cout << "For(a):\n";
    cout << "G1:\n";
    MatrixWDigraph g1(8), g1i(6), g1ii(6);
    g1.SetupG1();
    g1.Dijkstra(8, 4);
    cout << endl;
    //-----------------------------------------------------------
    cout << "G1':\n";
    g1i.SetupG1_1();
    g1i.Dijkstra(6, 0);
    cout << endl;
    //-----------------------------------------------------------
    cout << "G1'':\n";
    g1ii.SetupG1_2();
    g1ii.Dijkstra(6, 0);
    cout << "____________________________________________________\n";
    //-----------------------------------------------------------

    cout << "For(b):\n";
    cout << "G2:\n";
    MatrixWDigraph g2(7), g2i(3);
    g2.SetupG2();
    g2.BellmanFord(7, 0);
    cout << endl << endl;

    cout << "G2':\n";
    g2i.SetupG2_1();
    g2i.BellmanFord(3, 0);
    cout << "____________________________________________________\n";
    //-----------------------------------------------------------

    cout << "For (c):\n";
    cout << "G3:\n";
    MatrixWDigraph g3(3);
    g3.SetupG3();
    g3.Floyd(3);
    cout << endl;

    cout << "G2:\n";
    g2.Floyd(7);

    return 0;
}

