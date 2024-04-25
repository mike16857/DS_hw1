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
		header = new ChainNode<T>;
        header->link = header;
	};
    int count();
    void insertFront(T e);
    void insertBack(T e);
    void deleteFirst();
    void deleteLast();
    void deleteOther();
    void deconcatenate(HeaderCircularList<T> &split, int i);
    HeaderCircularList<T> merge(HeaderCircularList<T> &L2);
private:
    ChainNode<T>* header;
};

template <class T>
int HeaderCircularList<T>::count()
{
	int num = 1;
	ChainNode<T>* temp = header->link;
	
	while(temp->link != header){
		num++;
		temp = temp->link;
	}
	
	return num;
}

template <class T>
void HeaderCircularList<T>::insertFront(T e)
{
    ChainNode<T> *newNode = new ChainNode<T>;
    newNode->data = e;
    newNode->link = header->link;
    header->link = newNode;
	
    return;
}

template <class T>
void HeaderCircularList<T>::insertBack(T e)
{
    ChainNode<T>* temp = header->link;
    
    while(temp->link != header) temp = temp->link;
  	ChainNode<T> *newNode = new ChainNode<T>;
    newNode->data = e;
    newNode->link = header;
    temp->link = newNode;
	
    return;
}

template <class T>
void HeaderCircularList<T>::deleteFirst()
{
    if (header->link == NULL) throw "The List is empty, cannot delete.";
    ChainNode<T>* temp = header->link;
    header->link = temp->link;
    delete temp;
    
    return;
}

template <class T>
void HeaderCircularList<T>::deleteLast()
{
    if (header->link == NULL) throw "The List is empty, cannot delete.";
    ChainNode<T>* temp = header->link;
    
    while(temp->link->link != header) temp = temp->link;
	delete temp->link;
    temp->link = header;
    
    return;
}

template <class T>
void HeaderCircularList<T>:: deleteOther()
{
	int num = count();
	num = (num + 1) / 2;
	ChainNode<T>* temp;
	ChainNode<T>* de;
	
	if (header->link == NULL) throw "The List is empty, cannot delete.";
	deleteFirst();
	num--;
	temp = header->link;
	for(int i = 0; i < num; i++){
		de = temp->link;
		temp->link = temp->link->link;
		delete de; 
		temp = temp->link;
	}
	
	return;
}

template <class T>
void HeaderCircularList<T>::deconcatenate(HeaderCircularList<T> &split, int i)
{
    ChainNode<T>* temp = header->link;
    ChainNode<T>* end;
    
    for(int j = 1; j < i;j++) temp = temp->link;
    end = temp;
    temp = temp->link;
    while (temp != header) {
        split.insertBack(temp->data);
        temp = temp->link;
    }
    end->link = header;
    
    return;
}

template <class T>
HeaderCircularList<T> HeaderCircularList<T>::merge(HeaderCircularList<T> &L2)
{
    ChainNode<T>* temp1 = header->link;
    ChainNode<T>* temp2 = L2.header->link;
    HeaderCircularList<T> me;
    
    if (count() == 0 && L2.count() == 0) throw "Two Lists are both empty, cannot merge.";
    while(temp1->link != header && temp2->link != L2.header){
		me.insertBack(temp1->data);
		temp1 = temp1->link;
		me.insertBack(temp2->data);
		temp2 = temp2->link;
    }
    me.insertBack(temp1->data);
	temp1 = temp1->link;
    me.insertBack(temp2->data);
    temp2 = temp2->link;
    while(temp1 != header){
		me.insertBack(temp1->data);
		temp1 = temp1->link;
	}
    while(temp2 != L2.header){
		me.insertBack(temp2->data);
		temp2 = temp2->link;
	}
	
    return me;
}

template <class T>
ostream &operator<<(ostream &os, HeaderCircularList<T> &L)
{
    ChainNode<T>* temp = L.header->link;
    int i = 0;
    
	os << temp->data;
	temp = temp->link;
	while(temp != L.header){
		os << " ¡÷ " << temp->data;
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
	for(int i = 0; i < num; i++){
		is >> temp;
		L.insertBack(temp);
	}
	
    return is;
}

int main(void)
{
    HeaderCircularList<int> L1, L2, L3, L4;
    int k, num;
    
    cin >> L1;
    cin >> L2;
	cout << "L1 = " << L1;
    cout << "Length of L1 : " << L1.count() << endl;
    cout << "L2 = " << L2;
    
    cout << "Delete the first node in L1 : ";
    L1.deleteFirst();
    cout << L1;
    cout << "Delete the last node in L1 : ";
    L1.deleteLast();
    cout << L1;
    
    cout << "What number do you want to insert in front? : ";
    cin >> num;
	L1.insertFront(num);
    cout << "After insert : ";
    cout << L1;
    cout << "What number do you want to insert in back? : ";
    cin >> num;
    cout << "After insert : ";
    L1.insertBack(num);
    cout << L1;
    
    cout << "Delete every other node in L1 : ";
    L1.deleteOther();
    cout << L1;
    
    cout << "Where do you want to split in L2? : ";
    cin >> num;
    cout << "Split L2 : ";
    L2.deconcatenate(L3, num);
    cout << "First piece : " << L2;
    cout << "Second piece : " << L3;
    cout << "merge L2 Back : ";
    L4 = L2.merge(L3);
    cout << L4;
    
    return 0;
}
