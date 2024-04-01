#include <iostream>
using namespace std;

template < class T >
class Queue
{
public:
    Queue (int queueCapacity = 10);
    bool IsEmpty( ) const;
    void Push(const T& item);
    // add an item into the queue
    void Pop( );
    // delete an item
    T& Front() const;
    // return top element of stack
    T& Rear() const;
    // return top element of stack
private:
    T* queue;
    int front,
    rear,
    capacity;
} ;

template < class T >
Queue<T>::Queue(int queueCapacity ):capacity(queueCapacity)
{
    if (capacity < 1) throw "Queue capacity must be > 0";
    queue= new T[capacity];
    front = rear = 0; // indicate empty queue
}

template <class T>
inline bool Queue<T>:: IsEmpty() const
{
    return front == rear;
}

template <class T>
void Queue<T>::Push(const T& x)
{// add x to queue
    if ((rear + 1) % capacity == front) { //resize
        T* newQu = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(queue +start, queue+start+capacity-1, newQu);
        else {
            copy(queue +start, queue+capacity, newQu);
            copy(queue, queue+rear+1,newQu+capacity-start);
        }
        front = 2 * capacity - 1;
        rear = capacity -2;
        delete [] queue;
        queue = newQu; capacity *=2;
    }
    rear = (rear+1) % capacity; queue[rear] = x;
}

template <class T>
void Queue<T>::Pop( )
{
    if (IsEmpty()) throw "Queue is empty, cannot delete";
    front = (front + 1) % capcity;
    queue[front].~T(); // destructor for T
}

template <class T>
inline T& Queue<T>:: Front() const
{
    if (IsEmpty()) throw "Queue is empty. No front element.";
    return queue[(front + 1) % capacity]; //front unchanged
}

template <class T>
inline T& Queue<T>:: Rear() const
{
    if (IsEmpty()) throw "Queue is empty. No rear element.";
    return queue[rear];
}