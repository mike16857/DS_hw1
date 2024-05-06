#include <iostream>
using namespace std;


class DblList;  //forward declaration


class DblListNode 
{
    friend class DblList;
// public:
    // DblListNode(int x, DblListNode *l, DblListNode *r):data(x), left(l), right(r) {}
private:
    int data;
    DblListNode *left, *right;   
};


class DblList 
{
public:
    // List manipuation operations
    DblList();
    ~DblList();
    void Insert(DblListNode *p, DblListNode *x);
    void Delete(DblListNode *x);
    void Concatenate(DblList m);
    void PushFront(int x);  // Inject(x)
    void PushBack(int x);   // Push(x)
    void PopFront();        // Pop()
    void PopBack();         // Eject()
private:
    DblListNode *head;  // points to header node
};

DblList::DblList()
{
    head = new DblListNode;
    head->left = head->right = head;
}

DblList::~DblList()
{
    DblListNode *q;
    while (head->right != head) {
        q = head->right;
        head->right = q->right;
        delete q;
    }
    delete head;
}

void DblList::Insert(DblListNode *p, DblListNode *x)
{   // insert node p to the right of node x
    p->left = x;
    p->right = x->right;
    x->right->left = p;
    x->right = p;
}

void DblList::Delete(DblListNode *x)
{
    if (x == head)
        throw "Deletion of header node not permitted";
    else {
        x->left->right = x->right;
        x->right->left = x->left;
        delete x;
    }
}

void DblList::Concatenate(DblList m)
{
    DblListNode *q = m.head->right;
    while (q != m.head) {
        m.head->right = q->right;
        Insert(q, head->left);
        q = m.head->right;
    }
    delete m.head;
}

void DblList::PushFront(int x)
{
    DblListNode *p = new DblListNode;
    p->data = x;
    Insert(p, head);
}

void DblList::PushBack(int x)
{
    DblListNode *p = new DblListNode;
    p->data = x;
    Insert(p, head->left);
}

void DblList::PopFront()
{
    if (head->right == head)
        throw "PopFront() on empty list";
    else
        Delete(head->right);
}

void DblList::PopBack()
{
    if (head->right == head)
        throw "PopBack() on empty list";
    else
        Delete(head->left);
}

