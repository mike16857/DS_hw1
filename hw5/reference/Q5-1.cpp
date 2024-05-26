#include <iostream>
#include <utility>

using namespace std;
template <class T> class Chain;
class LinkedGraph;
template <class T> class ChainIterator;

template <class T>
class Queue
{
public:
    Queue(int queueCapacity = 10);
    bool IsEmpty() const;
    T& Front() const;
    T& Rear() const;
    void Push(const T &item);
    void Pop();
private:
    T *queue;
    int front;
    int rear;
    int capacity;
};

template <class T>
Queue<T>::Queue(int queueCapacity):capacity(queueCapacity)
{
    if (capacity < 1) throw "Queue capacity must be >0";
    queue = new T[capacity];
    front = rear = 0;
}

template <class T>
inline bool Queue<T>::IsEmpty() const
{
    return front == rear;
}

template <class T>
inline T& Queue<T>::Front () const
{
    if(IsEmpty()) throw "Queue is empty. No front element";
    return queue[(front + 1) % capacity];
}

template <class T>
inline T& Queue<T>:: Rear() const
{
    if(IsEmpty()) throw "Queue is empty. No rear element";
    return queue[rear];
}

template <class T>
void Queue<T>::Push(const T &item)
{
    if((rear + 1) % capacity == front) {
        T* newQueue = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(queue + start, queue + start + capacity - 1, newQueue);
        else {
            copy(queue + start, queue + capacity, newQueue);
            copy(queue, queue + rear + 1, newQueue + capacity - start);
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        capacity *= 2;
        delete [] queue;
        queue = newQueue;
    }
    rear = (rear + 1) % capacity;
    queue [rear] = item;
}

template <class T>
void Queue<T>::Pop()
{
    if(IsEmpty()) throw "Queue is empty. Cannot delete.";
    front = (front + 1) % capacity;
    queue[front].~T();
}

template <class T>
class ChainNode
{
    friend class Chain<T>;
    friend class LinkedGraph;
    friend class ChainIterator<T>;
    template <class U>
    friend ostream &operator<<(ostream& os, Chain<U> &L);
public:
    ChainNode(T e = NULL, ChainNode<T> *next = NULL) {data = e; link = next;};
private:
    T data;
    ChainNode<T> *link;
};

template <class T>
class Chain
{
public:
    friend class LinkedGraph;
    friend class ChainIterator<T>;
    friend class ChainNode<T>;
    Chain() {first = 0;}
    void InsertBack(const T &e);
    ChainIterator<T> begin() {return ChainIterator<T>(first);}
    ChainIterator<T> end() {return ChainIterator<T>(NULL);}
private:
    ChainNode<T> *first;
};

template <class T>
void Chain<T>:: InsertBack(const T &e)
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
    ChainIterator(ChainNode<T> *startNode = 0) {current = startNode;}
    ChainIterator(Chain<T> &ch){current = ch.first;}
    T& operator*() const {return current->data;}
    T* operator->() const {return &current->data;}
    ChainIterator &operator++() {current = current->link; return *this;}
    ChainIterator operator ++(int)
	{
        ChainIterator old = *this;
        current = current->link;
        return old;
    }
    bool NotNull() {return current != NULL;}
    bool NextNotNull() {return current->link != NULL;}
    bool operator!=(const ChainIterator right) const {return current != right.current;}
    bool operator==(const ChainIterator right) const {return current == right.current;}

protected:
    ChainNode<T>* current;
};

class LinkedGraph
{
public:
    LinkedGraph(const int vertices = 0):n(vertices), e(0) {adjLists = new Chain<int>[n]; dfn_num = 0;}
    void DFS(int v);
    void DFS(int v, bool driver);
    void BFS(int v);
    bool DfnLow(int v);
    void DFS_DfnLow(int v);
    void DFS_DfnLow(int v, bool driver);
    void BFS_forcheck(int v);
    void Componenets();
    void Setup1();
    void Setup2();
    void Setup3();
    bool Isconnected();
private:
    Chain<int> *adjLists;
    int n, e; 
    bool *visited;
    int *dfn, *low, *pred;
    int dfn_num;
};

void LinkedGraph::DFS(int v)
{
    visited = new bool[n];
    fill (visited, visited + n, false);
	cout << v;
	visited[v] = true;
    DFS(v, 0);
    cout << endl;
    delete [] visited;
}

void LinkedGraph::DFS(int v, bool driver)
{
    if(visited[v] == false){
    	cout << "¡÷" << v ;
    	visited[v] = true;
	}
    ChainIterator<int> li(adjLists[v]);
    if (!li.NotNull()) return;
    int w = *adjLists[v].begin();
    while (1) {
        if(!visited[w]) DFS(w, 0);
        if(li.NextNotNull()){
            li++;
            w = *li;
        }
        else return;
    }
};

void LinkedGraph::BFS(int v)
{
    visited = new bool[n];
    fill (visited, visited + n, false);
    visited[v] = true;
    Queue<int> q;
    q.Push(v);
    v = q.Front(); cout << v;
    while(!q.IsEmpty()){
        q.Pop();
        ChainIterator<int> li(adjLists[v]);
        for(; li.NotNull() == 1; li++) {
            int w = *li;
            if(!visited[w]){
                q.Push(w);
                visited[w] = true;
            }
        }
        if(!q.IsEmpty()){
        	cout << "¡÷";v = q.Front(); cout << v;
		}
    }
    delete [] visited;
    cout << endl;
    return;
}

bool LinkedGraph::DfnLow(int v)
{
    if(!Isconnected()) return false;
    dfn = new int[n]; low = new int[n]; pred = new int[n];
    DFS_DfnLow(v);
    cout << "Vertice    ";
    for (int i = 0; i < n; i++) cout << i << "  ";
    cout << endl;
    cout << "  dfn      ";
    for (int i = 0; i < n; i++) cout << dfn[i] << "  ";
    cout << endl;
    cout << "  low      ";
    for (int i = 0; i < n; i++) cout << low[i] << "  ";
    cout << endl;
    delete [] dfn; delete [] low; delete [] pred;
    return true;
}

void LinkedGraph::DFS_DfnLow(int v)
{
    visited = new bool[n];
    fill (visited, visited + n, false);
    DFS_DfnLow(v, 0);
    delete [] visited;
    
}

void LinkedGraph::DFS_DfnLow(int v, bool driver)
{
    visited[v] = true;
    dfn[v] = ++dfn_num;
    low[v] = dfn[v];
    ChainIterator<int> li(adjLists[v]);
    if (!li.NotNull()) return;
    int w = *adjLists[v].begin();
    while (1) {
        if (!visited[w]) {
            pred[w] = v;
            DFS_DfnLow(w, 0);
            low[v] = min(low[v], low[w]);
        }
		else if (w != pred[v]) low[v] = min(low[v], dfn[w]);
        if(li.NextNotNull()){
            li++;
            w = *li;
        }
        else return;
    }
}

void LinkedGraph::BFS_forcheck(int v)
{
    visited = new bool[n];
    fill (visited, visited + n, false);
    visited[v] = true;
    Queue<int> q;
    q.Push(v);
    while(!q.IsEmpty()){
        v = q.Front();
        q.Pop();
        ChainIterator<int> li(adjLists[v]);
        for(; li.NotNull() == 1; li++){
            int w = *li;
            if(!visited[w]){
                q.Push(w);
                visited[w] = true;
            }
        }
    }
    delete [] visited;
    return;
}
void LinkedGraph::Componenets()
{
    int num = 1;
    visited = new bool[n];
    fill(visited, visited + n, false);
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            cout << "component #" << num << ": ";
            DFS(i);
            num++;
        }
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
    
    return;
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
bool LinkedGraph::Isconnected()
{
    int num = 0;
    visited = new bool[n];
    fill (visited, visited + n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            BFS_forcheck(i);
            num++;
        }
    }
    
    return num == 1;
}

int main(void)
{
    LinkedGraph g1(8), g2(8), g3(10);
    cout << "G1 : " << endl;
    g1.Setup1();
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
    g1.Componenets();
    cout << "DfnLow starting at 3 : " << endl;
    if(!g1.DfnLow(3)) cout << "G1 is not connected, no dfn, low values." << endl;
    cout << endl;
    
    cout << "G2 : " << endl;
    g2.Setup2();
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
    g2.Componenets();
    cout << "DfnLow starting at 3 : " << endl;
    if(!g2.DfnLow(3)) cout << "G2 is not connected, no dfn, low values." << endl;
    cout << endl;
    
    cout << "G3 : " << endl;
    g3.Setup3();
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
    g3.Componenets();
    cout << "DfnLow starting at 3 : " << endl;
    if(!g3.DfnLow(3)) cout << "G3 is not connected, no dfn, low values." << endl;
    
    return 0;
}
