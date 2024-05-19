#include <iostream>
#include <utility>
using namespace std;

template <class K, class E> class BST;

template <class K, class E>
class TreeNode
{
    friend class BST<K, E>;
public:
    TreeNode(){};
    TreeNode(pair<K, E> thePair){data = thePair;};
private:
    pair<K, E> data;
    TreeNode<K, E> *leftChild = NULL;
    TreeNode<K, E> *rightChild = NULL;
    int leftSize = 1;
};

template <class U>
void ChangeSize1D(U* &a, const int oldSize, const int newSize)
{
    if(newSize < 0) throw "New length must be >= 0";

    U *temp = new U[newSize];
    int number = min(oldSize, newSize);    // choose the smallest Size to store
    copy(a, a + number, temp);          // copy the old array into new
    delete []a;                             // delete old array
    a = temp;
}

template <class K, class E>
class Dictionary{
    template <class A, class B>
    friend ostream& operator<<(ostream &os, Dictionary<A, B> &Dic);
    template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
public:
	Dictionary(int DCapacity = 10);
	virtual bool IsEmpty();
	virtual pair <K, E>* Get(const K&) const;
	virtual void Insert(const pair <K, E>&);
	virtual void Delete(const K&);
private:
	pair<K, E>* pages;
    int capacity;
    int Size;
};

template <class K, class E>
Dictionary<K, E>::Dictionary(int DCapacity)
{
    capacity = DCapacity;
    pages = new pair<K, E>[capacity];
    Size = 0;
}

template <class K, class E>
bool Dictionary<K, E>::IsEmpty()
{
	return Size == 0;
};

template <class K, class E>
pair<K, E>* Dictionary<K, E>::Get(const K &k) const
{
	for(int i = 0; i < Size; i++){
		if(pages[i].first == k) return &pages[i];
	}

	return 0;    
} 

template <class K, class E>
void Dictionary<K, E>::Insert(const pair<K, E> &thePair)
{
    if(capacity == Size){
        ChangeSize1D(pages, capacity, 2 * capacity);
        capacity *= 2;
    }
    pages[Size] = thePair;
    Size++;
    
    return;
}

template <class K, class E>
void Dictionary<K, E>::Delete(const K &k)
{
	int count = 0;
	
    for(int i = 0; i < Size; i++){
        if(pages[i].first == k){
            pages[i].~pair<K, E>();
            int pos = i;
            while(pos + 1< Size){
            	pages[pos] = pages[pos + 1];
            	pos++;
			}
        }
        else count++;
	}
	if(count == Size) cout << "The key doesn't exist" << endl;
	else Size--;
	
    return;
}

template <class A, class B>
ostream& operator<<(ostream &os, Dictionary<A, B> &Dic)
{
    for(int i = 0; i < Dic.Size; i++){
        os << "(" << Dic.pages[i].first << "," << Dic.pages[i].second << ") ";
    }
    os << endl;
    
    return os;
}

template <class K, class E>
class BST: public Dictionary<K, E>
{
	template <class A, class B>
	friend ostream& operator<<(ostream &os, pair<A, B> &pair);
public:
    BST(){root = NULL;};
    bool IsEmpty() const;
    pair<K, E>* Get(const K&);
	pair<K, E>* Get(TreeNode<K, E>*, const K &k);
    void Insert(const pair<K, E>&);
    void Delete(const K&);
    pair<K, E>* RankGet(int r);
    void Split(const K &k, BST<K, E> &small, pair<K, E>* &mid, BST<K, E>&big);
    void Preorder();
	void Preorder(TreeNode<K, E>* currentNode);
    void Inorder();
	void Inorder(TreeNode<K, E>* currentNode);
private:
    TreeNode<K, E>* root;
};

template <class K, class E>
bool BST<K, E>::IsEmpty() const
{
    return root == NULL;
}

template <class K, class E>
pair<K, E>* BST<K, E>::Get(const K &k)
{
    return Get(root, k);
}
template <class K, class E>
pair<K, E>* BST<K, E>::Get(TreeNode<K, E>* p, const K &k)
{
    if(!p) return 0;
    if(k < p->data.first) return Get(p->leftChild, k);
    if(k > p->data.first) return Get(p->rightChild, k);
    return &p->data;
}

template <class K, class E>
void BST<K, E>::Insert(const pair<K, E> &thePair)
{
	TreeNode<K, E> *p = root, *pp = 0;
	while(p){
		pp = p;
		if(thePair.first < p->data.first){
			p->leftSize++;
			p = p->leftChild;
		}
		else if(thePair.first > p->data.first) p = p->rightChild;
		else{ 
			p->data.second = thePair.second; 
			return;
		}
	}
	p = new TreeNode<K, E> (thePair);
	if(root){
		if(thePair.first < pp->data.first) pp->leftChild = p;
		else pp->rightChild = p;
	}
	else root = p;
}

template <class K, class E>
void BST<K, E>::Delete(const K &k)
{
	TreeNode<K, E> *p = root, *pp = p, *ppp;
	
	while(p != NULL && p->data.first != k){
		pp = p;
		if (k == p->data.first);
		else if(k < p->data.first){
			p->leftSize--;	
			p = p->leftChild;
		}
		else p = p->rightChild;
	}
	
	if(p->leftChild != NULL && p->rightChild != NULL){
		pp = p->leftChild;
		ppp = pp;
		while(pp->rightChild != NULL){
			ppp = pp;
			pp = pp->rightChild;
		}
		p->data = pp->data;
		if(pp->leftChild != NULL){				// 替代點的左邊還有元素 
			ppp->rightChild = pp->leftChild;	// 接到上一個的右邊 
			delete pp;
		}
		else if(ppp == pp){
			p->leftChild = NULL;
			delete pp;
		}
		else{									// 替代點的左邊沒有元素
			ppp->rightChild = NULL;				// 刪除替代點 
            delete pp;
		}
	}
	else if(p->leftChild != NULL){				// p右空 
		if(pp->rightChild == p) pp->rightChild = p->leftChild;	// p在pp右邊
        else pp->leftChild = p->leftChild;
        delete p;
	}
	else if(p->rightChild != NULL){				// p左空 
		if(pp->rightChild == p) pp->rightChild = p->rightChild;	// p在pp右邊
        else pp->leftChild = p->rightChild;
        delete p;
	}
	else{										// p左右空 
		if(pp->rightChild == p) pp->rightChild = NULL;	// p在pp右邊
        else pp->leftChild = NULL;
        delete p;
	}
}

template <class K, class E>
pair<K, E>* BST<K ,E>::RankGet(int r)
{
    TreeNode<K, E>* currentNode = root;
    
    while(currentNode){
        if(r < currentNode->leftSize) currentNode = currentNode->leftChild;
        else if(r > currentNode->leftSize) {
            r -= currentNode->leftSize;
            currentNode = currentNode->rightChild;
        }
        else return &currentNode->data;
	}
	
    return 0;
}

template <class K, class E> 
void BST<K, E>::Split(const K& k, BST<K, E>& small, pair<K, E>*& mid, 
BST<K, E>& big)
{ // Split the BST with respect to key k
	if(!root) {small.root = big.root = 0; return;} // empty tree
	TreeNode<K, E>* sHead = new TreeNode<K, E>, *s = sHead, *bHead = new TreeNode<K, E>, *b = bHead, *currentNode = root;
	while(currentNode){
		if(k < currentNode->data.first){ // case 1
			b->leftChild = currentNode;
			b = currentNode; currentNode = currentNode->leftChild;
		}
		else if(k > currentNode->data.first){ // case 2
			s->rightChild = currentNode;
			s = currentNode; currentNode = currentNode->rightChild;
		}
		else{ // case 3 
			s->rightChild = currentNode->leftChild;
			b->leftChild = currentNode->rightChild;
			small.root = sHead->rightChild; delete sHead;
			big.root = bHead->leftChild; delete bHead;
			mid = new pair<K, E>(currentNode->data.first, currentNode->data.second);
			delete currentNode;
			return;
		}			
	}// no pair with key k
	s->rightChild = b->leftChild = 0;
	small.root = sHead->rightChild; delete sHead;
	big.root = bHead->leftChild; delete bHead;
	mid = 0;
	return;
}

template <class K, class E>
void BST<K, E>::Preorder()
{
    Preorder(root);
}
template <class K, class E>
void BST<K, E>::Preorder(TreeNode<K, E>* currentNode)
{
    if (currentNode) {
        cout << currentNode->data;
        Preorder(currentNode->leftChild);
        Preorder(currentNode->rightChild);
    }
}

template <class K, class E>
void BST<K, E>::Inorder()
{
    Inorder(root);
}
template <class K, class E>
void BST<K, E>::Inorder(TreeNode<K, E>* currentNode)
{
    if (currentNode) {
        Inorder(currentNode->leftChild);
        cout << currentNode->data;
        Inorder(currentNode->rightChild);
    }
}

template <class K, class E>
ostream& operator<<(ostream &os, pair<K, E> &pair)
{
    os << "(" << pair.first << "," << pair.second << ") ";
    
    return os;
}

int main(void)
{
	int key, del;
    Dictionary<int, char> D;
    BST<int, char> T, left, right;
    pair<int, char> pair[13], *A, *mid;
    pair[0].first = 50; pair[0].second = 'I';
    pair[1].first = 5; pair[1].second = 'W';
    pair[2].first = 30; pair[2].second = 'I';
    pair[3].first = 40; pair[3].second = 'L';
    pair[4].first = 80; pair[4].second = 'L';
    pair[5].first = 35; pair[5].second = 'G';
    pair[6].first = 2; pair[6].second = 'E';
    pair[7].first = 20; pair[7].second = 'T';
    pair[8].first = 15; pair[8].second = 'A';
    pair[9].first = 60; pair[9].second = '+';
    pair[10].first = 70; pair[10].second = 'Y';
    pair[11].first = 8; pair[11].second = 'N';
    pair[12].first = 10; pair[12].second = 'M';
    
    for(int i = 0; i < 13; i++){
    	cout << "Inserts (" << pair[i].first << ", " << pair[i].second << ") to Dictionary and BST" << endl;
		D.Insert(pair[i]);
		T.Insert(pair[i]);
	}
	cout << endl;
	
	// Dictionary
	cout << "Dictionary :" << endl;
    cout << D;
    
    cout << "Which element do you want to get ? : ";
    cin >> key;
    cout << "Get element with key " << key << " : ";
    A = D.Get(key);
    if(A) cout << *A << endl;
    else cout << "Can't find" << endl;
    
    cout << "Which element do you want to delete ? : ";
    cin >> del;
    cout << "Delete element with key " << del << " : ";
    D.Delete(del);
    cout << endl << D;
    cout << endl;
    
    // BST
    cout << "BST :" << endl;
    cout << "Print BST in order : " << endl;
    T.Inorder();
    cout << endl;
    
    cout << "Which element do you want to get ? : ";
    cin >> key;
    cout << "Get element with key " << key << " : ";
    A = T.Get(key);
    if(A) cout << *A << endl;
    else cout << "Can't find" << endl;
   
    cout << "Which element do you want to delete ? : ";
    cin >> del;
    cout << "Delete element with key " << del << " : " << endl;
    T.Delete(del); T.Inorder(); cout << endl;
    
    cout << "Which element do you want to get by RankGet(1~12)? : ";
    cin >> key;
    A = T.RankGet(key);
    cout << "Get element by rank " << key << " : "<< *A << endl;
    
    cout << "Which element do you want to Split? : ";
    cin >> key;
    cout << "Split the element with key " << key << " : "<< endl;
    T.Split(key, left, mid, right);
    cout << "Print left BST preorder: " << endl;
    left.Preorder(); cout << endl;
    cout << "Mid element : ";
    cout << *mid << endl;
    cout << "Print left BST preorder: " << endl;
    right.Preorder(); cout << endl;
    
    return 0;
}

