#include <iostream>
using namespace std;

template <class T>
class Queue
{
public:
    Queue(int queueCapacity = 10);
    ~Queue();
    bool IsEmpty() const;
    int Size() const;
    void Push_rear(const T& item);
    // add an item into the queue
    void Pop_front();
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
void Queue<T>::Push_rear(const T& x)
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
void Queue<T>::Pop_front()
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

/* Deque */
template <class T>
class Deque : public Queue<T>
{
    using Queue<T>::queue;
    using Queue<T>::front;
    using Queue<T>::rear;
    using Queue<T>::capacity;
    template <class U>
	friend ostream& operator<<(ostream &os, Deque<U> &deque);
	template <class U>
	friend istream& operator>>(istream &is, Deque<U> &deque);
public:
    Deque(int dequeCapacity = 10);
    ~Deque();
    void Push_front(const T& item);
    void Pop_rear();
};

template <class T>
ostream& operator<<(ostream &os, Deque<T> &deque)
{
    os << "Queue: ( " << deque.queue[(deque.front + 1) % deque.capacity];
    for (int i = (deque.front + 2) % deque.capacity; i != (deque.rear + 1) % deque.capacity; ) {
        os << ", " << deque.queue[i];
        i = (i + 1) % deque.capacity;
    }
    os << " )" << endl;
    return os;
}

template <class T>
istream& operator>>(istream &is, Deque<T> &deque)
{
    int n;
    T element;

    cout << "How many elements do you want to push? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        is >> element;
        deque.Push_rear(element);
    }
    return is;
}

template <class T>
Deque<T>::Deque(int dequeCapacity) : Queue<T>(dequeCapacity) {}

template <class T>
Deque<T>::~Deque() {}

template <class T>
void Deque<T>::Push_front(const T& item)
{
    if ((front - 1) % capacity == rear) {
        T* newQueue = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(queue + start, queue + start + capacity - 1, newQueue + 1);
        else {
            copy(queue + start, queue + capacity, newQueue + 1);
            copy(queue, queue + rear + 1, newQueue + capacity - start + 1);
        }
        front = 0;
        rear = capacity - 1;
        delete[] queue;
        queue = newQueue;
        capacity *= 2;
    }
    queue[front] = item;
    front = (front - 1) % capacity;
}

template <class T>
void Deque<T>::Pop_rear()
{
    // if (IsEmpty()) throw "Queue is empty, cannot delete";
    rear = (rear - 1) % capacity;
    queue[rear].~T();
}


int main()
{
    Deque<int> D1(1);
    Deque<float> D2(1);
    int push;
    float pu;
    
    //int
    cout << "type in some integer" << endl;
    cin >> D1;
    cout << "D1 = " << D1;
    cout << "The size of D1 is : " << D1.Size() << endl;
	D1.Pop_front();
	cout << "D1 after pop in the front = " << D1;
	cout << "What element do you want to put in the front of D1? ";
    cin >> push;
    D1.Push_front(push);
    cout << "D1 = " << D1;
    D1.Pop_rear();
	cout << "D1 after pop at the rear = " << D1;
	cout << "What element do you want to put at the back of D1? ";
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
	cout << "What element do you want to put in the front of D2? ";
    cin >> pu;
    D2.Push_front(pu);
    cout << "D2 = " << D2;
    D2.Pop_rear();
	cout << "D2 after pop at the rear = " << D2;
	cout << "What element do you want to put at the back of D2? ";
    cin >> pu;
    D2.Push_rear(pu);
    cout << "D2 = " << D2 << endl;
    
    return 0;
}
