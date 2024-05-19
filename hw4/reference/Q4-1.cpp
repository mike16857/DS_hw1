#include <iostream>
using namespace std;

// Stack
template <class T>
class Stack
{
public:
    Stack (int stackCapacity = 10);
    bool IsEmpty() const;
    T& Top() const;
    void Push (const T& item);
    void Pop();
    void ChangeSize1D(T* &a, const int oldSize, const int newSize);
private:
    T* stack;
    int top;
    int capacity;
};

template <class T>
Stack<T>:: Stack(int stackCapacity): capacity(stackCapacity)
{
    if (capacity < 1) throw "Stack capacity must be > 0";
    stack = new T[capacity];
    top = -1;
}
template <class T>
inline bool Stack<T>::IsEmpty() const { return top == -1;}
template <class T>
inline T& Stack<T>::Top() const
{
    if (IsEmpty()) throw "Stack is empty";
    return stack[top];
}
template <class T>
void Stack<T>::Push(const T &item)
{
    if (top == capacity - 1) {
        ChangeSize1D(stack, capacity, 2 * capacity);
        capacity *= 2;
    }
    stack[++top] = item;
}
template <class T>
void Stack<T>::Pop()
{
    if (IsEmpty()) throw "Stack is empty. Cannot delete.";
    stack[top--].~T();
}
template <class T>
void Stack<T>::ChangeSize1D(T* &a, const int oldSize, const int newSize)
{
    if(newSize < 0) throw "New length must be >= 0";

    T *temp = new T[newSize];
    int number = min(oldSize, newSize);    // choose the smallest Size to store
    copy(a, a + number, temp);              // copy the old array into new
    delete []a;                             // delete old array
    a = temp;
}

// Queue
template <class T>
class Queue
{
public:
    Queue(int queueCapacity = 10);
	bool IsEmpty() const;
    void Push(const T& item);
    void Pop();
    T& Front() const;
    T& Rear() const;
private:
	T* queue;
	int front, rear, capacity;
};

template <class T>
Queue<T>::Queue(int queueCapacity):capacity(queueCapacity)
{
	if (capacity < 1) throw "Queue capacity must be > 0";
	queue= new T[capacity];
	front = rear = 0; // indicate empty queue
}
template <class T>
inline bool Queue<T>::IsEmpty() const
{
	return front == rear;
}
template <class T>
inline T& Queue<T>::Front() const
{
	if (IsEmpty()) throw "Queue is empty. No front element.";
	return queue[(front + 1) % capacity]; //front unchanged
}
template <class T>
inline T& Queue<T>::Rear() const
{
	if (IsEmpty()) throw "Queue is empty. No rear element.";
	return queue[rear];
}
template <class T>
void Queue<T>::Push(const T& x)
{
	if ((rear + 1) % capacity == front){ 
		T* newQu = new T[2 * capacity];
		int start = (front+1) % capacity;
		if(start < 2)
			copy(queue + start, queue + start + capacity - 1, newQu);
		else{
			copy(queue + start, queue + capacity, newQu);
			copy(queue, queue + rear + 1, newQu + capacity - start);
		}
		front = 2 * capacity - 1;
		rear = capacity - 2;
		delete[] queue;
		queue = newQu;
		capacity *= 2;
	}
	rear = (rear + 1) % capacity;
	queue[rear] = x;
}
template <class T>
void Queue<T>::Pop()
{
	if (IsEmpty()) throw "Queue is empty, cannot delete";
	front = (front + 1) % capacity;
	queue[front].~T(); // destructor for T
}

// BinaryTree
template <class T> class BinaryTree;
template <class T>
class TreeNode
{
friend class BinaryTree <T>;
private:
    T data;
    TreeNode<T>* leftChild;
    TreeNode<T>* rightChild;
};

template<class T>
class BinaryTree
{
public:
    BinaryTree(); // constructor for an empty binary tree
	BinaryTree(const BinaryTree<T> &s);
    bool IsEmpty(); // return true iff the binary tree is empty    
    BinaryTree(BinaryTree<T>& bt1, T item, BinaryTree<T>& bt2);   
    // constructor given the root item and left subtrees bt1 and right subtree bt2
	BinaryTree<T> LeftSubtree(); // return the left subtree
    BinaryTree<T> RightSubtree();// return the right subtree
    T RootData();  // return the data in the root node of *this
	void Inorder();
	void Inorder(TreeNode<T>* t);
	void Preorder();
	void Preorder(TreeNode<T>* t);
	void Postorder();
	void Postorder(TreeNode<T>* t);
	void LevelOrder();
	void NonrecInorder();
	void NoStackInorder();
	bool operator ==(const BinaryTree<T> &t) const;
	bool Equal(TreeNode<T>* a, TreeNode<T>* b) const;
	TreeNode<T>* Copy(TreeNode<T>* p);
	void Visit(TreeNode<T>* p);
private:
	TreeNode<T>* root;
};

template <class T>
BinaryTree<T>::BinaryTree()
{
	root = NULL;
}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &s)
{ // Copy constructor
	root = Copy(s.root);
}
template <class T>
TreeNode<T>* BinaryTree<T>::Copy(TreeNode<T>* p) // Workhorse
{//Return a pointer to an exact copy of the tree rooted at p
	if (!p) return 0; // a null pointer empty BT
	TreeNode<T>* newroot = new TreeNode<T>;
	newroot->data = p->data;
	newroot->leftChild = p->leftChild;
    newroot->rightChild = p->rightChild;
    
	return newroot;
}
template <class T>
bool BinaryTree<T>::IsEmpty()
{
	return(root == NULL);
}

template <class T>
BinaryTree<T>::BinaryTree(BinaryTree<T>& bt1, T item, BinaryTree<T>& bt2)
{
	root = new TreeNode<T>;
    root->data = item;
    root->leftChild = bt1.root;
    root->rightChild = bt2.root;
}

template <class T>
BinaryTree<T> BinaryTree<T>::LeftSubtree()
{
	BinaryTree left;   
    left.root = root->leftChild;
    
    return left;
}

template <class T>
BinaryTree<T> BinaryTree<T>::RightSubtree()
{
	BinaryTree right;   
    right.root = root->rightChild;
    
    return right;
}

template <class T>
T BinaryTree<T>::RootData()
{
	return root->data;
}

template <class T>
void BinaryTree<T>::Inorder()
{					// driver呼叫主程式以走訪整棵樹
	Inorder(root);	//Traverse inorderly
}
template <class T>
void BinaryTree<T>::Inorder(TreeNode<T>* p)
{ 								// Workhorse走訪樹根為p的子樹
	if(p){
		Inorder(p->leftChild); 	// L
		Visit(p); 				// **V**
		Inorder(p->rightChild); // R
	}
}

template <class T>
void BinaryTree<T>::Preorder()
{ 					// Driver
	Preorder(root); //Traverse preorderly
}
template <class T>
void BinaryTree<T>::Preorder(TreeNode<T>* p)
{									// Workhorse, a recursive function
	if(p){
		Visit(p); 					// **V**
		Preorder(p->leftChild); 	// L
		Preorder(p->rightChild); 	// R
	}
}

template <class T>
void BinaryTree<T>::Postorder()
{
	Postorder(root);	//Traverse postorderly
}
template <class T>
void BinaryTree<T>::Postorder(TreeNode<T>* p)
{									// Workhorse, a recursive function
	if(p){
		Postorder (p->leftChild); 	// L
		Postorder (p->rightChild); 	// R
		Visit(p); 					// **V**
	}
}

template <class T>
void BinaryTree<T>::LevelOrder()
{
	Queue<TreeNode<T>*> q;
	TreeNode<T> *currentNode = root;
	while(currentNode){
		Visit(currentNode);
		if(currentNode->leftChild) q.Push(currentNode->leftChild);
		if(currentNode->rightChild) q.Push(currentNode->rightChild);
		if(q.IsEmpty()) return;
		currentNode = q.Front();
		q.Pop();
	}
}

template <class T>
void BinaryTree<T>::NonrecInorder()
{	//nonrecursive inorder traversal
	Stack<TreeNode<T>*> s;
	TreeNode <T> *currentNode = root;
	while(1){
		while(currentNode){
			s.Push(currentNode);
			currentNode = currentNode->leftChild;
		}
	if(s.IsEmpty()) return;
	currentNode = s.Top();
	s.Pop();
	Visit(currentNode);
	currentNode = currentNode->rightChild;
	}
}

template <class T>
void BinaryTree<T>::NoStackInorder()
{
    if(!root) return;
    TreeNode<T> *top = 0, *lastRight = 0, *p, *q, *r, *r1;
    p = q = root;
    while(1){
        while(1){
            if((!p ->leftChild) && (!p->rightChild)){
                Visit(p);break;
            }
            if(!p->leftChild){
                Visit(p);
                r = p->rightChild; p->rightChild = q;
                q = p; p = r;
            }
            else{
                r = p->leftChild; p->leftChild = q;
                q = p; p = r;
            }
        }
        TreeNode<T> *av = p;
        while(1){
            if(p == root) return;
            if(!q->leftChild){
                r = q->rightChild; q->rightChild = p;
                p = q; q = r;
            }
            else if(!q->rightChild){
                r = q->leftChild; q->leftChild = p;
                p = q; q = r;
                Visit(p);
            }
            else{
                if(q == lastRight){
                    r = top; lastRight = r->leftChild;
                    top = r->rightChild;
                    r->leftChild = r->rightChild = 0;
                    r = q->rightChild; q->rightChild = p;
                    p = q; q = r;
                }
                else{
                    Visit(q);
                    av->leftChild = lastRight; av->rightChild = top;
                    top = av; lastRight = q;
                    r = q->leftChild; q->leftChild = p;
                    r1 = q->rightChild; q->rightChild = r;
                    p = r1;
                    break;
                }
            }
        }
    }
}

template <class T>
bool BinaryTree<T>::operator==(const BinaryTree<T> &t) const
{
	return Equal(root, t.root);
}
template <class T>
bool BinaryTree<T>::Equal(TreeNode<T>* a, TreeNode<T>* b) const
{// workhorse
	if((!a) && (!b)) return true; // two empty trees
	return(a && b && (a->data == b->data) && Equal(a->leftChild,b->leftChild) && Equal(a->rightChild,b->rightChild));
	// both a and b are non-zero // data is the same
}

template <class T>
void BinaryTree<T>::Visit(TreeNode<T>* p)
{
	cout << p->data << " ";
}

int main(void)
{
    BinaryTree<char> Null;
    BinaryTree<char> A(Null, 'A', Null);
    BinaryTree<char> B(Null, 'B', Null);
	BinaryTree<char> C(Null, 'C', Null);
	BinaryTree<char> D(Null, 'D', Null);
	BinaryTree<char> E(Null, 'E', Null);
    BinaryTree<char> minus(A, '-', B);
    BinaryTree<char> mult1(minus, '*', C);
    BinaryTree<char> mult2(mult1, '*', D);
    BinaryTree<char> Tree1(mult2, '+', E);

    cout << "Ex1 :" << endl;
    cout << "         +    " << endl;
	cout << "        / \\  " << endl;
	cout << "       *    E " << endl;
	cout << "      / \\    " << endl;
	cout << "     *   D    " << endl;
	cout << "    / \\      " << endl;
	cout << "   -   C      " << endl;
	cout << "  / \\        " << endl;
	cout << " A   B        " << endl << endl;
	
    if (Tree1.IsEmpty()) cout << "The tree is empty" << endl;
    else cout << "The tree is not empty" << endl;
    cout << endl;
	cout << "The root data is " << Tree1.RootData() << endl;
    cout << "Print the tree in Preorder : "; Tree1.Preorder(); cout << endl;
    cout << "Print the tree in Inorder : "; Tree1.Inorder(); cout << endl;
    cout << "Print the tree in Posorder : "; Tree1.Postorder(); cout << endl;
    cout << "Print the tree in LevelOrder : "; Tree1.LevelOrder(); cout << endl;
    
    cout << "Print the left subtree using NonrecInorder : "; Tree1.LeftSubtree().NonrecInorder(); cout << endl;
    cout << "Print the left subtree using NoStackInorder : "; Tree1.RightSubtree().NoStackInorder(); cout << endl;
    
    if (Tree1.LeftSubtree() == Tree1.RightSubtree()) cout << "The left subtree is equal to the right subtree";
    else cout << "The left subtree is not equal to the right subtree";
    cout << endl << endl;
    
    
    BinaryTree<char> H2(Null, 'H', Null);
    BinaryTree<char> J2(Null, 'J', Null);
    BinaryTree<char> E2(Null, 'E', Null);
	BinaryTree<char> G2(Null, 'G', Null);
	BinaryTree<char> F2(Null, 'F', Null);
    BinaryTree<char> D2(H2, 'D', J2);
    BinaryTree<char> B2(D2, 'B', E2);
    BinaryTree<char> C2(F2, 'C', G2);
    BinaryTree<char> Tree2(B2, 'A', C2);
    
    cout << "Ex2 : " << endl;
	cout << "          A       " << endl;
	cout << "         / \\     " << endl;
	cout << "        /   \\    " << endl;
	cout << "       B     C    " << endl;
	cout << "      / \\   / \\ " << endl;
	cout << "     D   E  F  G  " << endl;
	cout << "    / \\          " << endl;
	cout << "   H   J          " << endl << endl;
	
    if (Tree2.IsEmpty()) cout << "The tree is empty" << endl;
    else cout << "The tree is not empty" << endl;
    cout << endl;
	cout << "The root data is " << Tree2.RootData() << endl;
    cout << "Print the tree in Preorder : "; Tree2.Preorder(); cout << endl;
    cout << "Print the tree in Inorder : "; Tree2.Inorder(); cout << endl;
    cout << "Print the tree in Posorder : "; Tree2.Postorder(); cout << endl;
    cout << "Print the tree in LevelOrder : "; Tree2.LevelOrder(); cout << endl;
    
    cout << "Print the left subtree using NonrecInorder : "; Tree2.LeftSubtree().NonrecInorder(); cout << endl;
    cout << "Print the left subtree using NoStackInorder : "; Tree2.RightSubtree().NoStackInorder(); cout << endl;
    
    if (Tree2.LeftSubtree() == Tree2.RightSubtree()) cout << "The left subtree is equal to the right subtree";
    else cout << "The left subtree is not equal to the right subtree";
    
    return 0;
}
