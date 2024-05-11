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
// public:
//     ChainNode(int element = 0, ChainNode<T>* next = 0):data(element), link(next) {}
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
	bool IsEmpty();                     
    int Size();
    void InsertHead(const T& e);            
    void DeleteHead();                      
    const T& Front();                       
    const T& Back();                        
    void InsertBack(const T& e);            
    void DeleteBack();                      
    T& Get(int index);                      // index based, first node has index = 0
    T& Set(int index, const T& e);          // index based, first node has index = 0
    int IndexOf(const T& e) const;
    void Delete(int index);                 // index based, first node has index = 0
    void Insert(int i, const T& e);         // index based, first node has index = 0. Insert before the node with index = i
    void Concatenate(Chain<T>& b);          
    void Reverse();                         
    void Delete(ChainNode<T>* p);
    void Insert(ChainNode<T>* p, const T& e);   // p points to a node in the chain

    void InsertBeforeKthNode(int k, const T& e);    // (c) the kth node is the node with index (k - 1), k starts from 1
    void deleteOdd();                               // (d)
    void divideMid(Chain<T>& b);                    // (e)
    Chain<T> deconcatenate(ChainNode<T>* p);        // (f)
    void merge(Chain<T>& b);                        // (g)
    int evaluate();                                 // (j)

    // ChainNode<T> *demo = first->link->link;

	class ChainIterator
    {
    public: 
        //Constructor
        ChainIterator(ChainNode<T>* startNode = 0) {current = startNode;}
        //Dereferencing operators
        T& operator *() const {return current->data;}
        T* operator ->() const {return &current->data;}
        //Increment
        ChainIterator& operator ++() {current = current ->link; return *this;}  //preincrement
        ChainIterator& operator ++(int) {ChainIterator old = *this; current = current ->link; return old;}  //postincrement
        //Equality test
        bool operator!=(const ChainIterator r) {return current != r.current;}
        bool operator==(const ChainIterator r) {return current == r.current;}
    private: 
        ChainNode<T> *current;
    };
    ChainIterator begin() {return ChainIterator(first);}
    ChainIterator end()  {return ChainIterator(0);}

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
bool Chain<T>::IsEmpty()
{
    return first == NULL;
}

template <class T>
int Chain<T>::Size()
{
    ChainNode<T>* temp = first;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->link;
    }
    return count;
}

template <class T>
void Chain<T>::InsertHead(const T& e)
{
    ChainNode<T>* newNode = new ChainNode<T>;
    newNode->data = e;
    newNode->link = first;
    first = newNode;
    if (last == NULL) last = first;
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
const T& Chain<T>::Front()
{
    if (first == NULL) throw "empty list";
    return first->data;
}

template <class T>
const T& Chain<T>::Back()
{
    if (first == NULL) throw "empty list";
    return last->data;
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
void Chain<T>::DeleteBack()
{
    if (first == NULL) return;  // empty list
    if (first == last) {        // only one node in list
        delete first;
        first = last = NULL;
        return;
    }
    ChainNode<T>* temp = first;
    while (temp->link != last) temp = temp->link;
    delete last;
    last = temp;
    last->link = NULL;
}

template <class T>
T& Chain<T>::Get(int index) // index based, starting from 0
{
    if (index < 0) throw "index < 0 is invalid";
    ChainNode<T>* temp = first;
    for (int i = 0; i < index; i++) {
        if (temp == NULL) throw "index out of range";
        temp = temp->link;
    }
    if (temp == NULL) throw "index out of range";
    return temp->data;
}

template <class T>
T& Chain<T>::Set(int index, const T& e)
{
    if (index < 0) throw "index < 0 is invalid";
    ChainNode<T>* temp = first;
    for (int i = 0; i < index; i++) {
        if (temp == NULL) throw "index out of range";
        temp = temp->link;
    }
    if (temp == NULL) throw "index out of range";
    temp->data = e;
    return temp->data;
}

template <class T>
int Chain<T>::IndexOf(const T& e) const
{
    ChainNode<T>* temp = first;
    int index = 0;
    while (temp != NULL) {
        if (temp->data == e) return index;
        temp = temp->link;
        index++;
    }
    return -1;
}

template <class T>
void Chain<T>::Delete(int index)
{
    if (index < 0) throw "index < 0 is invalid";
    ChainNode<T>* temp = first;
    if (index == 0) {
        first = first->link;
        delete temp;
        if (first == NULL) last = NULL;
        return;
    }
    for (int i = 0; i < index - 1; i++) {
        if (temp == NULL) throw "index out of range";
        temp = temp->link;
    }
    if (temp == NULL || temp->link == NULL) throw "index out of range";
    ChainNode<T>* delNode = temp->link;
    temp->link = delNode->link;
    delete delNode;
    if (temp->link == NULL) last = temp;
}

template <class T>
void Chain<T>::Insert(int index, const T& e) // index based, starting from 0
{
    if (index < 0) throw "index < 0 is invalid";
    ChainNode<T>* newNode = new ChainNode<T>;
    newNode->data = e;
    if (index == 0) {
        newNode->link = first;
        first = newNode;
        if (last == NULL) last = first;
        return;
    }
    ChainNode<T>* temp = first;
    for (int i = 0; i < index - 1; i++) {
        if (temp == NULL) throw "index out of range";
        temp = temp->link;
    }
    if (temp == NULL) throw "index out of range";
    newNode->link = temp->link;
    temp->link = newNode;
    if (newNode->link == NULL) last = newNode;
}

template <class T>
void Chain<T>::Concatenate(Chain<T>& b)
{
    // if b is empty, do nothing
    if (first == NULL) { // a null, b null or b not null
        first = b.first;
        last = b.last;
    }
    else if (b.first != NULL) { // a not null, b not null
        last->link = b.first;
        last = b.last;
    }
    b.first = b.last = NULL;
}

template <class T>
void Chain<T>::Reverse()
{//a chain (a1,a2,..,an) becomes (an, an-1,..,a1)
    ChainNode<T> *curr = first;
    ChainNode<T> *prev = 0;
    ChainNode<T> *r = 0;
    while (curr) {
        r = prev; // r trails prev
        prev = curr; // prev trails curr
        curr = curr->link; // curr moves to the next
        prev->link = r; // link prev to r
    }
    last = first; // if has last variable
    first = prev;
}

template <class T>
void Chain<T>::Delete(ChainNode<T>* p)
{
    if (p == NULL) return;
    if (p == first) {
        first = first->link;
        delete p;
        if (first == NULL) last = NULL;
        return;
    }
    ChainNode<T>* temp = first;
    while (temp != NULL && temp->link != p) temp = temp->link;
    if (temp == NULL) throw "deleting non-existing node";
    temp->link = p->link;
    delete p;
    if (temp->link == NULL) last = temp;
}

template <class T>
void Chain<T>::Insert(ChainNode<T>* p, const T& e)
{
    if (p == NULL) return;
    ChainNode<T>* newNode = new ChainNode<T>;
    newNode->data = e;
    newNode->link = p->link;
    p->link = newNode;
    if (p == last) last = newNode;
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

// (c)
template <class T>
void Chain<T>::InsertBeforeKthNode(int k, const T& e)
{
    // if (k < 0) throw "index < 0 is invalid";
    ChainNode<T>* newNode = new ChainNode<T>;
    newNode->data = e;
    if (k == 1) {
        newNode->link = first;
        first = newNode;
        if (last == NULL) last = first;
        return;
    }
    ChainNode<T>* temp = first;
    for (int i = 1; i < k - 1; i++) {
        // if (temp == NULL) throw "index out of range";
        temp = temp->link;
    }
    // if (temp == NULL) throw "index out of range";
    newNode->link = temp->link;
    temp->link = newNode;
    if (newNode->link == NULL) last = newNode;
}

// (d)
template <class T>
void Chain<T>::deleteOdd() 
{
    ChainNode<T> *tmp = first->link;
    ChainNode<T> *toDel;
    delete first;
    first = tmp;
    while (tmp != NULL) {
        toDel = tmp->link;
        if (toDel == NULL) {
            break;  // if number of nodes is even
        }
        tmp->link = toDel->link;
        delete toDel;
        tmp = tmp->link;
    }
}

// (e)
template <class T>
void Chain<T>::divideMid(Chain<T> &subList)
{
    ChainNode<T> *tmp = first;
    int length = Size();
    for (int i = 1; i < (length + 1) / 2; i++) {
        tmp = tmp->link;
    }
    subList.first = tmp->link;
    tmp->link = NULL;
}

// (f)
template <class T>
Chain<T> Chain<T>::deconcatenate(ChainNode<T>* p)
{
    // if (p == NULL) return;
    ChainNode<T>* temp = first;
    Chain<T> List2;

    while (temp != NULL && temp->link != p) temp = temp->link;

    // construct List2
    List2.last = last;
    List2.first = p;

    // maintain original list
    last = temp;
    last->link = NULL;

    return List2;
}

// (g)
template <class T>
void Chain<T>::merge(Chain<T> &List2)
{
    ChainNode<T> *curr1 = first;
    ChainNode<T> *curr2 = List2.first;
    ChainNode<T> *next1, *next2;

    while (curr1->link != NULL && curr2->link != NULL) {
        next1 = curr1->link;
        next2 = curr2->link;
        curr1->link = curr2;
        curr2->link = next1;
        curr1 = next1;
        curr2 = next2;
    }

    if (curr1->link == NULL) {
        curr1->link = curr2;
        last = List2.last;
    } 
    else {
        next1 = curr1->link;
        curr1->link = curr2;
        curr2->link = next1;
    }
    List2.first = List2.last = NULL;
}

// (j)
template <class T>
int Chain<T>::evaluate()
{
    ChainIterator i = begin(), j = begin();
    T ans = 0;

    for(int k = 0; k < 5; k++) j++;
    for(; j != end(); i++, j++) ans += *i * *j;

    return ans;
}

/* Stack (h) */  
template <class T>
class LinkedStack : public Chain<T>
{
    using Chain<T>::InsertHead;
    using Chain<T>::DeleteHead;
    using Chain<T>::first;
public:
    LinkedStack() {top = NULL;};
    ~LinkedStack() {while (!IsEmpty()) Pop();};
    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& x);
    void Pop();
private:
    ChainNode<T> *top;
};

template <class T>
bool LinkedStack<T>::IsEmpty() const
{
    return top == NULL;
}

template <class T>
T& LinkedStack<T>::Top() const
{// Return reference to top element
    if (IsEmpty())
        throw "Stack is empty. No top element.";
    return top->data;
}

template <class T>
void LinkedStack<T>::Push(const T& e) {
    InsertHead(e);
    top = first;
}

template <class T>
void LinkedStack<T>::Pop()
{   
    if (IsEmpty()) throw "Stack is empty. Cannot delete.";
    DeleteHead();
    top = first;
}


/* Queue (i) */
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
    else rear = last;
    
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

/******client program******/
int main() 
{
    Chain<int> L1, L2;
    LinkedStack<int> S;
    LinkedQueue<int> Q;
    int num;
    int temp;
    
    cout << "Input List1: " << endl;
	cout << "How many element do you want to plug in : ";
	cin >> num;
	for(int i = 0; i < num; i++) {
		cin >> temp;
		L1.InsertBack(temp);
        S.Push(temp);
        Q.Push(temp);
	}
    cout << "Input List2: " << endl;
	cout << "How many element do you want to plug in : ";
	cin >> num;
	for(int i = 0; i < num; i++) {
	    cin >> temp;
		L2.InsertBack(temp);
	}
    // cout << "List1: " << endl;
    cout << "L1 = " << L1;
    // cout << "List2: " << endl;
    cout << "L2 = " << L2;

    
    cout << "What number do you want to insert in the front of L1? : ";
    cin >> temp;
    cout << "L1 = : ";
    L1.InsertHead(temp);
    cout << L1;
    cout << "Delete front element in L1 : ";
    L1.DeleteHead();
    cout << L1;
    cout << "Delete Back element in L1 : ";
    L1.DeleteBack();
    cout << L1;
    cout << "Front element of L1 : " << L1.Front() << endl;
    cout << "Back element of L1 : " << L1.Back() << endl;
    
    cout << "Which element do you want to get? (enter an index number, starting from 0): ";
    cin >> temp;
    cout << "The element with index " << temp << " in L1 is " << L1.Get(temp) << endl;
    cout << "Enter a number in the list : ";
    cin >> num;
    cout << "The index of " << num << " in L1 is " << L1.IndexOf(num) << endl;
    cout << "Which element do you want to delete? (enter an index number, starting from 0): ";
    cin >> temp;
    cout << "Delete the element with index " << temp << " in L1 : ";
    L1.Delete(temp);
    cout << L1;
    
    cout << "Where do you want to insert? (enter an index number, starting from 0): ";
    cin >> num;
    cout << "What number do you want to insert? : ";
    cin >> temp;
    cout << "L1 = : ";
    L1.Insert(num, temp);
    cout << L1;
    cout << "Reverse L1 : ";
    L1.Reverse();
    cout << L1;
    cout << endl;
    cout << "L2 = " << L2;
    cout << "L1 followed by L2 :";
    L1.Concatenate(L2);
    cout << L1;
    cout << endl;

    // (j)
    cout << "Compute given expression in L1 : " << L1.evaluate() << endl;
    cout << endl;
    
    // (c)
    cout << "Which element do you want to insert before in List1? (enter a serial number >= 1): ";
    cin >> num;
    cout << "What number do you want to insert? : ";
    cin >> temp;
    cout << "Insert " << temp << " before " << num << "th node : ";
    L1.InsertBeforeKthNode(num, temp);
    cout << L1;
    cout << endl;

    // (d)
    cout << "L1 after deleteing odd nodes (first, 3th, 5th...): ";
    L1.deleteOdd();
    cout << L1;
    cout << endl;

    // (e)
    Chain<int> subList;
    cout << "L1 after dividing mid: ";
    L1.divideMid(subList);
    cout << L1;
    cout << "subList: " << subList;
    cout << endl;

    // (f) not done yet
    // ChainNode<int>* p = L1.demo;
    // cout << "L1 after deconcatenating at 3th node: ";
    // Chain<int> List2 = L1.deconcatenate(p);
    // cout << L1;
    // cout << "List2: " << List2;
    // cout << endl;

    // (g)
    cout << "L1 after merging with subList: ";
    L1.merge(subList);
    cout << L1;
    cout << endl;

    
    // (h) stack
    cout << "LinkedStack :" << endl;
    cout << "S = " << S;
    cout << "Is S empty ? ";
    if (S.IsEmpty()) cout << "Yes" << endl;
    else cout << "No" << endl;
    cout << "Top element of S : " << S.Top() << endl;
    cout << "What number do you want to Push? : ";
    cin >> temp;
    cout << "Push " << temp << " into S : ";
    S.Push(temp);
    cout << S;
    cout << "S after a Pop : ";
    S.Pop();
    cout << S;
    cout << endl;
    
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