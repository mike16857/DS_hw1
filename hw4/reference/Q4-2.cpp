#include <iostream>
using namespace std;

template <class T>
class ThreadedNode
{
    template <class U>
    friend class ThreadedTree;

public:
    ThreadedNode(const T& value);
private:
    T data;
    bool leftThread;
    ThreadedNode<T>* leftChild;
    bool rightThread;
    ThreadedNode<T>* rightChild;
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
public:
    ThreadedTree();
    ThreadedNode<T>* Next(ThreadedNode<T>* node);
    void Inorder();
    void Preorder();
    void Postorder();
    void InsertRight(ThreadedNode<T>* s, ThreadedNode<T>* r);
    void InsertLeft(ThreadedNode<T>* s, ThreadedNode<T>* l);
	ThreadedNode<T>* getHead();
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
    if(node->rightThread) return temp;
    else{
        while(!temp->leftThread) temp = temp->leftChild;
        return temp;
    }
}

template <class T>
void ThreadedTree<T>::Inorder()
{
    ThreadedNode<T>* current = Next(head);
    while(current != head){
        cout << current->data << " ";
        current = Next(current);
    }
    cout << endl;
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
void ThreadedTree<T>::InsertRight(ThreadedNode<T>* s, ThreadedNode<T>* r)
{
    r->rightChild = s->rightChild;
    r->rightThread = s->rightThread;
    r->leftChild = s;
    r->leftThread = true;
    s->rightChild = r;
    s->rightThread = false;
    if(!r->rightThread){
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

    if(!l->leftThread){
        ThreadedNode<T>* temp = Next(l);
        temp->rightChild = l;
    }
}

template <class T>
ThreadedNode<T>* ThreadedTree<T>::getHead()
{
    return head;
}

int main()
{
    ThreadedTree<char> tree;

	ThreadedNode<char>* node1 = new ThreadedNode<char>('A');
    ThreadedNode<char>* node2 = new ThreadedNode<char>('B');
    ThreadedNode<char>* node3 = new ThreadedNode<char>('C');
    ThreadedNode<char>* node4 = new ThreadedNode<char>('D');
    ThreadedNode<char>* node5 = new ThreadedNode<char>('E');
    ThreadedNode<char>* node6 = new ThreadedNode<char>('F');
    ThreadedNode<char>* node7 = new ThreadedNode<char>('G');
    ThreadedNode<char>* node8 = new ThreadedNode<char>('H');
    ThreadedNode<char>* node9 = new ThreadedNode<char>('J');
    
    tree.InsertLeft(tree.getHead(), node1);
    tree.InsertLeft(node1, node2);
    tree.InsertRight(node1, node3);
    tree.InsertLeft(node2, node4);
    tree.InsertRight(node2, node5);
    tree.InsertLeft(node3, node6);
    tree.InsertRight(node3, node7);
    tree.InsertLeft(node4, node8);
    tree.InsertRight(node4, node9);
	
	cout << "Tree :" << endl;
	cout << "          A       " << endl;
	cout << "         / \\     " << endl;
	cout << "        /   \\    " << endl;
	cout << "       B     C    " << endl;
	cout << "      / \\   / \\ " << endl;
	cout << "     D   E  F  G  " << endl;
	cout << "    / \\          " << endl;
	cout << "   H   J          " << endl << endl;
	
    cout << "Inorder Traversal: ";
    tree.Inorder();

    cout << "Preorder Traversal: ";
    tree.Preorder();

    cout << "Postorder Traversal: ";
    tree.Postorder();

    return 0;
}
