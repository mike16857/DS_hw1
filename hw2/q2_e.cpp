#include <iostream>
using namespace std;

/* Stack */
template <class T>
class Stack
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
    bool IsEmpty() const;
    void Push(const T& item);
    void Pop();
    T& Top() const;
private:
    int top;
    int capacity;
    T* stack;
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
    Queue<T> ReverseQueue();                  // (e)
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

// (a)
template <class T>
int Queue<T>::Size() const
{
    return (rear - front + capacity) % capacity;
}

// (b)
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

// (c)
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

// (d)
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

// (e)
template <class T>
Queue<T> Queue<T>::ReverseQueue()
{
    Queue<T> newQueue(Size() + 1);
    Stack<T> tempStack(Size() + 1);

    // Push all elements in the original queue to the stack
    for (int i = (front + 1) % capacity; i != (rear + 1) % capacity; ) {
        tempStack.Push(queue[i]);
        i = (i + 1) % capacity;
    }

    // Pop all elements from the stack to the new queue
    while (!tempStack.IsEmpty()) {
        newQueue.Push(tempStack.Top());
        tempStack.Pop();
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

    cout << "How many elements do you want to push?";
    cin >> n;
    for (int i = 0; i < n; i++) {
        is >> element;
        queue.Push(element);
    }
    return is;
}


int main() 
{
    Queue<int> Q1(1), Q2(1);
    
    cin >> Q1;
    cout << "Q1 = " << Q1;
    Q2 = Q1.ReverseQueue();
    cout << "reverse of Q1 is " << Q2;
    return 0;
}
