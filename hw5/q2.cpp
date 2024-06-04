#include <iostream>
using namespace std;

class MatrixWDigraph
{

}

void MatrixWDigraph::Dijkstra(const int n, const int v)
{
    for (int i = 0; i < n ; i++) { // initialization
        s[i] = false; // the set, S
        dist[i] = length[v][i]; // dist[]
    }
    s[v] = true;
    dist[v] = 0;
    for (i = 0; i < n−1 ; i++) { // n-1 shortest paths from v
        choose u that is not in S and has smallest dist[u];
        s[u] = true; // u becomes a member of S
        for (each <u, w> in the graph) // update dist[w]
            if (!s[w] && (dist[u] + length[u][w]) < dist[w])
                dist[w] = dist[u] + length[u][w];
    }
}

void MatrixWDigraph::BellmanFord(const int v)
{ // n is the number of vertices
// in-place update for dist[] is used
    for (int i = 0; i < n ; i++)
        dist[i] = length[v][i]; // dist1[] initialization

    for (int k = 2; k <= n−1 ; k++) // dist2 ~ dist(n-1)
        for (each u, u != v)
            for (each <i, u> in the graph)
                if (dist[u] > dist[i] + length[i][u])
                    dist[u] = dist[i] + length[i][u];
    }

void MatrixWDigraph::Floyd(const int n)
{
    for (int i = 0; i<n; i++)
        for (int j = 0; j<n; j++)
            a[i][j]= length[i][j];
            
    for (int k= 0; k<n; k++)
        for (int i= 0; i<n; i++)
            for (int j= 0; j<n; j++)
                if(a[i][j] > (a[i][k] + a[k][j]))
                    kay[i][j] = k; a[i][j] = a[i][k] + a[k][j];
}


int main()
{
    return 0;
}