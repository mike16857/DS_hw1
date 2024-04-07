#include <iostream>
using namespace std;

/* Bag */
template <class T>
class Bag
{ 
    template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
public:
    Bag(int bagCapacity = 10);
    virtual ~Bag();
    virtual int Size() const;
    virtual bool IsEmpty() const;
    virtual T& Element() const;
    virtual void Push(const T&);
    virtual void Pop();
protected:
    T *array;
    int capacity;
    int top;
};

template <class U>
void ChangeSize1D(U* &a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";
    U *temp = new U[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);
    delete []a;
    a = temp;
}

template <class T>
Bag<T>::Bag(int bagCapacity) : capacity(bagCapacity)
{
    if (capacity < 1)
        throw "Capacity must be > 0";
    array = new T[capacity];
    top = -1;
}

template <class T>
Bag<T>::~Bag()
{
    delete [] array;
}

template <class T>
inline int Bag<T>::Size() const
{
    return top + 1;
}

template <class T>
bool Bag<T>::IsEmpty() const
{
    return (Size() == 0);
}

template <class T>
T& Bag<T>::Element() const
{
    if (IsEmpty())
        throw "Bag is empty";

    return array[0];
}

template <class T>
void Bag<T>::Push(const T& x)
{
    if (capacity == top + 1)
    {
        ChangeSize1D(array, capacity, 2 * capacity);
        capacity *= 2;
    }
    array[++top] = x;
}

template <class T>
void Bag<T>::Pop()
{
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    int deletePos = top / 2; // always delete (top/2)th element
    copy(array + deletePos + 1, array + top + 1, array + deletePos);
    array[top--].~T();
}

/* Stack */
template <class T>
class Stack : public Bag<T>
{
    template <class U>
	friend ostream& operator<<(ostream &os, Stack<U> &stack);
	template <class U>
	friend istream& operator>>(istream &is, Stack<U> &stack);
	template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
public:
    Stack (int stackCapacity = 10);
    ~Stack();
    T& Top() const;
    void Pop();
};

template <class T>
ostream& operator<<(ostream &os, Stack<T> &stack)
{
    os << "Stack: ( " << stack.array[0];
    for (int i = 1; i <= stack.top; i++)
        os << ", " << stack.array[i];
    os << " )" << endl;
    return os;
}

template <class T>
istream& operator>>(istream &is, Stack<T> &stack)
{
    int n;
    T element;

    cout << "How many elements do you want to push?";
    cin >> n;
    for (int i = 0; i < n; i++) {
        is >> element;
        stack.Push(element);
    }
    return is;
}

template <class T> 
Stack<T>::Stack(int stackCapacity) : Bag<T>(stackCapacity) {}

template <class T> 
Stack<T>::~Stack() {}

template <class T>
T& Stack<T>::Top() const
{
    if (IsEmpty()) throw "Stack is empty."
    return array[top];
}

template <class T>
void Stack<T>::Pop()
{
    if (IsEmpty()) throw "Stack is empty, cannot delete";
    array[top--].~T();
}


int main()
{
    
    return 0;
}