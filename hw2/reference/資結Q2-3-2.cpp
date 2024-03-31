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

//Queue
template <class T>
class Queue : public Bag<T>
{
	using Bag<T>::IsEmpty;
	using Bag<T>::capacity;
    using Bag<T>::array;
	template <class U>
	friend ostream& operator<<(ostream &os, Queue<U> &queue);
	template <class U>
	friend istream& operator>>(istream &is, Queue<U> &queue);
	template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
public:
	Queue(int queueCapacity = 10);
	~Queue();
    void Pop();
    int Size() const;
    void Push (const T& item);
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
void Queue<T>::Push(const T &item)
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
void Queue<T>::Pop()
{
	if (IsEmpty()) throw "Queue is empty, cannot delete";
	front = (front + 1) % capacity;
	array[front].~T(); // destructor for T
}

template <class T>
ostream& operator<<(ostream &os, Queue<T> &queue)
{    
    os << "The queue is : (" << queue.array[(queue.front + 1) % queue.capacity];
    for (int i = (queue.front + 2) % queue.capacity; i != (queue.rear + 1) % queue.capacity;){
    	os << ", " << queue.array[i];
    	i = (i + 1) % queue.capacity;
	}
    os << ")" << endl;

    return os;
}

template <class T>
istream &operator>>(istream& is, Queue<T> &queue)
{
    int num;
	float temp;
    
	cout << "How many element do you want to plug in : ";
	is >> num;
	for(int i = 0; i < num; i++){
		is >> temp;
		queue.Push(temp);
	}
    return is;
}

template <class T>
inline int Queue<T>::Size() const
{
    int result = (rear - front);
    if (result < 0) return result + capacity;
    else return result;
}

int main()
{
    Queue<int> S1(1);
    Queue<float> S2(1);
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
