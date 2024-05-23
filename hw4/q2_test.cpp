#include <iostream>
using namespace std;


template <class T> class ThreadedTree;
template <class T> class ThreadedInorderIterator;
template <class T>
class ThreadedNode
{
    friend class ThreadedTree<T>;
    friend class ThreadedInorderIterator<T>;
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

template <class T>
class ThreadedTree
{
    friend class ThreadedInorderIterator<T>;
public:
    ThreadedTree();
    ThreadedNode<T>* Next(ThreadedNode<T>* node);
    void Inorder();
    void Preorder();
    void Postorder();
    void InsertRight(ThreadedNode<T>* s, ThreadedNode<T>* r);
    void InsertLeft(ThreadedNode<T>* s, ThreadedNode<T>* l);
	ThreadedNode<T>* Head();
private:
    ThreadedNode<T>* head;
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
ThreadedNode<T>* ThreadedTree<T>::Next(ThreadedNode<T>* node)
{
    ThreadedNode<T>* temp = node->rightChild;
    if (node->rightThread) return temp;
    else {
        while (!temp->leftThread) temp = temp->leftChild;
        return temp;
    }
}

template <class T>
void ThreadedTree<T>::Inorder()
{
    ThreadedNode<T>* current = Next(head);
    while (current != head) {
        cout << current->data << " ";
        current = Next(current);
    }
    cout << endl;
}

template <class T>
void ThreadedTree<T>::Preorder()
{
    ThreadedNode<T>* current = head->leftChild;
    while (current != head) {
        cout << current->data << " ";
        if (!current->leftThread) current = current->leftChild;
        else if (!current->rightThread) current = current->rightChild;
        else {
            while (current != head && current->rightThread) current = current->rightChild;
            current = current->rightChild;
        }
    }
    cout << endl;
}

template <class T>
void ThreadedTree<T>::Postorder()
{
    ThreadedNode<T> *current = head->leftChild;
    ThreadedNode<T> *lastVisited = NULL;
    ThreadedNode<T> *prev = head;

    while (current != head) {
        if (!current->leftThread && lastVisited != current->leftChild && lastVisited != current->rightChild) {
            prev = current;
            current = current->leftChild;
        }
        else if (!current->rightThread && lastVisited != current->rightChild) {
            prev = current;
            current = current->rightChild;
        }
        else {
        	if (current != head->leftChild) cout << current->data << " ";
            if (current == prev) {
            	current = lastVisited->rightChild;
            	lastVisited = prev;
			}
			else {
				lastVisited = current;
            	current = prev;
			}
        }
    }
    cout << head->leftChild->data << endl;
}

template <class T>
void ThreadedTree<T>::InsertRight(ThreadedNode<T>* s, ThreadedNode<T>* r)
{
    r->rightChild = s->rightChild;
    r->rightThread = s->rightThread;

    r->leftChild = s;
    r->leftThread = true;

    s->rightChild = r;
    s->rightThread = false;

    if (!r->rightThread) {
        ThreadedNode<T>* temp = Next(r);
        temp->leftChild = r;
    }
}

template <class T>
void ThreadedTree<T>::InsertLeft(ThreadedNode<T>* s, ThreadedNode<T>* l)
{
    l->leftChild = s->leftChild;
    l->leftThread = s->leftThread;

    l->rightChild = s;
    l->rightThread = true;

    s->leftChild = l;
    s->leftThread = false;

    if (!l->leftThread) {
        ThreadedNode<T>* temp = Next(l);
        temp->rightChild = l;
    }
}

template <class T>
ThreadedNode<T>* ThreadedTree<T>::Head()
{
    return head;
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
    if(currentNode == t.head)
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
    // ThreadedTree<char> tree;

	// ThreadedNode<char>* node1 = new ThreadedNode<char>('A');
    // ThreadedNode<char>* node2 = new ThreadedNode<char>('B');
    // ThreadedNode<char>* node3 = new ThreadedNode<char>('C');
    // ThreadedNode<char>* node4 = new ThreadedNode<char>('D');
    // ThreadedNode<char>* node5 = new ThreadedNode<char>('E');
    // ThreadedNode<char>* node6 = new ThreadedNode<char>('F');
    // ThreadedNode<char>* node7 = new ThreadedNode<char>('G');
    // ThreadedNode<char>* node8 = new ThreadedNode<char>('H');
    // ThreadedNode<char>* node9 = new ThreadedNode<char>('J');
    
    // tree.InsertLeft(tree.Head(), node1);

    // tree.InsertLeft(node1, node2);
    // tree.InsertRight(node1, node3);

    // tree.InsertLeft(node2, node4);
    // tree.InsertRight(node2, node5);

    // tree.InsertLeft(node3, node6);
    // tree.InsertRight(node3, node7);

    // tree.InsertLeft(node4, node8);
    // tree.InsertRight(node4, node9);

    ThreadedTree<char> tree;
    ThreadedNode<char> *node_A = new ThreadedNode<char>('A');
    ThreadedNode<char> *node_B = new ThreadedNode<char>('B');
    ThreadedNode<char> *node_C = new ThreadedNode<char>('C');
    ThreadedNode<char> *node_D = new ThreadedNode<char>('D');
    ThreadedNode<char> *node_E = new ThreadedNode<char>('E');
    ThreadedNode<char> *node_F = new ThreadedNode<char>('F');
    ThreadedNode<char> *node_G = new ThreadedNode<char>('G');
    ThreadedNode<char> *node_H = new ThreadedNode<char>('H');
    ThreadedNode<char> *node_J = new ThreadedNode<char>('J');

    tree.InsertLeft(tree.Head(), node_A);
    
    tree.InsertLeft(node_A, node_B);
    tree.InsertRight(node_A, node_C);

    tree.InsertLeft(node_B, node_D);
    tree.InsertRight(node_B, node_E);

    tree.InsertLeft(node_C, node_F);
    tree.InsertRight(node_C, node_G);

    tree.InsertLeft(node_D, node_H);
    tree.InsertRight(node_D, node_J);
	
	cout << "The example tree :" << endl;
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

    cout << "Postorder Traversal: ";
    tree.Postorder();

    cout << "Preorder Traversal: ";
    tree.Preorder();

    

    return 0;
}
