#include <iostream>
#include <list>
// #include <queue>

using namespace std;

template <class T> class Chain; 
template <class T> class ChainIterator; 
class Graph; 

/* Queue */
template <class T>
class Queue
{
public:
    Queue(int queueCapacity = 10);
    ~Queue();
    // Queue(const Queue<T>& other); // Copy constructor
    // Queue<T>& operator=(const Queue<T>& other); // Copy assignment operator
    bool empty() const;
    int Size() const;
    void push(const T& item);
    void pop();
    T& Front() const;
    T& Rear() const;
private:
    T* queue;
    int front, rear;
    int capacity;
};

template <class T>
Queue<T>::Queue(int queueCapacity):capacity(queueCapacity)
{
    if (capacity < 1) throw "Queue capacity must be > 0";
    queue= new T[capacity];
    front = rear = 0; // indicate empty queue
}

template <class T>
Queue<T>::~Queue()
{
    delete [] queue;
}

// Copy constructor
// template <class T>
// Queue<T>::Queue(const Queue<T>& other)
// {
//     capacity = other.capacity;
//     queue = new T[capacity];
//     front = other.front;
//     rear = other.rear;
//     std::copy(other.queue, other.queue + capacity, queue);
// }

// Copy assignment operator
// template <class T>
// Queue<T>& Queue<T>::operator=(const Queue<T>& other)
// {
//     if (this != &other) { // Check for self-assignment
//         // Deallocate existing resources
//         delete[] queue;

//         // Copy data from the other queue
//         capacity = other.capacity;
//         queue = new T[capacity];
//         front = other.front;
//         rear = other.rear;
//         std::copy(other.queue, other.queue + capacity, queue);
//     }
//     return *this;
// }

template <class T>
bool Queue<T>::empty() const
{
    return (Size() == 0);
}

template <class T>
int Queue<T>::Size() const
{
    return (rear - front + capacity) % capacity;
}

template <class T>
void Queue<T>::push(const T& x)
{// add x to queue
    if ((rear + 1) % capacity == front) { //resize
        T* newQu = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(queue + start, queue + start + capacity - 1, newQu);
        else {
            copy(queue + start, queue + capacity, newQu);
            copy(queue, queue + rear + 1, newQu + capacity - start);
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        delete [] queue;
        queue = newQu; 
        capacity *= 2;
    }
    rear = (rear + 1) % capacity; 
    queue[rear] = x;
}

template <class T>
void Queue<T>::pop()
{
    if (empty()) throw "Queue is empty, cannot delete";
    front = (front + 1) % capacity;
    queue[front].~T(); // destructor for T
}

template <class T>
inline T& Queue<T>::Front() const
{
    if (empty()) throw "Queue is empty. No front element.";
    return queue[(front + 1) % capacity]; //front unchanged
}

template <class T>
inline T& Queue<T>::Rear() const
{
    if (empty()) throw "Queue is empty. No rear element.";
    return queue[rear];
}


template <class T>
class ChainNode 
{
    friend class Chain<T>;
    friend class ChainIterator<T>;
    template <class U>
    friend ostream& operator<<(ostream& os, Chain<U>& c);
public:
    ChainNode(T element = 0, ChainNode<T>* next = 0) {data = element; link = next;}
private:
	T data;
	ChainNode<T>* link;
};


template <class T>
class Chain 
{   
    friend class ChainIterator<T>;
    friend class LinkedGraph;
    friend class ChainNode<T>;
public:
	Chain() {first = 0;} // 建構子將first, last初始化成0
	// ~Chain(); //desctructor                  
    void InsertBack(const T& e);           
    ChainIterator<T> begin() {return ChainIterator<T>(first);}
    ChainIterator<T> end()  {return ChainIterator<T>(0);}
protected:
	ChainNode<T> *first;
};

// template <class T>
// Chain<T>::~Chain()
// {
//     ChainNode<T>* temp;
//     while (first != NULL) {
//         temp = first;
//         first = first->link;
//         delete temp;
//     }
// }

// template <class T>
// void Chain<T>::InsertBack(const T& e)
// {
//     ChainNode<T>* newNode = new ChainNode<T>;
//     newNode->data = e;
//     newNode->link = NULL;

//     if (first == NULL) first = newNode;
//     else {
//         ChainNode<T>* current;
//         for (current = first; current != NULL; current = current->link);
//         current->link = newNode;
//     }
// }
template <class T>
void Chain<T>::InsertBack(const T &e)
{
    ChainNode<T>* temp;
    if(first == NULL){
        first = new ChainNode<T>;
        first->data = e;
        first->link = NULL;
        return;
    }
    for (temp = first; temp->link != NULL; temp = temp->link);
    ChainNode<T> *newNode = new ChainNode<T>;
    newNode->data = e;
    temp->link = newNode;
    
    return;
}


template <class T>
class ChainIterator
{
    friend class LinkedGraph;
public: 
    //Constructor
    ChainIterator(ChainNode<T>* startNode = 0) {current = startNode;}
    ChainIterator(Chain<T> &ch){current = ch.first;}
    //Dereferencing operators
    T& operator *() const {return current->data;}
    T* operator ->() const {return &current->data;}
    //Increment
    ChainIterator& operator ++() {current = current ->link; return *this;}  //preincrement
    ChainIterator& operator ++(int) {ChainIterator old = *this; current = current ->link; return old;}  //postincrement
    //Equality test
    bool operator!=(const ChainIterator r) {return current != r.current;}
    bool operator==(const ChainIterator r) {return current == r.current;}
    bool NotNull() {return current != 0;}
    bool NextNotNull() {return current->link != 0;}
    
private: 
    ChainNode<T> *current;
};


class Graph {
public:
    Graph(const int vertices = 0):n(vertices), e(0)
        {adjLists = new list<int>[n];}
        // {adjLists = new Chain<int>[n];}
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
    // Chain<int> *adjLists;
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
    // adjLists[u].InsertBack(v);
    // adjLists[v].InsertBack(u);
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
    // ChainIterator<int> li(adjLists[v]);
    // for (; li != adjLists[v].end(); li++)
    //     if (!visited[*li]) hDFS(*li);
}



void Graph::BFS(int v)
{
    visited = new bool [n];
    fill(visited, visited + n, false);
    cout << v << " ";
    visited[v] = true;
    // queue<int> q;
    Queue<int> q;
    q.push(v);
    while (!q.empty()) {
        v = q.Front();
        // v = q.front();
        q.pop();
        list<int>::iterator it;
        for (it = adjLists[v].begin(); it != adjLists[v].end(); it++)
            if (!visited[*it]) {
                q.push(*it);
                cout << *it << " ";
                visited[*it] = true;
            }
        // ChainIterator<int> li(adjLists[v]);
        // for (; li != adjLists[v].end(); li++)
        //     if (!visited[*li]) {
        //         q.push(*li);
        //         cout << *li << " ";
        //         visited[*li] = true;
        //     }
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
    // ChainIterator<int> li(adjLists[v]);
    // for (; li != adjLists[u].end(); li++)
    //     if (dfn[*li] == 0) {
    //         DfnLow(*li, u);
    //         low[u] = min(low[u], low[*li]);
    //     }
    //     else if (*li != v) low[u] = min(low[u], dfn[*li]);
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
