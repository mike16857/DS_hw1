#include <iostream>
#define MAX 100000
using namespace std;

template <class T>
class Stack
{
public:
    Stack (int stackCapacity = 10);
    bool IsEmpty() const;
    T& Top() const;
    void Push(const T&item);
    void Pop();
    void ChangeSize1D(T* &a, const int oldSize, const int newSize);
private:
    T* stack;
    int top;
    int capacity;
};

template <class T>
Stack<T>:: Stack(int stackCapacity): capacity(stackCapacity)
{
    if (capacity < 1) throw "Stack capacity must be > 0";
    stack = new T[capacity];
    top = -1;
}

template <class T>
inline bool Stack<T>:: IsEmpty() const { return top == -1;}

template <class T>
inline T& Stack<T>:: Top() const
{
    if (IsEmpty()) throw "Stack is empty";
    return stack[top];
}

template <class T>
void Stack<T>:: Push(const T &item)
{
    if (top == capacity - 1) {
        ChangeSize1D(stack, capacity, 2 * capacity);
        capacity *= 2;
    }
    stack[++top] = item;
}

template <class T>
void Stack<T>:: Pop()
{
    if (IsEmpty()) throw "Stack is empty. Cannot delete.";
    stack[top--].~T();
}

template <class T>
void Stack<T>:: ChangeSize1D(T* &a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";

    T *temp = new T[newSize];
    int number = min(oldSize, newSize);    // choose the smallest Size to store
    copy(a, a + number, temp);              // copy the old array into new
    delete []a;                             // delete old array
    a = temp;
}

class MatrixDigraph
{
public:
    MatrixDigraph(const int vertices = 0):n(vertices), e(0)
    {
        matrix = new int* [n];
        length = new int* [n];
        for(int i = 0; i < n; i++){
            matrix[i] = new int [n];
            length[i] = new int [n];
        }
    }
    void Dijkstra(const int n, const int v);
    void Setup1();
    void Setup2();
    void Setup3();
    bool IsAdjacentto(int u, int v) {return matrix[u][v] != 0;}
    void BellmanFord(const int v);
    void Setup4();
    void Setup5();
    void AllLengths(const int n);
    void Setup6();
private:
    int **matrix;
    int **length;
    int n, e;
};

void MatrixDigraph::Dijkstra(const int n, const int v)
{
    bool S[n];
    int Dist[n], P[n], A[n];
    int u;
    int num;
    if (v == n - 1) u = v - 1;
    else u = v + 1;
    int i, j, k = 0;
    Stack<int> s;
    char inf[] = "¡Û";
    
    for (i = 0; i < n; i++) {
        S[i] = false;
        Dist[i] = length[v][i];
        P[i] = v;
    }
    S[v] = true;
    Dist[v] = 0;
    P[v] = -1;
    
    cout << "Iteration        Vertex                     Distance" << endl;
    cout << "                selected      ";
    for (i = 0; i < n; i++) cout << "[" << i << "]     "; cout << endl;
    cout << "  Initial           -    ";
    for (i = 0; i < n; i++)
        if (Dist[i] >= MAX)
            printf("%8s", inf);
        else printf("%8d", Dist[i]);
    cout << endl;
    
    for (i = 0; i < n - 1; i++) {
        cout << "        " << i + 1;
        for (j = 0; j < n; j++)
            if (!S[j]) {
                u = j;
            }
        for (j = 0; j < n; j++) {
            if (!S[j])
                if (Dist[j] < Dist[u]) u = j;
        }
        S[u] = true;
        A[k] = u;
        k++;
        printf("%12d    ", u);

        for (int w = 0; w < n; w++) {
            if (matrix[u][w] != 0 && !S[w] && (Dist[u] + length[u][w] < Dist[w])) {
                Dist[w] = Dist[u] + length[u][w];
                P[w] = u;
            }
        }
        for (int i = 0; i < n; i++)
            if (Dist[i] >= MAX)
                printf("%8s", inf);
            else printf("%8d", Dist[i]);
        cout << endl;
    }
    
    cout << "Path              Length" << endl;
    for (int i = 0; i < n - 1; i++) {
        num = 0;
        for (int j = A[i]; j != -1; j = P[j]) s.Push(j);
        while (!s.IsEmpty()) {
            cout << s.Top();
            s.Pop();
            num++;
            if (!s.IsEmpty()) cout << "¡÷";
        }
        num = 20 - 3 * num;
        while (num--) cout << " ";
        if (Dist[A[i]] >= MAX) cout << "oo";
        else
            cout << Dist[A[i]];
        cout << endl;
    }
}

void MatrixDigraph::Setup1()
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            matrix[i][j] = 0;
    matrix[1][0] = 300;
    matrix[2][0] = 1000;matrix[2][1] = 800;
    matrix[3][2] = 1200;
    matrix[4][3] = 1500; matrix[4][5] = 250;
    matrix[5][3] = 1000; matrix[5][6] = 900; matrix[5][7] = 1400;
    matrix[6][7] = 1000;
    matrix[7][0] = 1700;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (matrix[i][j]) length[i][j] = matrix[i][j];
            else length[i][j] = MAX;
        }
    }
}

void MatrixDigraph::Setup2()
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            matrix[i][j] = 0;
    matrix[0][1] = 50; matrix[0][2] = 45; matrix[0][3] = 10;
    matrix[1][2] = 10; matrix[1][3] = 15;
    matrix[2][4] = 30;
    matrix[3][0] = 20; matrix[3][4] = 15;
    matrix[4][1] = 20; matrix[4][2] = 30;
    matrix[5][4] = 3;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(matrix[i][j]) length[i][j] = matrix[i][j];
            else length[i][j] = MAX;
        }
    }   
}

void MatrixDigraph::Setup3()
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            matrix[i][j] = 0;
    matrix[0][1] = 20;  matrix[0][2] = 15;
    matrix[1][0] = 2; matrix[1][4] = 10;  matrix[1][5] = 30;
    matrix[2][3] = 30; matrix[2][5] = 10;
    matrix[4][3] = 15;
    matrix[5][4] = 10; matrix[5][3] = 4;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (matrix[i][j]) length[i][j] = matrix[i][j];
            else length[i][j] = MAX;
        }
    }
}

void MatrixDigraph::BellmanFord(const int v)
{
    int Dist[n];
    char inf[] = "oo";
    
    for(int i = 0; i < n; i++) Dist[i] = length[v][i];
    Dist[v] = 0;
    for(int i = 0; i < 4 * n; i++) printf(" ");
    printf("dist^k[%d]\n", n);
    for(int i = 0; i < 9 * n; i++) printf("-"); cout << endl;
    printf("   k");
    for(int i = 0; i < n; i++) printf("%8d", i); cout << endl;
    for(int i = 0; i < 9 * n; i++) printf("-"); cout << endl;
    printf("   1");
    for(int i = 0; i < n; i++)
        if(Dist[i] >= MAX) printf("%8s", inf);
        else printf("%8d", Dist[i]);
    cout << endl;
    
    for(int k = 2; k <= n - 1; k++){
        for(int u = 0; u < n; u++){
            if(u != v){
                for(int i = 0; i < n; i++)
                    if(matrix[i][u] != 0 && Dist[u] > Dist[i] + length[i][u]) Dist[u] = Dist[i] + length[i][u];
            }
        }
        printf("   %d", k);
        for(int i = 0; i < n; i++)
            if(Dist[i] >= MAX) printf("%8s", inf);
            else printf("%8d", Dist[i]);
        cout << endl;
    }
}

void MatrixDigraph::Setup4()
{
   for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            matrix[i][j] = 0;
    matrix[0][1] = 6; matrix[0][2] = 5; matrix[0][3] = 5;
    matrix[1][4] = -1;
    matrix[2][1] = -2; matrix[2][4] = 1;
    matrix[3][2] = -2; matrix[3][5] = -1;
    matrix[4][6] = 3;
    matrix[5][6] = 3;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (matrix[i][j]) length[i][j] = matrix[i][j];
            else length[i][j] = MAX;
        }
    }
}

void MatrixDigraph::Setup5()
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            matrix[i][j] = 0;
    matrix[0][1] = 7; matrix[0][2] = 5;
    matrix[1][2] = -5;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (matrix[i][j]) length[i][j] = matrix[i][j];
            else length[i][j] = MAX;
        }
    }
}

void MatrixDigraph::AllLengths(const int n)
{
    int Dist[n][n];
    char inf[] = "oo";
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(i == j) Dist[i][j] = 0;
            else Dist[i][j] = length[i][j];
    printf(" A^-1|"); for (int i = 0; i < n; i++) printf("%5d", i); cout << endl;
    for(int i = 0; i < 9 * n; i++) printf("-"); cout << endl;
    for(int a = 0; a < n; a++){
        printf("  %d  |", a);
        for(int b = 0; b < n; b++)
            if(Dist[a][b] >= MAX) printf("%5s", inf);
            else printf("%5d", Dist[a][b]);
        cout << endl;
    }
    cout << endl;
    
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(Dist[i][j] > (Dist[i][k] + Dist[k][j]))
                    Dist[i][j] = Dist[i][k] + Dist[k][j];
            }
        }
        printf(" A^%d |", k); 
		for(int i = 0; i < n; i++) printf("%5d", i); cout << endl;
        for(int i = 0; i < 9 * n; i++) printf("-"); cout << endl;
        for(int a = 0; a < n; a++){
            printf("  %d  |", a);
            for(int b = 0; b < n; b++)
                if (Dist[a][b] >= MAX) printf("%5s", inf);
                else printf("%5d", Dist[a][b]);
            cout << endl;
        }
        cout << endl;
    }
}

void MatrixDigraph::Setup6()
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            matrix[i][j] = 0;
    matrix[0][1] = 4; matrix[0][2] = 11;
    matrix[1][0] = 6; matrix[1][2] = 2;
    matrix[2][0] = 3;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (matrix[i][j]) length[i][j] = matrix[i][j];
            else length[i][j] = MAX;
        }
    }
}

int main(void) {

    MatrixDigraph g1(8);
    MatrixDigraph g2(6);
    MatrixDigraph g3(6);
    MatrixDigraph g4(7);
    MatrixDigraph g5(3);
    MatrixDigraph g6(3);
    
    g1.Setup1();
    cout << "G1-1 Dijkstra\n";
    g1.Dijkstra(8, 4);
    cout << endl;
    g2.Setup2();
    cout << "G1-2 Dijkstra\n";
    g2.Dijkstra(6, 0);
    cout << endl;
    g3.Setup3();
    cout << "G1-3 Dijkstra\n";
    g3.Dijkstra(6, 0);
    cout << endl;
    g4.Setup4();
    cout << "G2-1 BellmanFord\n";
    g4.BellmanFord(0);
    cout << endl;
    g5.Setup5();
    cout << "G2-2 BellmanFord\n";
    g5.BellmanFord(0);
    g6.Setup6();
    cout << endl;
    cout << "G3 Floyd\n";
    g6.AllLengths(3);
    
    return 0;
}
