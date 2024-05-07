#include <iostream>
using namespace std;


template <class T> class HeaderCircularList;


template <class T>
class ChainNode
{
	template <class U>
    friend class HeaderCircularList;
    template <class U>
    friend ostream &operator<<(ostream &os, HeaderCircularList<U> &L);
    template <class U>
	friend istream &operator>>(istream& is, HeaderCircularList<U> &L);
public:
    ChainNode(const T& e = 0, ChainNode<T>* next = 0): data(e), link(next) {}
private:
    T data;
    ChainNode<T>* link;
};


template <class T>
class HeaderCircularList
{
    template <class U>
    friend ostream &operator<<(ostream &os, HeaderCircularList<U> &L);
    template <class U>
    friend istream &operator>>(istream& is, HeaderCircularList<U> &L);
public:
    HeaderCircularList()
	{
		head = new ChainNode<T>;
        head->link = head;
	};
    int length();
    void InsertFront(T e);
    void InsertBack(T e);
    void DeleteFirst();
    void DeleteBack();
    void deleteOdd();
    void deconcatenate(HeaderCircularList<T> &L2, T e);
    HeaderCircularList<T> merge(HeaderCircularList<T> &L2);
private:
    ChainNode<T> *head;
};

template <class T>
int HeaderCircularList<T>::length() 
{
    int count = 0;
    ChainNode<T> *tmp = head;
    while (tmp->link != head) {
        count++;
        tmp = tmp->link;
    }
    return count;
}

template <class T>
void HeaderCircularList<T>::InsertFront(T element) 
{
    ChainNode<T> *newNode = new ChainNode<T>(element);
    newNode->link = head->link;
    head->link = newNode;
}

template <class T>
void HeaderCircularList<T>::InsertBack(T element) 
{
    ChainNode<T> *newNode = new ChainNode<T>(element);
    ChainNode<T> *tmp = head;
    while (tmp->link != head) {
        tmp = tmp->link;
    }
    tmp->link = newNode;
    newNode->link = head;
}

template <class T>
void HeaderCircularList<T>::DeleteFirst() 
{
    ChainNode<T> *toDel = head->link;
    head->link = toDel->link;
    delete toDel;
}

template <class T>
void HeaderCircularList<T>::DeleteBack() 
{
    ChainNode<T> *tmp = head;
    ChainNode<T> *toDel;
    while (tmp->link->link != head) {
        tmp = tmp->link;
    }
    toDel = tmp->link;
    tmp->link = head;
    delete toDel;
}

// template <class T>
// void HeaderCircularList<T>::deleteOdd() 
// { 
//     int times = (length() + 1) / 2;
// 	ChainNode<T>* tmp;
// 	ChainNode<T>* toDel;
	
// 	if (first == NULL) throw "The List is empty, cannot delete.";
// 	DeleteFirst();
// 	times--;
// 	tmp = first;

// 	for (int i = 0; i < times; i++) {
// 		toDel = tmp->link;
// 		tmp->link = tmp->link->link;
// 		delete toDel; 
// 		tmp = tmp->link;
// 	} 
// }

template <class T>
void HeaderCircularList<T>::deleteOdd() 
{ 
    ChainNode<T> *tmp = head->link->link;
    ChainNode<T> *toDel = head->link;
    delete toDel;
    head->link = tmp;
    while (tmp != head) {
        toDel = tmp->link;
        if (toDel == head) {
            break; // if number of nodes is even
        }
        tmp->link = toDel->link;
        delete toDel;
        tmp = tmp->link;
    }
}

template <class T>
void HeaderCircularList<T>::deconcatenate(HeaderCircularList<T> &L2, T e) 
{
    ChainNode<T> *split = head->link;
    ChainNode<T> *before, *tmp;

    while (split != head) {
        if (split->data == e) break;
        before = split;
        split = split->link;
    }

    L2.head->link = split;     // split points to the first node of L2
    before->link = head;       // wrap around L1
    
    tmp = L2.head->link;
    while (tmp->link != head) {
        tmp = tmp->link;
    }
    tmp->link = L2.head;       // wrap around L2
}

template <class T>
HeaderCircularList<T> HeaderCircularList<T>::merge(HeaderCircularList<T> &L2) 
{
    HeaderCircularList<T> L3;
    ChainNode<T> *curr1 = head->link;
    ChainNode<T> *curr2 = L2.head->link;

    while (curr1 != head && curr2 != L2.head) {
        L3.InsertBack(curr1->data);
        L3.InsertBack(curr2->data);
        curr1 = curr1->link;
        curr2 = curr2->link;
    }

    // at this point, either curr1 or curr2 is at the end of the list    
    while (curr2 != L2.head) {
        L3.InsertBack(curr2->data);
        curr2 = curr2->link;
    }
    while (curr1 != head) {
        L3.InsertBack(curr1->data);
        curr1 = curr1->link;
    }

    return L3;
}

// template <class T>
// HeaderCircularList<T> HeaderCircularList<T>::merge(HeaderCircularList<T> &L2) 
// {   
//     HeaderCircularList<T> L3;
//     ChainNode<T> *curr1 = head->link;
//     ChainNode<T> *curr2 = L2.head->link;
//     ChainNode<T> *next1, *next2;

//     while (curr1->link != head && curr2->link != L2.head) {
//         next1 = curr1->link;
//         next2 = curr2->link;
//         curr1->link = curr2;
//         curr2->link = next1;
//         curr1 = next1;
//         curr2 = next2;
//     }

//     // if L1 is shorter
//     if (curr1->link == head) { 
//         curr1->link = curr2;
//         while (curr2->link != L2.head) {
//             curr2 = curr2->link;
//         }
//         curr2->link = head;    // wrap around
//     }
//     // if L2 is shorter
//     else {                     
//         next1 = curr1->link;
//         curr1->link = curr2;
//         curr2->link = next1;
//         while (next1->link != head) {
//             next1 = next1->link;
//         }
//         next1->link = head;   // wrap around
//     }

//     L3 = *this;
//     return L3;
// }

template <class T>
ostream &operator<<(ostream &os, HeaderCircularList<T> &L)
{
    ChainNode<T>* temp = L.head->link;
    
	os << temp->data;
	temp = temp->link;
	while(temp != L.head){
		os << " -> " << temp->data;
		temp = temp->link;
	}
    os << endl;
    
    return os;
}

template <class T>
istream &operator>>(istream& is, HeaderCircularList<T> &L)
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
    HeaderCircularList<int> L1, L2, L3, L4;
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