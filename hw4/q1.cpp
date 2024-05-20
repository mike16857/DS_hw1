#include <iostream>
using namespace std;


template <class T> class Tree;


template <class T>
class TreeNode 
{
    friend class Tree <T>;
    friend class InorderIterator<T>;//inorder iterator
private:
    T data;
    TreeNode <T> *leftChild;
    TreeNode <T> *rightChild;
};


template<class T>
class Tree
{ 
    friend class InorderIterator<T>;//inorder iterator
public:
    Tree(); // constructor for an empty binary tree
    Tree(Tree<T>& bt1, T& item, Tree<T>& bt2);   
    Tree(const Tree<T>&); //copy constructor
    // constructor given the root item and left subtrees bt1 and right subtree bt2
    ~Tree();
    bool IsEmpty(); // return true iff the binary tree is empty    
	Tree<T> LeftSubtree(); // return the left subtree
    Tree<T> RightSubtree();// return the right subtree
    T RootData();  // return the data in the root node of *this
	// more operations
    void Inorder()
    void Preorder()
    void Postorder()
    void LevelOrder()
    void NonrecInorder()
    void NoStackInorder()
    bool operator == (const Tree& t);
    TreeNode<T> * Copy(TreeNode<T> * p); // Workhorse
    bool Equal(const Tree<T>& t);
    bool Equal(TreeNode<T>* a , TreeNode<T>* b);
    void setup1();
    void setup2();
    void output();

private:
	TreeNode <T> *root;
	void Visit(TreeNode<T> *p){cout << p->data << "  ";}
};


template <class T>
class InorderIterator
{
public:
    InorderIterator(){ currentNode = root;} // Constructor
    InorderIterator(Tree<T> tree):t(tree){ currentNode = t.root; }
    T* Next();
    T& operator *(); 
    bool  operator!=(const InorderIterator r)
private:
    Tree<T> t;
    Stack<TreeNode<T>*> s;
    TreeNode<T> * currentNode;
};
