#include <iostream>
#include <utility>
using namespace std;


template <class K, class E> class BST;
template <class K, class E>
class TreeNode 
{   
    friend class BST<K, E>;
public:
    TreeNode() {}
    TreeNode(pair<K, E> thePair) { data = thePair; leftChild = rightChild = 0; leftSize = 1;}
private:
    pair<K, E> data;
    TreeNode<K, E> *leftChild;
    TreeNode<K, E> *rightChild;
    int leftSize; // number of nodes in left subtree
};


template <class K, class E>
class Dictionary 
{  
public:
    Dictionary() {} // constructor    
    virtual bool IsEmpty();  
        // return true if dictionary is empty
    virtual pair<K, E>* Get(const K&) const;
        // return pointer to the pair w. specified key         
    virtual void Insert(const pair <K, E>&); 
        // insert the given pair; if key ia a duplicate, update associate element
    virtual void Delete(const K&);  
        // delete pair w. specified key      
};

template <class K, class E>
bool Dictionary<K, E>::IsEmpty()
{
    return true;
}

template <class K, class E>
pair<K, E>* Dictionary<K, E>::Get(const K& k) const
{
    return 0;
}

template <class K, class E>
void Dictionary<K, E>::Insert(const pair<K, E>& thePair)
{
}

template <class K, class E>
void Dictionary<K, E>::Delete(const K& k)
{
}   


template <class K, class E>
class BST : public Dictionary<K, E>
{
    template <class A, class B>
    friend ostream& operator<<(ostream& os, pair<A, B>& pair);
public:
    BST() { root = 0; }  // constructor
    bool IsEmpty() const { return root == 0; }
    pair<K, E>* Get(const K&);  // return pointer to element with key k
    pair<K, E>* Get(TreeNode<K, E>*, const K &k);
    void Insert(const pair<K, E>&);  // insert a pair into the BST
    void Delete(const K&);  // delete the pair with key k
    pair<K, E>* RankGet(int r); // return pointer to element with rank r
    void Split(const K& k, BST<K, E>& small, pair<K, E>*& mid, BST<K, E>& big);
    void Inorder();  // inorder traversal
    void Inorder(TreeNode<K, E> * p);  
    void Preorder();  // preorder traversal
    void Preorder(TreeNode<K, E> * p);  
private:
    TreeNode<K, E> *root;  // pointer to the root
};

template <class K, class E>
pair<K, E>* BST<K, E>::Get(const K& k)
{// Driver
    return Get(root, k);
}
template <class K, class E>
pair<K, E>* BST<K, E>::Get(TreeNode<K, E>* p, const K& k)
{// Workhorse
    if (!p) return 0; //empty
    if (k < p->data.first) return Get(p->leftChild, k);
    if (k > p->data.first) return Get(p->rightChild, k);
    return &p->data;
}

template <class K, class E>
void BST<K, E>::Insert(const pair<K, E>& thePair)
{ // insert thePair into the BST
// search for thePair.first，pp parent of p
    TreeNode<K, E> *p = root, *pp = 0;
    while (p) {
        pp = p;
        if (thePair.first < p->data.first) {
            p->leftSize++;
            p = p->leftChild;
        }
        else if (thePair.first > p->data.first) p = p->rightChild;
        else {// duplicate, update associated element
            p->data.second = thePair.second; 
            return;
        }
    }
    // perform insertion
    p = new TreeNode<K, E> (thePair);
    if (root) // tree is nonempty
        if (thePair.first < pp->data.first) pp->leftChild = p;
        else pp->rightChild = p;
    else root = p;
}

template <class K, class E>
void BST<K, E>::Delete(const K& k) 
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
		if(pp->leftChild != NULL){				 
			ppp->rightChild = pp->leftChild;	
			delete pp;
		}
		else if(ppp == pp){
			p->leftChild = NULL;
			delete pp;
		}
		else{									
			ppp->rightChild = NULL;				
            delete pp;
		}
	}
	else if(p->leftChild != NULL){				
		if(pp->rightChild == p) pp->rightChild = p->leftChild;	
        else pp->leftChild = p->leftChild;
        delete p;
	}
	else if(p->rightChild != NULL){				
		if(pp->rightChild == p) pp->rightChild = p->rightChild;	
        else pp->leftChild = p->rightChild;
        delete p;
	}
	else{										
		if(pp->rightChild == p) pp->rightChild = NULL;	
        else pp->leftChild = NULL;
        delete p;
	}
}

template <class K, class E>
pair<K, E>* BST<K, E>::RankGet(int r) //search by rank
{ //search the BST for the rth smallest pair
    TreeNode <K, E> *currentNode = root;
    while (currentNode) {
        if (r < currentNode -> leftSize)
            currentNode = currentNode -> leftChild;
        else if (r > currentNode -> leftSize) {
            r -= currentNode -> leftSize;
            currentNode = currentNode -> rightChild;
        }
        else return &currentNode->data;
    }
    return 0;
}

template <class K, class E>
void BST<K, E>::Split(const K& k, BST<K, E>& small, pair<K, E>*& mid, BST<K, E>& big)
{ // Split the BST with respect to key k
    if (!root) {small.root = big.root = 0; return;} // empty tree
    // create temporary header nodes for small and big
    TreeNode<K, E> *sHead = new TreeNode<K, E>,
                   *s = sHead,
                   *bHead = new TreeNode<K, E>,
                   *b = bHead,
                   *currentNode = root;

    while (currentNode) {
        if (k < currentNode->data.first) { // case 1
            b->leftChild = currentNode;
            b = currentNode; currentNode = currentNode->leftChild;
        }
        else if (k > currentNode->data.first) { // case 2
            s->rightChild = currentNode;
            s = currentNode; currentNode = currentNode->rightChild;
        }
        else { // case 3
            s->rightChild = currentNode->leftChild;
            b->leftChild = currentNode->rightChild;
            small.root = sHead->rightChild; delete sHead;
            big.root = bHead->leftChild; delete bHead;
            mid = new pair<K, E>(currentNode->data.first,
                                 currentNode->data.second);
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
void BST<K, E>::Inorder()
{
    Inorder(root);    //Traverse inorderly
}
template <class K, class E>
void BST<K, E>::Inorder(TreeNode<K, E> * p)
{// Workhorse, a recursive function
    if(p) {
        Inorder (p->leftChild); // L
        cout << p->data; // **V**
        Inorder (p->rightChild); // R
    }
}

template <class K, class E>
void BST<K, E>::Preorder()
{
    Preorder(root);    //Traverse preorderly
}
template <class K, class E>
void BST<K, E>::Preorder(TreeNode<K, E> * p)
{// Workhorse, a recursive function
    if(p) {
        cout << p->data; // **V**
        Preorder (p->leftChild); // L
        Preorder (p->rightChild); // R
    }
}


template <class K, class E>
ostream& operator<<(ostream &os, pair<K, E> &pair)
{
    os << "(" << pair.first << "," << pair.second << ") ";
    
    return os;
}


int main()
{
    int key, del;
    BST<int, char> T, left, right;
    pair<int, char> pair[13], *A, *mid;
    pair[0].first = 50; pair[0].second = 'A';
    pair[1].first = 5; pair[1].second = 'B';
    pair[2].first = 30; pair[2].second = 'C';
    pair[3].first = 40; pair[3].second = 'D';
    pair[4].first = 80; pair[4].second = 'E';
    pair[5].first = 35; pair[5].second = 'F';
    pair[6].first = 2; pair[6].second = 'G';
    pair[7].first = 20; pair[7].second = '+';
    pair[8].first = 15; pair[8].second = '-';
    pair[9].first = 60; pair[9].second = '*';
    pair[10].first = 70; pair[10].second = '=';
    pair[11].first = 8; pair[11].second = 'M';
    pair[12].first = 10; pair[12].second = 'N';
    
    for(int i = 0; i < 13; i++){
    	cout << "Inserts (" << pair[i].first << ", " << pair[i].second << ") to Dictionary and BST" << endl;
		T.Insert(pair[i]);
	}
	cout << endl;

    
    // BST
    cout << "BST :" << endl;
    cout << "Print BST in inorder : " << endl;
    T.Inorder(); cout << endl;
    cout << "Print BST in preorder : " << endl;
    T.Preorder();
    cout << endl << endl;


    cout << "------------------------------------" << endl;
    

    cout << "Which element do you want to get ? : ";
    cin >> key;
    cout << "Get element with key " << key << " : ";
    A = T.Get(key);
    if(A) cout << *A << endl << endl;
    else cout << "Can't find" << endl << endl;
   
    cout << "Which element do you want to delete(enter a key) ? : ";
    cin >> del;
    cout << "Delete element with key " << del << " : " << endl;
    T.Delete(del); T.Inorder(); cout << endl << endl;
    
    cout << "Which element do you want to get by RankGet(enter a rank in the range 1~12)? : ";
    cin >> key;
    A = T.RankGet(key);
    cout << "Get element by rank " << key << " : "<< *A << endl;


    cout << "------------------------------------" << endl;


    cout << "Which element do you want to Split the BST with? : ";
    cin >> key;
    cout << "Split the element with key " << key << " : "<< endl;
    T.Split(key, left, mid, right);

    cout << "Left BST: " << endl;
    cout << "Preorder: ";
    left.Preorder(); cout << endl;
    cout << "Inorder: ";
    left.Inorder(); cout << endl << endl;

    cout << "Mid element : ";
    cout << *mid << endl << endl;

    cout << "Right BST: " << endl;
    cout << "Preorder: ";
    right.Preorder(); cout << endl;
    cout << "Inorder: ";
    right.Inorder(); cout << endl;

    return 0;
}