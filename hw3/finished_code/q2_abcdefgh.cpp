#include <iostream>
using namespace std;


template <class T> class CircularList;


template <class T>
class ChainNode
{
	template <class U>
    friend class CircularList;
    template <class U>
    friend ostream &operator<<(ostream &os, CircularList<U> &L);
    template <class U>
	friend istream &operator>>(istream& is, CircularList<U> &L);
public:
    ChainNode(const T& e, ChainNode<T>* next = 0): data(e), link(next) {}
private:
    T data;
    ChainNode<T>* link;
};


template <class T>
class CircularList
{
    template <class U>
    friend ostream &operator<<(ostream &os, CircularList<U> &L);
    template <class U>
    friend istream &operator>>(istream& is, CircularList<U> &L);
public:
    CircularList() {first = NULL;}
    int length();
    void InsertFront(T e);
    void InsertBack(T e);
    void DeleteFirst();
    void DeleteBack();
    void deleteOdd();
    void deconcatenate(CircularList<T> &L2, T e);
    CircularList<T> merge(CircularList<T> &L2);
private:
    ChainNode<T>* first;
};

template <class T>
int CircularList<T>::length() 
{
    int count = 1;
    ChainNode<T> *tmp = first;
    while (tmp->link != first) {
        count++;
        tmp = tmp->link;
    }
    return count;
}

template <class T>
void CircularList<T>::InsertFront(T element) 
{
    ChainNode<T> *newNode = new ChainNode<T>(element);
    if (first == NULL) {
        first = newNode;
        first->link = first;
    } 
    else {
        newNode->link = first->link;
        first->link = newNode;
        newNode->data = first->data;
        first->data = element;
    }
}

template <class T>
void CircularList<T>::InsertBack(T element) 
{
    ChainNode<T> *newNode = new ChainNode<T>(element);
    if (first == NULL) {
        first = newNode;
        first->link = first;
    } 
    else {
        newNode->link = first->link;
        first->link = newNode;
        newNode->data = first->data;
        first->data = element;
        first = newNode;
    }
}

template <class T>
void CircularList<T>::DeleteFirst() 
{
    if (first->link == first) {
        delete first;
        first = NULL;
    } 
    else {
        ChainNode<T> *toDel = first;
        ChainNode<T> *last = first;
        while (last->link != first) {
            last = last->link;
        }
        last->link = first->link;
        first = first->link;
        delete toDel;
    }
}

template <class T>
void CircularList<T>::DeleteBack() 
{
    if (first->link == first) {
        delete first;
        first = NULL;
    } 
    else {
        ChainNode<T> *beforeNode = first;
        ChainNode<T> *last;
        while (beforeNode->link->link != first) {
            beforeNode = beforeNode->link;
        }
        last = beforeNode->link;
        beforeNode->link = first;
        delete last;
    }
}

template <class T>
void CircularList<T>::deleteOdd() 
{ 
    int times = (length() + 1) / 2;
	ChainNode<T>* tmp;
	ChainNode<T>* toDel;
	
	if (first == NULL) throw "The List is empty, cannot delete.";
	DeleteFirst();
	times--;
	tmp = first;

	for (int i = 0; i < times; i++) {
		toDel = tmp->link;
		tmp->link = tmp->link->link;
		delete toDel; 
		tmp = tmp->link;
	} 
}

template <class T>
void CircularList<T>::deconcatenate(CircularList<T> &L2, T e) 
{
    ChainNode<T> *split = first;
    ChainNode<T> *before, *tmp;
    while (split->link != first) {
        if (split->data == e) break;
        before = split;
        split = split->link;
    }

    L2.first = split;     // split points to the first node of L2
    before->link = first; // wrap around L1
    
    tmp = L2.first;
    while (tmp->link != first) {
        tmp = tmp->link;
    }
    tmp->link = L2.first; // wrap around L2
}

template <class T>
CircularList<T> CircularList<T>::merge(CircularList<T> &L2) 
{
    CircularList<T> L3;
    ChainNode<T> *curr1 = first;
    ChainNode<T> *curr2 = L2.first;

    while (curr1->link != first && curr2->link != L2.first) {
        L3.InsertBack(curr1->data);
        L3.InsertBack(curr2->data);
        curr1 = curr1->link;
        curr2 = curr2->link;
    }

    L3.InsertBack(curr1->data);
    L3.InsertBack(curr2->data);
    curr1 = curr1->link;
    curr2 = curr2->link;

    // at this point, either curr1 or curr2 is at the end of the list    
    while (curr2 != L2.first) {
        L3.InsertBack(curr2->data);
        curr2 = curr2->link;
    }
    while (curr1 != first) {
        L3.InsertBack(curr1->data);
        curr1 = curr1->link;
    }

    return L3;
}

template <class T>
ostream &operator<<(ostream &os, CircularList<T> &L)
{
    ChainNode<T>* temp = L.first;
    
	os << temp->data;
	temp = temp->link;
	while(temp != L.first){
		os << " -> " << temp->data;
		temp = temp->link;
	}
    os << endl;
    
    return os;
}

template <class T>
istream &operator>>(istream& is, CircularList<T> &L)
{
    int num;
    int temp;
    
	cout << "How many element do you want to plug in : ";
	is >> num;
	cout << "What do you want to plug in : ";
	for(int i = 0; i < num; i++){
		is >> temp;
		L.InsertBack(temp);
	}
	
    return is;
}


int main()
{
    CircularList<int> L1, L2, L3, L4;
    int k, num;
    
    cout << "Enter L1:" << endl;
    cin >> L1;
    cout << "Enter L2:" << endl;
    cin >> L2;
	cout << "L1 = " << L1;
    cout << "Length of L1 : " << L1.length() << endl;
    cout << "L2 = " << L2;
    
    cout << "Delete the first node in L1 : ";
    L1.DeleteFirst();
    cout << L1;
    cout << "Delete the last node in L1 : ";
    L1.DeleteBack();
    cout << L1;
    
    cout << "What number do you want to insert in the front of L1? : ";
    cin >> num;
	L1.InsertFront(num);
    cout << "After insert : ";
    cout << L1;
    cout << "What number do you want to insert in the back of L1? : ";
    cin >> num;
    cout << "After insert : ";
    L1.InsertBack(num);
    cout << L1;
    
    cout << "Delete every other node in L1 (The first, 3rd, 5th, ... node are deleted): ";
    L1.deleteOdd();
    cout << L1;
    
    cout << "Where do you want to split in L2? : ";
    cin >> num;
    cout << "Split L2 : ";
    L2.deconcatenate(L3, num);
    cout << "L2 after split : " << L2;
    cout << "The list \"split\" points to: " << L3;
    cout << "merge L1 and L2 : ";
    L4 = L1.merge(L2);
    cout << L4;
    
    return 0;
}