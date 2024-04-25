#include <iostream>

using namespace std;

template < class T > class Chain;  // 前向宣告
template <class T>  ostream& operator<<(ostream &os, Chain<T> &c);


template < class T >
class ChainNode {
    friend class Chain <T>;
    friend ostream& operator<<<T>(ostream& os, Chain<T>& c);
public:
    ChainNode(int element = 0, ChainNode<T>* next = 0):data(element), link(next){};
private:
	T data;
	ChainNode<T>* link;
};

template <class T>
class Chain
{

     friend ostream& operator<<<T>(ostream &os, Chain<T> &c);
public:
	Chain( ) {first = 0;} // 建構子將first初始化成0
	~Chain();
	void InsertFront(const T& e);
    void InsertBack(const T& e);

	void DeleteFront();
	void DeleteBack();
	T& Front();
	T& Back();
	T& Get(int i);
	void Delete(int i);
	void Insert(int i, T e);
	int Length();
	void ChangeData(int k, T Y);
	void D_E_O();
	void divideMid(Chain<T>& myList, Chain<T>& subList);
	void split(int k, Chain<T> &x);
	Chain merge(Chain y);
	/*class Iterator {
        public:
            Iterator(ChainNode<T>* startNode = 0) {current = startNode;};
            T& operator *() const {return current->data;}
            T* operator ->() const {return &current->data;}
            Iterator& operator++()     // preincrement
                {current = current->link; return *this;}
            Iterator operator++(int)   // postincrement
                {
                    Iterator old = *this;
                    current = current->link;
                    return old;
                }
            bool operator!=(const Iterator right) const
                {return current != right.current;}
            bool operator==(const Iterator right) const
                {return current == right.current;}
        private:
            ChainNode<T>* current;
        };
        Iterator begin(){return Iterator(first);}
        Iterator end(){return Iterator(0);}
        friend ostream& operator << (ostream& out, Chain<T>& L1) {
            for (Iterator i = L1.begin(); i != L1.end(); i++)
                out << *i << " ";
            return out;
        }*/
private:
	ChainNode<T> * first;
};

template<class T>
Chain<T>::~Chain()
{
    while(first == NULL) {
        ChainNode<T>* next = first->link;
        delete first;
        first = next;
    }
}

template<class T>
void Chain<T>::InsertBack(const T& e)
{
    if (first) {
        ChainNode<T>* last;
        for(last = first; last->link != NULL; last = last->link){}
        last->link = new ChainNode<T>(e);
    }
    else first = new ChainNode<T>(e);
}

template<class T>
void Chain<T>::InsertFront(const T& e)
{
    if (first) {
        ChainNode<T>* newfirst = new ChainNode<T>(e, first);
        first = newfirst;
    }
    else first = new ChainNode<T>(e);
}

template<class T>
void Chain<T>::DeleteFront()
{
    if (first == NULL) throw "The list is empty. Cannot delete.";
    ChainNode<T>* delNode = first;
    first = first->link;
    delete delNode;
}

template<class T>
void Chain<T>::DeleteBack()
{
    if (first == NULL) throw "The list is empty. Cannot delete.";
    ChainNode<T>* delNode;
    ChainNode<T>* curr;
    for (curr = first; curr->link->link != NULL; curr = curr->link){}
    delNode = curr->link;
    curr->link = NULL;
    delete delNode;
}

template<class T>
inline T& Chain<T>::Front()
{
    if (first == NULL) throw invalid_argument("The list is empty. We don't have front element.");
    return first->data;
}

template<class T>
T& Chain<T>::Back()
{
    if (first == NULL) throw invalid_argument("The list is empty. We don't have back element.");
    ChainNode<T>* last;
    for (last = first; last->link != NULL; last = last->link){}
    return last->data;
}

template<class T>
T& Chain<T>::Get(int i)
{
    ChainNode<T>* current = first;
    for (int j = 0; j < i - 1; j++)
        current = current->link;
    return current->data;
}

template<class T>
void Chain<T>::Delete(int i)
{
    if (first == NULL) throw invalid_argument("The list is empty. Cannot delete.");
    int index;
    ChainNode<T>* pre = first;
    for (index = 1; index < i - 1 && pre->link != NULL; index++) pre = pre->link;
    if (pre->link == NULL) throw invalid_argument("The list has less than i elements. Cannot delete the ith element.");
    ChainNode<T>* delNode = pre->link;
    pre->link = pre->link->link;
    delete delNode;
}

template<class T>
void Chain<T>::Insert(int i, T e)
{
    if (first == NULL) {
        if (i == 1) first = new ChainNode<T>(e);
        else throw invalid_argument("The list is empty. We can just insert at the first position.");
    }
    else {
        ChainNode<T>* pre = first;
        int index;
        for (index = 1; index < i - 1 && pre->link != NULL; index++) pre = pre->link;
        if (pre->link == NULL) {
            if (index == i - 1) pre->link = new ChainNode<T>(e); // pre points to the last node and we can directly add one new node
            else throw invalid_argument("We cannot insert at the ith  position because there is no (i-1)th element.");
        }
        else {
            ChainNode<T>* newNode = new ChainNode<T>(e, pre->link);
            pre->link = newNode;
        }
    }
}

template <class T>
int Chain<T>::Length()
{
    int length = 0;
    for (ChainNode<T> *current = first; current != 0; current = current -> link)
        length++;			// 當找到一個新node時，長度加1
    return length;
}

template <class T>
void Chain<T>::ChangeData(int k, T Y)
{
	ChainNode<T> *current = first;
	for (int i = 0; i < k - 1; i++)		// find the kth element
		current = current->link;
	current->data = Y;
}

template <class T>
void Chain<T>::D_E_O()
{
	if (first) {			// check whether the first node exist
		ChainNode<T> *del = first;	// delete the first node
		first = first->link;
		delete del;
		// delete other node
		for (ChainNode<T> *current = first; current != 0; current = current->link) {
			del = current->link;
			if (del) {	// check whether the del node exist
				current->link = del->link;
				delete del;
			}
		}
	}
}

template <class T>
void Chain<T>::divideMid(Chain<T>& myList, Chain<T>& subList)
{
	int length = Length() / 2;
	myList.first = first;
	ChainNode<T> *current = first;
	for (int i = 0; i < length - 1; i++)		// put current to the middle
		current = current->link;
	if (Length() % 2 == 0) {				// if the number of chainNode is
		subList.first = current->link;			// even, divide the chain at that
		current->link = NULL;			// position
	}
	else {							// if the number of chainNode is
		subList.first = current->link->link;	// odd, divide the chain at next
		current->link->link = NULL;		// position
	}
}

template <class T>
void Chain<T>::split(int k, Chain<T> &x)	// x point to first of second chain
{
	ChainNode<T>* current = first;
	for (int i = 0; i < k - 2; i++) {
        current = current->link;
	}	// cut the link
	x.first = current->link;
	current->link = NULL;							// between
}


template <class T>
ostream &operator<<(ostream &os, Chain<T> &c)
{
    ChainNode<T> *temp = c.first;
    while(temp!= NULL){
        os << temp->data;
        if(temp -> link != NULL)
            cout << "->";
        temp = temp->link;
    }
    return os;
}
template <class T>
Chain<T> Chain<T>::merge(Chain<T> y)
{
	bool k;
    Chain<T> z;
    ChainNode<T> *tmp = new ChainNode<T>;
//    ChainNode<T> *y_first = y.first;
    int size_x = this -> Length();
    int size_y = y.Length();

    if(size_x == 0 && size_y == 0){
        z.first = 0;
        return z;
    }else if(size_x == 0){
        z.first = y.first;
        return z;
    }else if(size_y == 0){
        z.first = this -> first;
        return z;
    }

    z.first = this -> first;		// set up first node in L3

    if(size_x > size_y)
    	k = true;
    else
    	k = false;

    if(k){
    	for(int i = 0; i < size_y; i++){
    		tmp -> link = this -> first; 	// first take from L1
    		this -> first = this -> first -> link;
    		tmp -> link -> link = y.first;		// second take from L2
    		y.first = y.first -> link;
    		tmp = tmp -> link -> link;	// update tmp
    	}
    	tmp -> link = this -> first;		// link the rest nodes in L1
    }else{
    	for(int i = 0; i < size_x; i++){
	    	tmp -> link = this -> first; 	// first take from L1
	    	this -> first = this -> first -> link;
	    	tmp -> link -> link = y.first;		// second take from L2
	    	y.first = y.first -> link;
	    	tmp = tmp -> link -> link;	// update tmp
	    }
        tmp -> link = y.first;		// link the rest nodes in L2
//        while(tmp -> link != y_first)
//            tmp = tmp -> link;

//        tmp -> link = NULL;
    }
    return z;
}

int main() {
    Chain<int> L2, L3, L4, L5;
    Chain<int> list;
    int ch, item, index;
    bool quit = false;
    int i = 0;
    do{
        while(!i){
        cout<<"===================================="<<endl;
        cout<<"select option :"<<endl;
        cout<<"1: insert back"<<endl;
        cout<<"2: insert front"<<endl;
        cout<<"3: insert at index"<<endl;
        cout<<"4: display items"<<endl;
        cout<<"5: get item at index"<<endl;
        cout<<"6: delete back"<<endl;
        cout<<"7: delete front"<<endl;
        cout<<"8: delete at index"<<endl;
        cout<<"9: exit"<<endl;
        i++;
        }
        cin>>ch;
        //cout<<"===================================="<<endl;
        switch (ch)
        {
        case 1:
            //cout<<"enter item to insert:"<<endl;
            cin>>item;
            list.InsertBack(item);
            break;
        case 2:
            //cout<<"enter item to insert:"<<endl;
            cin>>item;
            list.InsertFront(item);
            break;
        case 3:
            cout<<"enter item to insert:"<<endl;
            cin>>item;
            cout<<"enter index:"<<endl;
            cin>>index;
            list.Insert(index, item);
            break;
        case 4:
            cout << list << endl;
            break;

        case 5:
            cout<<"enter index:"<<endl;
            cin>>index;
            cout<<"item at index "<<index<<": "<<list.Get(index)<<endl;
            break;
        case 6:
            list.DeleteBack();
            break;
        case 7:
            list.DeleteFront();
            break;
        case 8:
            cout<<"enter index:"<<endl;
            cin>>index;
            list.Delete(index);
            break;
        case 9:
            quit = true;
            break;
        default:
            cout<<"invalid selection"<<endl;
            break;
        }
    }while(!quit);

    cout << "The first element of L1 now is " << list.Front() << endl;
    cout << "The last element of L1 now is " << list.Back() << endl;
    cout << "The length of L1 is " << list.Length() << endl;

    int j, in;

    cout << "Position you want to change: ";
    cin >> i;
    cout << "New value: ";
    cin >> in;
    list.ChangeData(i, in);
    cout << "L1 now is " << list << endl;

    cout << "Delete every other node" << endl;
    list.D_E_O();
    cout << "L1 now is " << list << endl;

    cout << "divide L1 into L2 and L3" << endl;
    list.divideMid(L2, L3);
    cout << "L2 now is " << L2 << endl;
    cout << "L3 now is " << L3 << endl;
    cout << "Split L2 into L2 and L4" << endl;
    cout << "Split L2 in which position: ";
    cin >> j;
    L2.split(j, L4);
    cout << "L4 now is " << L4 << endl;
    cout << "merge L4 and L3 in L5" << endl;
    L5 = L4.merge(L3);
    cout << "L5 now is " << L5 << endl;
    cout << "Delete all the data in L5" << endl;

    list.~Chain<int>();
}
