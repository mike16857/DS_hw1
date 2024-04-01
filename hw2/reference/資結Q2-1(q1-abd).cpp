#include <iostream>
using namespace std;

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
    int Size() const;
    int Capacity() const;
    Queue<T> Merge(Queue<T> q);
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
int Queue<T>::Size() const
{
	int size = rear - front;
	if(size >= 0) return size;
	else return size + capacity;
}

template <class T>
int Queue<T>::Capacity() const
{
	return capacity;
}

template <class T>
Queue<T> Queue<T>::Merge(Queue<T> q)
{
	int pos1 = (front + 1) % capacity, pos2 = (q.front + 1) % q.capacity;
	int cap = Size() + q.Size();
	Queue<T> Q1(cap + 1);
	
	while(pos1 != (rear + 1) % capacity && pos2 != (q.rear + 1) % q.capacity){
		Q1.Push(queue[pos1]);
		Q1.Push(q.queue[pos2]);
		pos1 = (pos1 + 1) % capacity;
		pos2 = (pos2 + 1) % q.capacity;
	}
	while(pos1 != (rear + 1) % capacity){
		Q1.Push(queue[pos1]);
		pos1 = (pos1 + 1) % capacity;
	}
	while(pos2 != (q.rear + 1) % q.capacity){
		Q1.Push(q.queue[pos2]);
		pos2 = (pos2 + 1) % q.capacity;
	}

	return Q1;
}

template <class T>
ostream &operator<<(ostream& os, Queue<T> &queue)
{
    int i;
    
    if(queue.IsEmpty()) os << "Empty" << endl;
    else{
    	os << "(";
    	for (i = (queue.front + 1) % queue.capacity; i != queue.rear; i = (i + 1) % queue.capacity)
    		os << queue.queue[i] << ",";
    	os << queue.queue[i] << ")" << endl;    // output queue in (,) order
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

int main()
{
	Queue<int> Q1(1), Q2(1), Q3(1);
	int push;
	
	cin >> Q1;
	cin >> Q2;
	cout << "Q1 = " << Q1;
	cout << "The capacity of Q1 is : " << Q1.Capacity() << endl;
	cout << "Q2 = " << Q2;
	if (Q2.IsEmpty()) cout << "The queue is empty";
    else cout << "The size of Q2 is : " << Q2.Size() << endl;
    cout << "What num do you wan't to put in Q1? ";
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
}


