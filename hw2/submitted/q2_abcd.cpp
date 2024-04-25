#include <iostream>
using namespace std;

/* Queue */
template <class T>
class Queue
{
    template <class U>
	friend ostream& operator<<(ostream &os, Queue<U> &queue);
	template <class U>
	friend istream& operator>>(istream &is, Queue<U> &queue);
public:
    Queue(int queueCapacity = 10);
    ~Queue();
    Queue(const Queue<T>& other); // Copy constructor
    Queue<T>& operator=(const Queue<T>& other); // Copy assignment operator
    bool IsEmpty() const;
    int Size() const;                         // (a)
    int Capacity() const;                     // (b)
    void Push(const T& item);
    void Pop();
    T& Front() const;
    T& Rear() const;
    bool operator==(const Queue<T>& q) const; // (c)
    Queue<T> Merge(Queue<T> q);               // (d)
private:
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

// Copy constructor
template <class T>
Queue<T>::Queue(const Queue<T>& other)
{
    capacity = other.capacity;
    queue = new T[capacity];
    front = other.front;
    rear = other.rear;
    std::copy(other.queue, other.queue + capacity, queue);
}

// Copy assignment operator
template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if (this != &other) { // Check for self-assignment
        // Deallocate existing resources
        delete[] queue;

        // Copy data from the other queue
        capacity = other.capacity;
        queue = new T[capacity];
        front = other.front;
        rear = other.rear;
        std::copy(other.queue, other.queue + capacity, queue);
    }
    return *this;
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
int Queue<T>::Capacity() const
{
    return capacity;
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
            copy(queue, queue + rear + 1, newQu + capacity - start);
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        delete [] queue;
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
bool Queue<T>::operator==(const Queue<T>& q) const
{
    if (Size() != q.Size()) return false;
    int s = Size();
    for (int i = 0; i < s; i++)
        if (queue[(front + i + 1) % capacity] != q.queue[(q.front + i + 1) % q.capacity])
            return false;
    return true;
}

template <class T>
Queue<T> Queue<T>::Merge(Queue<T> q)
{
    int Pos, qPos;
    int newCap = Size() + q.Size() + 1;
    Queue<T> newQueue(newCap + 1);

    for (Pos = (front + 1) % capacity, qPos = (q.front + 1) % q.capacity;
         Pos != (rear + 1) % capacity && qPos != (q.rear + 1) % q.capacity;
         Pos = (Pos + 1) % capacity, qPos = (qPos + 1) % q.capacity) {
        
        newQueue.Push(queue[Pos]);
        newQueue.Push(q.queue[qPos]);
    }

    while (Pos != (rear + 1) % capacity) {
        newQueue.Push(queue[Pos]);
        Pos = (Pos + 1) % capacity;
    }

    while (qPos != (q.rear + 1) % q.capacity) {
        newQueue.Push(q.queue[qPos]);
        qPos = (qPos + 1) % q.capacity;
    }  

    return newQueue;
}

template <class T>
ostream& operator<<(ostream &os, Queue<T> &queue)
{
    os << "Queue: ( " << queue.queue[(queue.front + 1) % queue.capacity];
    for (int i = (queue.front + 2) % queue.capacity; i != (queue.rear + 1) % queue.capacity; ) {
        os << ", " << queue.queue[i];
        i = (i + 1) % queue.capacity;
    }
    os << " )" << endl;
    return os;
}

template <class T>
istream& operator>>(istream &is, Queue<T> &queue)
{
    int n;
    T element;

    cout << "How many elements do you want to push? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        is >> element;
        queue.Push(element);
    }
    return is;
}


int main()
{
	Queue<int> Q1(1), Q2(1), Q3(1);
	int push;
	
    cout << "Enter elements(of integer type) for Q1: " << endl;
	cin >> Q1;
    cout << "Enter elements(of integer type) for Q2: " << endl;
	cin >> Q2;

	cout << "Q1 = " << Q1;
	cout << "The capacity of Q1 is : " << Q1.Capacity() << endl;

	cout << "Q2 = " << Q2;
	if (Q2.IsEmpty()) cout << "The queue is empty.";
    else cout << "The size of Q2 is : " << Q2.Size() << endl;

    if (Q1 == Q2) cout << "Q1 and Q2 are the same" << endl;
    else cout << "Q1 and Q2 are different." << endl;

    Q3 = Q1.Merge(Q2);
    cout << "Q1 merge Q2 = " << Q3;

    cout << "What number do you want to put into Q1? ";
    cin >> push;
    Q1.Push(push);
    cout << "Q1 = " << Q1;

    cout << "last element of Q1 is : ";
	cout << Q1.Rear() << endl;

	cout << "first element of Q2 is : ";
	cout << Q2.Front() << endl;

	Q2.Pop();
    cout << "Q2 after pop = " << Q2;

    Q3 = Q1.Merge(Q2);
    cout << "Q1 merge Q2 = " << Q3;
    
    return 0;
}