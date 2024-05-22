#include <iostream>
using namespace std;

/* Queue */
template <class T>
class Queue
{
public:
    Queue(int queueCapacity = 10);
    ~Queue();
    bool IsEmpty() const;
    int Size() const;
    void Push(const T& item);
    // add an item into the queue
    void Pop();
    // delete an item
    T& Front() const;
    // return top element of stack
    T& Rear() const;
    // return top element of stack
protected:
    T* queue;
    int front, rear;
    int capacity;
};

template <class T>
Queue<T>::Queue(int queueCapacity):capacity(queueCapacity)
{
    if (capacity < 1) throw "Queue capacity must be > 0";
    queue= new T[capacity];
    front = rear = 0; // indicate empty queue
}

template <class T>
Queue<T>::~Queue()
{
    delete [] queue;
}

template <class T>
bool Queue<T>::IsEmpty() const
{
    return (Size() == 0);
}

template <class T>
int Queue<T>::Size() const
{
    return (rear - front + capacity) % capacity;
}

template <class T>
void Queue<T>::Push(const T& x)
{// add x to queue
    if ((rear + 1) % capacity == front) { //resize
        T* newQu = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(queue + start, queue + start + capacity - 1, newQu);
        else {
            copy(queue + start, queue + capacity, newQu);
            copy(queue, queue + rear + 1,newQu + capacity - start);
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        delete [] queue;
        queue = newQu; 
        capacity *=2;
    }
    rear = (rear + 1) % capacity; queue[rear] = x;
}

template <class T>
void Queue<T>::Pop()
{
    if (IsEmpty()) throw "Queue is empty, cannot delete";
    front = (front + 1) % capacity;
    queue[front].~T(); // destructor for T
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


/* Stack */
template <class T>
class Stack
{   
	template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
public:
    Stack (int stackCapacity = 10);
    ~Stack();
    bool IsEmpty() const;
    void Push(const T& item);
    void Pop();
    T& Top() const;
private:
    int top;
    int capacity;
    T* stack;
};

template <class U>
void ChangeSize1D(U* &a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";
    U *temp = new U[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);
    delete [] a;
    a = temp;
}

template <class T> 
Stack<T>::Stack(int stackCapacity):capacity(stackCapacity)
{
    if (capacity < 1) throw "Stack capacity must be > 0";
    stack = new T[capacity];
    top = -1;
}

template <class T> 
Stack<T>::~Stack() 
{
    delete [] stack;
}

template <class T>
bool Stack<T>::IsEmpty() const
{
    return top == -1;
}

template <class T>
void Stack<T>::Push(const T& item)
{// add x to stack
    if (top == capacity - 1) {
        ChangeSize1D (stack, capacity, 2 * capacity);
        capacity *= 2;
    }
    stack[++top] = item;
}

template <class T>
void Stack<T>::Pop()
{
    if (IsEmpty()) throw "Stack is empty, cannot delete";
    stack[top--].~T();
}

template <class T>
T& Stack<T>::Top() const
{
    if (IsEmpty()) throw "Stack is empty.";
    return stack[top];
}


template <class T> class Tree;
template <class T> class InorderIterator;
template <class T>
class TreeNode 
{
    friend class Tree<T>;
    friend class InorderIterator<T>;//inorder iterator
private:
    T data;
    TreeNode<T> *leftChild;
    TreeNode<T> *rightChild;
};


template<class T>
class Tree
{ 
    friend class InorderIterator<T>;//inorder iterator
public:
    Tree(); // constructor for an empty binary tree
    Tree(Tree<T>& bt1, T item, Tree<T>& bt2);   // constructor given the root item and left subtrees bt1 and right subtree bt2
    Tree(const Tree<T>&); //copy constructor
    ~Tree();
    bool IsEmpty(); // return true iff the binary tree is empty    
	Tree<T> LeftSubtree(); // return the left subtree
    Tree<T> RightSubtree();// return the right subtree
    T RootData();  // return the data in the root node of *this
	// more operations
    void Inorder();
    void Inorder(TreeNode<T>* p); // Workhorse
    void Preorder();
    void Preorder(TreeNode<T>* p); // Workhorse
    void Postorder();  
    void Postorder(TreeNode<T>* p); // Workhorse
    void LevelOrder();
    void NonrecInorder();
    void NoStackInorder();
    bool operator == (const Tree& t);
    TreeNode<T>* Copy(TreeNode<T>* p); // Workhorse
    // void Destroy(TreeNode<T>* p);
    bool Equal(const Tree<T>& t);
    bool Equal(TreeNode<T>* a , TreeNode<T>* b);
    void setup1();
    void setup2();
    // void output();

private:
	TreeNode<T> *root;
	void Visit(TreeNode<T> *p){cout << p->data << "  ";}
};

template <class T>
Tree<T>::Tree()
{
    root = 0;
}

template <class T>
Tree<T>::Tree(Tree<T>& bt1, T item, Tree<T>& bt2)
{
    root = new TreeNode<T>;
    root->data = item;
    root->leftChild = bt1.root;
    root->rightChild = bt2.root;
}

template <class T>
Tree<T>::Tree(const Tree<T>& t)
{
    root = Copy(t.root);
}
template <class T>
TreeNode<T>* Tree<T>::Copy(TreeNode<T> * p)
{
    if (!p) return 0;

    TreeNode<T>* q = new TreeNode<T>;
    q->data = p->data;
    q->leftChild = Copy(p->leftChild);
    q->rightChild = Copy(p->rightChild);
    return q;
}

template <class T>
Tree<T>::~Tree() 
{
    // Destroy(root);

//     Queue<TreeNode<T>*> q;
//     if (root) q.Push(root);
//     while (!q.IsEmpty()) {
//         TreeNode<T>* currentNode = q.Front();
//         q.Pop();
//         if (currentNode->leftChild) q.Push(currentNode->leftChild);
//         if (currentNode->rightChild) q.Push(currentNode->rightChild);
//         delete currentNode;
//     }
}
// template <class T>
// void Tree<T>::Destroy(TreeNode<T>* p) 
// {
//     if (p) {
//         Destroy(p->leftChild);
//         Destroy(p->rightChild);
//         delete p;
//     }
// }

template <class T>
bool Tree<T>::IsEmpty()
{
    return root == 0;
}

template <class T>
Tree<T> Tree<T>::LeftSubtree()
{
    Tree<T> t;
    t.root = root->leftChild;
    return t;
}

template <class T>
Tree<T> Tree<T>::RightSubtree()
{
    Tree<T> t;
    t.root = root->rightChild;
    return t;
}

template <class T>
T Tree<T>::RootData()
{
    return root->data;
}

template <class T>
void Tree<T>::Inorder()
{
    Inorder(root);    //Traverse inorderly
}
template <class T>
void Tree<T>::Inorder(TreeNode<T> * p)
{// Workhorse, a recursive function
    if(p) {
        Inorder (p->leftChild); // L
        Visit(p); // **V**
        Inorder (p->rightChild); // R
    }
}

template <class T>
void Tree<T>::Preorder()
{
    Preorder(root);    //Traverse preorderly
}
template <class T>
void Tree<T>::Preorder(TreeNode<T> * p)
{// Workhorse, a recursive function
    if(p) {
        Visit(p); // **V**
        Preorder (p->leftChild); // L
        Preorder (p->rightChild); // R
    }
}

template <class T>
void Tree<T>::Postorder()
{
    Postorder(root);    //Traverse postorderly
}
template <class T>
void Tree<T>::Postorder(TreeNode<T> * p)
{// Workhorse, a recursive function
    if(p) {
        Postorder (p->leftChild); // L
        Postorder (p->rightChild); // R
        Visit(p); // **V**
    }
}

template <class T>
void Tree<T>::LevelOrder()
{
    Queue<TreeNode<T>*> q;
    TreeNode<T> *currentNode = root;
    while (currentNode) {
        Visit(currentNode);

        if (currentNode->leftChild)
            q.Push(currentNode->leftChild);
        if (currentNode->rightChild)
            q.Push(currentNode->rightChild);

        if (q.IsEmpty())
            return;

        currentNode = q.Front();
        q.Pop();
    }
}

template <class T>
void Tree<T>::NonrecInorder()
{//nonrecursive inorder traversal
    Stack <TreeNode<T>*> s;
    TreeNode <T> *currentNode = root;
    while(1) {
        while (currentNode) {
            s.Push(currentNode);
            currentNode = currentNode->leftChild;
        }
        if (s.IsEmpty())
            return;
        currentNode = s.Top();
        s.Pop();
        Visit(currentNode);
        currentNode = currentNode->rightChild;
    }
}

template <class T>
void Tree <T>::NoStackInorder()
{// 使用固定量額外空間的二元樹中序走訪
    if (!root) return; //空的二元樹
    TreeNode<T> *top = 0, *lastRight =0, *p, *q, *r, *r1;
    p = q = root;
    while(1) {
        while(1) {
            if ((!p->leftChild) && (!p->rightChild)) { //樹葉節點
                Visit(p);break;
            }
            if (!p->leftChild) { // 拜訪p並移至p->rightChild
                Visit(p);
                r = p->rightChild; p->rightChild = q;
                q = p; p = r;
            }
            else { // 移至p->leftChild
                r = p->leftChild; p->leftChild = q;
                q = p; p = r;
            }
        } // 內圈while結束

        // p是一個葉節點，向上移至右子樹還沒被檢查的節點
        TreeNode<T> *av = p;
        while(1) {
            if (p == root) return;
            if (!q->leftChild) { // q是透過rightChild鏈結的
                r = q->rightChild; q->rightChild = p;
                p = q; q = r;
            }
            else if (!q->rightChild) { // q是透過leftChild鏈結的
                r = q->leftChild; q->leftChild = p;
                p = q; q = r; Visit(p);
            }
            else { // 檢查p是否為q的rightChild
                if (q == lastRight) {
                    r = top; lastRight = r->leftChild;
                    top = r->rightChild; // 彈出堆疊
                    r->leftChild = r->rightChild = 0;
                    r = q->rightChild; q->rightChild = p;
                    p = q; q = r;
                }
                else { // p是q的leftChild
                    Visit(q);
                    av->leftChild = lastRight; av->rightChild = top;
                    top = av; lastRight = q;
                    r = q->leftChild; q->leftChild = p;
                    r1 = q->rightChild; q->rightChild = r;
                    p = r1;
                    break;
                }
            }
        } // 內圈while結束
    } // 外圈while結束
}

template <class T>
bool Tree<T>::operator==(const Tree& t)
{
    return Equal(root, t.root);
}
template <class T>
bool Tree<T>::Equal(const Tree<T>& t)
{
    return Equal(root, t.root);
}
template <class T>
bool Tree<T>::Equal(TreeNode<T>* a , TreeNode<T>* b)
{// workhorse
    if ((!a) && (!b)) // two empty trees
        return true;
    return ( a && b // both a and b are non-zero
               && (a->data == b->data) // data is the same
               && Equal(a->leftChild,b->leftChild)
               && Equal(a->rightChild,b->rightChild));
}   

template <class T>
void Tree<T>::setup1()
{
    Tree<char> Null;
    Tree<char> A(Null, 'A', Null);
    Tree<char> B(Null, 'B', Null);
	Tree<char> C(Null, 'C', Null);
	Tree<char> D(Null, 'D', Null);
	Tree<char> E(Null, 'E', Null);
    Tree<char> minus(A, '-', B);
    Tree<char> mult1(minus, '*', C);
    Tree<char> mult2(mult1, '*', D);
    *this = Tree<char> (mult2, '+', E);
}

template <class T>
void Tree<T>::setup2()
{
    Tree<char> Null;
    Tree<char> H2(Null, 'H', Null);
    Tree<char> J2(Null, 'J', Null);
    Tree<char> E2(Null, 'E', Null);
	Tree<char> G2(Null, 'G', Null);
	Tree<char> F2(Null, 'F', Null);
    Tree<char> D2(H2, 'D', J2);
    Tree<char> B2(D2, 'B', E2);
    Tree<char> C2(F2, 'C', G2);
    *this = Tree<char> (B2, 'A', C2);
}

// template <class T>
// void Tree<T>::output()
// {

// }


template <class T>
class InorderIterator
{
public:
    // InorderIterator(){ currentNode = root;} // Constructor
    InorderIterator(Tree<T> tree):t(tree){ currentNode = t.root; }
    T* Next();
    T& operator*(); 
    bool operator!=(const InorderIterator r);
private:
    Tree<T> t;
    Stack<TreeNode<T>*> s;
    TreeNode<T> *currentNode;
};

template <class T>
T* InorderIterator<T>::Next()
{
    while (currentNode) {
        s.Push(currentNode);
        currentNode = currentNode->leftChild;
    }
    if (s.IsEmpty()) return 0;
    currentNode = s.Top();
    s.Pop();
    T* p = &currentNode->data;
    currentNode = currentNode->rightChild;
    return p;
}

template <class T>
T& InorderIterator<T>::operator*()
{
    return currentNode->data;
}

template <class T>
bool InorderIterator<T>::operator!=(const InorderIterator r)
{
    return currentNode != r.currentNode;
}


int main()
{
    Tree<char> Tree1, Tree2;
    Tree1.setup1();
    Tree2.setup2();

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

    // iterator traversal
    InorderIterator<char> it(Tree1);
    cout << "Inorder traversal using iterator: ";
    for (char* data = it.Next(); data != NULL; data = it.Next()) {
        cout << *data << "  ";
    }
    cout << endl;
    
    cout << "Print the tree in Posorder : "; Tree1.Postorder(); cout << endl;
    cout << "Print the tree in LevelOrder : "; Tree1.LevelOrder(); cout << endl;
    
    cout << "Print the left subtree using NonrecInorder : "; Tree1.LeftSubtree().NonrecInorder(); cout << endl;
    cout << "Print the left subtree using NoStackInorder : "; Tree1.RightSubtree().NoStackInorder(); cout << endl;
    
    if (Tree1.LeftSubtree() == Tree1.RightSubtree()) cout << "The left subtree is equal to the right subtree";
    else cout << "The left subtree is not equal to the right subtree";
    cout << endl << endl;
    
    cout << "------------------------------------------------------------" << endl << endl;
    
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

    // iterator traversal
    InorderIterator<char> it2(Tree2);
    cout << "Inorder traversal using iterator: ";
    for (char* data = it2.Next(); data != NULL; data = it2.Next()) {
        cout << *data << "  ";
    }
    cout << endl;

    cout << "Print the tree in Posorder : "; Tree2.Postorder(); cout << endl;
    cout << "Print the tree in LevelOrder : "; Tree2.LevelOrder(); cout << endl;
    
    cout << "Print the left subtree using NonrecInorder : "; Tree2.LeftSubtree().NonrecInorder(); cout << endl;
    cout << "Print the left subtree using NoStackInorder : "; Tree2.RightSubtree().NoStackInorder(); cout << endl;
    
    if (Tree2.LeftSubtree() == Tree2.RightSubtree()) cout << "The left subtree is equal to the right subtree";
    else cout << "The left subtree is not equal to the right subtree";


    return 0;
}