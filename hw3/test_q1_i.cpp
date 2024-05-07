#include <iostream>
using namespace std;

template <class T> class Chain;
template <class T> class LinkedStack;
template <class T> class LinkedQueue;

template <class T>
class ChainNode 
{
    friend class Chain<T>;
    friend class LinkedStack<T>;
    friend class LinkedQueue<T>;
    template <class U>
    friend ostream& operator<<(ostream& os, Chain<U>& c);
private:
	T data;
	ChainNode<T>* link;
};


template <class T>
class Chain 
{
    template <class U>
    friend ostream& operator<<(ostream& os, Chain<U>& c);   // (b)
public:
	Chain() {first = last = 0;} // 建構子將first, last初始化成0
	~Chain(); //desctructor
    void DeleteHead();                                 
    void InsertBack(const T& e);                             
protected:
	ChainNode<T> *first, *last;
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
ostream& operator<<(ostream& os, Chain<T>& c)
{
    ChainNode<T>* temp = c.first;

    os << temp->data;
    temp = temp->link;
    while (temp != NULL) {
        os << " -> " << temp->data;
        temp = temp->link;
    }
    os << endl;

    return os;
}

template <class T>
void Chain<T>::DeleteHead()
{
    if (first == NULL) return;
    ChainNode<T>* temp = first;
    first = first->link;
    delete temp;
    if (first == NULL) last = NULL; // empty list
}

template <class T>
void Chain<T>::InsertBack(const T& e)
{
    ChainNode<T>* newNode = new ChainNode<T>;
    newNode->data = e;
    newNode->link = NULL;
    if (first == NULL) first = last = newNode;
    else {
        last->link = newNode;
        last = newNode;
    }
}


template <class T>
class LinkedQueue : public Chain<T>
{
    using Chain<T>::InsertBack;
    using Chain<T>::DeleteHead;
    using Chain<T>::first;
    using Chain<T>::last;
public:
    LinkedQueue() {front = rear = NULL;};
    ~LinkedQueue() {while (!IsEmpty()) Pop();};
    bool IsEmpty() const;
    T& Front() const;
    T& Rear() const;
    void Push(const T& x);
    void Pop();
private:
    ChainNode<T> *front, *rear;
};

template <class T>
bool LinkedQueue<T>::IsEmpty() const
{
    return (front == NULL);
}

template <class T>
T& LinkedQueue<T>::Front() const
{
    if (IsEmpty()) throw "Queue is empty. No front element.";
    return front->data;
}

template <class T>
T& LinkedQueue<T>::Rear() const
{
    if (IsEmpty()) throw "Queue is empty. No rear element.";
    return rear->data;
}

template <class T>
void LinkedQueue<T>::Push(const T& e)
{
    InsertBack(e);

    if(IsEmpty()) front = rear = first;
    else {
        rear = last;
        // last = last->link;
    }
    return;
}

template <class T>
void LinkedQueue<T>::Pop()
{ 
    if (IsEmpty()) throw "Queue is empty. Cannot delete.";

    DeleteHead();
    if (IsEmpty()) front = rear = NULL;
    else front = first;

    return;
}


int main() 
{
    LinkedQueue<int> Q;
    int num;
    int temp;
    
    cout << "Input List1: " << endl;
	cout << "How many element do you want to plug in : ";
	cin >> num;
	for(int i = 0; i < num; i++) {
		cin >> temp;
        Q.Push(temp);
	}
    // (i) queue
    cout << "LinkedQueue :" << endl;
    cout << "Q = " << Q;
    cout << "Is Q empty ? ";
    if (Q.IsEmpty()) cout << "Yes" << endl;
    else cout << "No" << endl;
    cout << "Front element of Q : " << Q.Front() << endl;
    cout << "Rear element of Q : " << Q.Rear() << endl;
    cout << "What number do you want to Push? : ";
    cin >> temp;
    cout << "Push " << temp << " into Q : ";
    Q.Push(temp);
    cout << Q;
    cout << "Pop from Q : ";
    Q.Pop();
    cout << Q;

    cout << "End of program" << endl;

    return 0;
}