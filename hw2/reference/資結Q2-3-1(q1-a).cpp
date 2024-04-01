#include <iostream>
using namespace std;

template<class T>
class Bag
{
	template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
public:
	Bag (int bagCapacity = 10);
	virtual ~Bag();
	virtual int Size() const;
	virtual bool IsEmpty() const;
	virtual T& Element() const;
	virtual void Push(const T&);
	virtual void Pop();
protected:
	T* array;
	int top,capacity;
};

template <class T>
void ChangeSize1D(T* &a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";
    T *temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);
    delete []a;
    a = temp;
}

template<class T>
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
	if(IsEmpty()) throw"Bag is empty"; 
	return array[0];
}

template <class T>
void Bag<T>::Push(const T& x)
{
    if (capacity == top + 1) {
        ChangeSize1D(array, capacity, 2 * capacity);
        capacity *= 2;
    }
    array[++top] = x;
}

template <class T>
void Bag<T>::Pop()
{
	if (IsEmpty()) throw "Bag is empty, cannot delete";
	int deletePos = top/2;
	copy(array+deletePos+1, array+top + 1, array + deletePos);
	array[top--].~T();
}

//stack
template <class T>
class Stack : public Bag<T>
{
	using Bag<T>::IsEmpty;
	using Bag<T>::capacity;
    using Bag<T>::array;
    using Bag<T>::top;
	template <class U>
	friend ostream& operator<<(ostream &os, Stack<U> &stack);
	template <class U>
	friend istream& operator>>(istream &is, Stack<U> &stack);
	template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
public:
	Stack(int stackCapacity = 10);
	~Stack();
	void Pop();
	T& Top() const;
};

template <class T>
Stack<T>::Stack(int stackCapacity):Bag<T>(stackCapacity){}

template <class T>
Stack<T>::~Stack(){}

template <class T>
inline T& Stack<T>::Top() const
{
	if (IsEmpty()) throw "Stack is empty";
	return array[top];
}

template <class T>
void Stack<T>::Pop()
{
	if (IsEmpty()) throw "Stack is empty, cannot delete";
	array[top--].~T();
}

template <class T>
ostream& operator<<(ostream &os, Stack<T> &stack)
{    
    os << "The stack is : (" << stack.array[0];
    for (int i = 1; i < stack.Size(); i++) os << ", " << stack.array[i];
    os << ")" << endl;

    return os;
}

template <class T>
istream &operator>>(istream& is, Stack<T> &stack)
{
    int num;
	float temp;
    
	cout << "How many element do you want to plug in : ";
	is >> num;
	for(int i = 0; i < num; i++){
		is >> temp;
		stack.Push(temp);
	}
    return is;
}

int main()
{
    Stack<int> S1(1);
    Stack<float> S2(1);
    int push;
    float pu;
    
    //int
    cout << "type in int" << endl;
    cin >> S1;
    cout << "S1 = " << S1;
    cout << "The size of S1 is : " << S1.Size() << endl;
	S1.Pop();
	cout << "S1 after pop = " << S1;
	cout << "What element do you wan't to put in S1? ";
    cin >> push;
    S1.Push(push);
    cout << "S1 = " << S1 << endl;
    
	//float
	cout << "type in float" << endl;
    cin >> S2;
    cout << "S2 = " << S2;
    cout << "The size of S2 is : " << S2.Size() << endl;
	S2.Pop();
	cout << "S2 after pop = " << S2;
	cout << "What element do you wan't to put in S2? ";
    cin >> pu;
    S2.Push(pu);
    cout << "S2 = " << S2;
    
    return 0;
}
