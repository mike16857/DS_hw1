#include <iostream>
using namespace std;


class DblList;  //forward declaration


class DblListNode 
{
    friend ostream& operator<<(ostream& os, DblList &list);
    friend istream& operator>>(istream& is, DblList &list);
    friend class DblList;
// public:
    // DblListNode(int x, DblListNode *l, DblListNode *r):data(x), left(l), right(r) {}
private:
    int data;
    DblListNode *left, *right;   
};


class DblList 
{
    friend ostream& operator<<(ostream& os, DblList &list);
    friend istream& operator>>(istream& is, DblList &list);
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
    DblListNode *temp;
    while (q != m.head) {
        temp = q;
        q = q->right;
        Insert(temp, head->left);
    }
    m.head->right = m.head->left = m.head;
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

ostream& operator<<(ostream& os, DblList &list)
{
    DblListNode *p = list.head->right;

    if (p == list.head) {
        os << "Empty list";
        return os;
    }

    os << p->data;
    p = p->right;
    while (p != list.head) {
        os << " -> " << p->data;
        p = p->right;
    }

    return os;
}

istream& operator>>(istream& is, DblList &list)
{
    int num;
    int temp;
    cout << "Enter the number of elements: ";
    is >> num;
    cout << "Enter the elements: " << endl;
    for (int i = 0; i < num; i++) {
        is >> temp;
        list.PushBack(temp);
    }
    return is;
}


int main()
{
    DblList list1, list2;
    int x;

    cout << "Enter list1: " << endl;
    cin >> list1;
    cout << "Enter list2: " << endl;
    cin >> list2;

    cout << "list1: " << list1 << endl;
    cout << "list2: " << list2 << endl;

    cout << "What number do you want to insert at the front of list1? ";
    cin >> x;
    list1.PushFront(x);
    cout << list1 << endl;

    cout << "What number do you want to insert at the back of list1? ";
    cin >> x;
    list1.PushBack(x);
    cout << list1 << endl;

    list1.Concatenate(list2);
    cout << "list1 after concatenation: " << list1 << endl;
    cout << "list2 after concatenation: " << list2 << endl;

    cout << "Pop the first element of list1: ";
    list1.PopFront();
    cout << list1 << endl;

    cout << "Pop the last element of list1: ";
    list1.PopBack();
    cout << list1 << endl;

    // cout << "What number do you want to insert at the front of list1? ";
    // cin >> x;
    // list1.PushFront(x);
    // cout << list1 << endl;

    // cout << "What number do you want to insert at the back of list1? ";
    // cin >> x;
    // list1.PushBack(x);
    // cout << list1 << endl;

    // cout << "End of program\n";

    return 0;
}