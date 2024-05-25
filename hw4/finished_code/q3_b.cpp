#include <iostream>
using namespace std;


template <class U>
void ChangeSize1D(U* &a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";
    U *temp = new U[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number + 1, temp);
    delete []a;
    a = temp;
}


template <class T>
class MinPQ 
{
    template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
    template <class U>
    friend ostream& operator<<(ostream &, MinPQ<U> &);
public:
    virtual ~MinPQ() {}  // virtual destructor
    virtual bool IsEmpty() const = 0; //return true iff empty
    virtual const T& Top() const = 0; //return reference to the max
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};


template <class T>
class MinHeap : public MinPQ<T>
{
    template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
    template <class U>
    friend ostream& operator<<(ostream &, MinHeap<U> &);
public:
    MinHeap(int theCapacity = 10); // constructor
    MinHeap(T* array, int n); // bottom up heap construction
    bool IsEmpty() const; //return true iff empty
    const T& Top() const; //return reference to the max
    void Push(const T&);
    void Pop();
private:
    T* heap; // element array
    int heapSize; // number of elements in heap
    int capacity; // size of the element array
};

template <class T>
MinHeap<T>::MinHeap(int theCapacity) // constructor
{
    if(theCapacity < 1) throw "Capacity must be >= 1";
    capacity = theCapacity;
    heapSize = 0;
    heap = new T [capacity + 1]; // heap[0] unused
}

template <class T>
bool MinHeap<T>::IsEmpty() const
{
    return heapSize == 0;
}

template <class T>
const T& MinHeap<T>::Top() const
{
    if (IsEmpty()) throw "Heap is empty. Cannot return.";
    return heap[1];
}

template <class T>
void MinHeap<T>::Push(const T& e)
{ // add element e to max heap
    if(heapSize == capacity){ // double the capacity
        ChangeSize1D(heap, capacity, 2 * capacity);
        capacity *= 2;
    }
    int currentNode = ++heapSize;
    while(currentNode != 1 && heap[currentNode / 2] > e){
        heap[currentNode] = heap[currentNode / 2];//move parent down
        currentNode /= 2;
    }
    heap[currentNode] = e;
}

template <class T>
void MinHeap<T>::Pop()
{
    if(IsEmpty ()) throw "Heap is empty. Cannot delete.";
    heap[1].~T(); // delete max element
    T lastE = heap[heapSize--]; // last element in heap
    int currentNode = 1;
    while (currentNode * 2 <= heapSize) {
        int child = currentNode * 2;
        if (child < heapSize && heap[child + 1] < heap[child]) child++;
        if (lastE <= heap[child]) break;
        heap[currentNode] = heap[child];
        currentNode = child; child *= 2;
    }
    heap[currentNode] = lastE;
}

template <class T> 
MinHeap<T>::MinHeap(T* array, int n)
{
    capacity = n + 1;
    heapSize = n;
    heap = new T[capacity];
    copy(array, array + n, heap + 1);

    for (int i = heapSize / 2; i >= 1; i--) {
        T node = heap[i];
        int currentNode = i;
        int child = 2 * i;

        while (child <= heapSize) {
            if (child < heapSize && heap[child] > heap[child + 1]) child++;
            if (node <= heap[child]) break;
            heap[currentNode] = heap[child];
            currentNode = child;
            child *= 2;
        }
        heap[currentNode] = node;
    }
}

template <class T>
ostream& operator<<(ostream& os, MinHeap<T> &H)
{
    int i;
    os << "[" << H.heap[1];
    for (i = 2; i <= H.heapSize; i++)
        os << ", " << H.heap[i];
    os << "]" << endl;
    
    return os;
}


int main()
{
    MinHeap<int> heap;
    // MinPQ<int> M;
    int A[13] = {50, 5, 30, 40, 80, 35, 2, 20, 15, 60, 70, 8, 10};
    
    
    // cout << "MinPQ : " << endl;
    // for (int i = 0; i < 13; i++) {
    //     cout << "Push " << A[i] << ": ";
    //     M.Push(A[i]);
    //     cout << M;
    // }
    // cout << endl;
    
    // if(M.IsEmpty()) cout << "The Heap is empty";
    // else cout << "The Heap is not empty" << endl;
    // cout << "The Min element is : " << M.Top() << endl;
    // cout << "After Pop : ";
    // M.Pop();
	// cout << M;
    // cout << "The Min element is : " << M.Top() << endl << endl;
    
    
    cout << "Min Heap : " << endl;
    for(int i = 0; i < 13; i++) {
        cout << "Push " << A[i] << ": ";
        heap.Push(A[i]);
        cout << heap;
    }
    
    cout << endl;
    if(heap.IsEmpty()) cout << "The Heap is empty";
    else cout << "The Heap is not empty" << endl;
    cout << "The Min element is : " << heap.Top() << endl;
    cout << "After Pop : ";
    heap.Pop();
	cout << heap;
    cout << "The Min element is : " << heap.Top() << endl << endl;

    cout << "Initialize using bottom up : " << endl;   
	MinHeap<int> heap2(A, 13);
	cout << heap2;
    return 0;
}