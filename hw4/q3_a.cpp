#include <iostream>
using namespace std;


template <class T>
class MaxPQ 
{
    template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
    template <class U>
    friend ostream& operator<<(ostream &, MaxPQ<U> &);
public:
    virtual ~MaxPQ() {}  // virtual destructor
    virtual bool IsEmpty() const = 0; //return true iff empty
    virtual const T& Top() const = 0; //return reference to the max
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

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
class MaxHeap : public class MaxPQ<T>
{
    template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
    template <class U>
    friend ostream& operator<<(ostream &, MaxHeap<U> &);
public:
    MaxHeap(int theCapacity = 10); // constructor
    bool IsEmpty() const; //return true iff empty
    const T& Top() const; //return reference to the max
    void Push(const T&);
    void Pop();
    // HeapConstruct(T* array, int n);
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
    if (IsEmpty()) throw "Heap is empty. Cannot return.";
    return heap[1];
}

template <class T>
void MaxHeap<T>::Push(const T& e)
{ // add element e to max heap
    if (heapSize == capacity) { // double the capacity
        ChangeSize1D(heap, capacity, 2 * capacity);
        capacity *= 2;
    }
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] < e) { // bubbling up
        heap[currentNode] = heap[currentNode / 2];//move parent down
        currentNode /= 2;
    }
    heap[currentNode] = e;
}

template <class T>
void MaxHeap<T>::Pop()
{ // Delete max element
    if (IsEmpty ()) throw "Heap is empty. Cannot delete.";
    heap[1].~T(); // delete max element
    T lastE = heap[heapSize--]; // remove last element from heap
    // trickle down to find a position to place the last element
    int currentNode = 1; // root
    int child = 2; // a child of current node
    while (child <= heapSize) {
        // set child to larger child of currentNode
        if (child < heapSize && heap[child] < heap[child + 1]) child++;
        if (lastE >= heap[child]) break;
        heap[currentNode] = heap[child]; // move child up
        currentNode = child; child *= 2; // move down a level
    }
    heap[currentNode] = lastE;
}

// template <class T>
// MaxHeap<T>::HeapConstruct(T* array, int n)
// {
//     heap = array;
//     heapSize = n;
//     capacity = n;
//     for (int i = n / 2; i >= 1; i--) {
//         T e = heap[i];
//         int currentNode = i;
//         int child = 2 * i;
//         while (child <= heapSize) {
//             if (child < heapSize && heap[child] < heap[child + 1]) child++;
//             if (e >= heap[child]) break;
//             heap[currentNode] = heap[child];
//             currentNode = child;
//             child *= 2;
//         }
//         heap[currentNode] = e;
//     }
// }



int main()
{
    
    return 0;
}