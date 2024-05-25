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


template <class T>
class MaxHeap : public MaxPQ<T>
{
    template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
    template <class U>
    friend ostream& operator<<(ostream &, MaxHeap<U> &);
public:
    MaxHeap(int theCapacity = 10); // constructor
    MaxHeap(T* array, int n); // bottom up heap construction
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

template <class T>
MaxHeap<T>::MaxHeap(T* array, int n)
{
    capacity = n + 1;
    heapSize = n;
    heap = new T[capacity];
    copy(array, array + n, heap + 1);

    for (int i = heapSize / 2; i > 0; i--) {
        T node = heap[i];
        int currentNode = i;
        int child = 2 * i;
        // bubble down
        while (child <= heapSize) {
            if (child < heapSize && heap[child] < heap[child + 1]) child++; // swap with the larger child
            if (node >= heap[child]) break;
            heap[currentNode] = heap[child];
            currentNode = child;
            child *= 2;
        }
        heap[currentNode] = node;
    }
}

// template <class T>
// MaxHeap<T>::MaxHeap(T array[], int N)
// {
//     heap = new T[N + 1];
//     capacity = N + 1;
//     heapSize = N;
    
//     for(int i = 0; i < N; i++){
//         heap[i + 1] = array[i];
//     }
//     for(int i = N / 2; i >= 1; i--){
//         int k = i;
//         T v = heap[k];
//         bool flag = false;
//         while(!flag && 2 * k <= N){
//             int j = 2 * k;
//             if((j < N) && (heap[j] < heap[j + 1])) j += 1;
//             if(v >= heap[j]) flag = true;
//             else{
//                 heap[k] = heap[j];
//                 k = j;
//             }
//         }
//         heap[k] = v;
//     }
// }


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


int main()
{
    MaxHeap<int> heap;
    // MaxPQ<int> M;
    int A[13] = {50, 5, 30, 40, 80, 35, 2, 20, 15, 60, 70, 8, 10};
    
    
    // cout << "MaxPQ : " << endl;
    // for (int i = 0; i < 13; i++) {
    //     cout << "Push " << A[i] << ": ";
    //     M.Push(A[i]);
    //     cout << M;
    // }
    // cout << endl;
	 
    // if(M.IsEmpty()) cout << "The Heap is empty";
    // else cout << "The Heap is not empty" << endl;
    // cout << "The Max element is : " << M.Top() << endl;
    // cout << "After Pop : ";
    // M.Pop();
	// cout << M;
    // cout << "The Max element is : " << M.Top() << endl << endl;
    
    
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