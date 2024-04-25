#include <iostream>
using namespace std;

template <class T> class List;
template <class T> class LinkedStack;
template <class T> class LinkedQueue;

template <class T>
class Node{
	friend class List<T>;
	friend class LinkedStack<T>;
    friend class LinkedQueue<T>;
	template <class U>
    friend ostream& operator<<(ostream&, List<U>&);
private: 
	T data;
    Node* link;
};

template <class T>
class List
{
	template <class U>
    friend ostream& operator<<(ostream&, List<U>&);
public: 
	List(){first = NULL;};
	~List();
	void InsertFront(const T &e);
    void InsertBack(const T& e);
    void Concatenate(List<T>& b);
	void Reverse();
	void DeleteFront();
    void DeleteBack();
    T Front();
    T Back();
    T Get(int i);
    void Delete(int i);
    void Insert(int i, T e);
    T Compute();
	class Iterator
	{
	public:
		Iterator(Node<T>* startNode = 0){current = startNode;}	//Constructor
		T& operator *() const {return current->data;}
		T* operator ->() const {return &current->data;}
		Iterator &operator ++(){current = current->link; return *this;}	//preincrement
		Iterator operator ++(int){Iterator old = *this; current = current->link; return old;}	//postincrement
		bool operator!=(const Iterator r){return current != r.current;}
		bool operator==(const Iterator r){return current == r.current;}
	private:
		Node<T>* current;
	};
	Iterator Begin(){return Iterator(first);}
	Iterator End(){return Iterator(NULL);}
protected:
    Node<T>* first;
};

template <class T>
List<T>::~List()
{
	Node<T>* temp;
    
    while (first->link != NULL){
    	temp = first->link;
    	first->link = first->link->link;
    	delete temp;
    }
    delete first;
}

template <class T>
void List<T>:: InsertFront(const T &e)
{
    Node<T> *newfirst = new Node<T>;
    newfirst->data = e;
    newfirst->link = first;
    first = newfirst;
    
    return;
}

template <class T>
void List<T>::InsertBack(const T &e)
{
    Node<T>* temp = first;
    
   if (first == NULL) {
        InsertFront(e);
        return;
    }
    while(temp->link != NULL) temp = temp->link;
    Node<T>* newNode = new Node<T>;
    newNode->data = e;
    newNode->link = NULL;
    temp->link = newNode;
	
    return;
}

template <class T>
void List<T>::Concatenate(List<T> &b)
{
	Node<T>* temp = b.first;
	
	while(temp != NULL){
		InsertBack(temp->data);
		temp = temp->link;
	}
	
	return;
}

template <class T>
void List<T>::Reverse()
{
	Node<T>* curr = first;
	Node<T>* prev = 0;
	Node<T>* r = 0;
	while(curr){
		r = prev; // r trails prev
		prev = curr; // prev trails curr
		curr = curr->link; // curr moves to the next
		prev->link = r; // link prev to r
	}
	first = prev;
}

template <class T>
void List<T>::DeleteFront()
{
	if (first == NULL) throw "The List is empty, cannot delete.";
	Node<T>* temp;
	
    temp = first->link;
    delete first;
    first = temp;
    
    return;
}

template <class T>
void List<T>::DeleteBack()
{
	if (first == NULL) throw "The List is empty, cannot delete.";
	Node<T>* temp = first;
	Node<T>* de;
	
	while(temp->link->link != NULL) temp = temp->link;
	de = temp->link;
	temp->link = NULL;
	delete de;
    
    return;
}

template <class T>
T List<T>::Front()
{
    return first->data;
}

template <class T>
T List<T>::Back()
{
	Node<T>* temp = first;
	while(temp->link != NULL) temp = temp->link;
	
    return temp->data;
}

template <class T>
T List<T>::Get(int i)
{
    Node<T>* temp = first;
    for(int j = 1; j < i; j++) temp = temp->link;
    
    return temp->data;
}

template <class T>
void List<T>::Delete(int i)
{
    Node<T>* temp = first;
    Node<T>* de;
    
    if(i == 1) DeleteFront();
    else{
    	for(int j = 1; j < i - 1; j++) temp = temp->link;
    	de = temp->link;
    	temp->link = temp->link->link;
    	delete de;
	}
    
    return;
}

template <class T>
void List<T>::Insert(int i, T e)
{
	Node<T>* temp = first;
	Node<T>* newelement = new Node<T>;
	
	for(int j = 1; j < i; j++) temp = temp->link;
    newelement->data = e;
    newelement->link = temp->link;
	temp->link = newelement;
	
	return;
}

template <class T>
T List<T>::Compute()
{
	Iterator i = Begin(), j = Begin();
    T result = 0;
    for(int k = 0; k < 5; k++) j++;
    
    while(j != End()){
    	result += *i * *j;
    	i++;
    	j++;
	}
    
    return result;
}

template <class T>
ostream &operator<<(ostream &os, List<T> &L)
{
    Node<T>* temp = L.first;
    int i = 0;
    
	os << temp->data;
	temp = temp->link;
	while(temp != NULL){
		os << " ¡÷ " << temp->data;
		temp = temp->link;
	}
    os << endl;
    
    return os;
}

// stack
template <class T>
class LinkedStack : public List<T>
{	
	using List<T>::InsertBack;
	using List<T>::DeleteBack;
	using List<T>::first;
public:
	LinkedStack(){top = NULL;}; // constructor
	~LinkedStack(){}
	void Push(const T&);
	T& Top() const;
	void Pop();
	bool IsEmpty();
protected:
	Node<T>* top;
};

template <class T>
void LinkedStack<T>::Push(const T &item)
{
    InsertBack(item);
    if (top == NULL)
        top = first->link;
    else
        top = top->link;
    
    return;
}

template <class T>
T& LinkedStack<T>::Top() const
{
    return top->data;
}

template <class T>
void LinkedStack<T>::Pop()
{
    Node<T> *temp, *pre;
    
    for (temp = first; temp->link != NULL; temp = temp->link) pre = temp;
    DeleteBack();
    top = pre;
    
    return;
}

template <class T>
bool LinkedStack<T>::IsEmpty()
{
    return(top == NULL);
}

// queue
template <class T>
class LinkedQueue : public List<T>
{
	using List<T>::InsertBack;
	using List<T>::DeleteFront;
	using List<T>::first;
public:
	LinkedQueue(){front = new Node<T>; rear = front;}; // constructor
	~LinkedQueue(){};
	void Push(const T&);
	T& Front() const;
	T& Rear() const;
	void Pop();
	bool IsEmpty();
protected:
	Node<T> *front, *rear;
};

template <class T>
void LinkedQueue<T>::Push(const T &item)
{
    InsertBack(item);
    if(rear == front){
        rear = first;
        front->link = rear;
    }
    else rear = rear->link;
    
    return;
}

template <class T>
T& LinkedQueue<T>::Front() const
{
    return(front->link->data);
}

template <class T>
T& LinkedQueue<T>::Rear() const
{
    return(rear->data);
}

template <class T>
void LinkedQueue<T>::Pop()
{
    DeleteFront();
    front->link = first;
    
    return;
}

template <class T>
bool LinkedQueue<T>::IsEmpty()
{
    return(rear == front);
}

int main(void) 
{
    List<int> L1, L2;
    LinkedQueue<int> Q;
    LinkedStack<int> S;
    int num;
    int temp;
    
	cout << "How many element do you want to plug in : ";
	cin >> num;
	for(int i = 0; i < num; i++){
		cin >> temp;
		L1.InsertBack(temp);
        S.Push(temp);
        Q.Push(temp);
	}
	cout << "How many element do you want to plug in : ";
	cin >> num;
	for(int i = 0; i < num; i++){
		cin >> temp;
		L2.InsertBack(temp);
	}
    cout << "List: " << endl;
    cout << "L1 = " << L1;
    
    cout << "What number do you want to insert in front? : ";
    cin >> temp;
    cout << "L1 = : ";
    L1.InsertFront(temp);
    cout << L1;
    cout << "Delete front element in L1 : ";
    L1.DeleteFront();
    cout << L1;
    cout << "Delete Back element in L1 : ";
    L1.DeleteBack();
    cout << L1;
    cout << "Front element of L1 : " << L1.Front() << endl;
    cout << "Back element of L1 : " << L1.Back() << endl;
    
    cout << "Which element do you want to get? : ";
    cin >> temp;
    cout << "Get " << temp << "th element of L1 : " << L1.Get(temp) << endl;
    cout << "Which element do you want to delete? : ";
    cin >> temp;
    cout << "Delete " << temp << "th element of L1 : ";
    L1.Delete(temp);
    cout << L1;
    
    cout << "Where do you want to insert? : ";
    cin >> num;
    cout << "Which element do you want to insert? : ";
    cin >> temp;
    cout << "L1 = : ";
    L1.Insert(num, temp);
    cout << L1;
    cout << "Reverse L1 : ";
    L1.Reverse();
    cout << L1;
    cout << "L2 = " << L2;
    cout << "L1 followed by L2 :";
    L1.Concatenate(L2);
    cout << L1;
    cout << "Compute given expression in L1 : " << L1.Compute() << endl;
    cout << endl;
    
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
    cout << "Pop from S : ";
    S.Pop();
    cout << S;
    cout << endl;
    
    cout << "demo LinkedQueue :" << endl;
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
    return 0;
}
