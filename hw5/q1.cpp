#include <iostream>
using namespace std;


template <class T> class Chain; // forward declaration
template <class T> class ChainIterator; // forward declaration
class LinkedGraph; // forward declaration

/* Queue */
template <class T>
class Queue
{
    template <class U>
	friend ostream& operator<<(ostream &os, Queue<U> &queue);
	template <class U>
	friend istream& operator>>(istream &is, Queue<U> &queue);
public:
    Queue(int queueCapacity = 10);
    ~Queue();
    Queue(const Queue<T>& other); // Copy constructor
    Queue<T>& operator=(const Queue<T>& other); // Copy assignment operator
    bool IsEmpty() const;
    void Push(const T& item);
    void Pop();
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
template <class T>
Queue<T>::Queue(const Queue<T>& other)
{
    capacity = other.capacity;
    queue = new T[capacity];
    front = other.front;
    rear = other.rear;
    std::copy(other.queue, other.queue + capacity, queue);
}

// Copy assignment operator
template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if (this != &other) { // Check for self-assignment
        // Deallocate existing resources
        delete[] queue;

        // Copy data from the other queue
        capacity = other.capacity;
        queue = new T[capacity];
        front = other.front;
        rear = other.rear;
        std::copy(other.queue, other.queue + capacity, queue);
    }
    return *this;
}

template <class T>
bool Queue<T>::IsEmpty() const
{
    return (Size() == 0);
}

template <class T>
void Queue<T>::Push(const T& x)
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
void Queue<T>::Pop()
{
    if (IsEmpty()) throw "Queue is empty, cannot delete";
    front = (front + 1) % capacity;
    queue[front].~T(); // destructor for T
}

template <class T>
inline T& Queue<T>::Front() const
{
    if (IsEmpty()) throw "Queue is empty. No front element.";
    return queue[(front + 1) % capacity]; //front unchanged
}

template <class T>
inline T& Queue<T>::Rear() const
{
    if (IsEmpty()) throw "Queue is empty. No rear element.";
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
    ChainNode(T element = 0, ChainNode<T>* next = 0):data(element), link(next) {}
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
	~Chain(); //desctructor                  
    void InsertBack(const T& e);           
    ChainIterator<T> begin() {return ChainIterator<T>(first);}
    ChainIterator<T> end()  {return ChainIterator<T>(0);}
protected:
	ChainNode<T> *first;
};

template <class T>
Chain<T>::~Chain()
{
    ChainNode<T>* temp;
    while (first != NULL) {
        temp = first;
        first = first->link;
        delete temp;
    }
}

template <class T>
void Chain<T>::InsertBack(const T& e)
{
    ChainNode<T>* newNode = new ChainNode<T>;
    newNode->data = e;
    newNode->link = NULL;

    if (first == NULL) first = newNode;
    else {
        for (ChainNode<T>* current = first; current != NULL; current = current->link);
        current->link = newNode;
    }
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


class LinkedGraph
{
public:
    LinkedGraph(const int vertices = 0):n(vertices), e(0) { adjLists = new Chain<int>[n]; }
    void DFS();
    void DFS(int v);
    void BFS(int v);
    void DfnLow(const int x);
    void DfnLow(const int u, const int v);
    void Components();
    void Setup1();
    void Setup2();
    void Setup3();
private:
    Chain<int> *adjLists;
    int n, e;
    bool *visited;
    int *dfn, *low;
};

void LinkedGraph::DFS() // Driver
{
    visited = new bool[n];
    fill (visited, visited + n, false);
    DFS(0); // start search at vertex 0
    delete [] visited;
}
void LinkedGraph::DFS(const int v)
// visit all previously unvisited vertices that are
// reachable from vertex @v@
{
    visited[v] = true; cout << v << ", ";
    ChainIterator<int> li(adjLists[v]);
    if (!li.NotNull()) return;
    int w = *adjLists[v].begin();
    while (1) {
        if (!visited[w]) DFS(w);
        if (li.NextNotNull()){
            w = *li++;
        }
        else return;
    }
}

void LinkedGraph::BFS(int v)
{//BFS(v), visited[i]=true when visited
    visited = new bool [n];
    fill (visited, visited + n, false);
    visited[v] = true;
    Queue<int> q;
    q.Push(v);
    while (!q.IsEmpty()) {
        v = q.Front();
        q.Pop();
        ChainIterator<int> li(adjLists[v]);
        for (; li.NotNull(); li++) {
            int w = *li;
            if (!visited[w]) {
                q.Push(w);
                visited[w] = true;
            }
        }
    } // end of while loop
    delete [] visited;
}

void LinkedGraph::Components()
{
    visited = new bool [n];
    fill (visited, visited + n, false);
    for (int i = 0 ; i < n ; i++){
        if (!visited[i]) {
            DFS(i); // find the component containing i
            // OutputNewComponent();
        }
    }
    delete [] visited;
}

void LinkedGraph::DfnLow(const int x)//從頂點x開始執行DFS
{
    num = 1; // num 是Graph的一個int資料成員
    dfn = new int[n]; // dfn 在Graph中宣告為int*
    low= new int[n]; // low 在Graph中宣告為int*
    fill (dfn, dfn + n, 0);
    fill (low, low + n, 0);
    DfnLow(x, -1); // 從頂點x開始
    delete [] dfn;
    delete [] low;
}
void LinkedGraph::DfnLow(const int u, const int v)
{   // 由頂點u開始，一邊做深度優先搜尋一邊計算dfn及low。
    // 在製造出的生成樹中v是u的父節點（如果v存在的話）
    dfn [u] = low [u] = num++;
    for (每個與u相鄰的頂點w) { // 實際的程式碼使用疊代器
        if (dfn[w] == 0) { // w是未拜訪過的頂點
            DfnLow(w, u);
            low[u] = min(low[u], low[w]);
        }
        else if (w != v) low[u] = min(low[u], dfn[w]); // back edge
    }
}

void LinkedGraph::Setup1()
{
    adjLists[0].InsertBack(1); adjLists[0].InsertBack(2);
    adjLists[1].InsertBack(0); adjLists[1].InsertBack(3);
    adjLists[2].InsertBack(0); adjLists[2].InsertBack(3);
    adjLists[3].InsertBack(1); adjLists[3].InsertBack(2);
    adjLists[4].InsertBack(5);
    adjLists[5].InsertBack(4); adjLists[5].InsertBack(6);
    adjLists[6].InsertBack(5); adjLists[6].InsertBack(7);
    adjLists[7].InsertBack(6);
}

void LinkedGraph::Setup2()
{
    adjLists[0].InsertBack(1); adjLists[0].InsertBack(2);
    adjLists[1].InsertBack(0); adjLists[1].InsertBack(3); adjLists[1].InsertBack(4);
    adjLists[2].InsertBack(0); adjLists[2].InsertBack(5); adjLists[2].InsertBack(6);
    adjLists[3].InsertBack(1); adjLists[3].InsertBack(7);
    adjLists[4].InsertBack(1); adjLists[4].InsertBack(7);
    adjLists[5].InsertBack(2); adjLists[5].InsertBack(7);
    adjLists[6].InsertBack(2); adjLists[6].InsertBack(7);
    adjLists[7].InsertBack(3); adjLists[7].InsertBack(4); adjLists[7].InsertBack(5); adjLists[7].InsertBack(6);
}

void LinkedGraph::Setup3()
{
    adjLists[0].InsertBack(1);
    adjLists[1].InsertBack(0); adjLists[1].InsertBack(2); adjLists[1].InsertBack(3);
    adjLists[2].InsertBack(1); adjLists[2].InsertBack(4);
    adjLists[3].InsertBack(1); adjLists[3].InsertBack(4); adjLists[3].InsertBack(5);
    adjLists[4].InsertBack(2); adjLists[4].InsertBack(3);
    adjLists[5].InsertBack(3); adjLists[5].InsertBack(6); adjLists[5].InsertBack(7);
    adjLists[6].InsertBack(5); adjLists[6].InsertBack(7);
    adjLists[7].InsertBack(5); adjLists[7].InsertBack(8); adjLists[7].InsertBack(9);
    adjLists[8].InsertBack(7);
    adjLists[9].InsertBack(7);
    
}


int main()
{
    LinkedGraph g1(8), g2(8), g3(10);
    g1.Setup1();
    g2.Setup2();
    g3.Setup3();

    cout << "G1 : " << endl;
    cout << "BFS starting at 0: ";
    g1.BFS(0);
    cout << "BFS starting at 3: ";
    g1.BFS(3);
    cout << "BFS starting at 7: ";
    g1.BFS(7);
    cout << "DFS starting at 0: ";
    g1.DFS(0);
    cout << "DFS starting at 3: ";
    g1.DFS(3);
    cout << "DFS starting at 7: ";
    g1.DFS(7);
    cout << "Components of G1 : " << endl;
    g1.Components();
    cout << "DfnLow starting at 3 : " << endl;
    if(!g1.DfnLow(3)) cout << "G1 is not connected, no dfn, low values." << endl;
    cout << endl;
    
    cout << "G2 : " << endl;
    cout << "BFS starting at 0: ";
    g2.BFS(0);
    cout << "BFS starting at 3: ";
    g2.BFS(3);
    cout << "BFS starting at 7: ";
    g2.BFS(7);
    cout << "DFS starting at 0: ";
    g2.DFS(0);
    cout << "DFS starting at 3: ";
    g2.DFS(3);
    cout << "DFS starting at 7: ";
    g2.DFS(7);
    cout << "Components of G2 : " << endl;
    g2.Components();
    cout << "DfnLow starting at 3 : " << endl;
    if(!g2.DfnLow(3)) cout << "G2 is not connected, no dfn, low values." << endl;
    cout << endl;
    
    cout << "G3 : " << endl;
    cout << "BFS starting at 0: ";
    g3.BFS(0);
    cout << "BFS starting at 3: ";
    g3.BFS(3);
    cout << "BFS starting at 7: ";
    g3.BFS(7);
    cout << "DFS starting at 0: ";
    g3.DFS(0);
    cout << "DFS starting at 3: ";
    g3.DFS(3);
    cout << "DFS starting at 7: ";
    g3.DFS(7);
    cout << "Components of G3 : " << endl;
    g3.Components();
    cout << "DfnLow starting at 3 : " << endl;
    if(!g3.DfnLow(3)) cout << "G3 is not connected, no dfn, low values." << endl;
    return 0;
}


