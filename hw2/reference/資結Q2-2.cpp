#include <iostream>
using namespace std;

template <class T>
class Stack
{
	template <class U>
	friend class Queue;
public:
	Stack(int stackCapacity = 10);
	bool IsEmpty() const;
	void Push(const T& item);
	void Pop();
	T& Top() const;
	void ChangeSize1D(T* &a, const int oldSize, const int newSize);
private:
	int top, capacity;
	T* stack;
};
template <class T>
Stack<T>::Stack(int stackCapacity):capacity(stackCapacity)
{
	if (capacity < 1) throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}
template <class T>
inline bool Stack<T>::IsEmpty() const
{
	return top == -1;
}
template <class T>
inline T& Stack<T>::Top() const
{
	if (IsEmpty()) throw "Stack is empty";
	return stack[top];
}
template <class T>
void Stack<T>::Push(const T& x)
{
	if (top == capacity - 1) {
		ChangeSize1D(stack, capacity, 2 * capacity);
		capacity *= 2;
	}
	stack[++top] = x;
}
template <class T>
void Stack<T>::Pop()
{
	if (IsEmpty()) throw "Stack is empty, cannot delete";
	stack[top--].~T();
}
template <class T>
void Stack<T>::ChangeSize1D (T* &a, const int oldSize, const int newSize )
{
	if (newSize < 0) throw "New length must be >=0";
	T* temp = new T [newSize]; // new array
	int number = min (oldSize, newSize); // number to copy
	copy (a, a + number, temp);
	delete [] a; // deallocate old memory
	a = temp;
}

// Queue
template <class T>
class Queue
{
	template <class U>
	friend ostream &operator<<(ostream& os, Queue<U> &queue);
public:
    Queue (int queueCapacity = 0);
	bool IsEmpty() const;
    void Push(const T& item);
    void Pop();
    T& Front() const;
    T& Rear() const;
	Queue<T> reverseQueue();
private:
	T* queue;
	int front, rear, capacity;
};

template <class T>
Queue<T>::Queue(int queueCapacity):capacity(queueCapacity)
{
	if (capacity < 1) throw "Queue capacity must be > 0";
	queue= new T[capacity];
	front = rear = 0; // indicate empty queue
}

template <class T>
inline bool Queue<T>::IsEmpty() const
{
	return front == rear;
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
void Queue<T>::Push(const T& x)
{
	if ((rear + 1) % capacity == front){ 
		T* newQu = new T[2 * capacity];
		int start = (front+1) % capacity;
		if(start < 2)
			copy(queue + start, queue + start + capacity - 1, newQu);
		else{
			copy(queue + start, queue + capacity, newQu);
			copy(queue, queue + rear + 1, newQu + capacity - start);
		}
		front = 2 * capacity - 1;
		rear = capacity - 2;
		delete[] queue;
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
ostream &operator<<(ostream& os, Queue<T> &queue)
{
    int i;
    
    if(queue.IsEmpty()) os << "Empty" << endl;
    else{
    	os << "(";
    	for (i = (queue.front + 1) % queue.capacity; i != queue.rear; i = (i + 1) % queue.capacity)
    		os << queue.queue[i] << ", ";
    	os << queue.queue[i] << ")" << endl;
	}
    
    return os;
}

template <class T>
istream &operator>>(istream& is, Queue<T> &queue)
{
    int num;
	int temp;
    
	cout << "How many element do you want to plug in : ";
	is >> num;
	for(int i = 0; i < num; i++){
		is >> temp;
		queue.Push(temp);
	}
    return is;
}

template <class T>
Queue<T> Queue<T>::reverseQueue()
{
	Queue<T> Q1(capacity);
	Stack<T> stack;
	int pos = (front + 1) % capacity;
	
	while(pos != rear){
		stack.Push(queue[pos]);
		pos = (pos + 1) % capacity;
	}
	stack.Push(queue[rear]);
	
	while (!stack.IsEmpty()) {      // Pop every element in stack
        Q1.Push(stack.Top());    // store the Top element in Stack for reversing order
        stack.Pop();                // Pop stack
    }
    
    return Q1;
}

int main(void) {
    Queue<int> Q1(1), Q2(1);
    
    cin >> Q1;
    cout << "Q1 = " << Q1;
    Q2 = Q1.reverseQueue();
    cout << "reverse of Q1 is " << Q2;
    return 0;
}
