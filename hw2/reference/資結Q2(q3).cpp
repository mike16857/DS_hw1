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
	int top;
	int capacity;
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

//Queue
template <class T>
class Queue : public Bag<T>
{
	template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
public:
	Queue(int queueCapacity = 10);
	~Queue();
    int Size() const;
    bool IsEmpty() const;
protected:
    int front, rear;
};

template <class T>
Queue<T>::Queue(int queueCapacity):Bag<T>(queueCapacity)
{
	front = 0;
	rear = 0;
}

template <class T>
Queue<T>::~Queue(){}

template <class T>
inline bool Queue<T>::IsEmpty() const
{
    return front == rear;
}

template <class T>
inline int Queue<T>::Size() const
{
    int result = (rear - front);
    if (result < 0) return result + Bag<T>::capacity;
    else return result;
}

template <class T>
class Deque : public Queue<T>
{
    using Bag<T>::array;
    using Bag<T>::capacity;
    using Queue<T>::rear;
    using Queue<T>::front;
	using Queue<T>::IsEmpty;
	template <class U>
	friend ostream& operator<<(ostream& os, Deque<U> &deque);
	template <class U>
	friend istream& operator>>(istream &is, Deque<U> &deque);
	template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
public:
	Deque(int dequeCapacity = 10);
    ~Deque();
    void Push_front(const T &item);
    void Push_rear(const T &item);
    void Pop_front();
    void Pop_rear();
};

template <class T>
Deque<T>::Deque(int dequeCapacity):Queue<T>(dequeCapacity){}

template <class T>
Deque<T>::~Deque(){}

template <class T>
void Deque<T>::Push_front(const T &item)
{
	if ((front - 1) % capacity == rear) {
        T* newQueue = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(array + start, array + start + capacity - 1, newQueue + 1);
        else {
            copy(array + start, array + capacity, newQueue + 1);
            copy(array, array + rear + 1, newQueue + capacity - start + 1);
        }
        front = 0;
		rear = capacity - 1;
		delete[] array;
		array = newQueue;
		capacity *= 2;
	}
	array[front] = item;
	front = (front - 1) % capacity;
}

template <class T>
void Deque<T>::Push_rear(const T &item)
{
	if ((rear + 1) % capacity == front) {
        T* newQueue = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(array + start, array + start + capacity - 1, newQueue);
        else {
            copy(array + start, array + capacity, newQueue);
            copy(array, array + rear + 1, newQueue + capacity - start);
        }
        front = 2 * capacity - 1;
		rear = capacity - 2;
		delete[] array;
		array = newQueue;
		capacity *= 2;
	}
	rear = (rear + 1) % capacity;
	array[rear] = item;
}

template <class T>
void Deque<T>::Pop_front()
{
	if (IsEmpty()) throw "Queue is empty, cannot delete";
	front = (front + 1) % capacity;
	array[front].~T(); // destructor for T
}

template <class T>
void Deque<T>::Pop_rear()
{
	if (IsEmpty()) throw "Queue is empty, cannot delete";
	array[rear].~T(); // destructor for T
	rear = (rear - 1) % capacity;
}

template <class T>
istream &operator>>(istream& is, Deque<T> &deque)
{
    int num;
	float temp;
    
	cout << "How many element do you want to plug in : ";
	is >> num;
	for(int i = 0; i < num; i++){
		is >> temp;
		deque.Push_rear(temp);
	}
    return is;
}

template <class T>
ostream& operator<<(ostream& os, Deque<T> &deque)
{    
    os << "The Deque is : (" << deque.array[(deque.front + 1) % deque.capacity];
    for (int i = (deque.front + 2) % deque.capacity; i != (deque.rear + 1) % deque.capacity;){
    	os << ", " << deque.array[i];
    	i = (i + 1) % deque.capacity;
	}
    os << ")" << endl;

    return os;
}

int main()
{
    Deque<int> D1(1);
    Deque<float> D2(1);
    int push;
    float pu;
    
    //int
    cout << "type in int" << endl;
    cin >> D1;
    cout << "D1 = " << D1;
    cout << "The size of D1 is : " << D1.Size() << endl;
	D1.Pop_front();
	cout << "D1 after pop in the front = " << D1;
	cout << "What element do you wan't to put in the front of D1? ";
    cin >> push;
    D1.Push_front(push);
    cout << "D1 = " << D1;
    D1.Pop_rear();
	cout << "D1 after pop at the rear = " << D1;
	cout << "What element do you wan't to put at the back of D1? ";
    cin >> push;
    D1.Push_rear(push);
    cout << "D1 = " << D1 << endl;
    
	//float
	cout << "type in float" << endl;
    cin >> D2;
    cout << "D2 = " << D2;
    cout << "The size of D2 is : " << D2.Size() << endl;
	D2.Pop_front();
	cout << "D2 after pop in the front = " << D2;
	cout << "What element do you wan't to put in the front of D2? ";
    cin >> pu;
    D2.Push_front(pu);
    cout << "D2 = " << D2;
    D2.Pop_rear();
	cout << "D2 after pop at the rear = " << D2;
	cout << "What element do you wan't to put at the back of D2? ";
    cin >> pu;
    D2.Push_rear(pu);
    cout << "D2 = " << D2 << endl;
    
    return 0;
}
