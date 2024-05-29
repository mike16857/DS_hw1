#include <iostream>
using namespace std;


template <class T> class ChainNode;
template <class T> class Chain;
template <class T> class ChainIterator;


/* Stack */
template <class T>
class Stack
{   
	template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
public:
    Stack (int stackCapacity = 10);
    ~Stack();
    bool IsEmpty() const;
    void Push(const T& item);
    void Pop();
    T& Top() const;
private:
    int top;
    int capacity;
    T* stack;
};

template <class U>
void ChangeSize1D(U* &a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";
    U *temp = new U[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);
    delete []a;
    a = temp;
}

template <class T> 
Stack<T>::Stack(int stackCapacity):capacity(stackCapacity)
{
    if (capacity < 1) throw "Stack capacity must be > 0";
    stack = new T[capacity];
    top = -1;
}

template <class T> 
Stack<T>::~Stack() 
{
    delete [] stack;
}

template <class T>
bool Stack<T>::IsEmpty() const
{
    return top == -1;
}

template <class T>
void Stack<T>::Push(const T& item)
{// add x to stack
    if (top == capacity - 1) {
        ChangeSize1D (stack, capacity, 2 * capacity);
        capacity *= 2;
    }
    stack[++top] = item;
}

template <class T>
void Stack<T>::Pop()
{
    if (IsEmpty()) throw "Stack is empty, cannot delete";
    stack[top--].~T();
}

template <class T>
T& Stack<T>::Top() const
{
    if (IsEmpty()) throw "Stack is empty.";
    return stack[top];
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


class LinkedDigraph
{
public:
    LinkedDigraph(const int vertices = 0):n(vertices), e(0) { adjLists = new Chain<int>[n]; }
    void DFS();
    void DFS(int v);
    void BFS(int v);
    void DfnLow(const int x);
    void DfnLow(const int u, const int v);
    void Components();
    void Setup1();
    void Setup2();
private:
    Chain<int> *adjLists;
    int n, e;
    bool *visited;
    int *dfn, *low;
};



void LinkedDigraph::TopologicalOrder()
{
Stack<int> s; // A stack holds 0-indegree vertices
// Any container is good for this algorithm
for (int i = 0; i<n; i++)
if (count[i] == 0) s.push(i);
for (i = 0; i< n; i++) {
if (s.isEmpty() ) throw “Network has a cycle.”;
int j = s.top(); s.pop();
cout << j <<endl;
Chain<int>::ChainIterator ji = adjLists[j].begin();
while (ji) {
count [*ji]--;
if (count[*ji] == 0) s.push(*ji);
ji++;
}
}
}


