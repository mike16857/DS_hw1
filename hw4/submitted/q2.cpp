#include <iostream>
using namespace std;


template <class T> class ThreadedTree;
template <class T> class ThreadedInorderIterator;
template <class T>
class ThreadedNode 
{
    friend class ThreadedTree<T>;
    friend class ThreadedInorderIterator<T>; //inorder iterator
public:
    ThreadedNode(const T& value);
private:
    T data;
    bool leftThread;
    ThreadedNode<T> *leftChild;
    bool rightThread;
    ThreadedNode<T> *rightChild;
};

template <class T>
ThreadedNode<T>::ThreadedNode(const T& value)
{
    data = value;
    leftThread = true;
    leftChild = NULL;
    rightThread = true;
    rightChild = NULL;
}


template<class T>
class ThreadedTree
{ 
    friend class ThreadedInorderIterator<T>;  //inorder iterator
public:
    ThreadedTree(); 
    ThreadedNode<T>* InorderSucc(ThreadedNode<T>* p);
    ThreadedNode<T>* InorderPred(ThreadedNode<T>* p);    
    void Preorder(); //
    void Postorder();   //
    void InsertRight(ThreadedNode<T>* s, ThreadedNode<T>* r); // insert r as the right child of s //
    void InsertLeft(ThreadedNode<T>* s, ThreadedNode<T>* l); // insert l as the left child of s //
    ThreadedNode<T>* Head(){return head;}
private:
	ThreadedNode<T> *head;
};

template <class T>
ThreadedTree<T>::ThreadedTree()
{
    head = new ThreadedNode<T>(T());
    head->leftChild = NULL;
    head->leftThread = true;
    head->rightChild = head;
    head->rightThread = false;
}

template <class T>
ThreadedNode<T>* ThreadedTree<T>::InorderSucc(ThreadedNode<T>* p) // return the inorder successor of p
{
    ThreadedNode<T> *temp = p->rightChild;
    if(p->rightThread) return temp;
    else{
        while(!temp->leftThread) temp = temp->leftChild;
        return temp;
    }
}

template <class T>
ThreadedNode<T>* ThreadedTree<T>::InorderPred(ThreadedNode<T>* p) // find the inorder predecessor of p
{
    ThreadedNode<T> *temp = p->leftChild;
    if(p->leftThread) return temp;
    else{
        while(!temp->rightThread) temp = temp->rightChild;
        return temp;
    }
}

template <class T>
void ThreadedTree<T>::Preorder()
{
    ThreadedNode<T>* current = head->leftChild;
    while(current != head){
        cout << current->data << " ";
        if(!current->leftThread) current = current->leftChild;
        else if(!current->rightThread) current = current->rightChild;
        else{
            while (current != head && current->rightThread) current = current->rightChild;
            current = current->rightChild;
        }
    }
    cout << endl;
}

template <class T>
void ThreadedTree<T>::Postorder()
{
    ThreadedNode<T>* current = head->leftChild;
    ThreadedNode<T>* lastVisited = NULL;
    ThreadedNode<T>* prev = head;

    while(current != head){
        if(!current->leftThread && lastVisited != current->leftChild && lastVisited != current->rightChild){
            prev = current;
            current = current->leftChild;
        }
        else if(!current->rightThread && lastVisited != current->rightChild){
            prev = current;
            current = current->rightChild;
        }
        else{
        	if(current != head->leftChild) cout << current->data << " ";
            if(current == prev){
            	current = lastVisited->rightChild;
            	lastVisited = prev;
			}
			else{
				lastVisited = current;
            	current = prev;
			}
        }
    }
    cout << head->leftChild->data << endl;
}

template <class T>
void ThreadedTree<T>::InsertRight(ThreadedNode <T> *s, ThreadedNode <T> *r)
{// insert r as the right child of s
    r->rightChild = s->rightChild;
    r->rightThread = s->rightThread;

    r->leftChild = s;
    r->leftThread = true;//leftChild is a thread

    s->rightChild = r;
    s->rightThread = false;
    
    if (!r->rightThread) {
        ThreadedNode <T> *temp = InorderSucc(r);
        temp->leftChild = r;
    }
}

template <class T>
void ThreadedTree<T>::InsertLeft(ThreadedNode <T> *s, ThreadedNode <T> *l)
{// insert l as the left child of s
    l->leftChild = s->leftChild;
    l->leftThread = s->leftThread;
    l->rightChild = s;
    l->rightThread = true;//rightChild is a thread
    s->leftChild = l;
    s->leftThread = false;
    if (!l->leftThread) {
        ThreadedNode <T> *temp = InorderPred(l);
        temp->rightChild = l;
    }
}

template <class T>
class ThreadedInorderIterator
{
public:
    ThreadedInorderIterator(ThreadedTree<T> tree):t(tree){ currentNode = t.head; }
    T* Next();
    T& operator*(); 
    bool operator!=(const ThreadedInorderIterator r);
private:
    ThreadedTree<T> t;
    ThreadedNode<T> *currentNode;
};

template <class T>
T* ThreadedInorderIterator<T>::Next()
{
    ThreadedNode <T> *temp = currentNode->rightChild;
    if(currentNode->rightThread) {
        currentNode = temp;
    }
    else {
        while (!temp->leftThread)
            temp = temp->leftChild;
        currentNode = temp;
    }
    if(currentNode == t.Head())
        return 0;
    else
        return &currentNode->data;
}

template <class T>
bool ThreadedInorderIterator<T>::operator!=(const ThreadedInorderIterator r)
{
    return currentNode != r.currentNode;
}

template <class T>
T& ThreadedInorderIterator<T>::operator*()
{
    return currentNode->data;
}


int main()
{
    ThreadedTree<char> tree;
    ThreadedNode<char> *a = new ThreadedNode<char>('A');
    ThreadedNode<char> *b = new ThreadedNode<char>('B');
    ThreadedNode<char> *c = new ThreadedNode<char>('C');
    ThreadedNode<char> *d = new ThreadedNode<char>('D');
    ThreadedNode<char> *e = new ThreadedNode<char>('E');
    ThreadedNode<char> *f = new ThreadedNode<char>('F');
    ThreadedNode<char> *g = new ThreadedNode<char>('G');
    ThreadedNode<char> *h = new ThreadedNode<char>('H');
    ThreadedNode<char> *j = new ThreadedNode<char>('J');

    tree.InsertLeft(tree.Head(), a);

    tree.InsertLeft(a, b);
    tree.InsertRight(a, c);

    tree.InsertLeft(b, d);
    tree.InsertRight(b, e);

    tree.InsertLeft(c, f);
    tree.InsertRight(c, g);

    tree.InsertLeft(d, h);
    tree.InsertRight(d, j);

    cout << "The example tree: " << endl;
    cout << "          A       " << endl;
	cout << "         / \\     " << endl;
	cout << "        /   \\    " << endl;
	cout << "       B     C    " << endl;
	cout << "      / \\   / \\ " << endl;
	cout << "     D   E  F  G  " << endl;
	cout << "    / \\          " << endl;
	cout << "   H   J          " << endl << endl;

    ThreadedInorderIterator<char> iter(tree);
    cout << "Inorder traversal by iterator: ";
    for (char *data = iter.Next(); data != NULL ; data = iter.Next())
        cout << *data << " ";
    cout << endl;

    cout << "Postorder traversal: ";
    tree.Postorder();

    cout << "Preorder traversal: ";
    tree.Preorder();

    return 0;
}