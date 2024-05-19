#include <iostream>
using namespace std;

template <class T>
void ChangeSize1D(T* &a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";

    T *temp = new T[newSize];
    int number = min(oldSize, newSize);    // choose the smallest Size to store
    copy(a, a + number + 1, temp);              // copy the old array into new
    delete []a;                             // delete old array
    a = temp;
}

template <class T>
class MaxPQ 
{
	template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
    template <class U>
    friend ostream& operator<<(ostream &, MaxPQ<U> &);
public:
	MaxPQ(int PQCapacity = 10);
    virtual ~MaxPQ();  // virtual destructor
    virtual bool IsEmpty() const; //return true iff empty
    virtual const T& Top() const; //return reference to the max
    virtual void Push(const T&);
    virtual void Pop();
private:
    T *Queue;
    int Size;
    int capacity;
};

template <class T>
MaxPQ<T>::MaxPQ(int PQCapacity)
{
    capacity = PQCapacity;
    Queue = new T[capacity];
    Size = 0;
}

template <class T>
MaxPQ<T>::~MaxPQ()
{
	delete []Queue;
}

template <class T>
bool MaxPQ<T>::IsEmpty() const
{
    return Queue == NULL;
}

template <class T>
const T& MaxPQ<T>::Top() const
{
    if (IsEmpty()) throw "Queue is empty, cannot return.";
    return Queue[Size - 1];
}

template <class T>
void MaxPQ<T>::Push(const T &e)
{
	int i = 0;
	
    if (Size == capacity) {
        ChangeSize1D(Queue, capacity, 2 * capacity);
        capacity *= 2;
    }
    while(e > Queue[i] && i < Size) i++;
    if(i == Size) {
        Queue[i] = e;
        Size++;
        return;
    }
    else{
        for (int j = Size; j > i; j--) Queue[j] = Queue[j - 1];
        Queue[i] = e;
        Size++;
        return;
    }
}

template <class T>
void MaxPQ<T>::Pop()
{
	Queue[Size - 1].~T();
    Size--;
    
    return;
}

template <class T>
ostream& operator<<(ostream &os, MaxPQ<T> &PQ)
{
    int i;
    
    os << "[" << PQ.Queue[0];
    for (i = 1; i < PQ.Size; i++) {
        os << ", " << PQ.Queue[i];
    }
    os << "]" << endl;
    
    return os;
}

template <class T>
class MaxHeap : public MaxPQ<T>
{
	template <class U>
    friend ostream &operator<<(ostream &os, MaxHeap<U> &H);
public:
	MaxHeap(int theCapacity = 10); // constructor
	bool IsEmpty() const; //return true iff empty
	const T& Top() const; //return reference to the max
	void Push(const T&);
	void Pop();
	MaxHeap(T array[], int N);
private:
	T* heap; // element array
	int heapSize; // number of elements in heap
	int capacity; // size of the element array
};

template <class T>
MaxHeap<T>::MaxHeap(int theCapacity) // constructor
{
	if(theCapacity < 1) throw "Capacity must be >= 1";
	capacity = theCapacity;
	heapSize = 0;
	heap = new T [capacity + 1]; // heap[0] unused
}

template <class T>
bool MaxHeap<T>::IsEmpty() const
{
    return heapSize == 0;
}

template <class T>
const T& MaxHeap<T>::Top() const
{
    return heap[1];
}

template <class T>
void MaxHeap<T>::Push(const T& e)
{ // add element e to max heap
	if(heapSize == capacity){ // double the capacity
		ChangeSize1D(heap, capacity, 2 * capacity);
		capacity *= 2;
	}
	int currentNode = ++heapSize;
	while(currentNode != 1 && heap[currentNode/2] < e){
		heap[currentNode] = heap[currentNode/2];//move parent down
		currentNode /= 2;
	}
	heap[currentNode] = e;
}

template <class T>
void MaxHeap<T>::Pop()
{ // Delete max element
	if(IsEmpty ()) throw "Heap is empty. Cannot delete.";
	heap[1].~T(); // delete max element
	T lastE = heap[heapSize--]; // remove last element from heap
	int currentNode = 1; // root
	int child = 2; // a child of current node
	while(child <= heapSize){
		if(child < heapSize && heap[child] < heap[child + 1]) child++;
		if(lastE >= heap[child]) break;
		heap[currentNode] = heap[child]; // move child up
		currentNode = child; child *= 2; // move down a level
	}
	heap[currentNode] = lastE;
}

template <class T>
ostream& operator<<(ostream& os, MaxHeap<T> &H)
{
    int i;
    os << "[" << H.heap[1];
    for (i = 2; i <= H.heapSize; i++)
        os << ", " << H.heap[i];
    os << "]" << endl;
    
    return os;
}
/*
template <class T>
MaxHeap<T>::MaxHeap(T array[], int N)	// Construction
{
    capacity = N + 2;
	heap = new T[capacity];
    heapSize = N;
    int j = 0, count = 0, first = 0;
    
	N++;
    for(int i = 0; i < N; i++) heap[i] = 0;
    
    while(count < N - 1){
    	int level = 1;
    	while(level < N - count) level *= 2;
    	level = level / 2;
    	if(first == 0){
    		for(int i = level; i < N; i++){
    			heap[i] = array[j++];
    			count++;
			}
			first++;
		}
		else{
			for(int i = level; i < level * 2; i++){
    			heap[i] = array[j++];
    			count++;
			}
		}
		for(int i = level; i < N; i++){
    		if(i * 2 <= N){
    			if(heap[i] < heap[i * 2]){
    				int temp = heap[i];
    				heap[i] = heap[i * 2];
    				heap[i * 2] = temp;
				}
			}
			if(i * 2 + 1 <= N){
    			if(heap[i] < heap[i * 2 + 1]){
    				int temp = heap[i];
    				heap[i] = heap[i * 2 + 1];
    				heap[i * 2 + 1] = temp;
				}
			}
		}
	}
	
}
*/
template <class T>
MaxHeap<T>::MaxHeap(T array[], int N)
{
    heap = new T[N + 1];
    capacity = N + 1;
    heapSize = N;
    
    for(int i = 0; i < N; i++){
        heap[i + 1] = array[i];
    }
    for(int i = N / 2; i >= 1; i--){
        int k = i;
        T v = heap[k];
        bool flag = false;
        while(!flag && 2 * k <= N){
            int j = 2 * k;
            if((j < N) && (heap[j] < heap[j + 1])) j += 1;
            if(v >= heap[j]) flag = true;
            else{
                heap[k] = heap[j];
                k = j;
            }
        }
        heap[k] = v;
    }
}

int main(void)
{
    MaxHeap<int> heap;
    MaxPQ<int> M;
    int A[13] = {50, 5, 30, 40, 80, 35, 2, 20, 15, 60, 70, 8, 10};
    
    
    cout << "MaxPQ : " << endl;
    for (int i = 0; i < 13; i++) {
        cout << "Push " << A[i] << ": ";
        M.Push(A[i]);
        cout << M;
    }
    cout << endl;
	 
    if(M.IsEmpty()) cout << "The Heap is empty";
    else cout << "The Heap is not empty" << endl;
    cout << "The Max element is : " << M.Top() << endl;
    cout << "After Pop : ";
    M.Pop();
	cout << M;
    cout << "The Max element is : " << M.Top() << endl << endl;
    
    
    cout << "Max Heap : " << endl;
    for(int i = 0; i < 13; i++) {
        cout << "Push " << A[i] << ": ";
        heap.Push(A[i]);
        cout << heap;
    }
    
    cout << endl;
    if(heap.IsEmpty()) cout << "The Heap is empty";
    else cout << "The Heap is not empty" << endl;
    cout << "The Max element is : " << heap.Top() << endl;
    cout << "After Pop : ";
    heap.Pop();
	cout << heap;
    cout << "The Max element is : " << heap.Top() << endl << endl;

    cout << "Initialize using bottom up : " << endl;   
	MaxHeap<int> heap2(A, 13);
	cout << heap2;
    return 0;
}

