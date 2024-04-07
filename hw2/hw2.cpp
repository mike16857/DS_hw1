template<class T>
Stack<T> Stack<T>::Merge(Stack<T> s2) 
{
    int newSize = size() + s2.size() + 1;
    Stack<T> tmp(newSize);     // max on top
    Stack<T> result(newSize);  // min on top

    while (Size() && s2.Size()) {
        if (Top() > s2.Top()) {
            tmp.push(Top());
            pop();
        } else {
            tmp.push(s2.Top());
            s2.pop();
        }
    }
    while (Size()) {
        tmp.push(Top());
        pop();
    }
    while (s2.Size()) {
        tmp.push(s2.Top());
        s2.pop();
    }

    // reverse
    while (tmp.Size()) {
        result.push(tmp.Top());
        tmp.pop();
    }

    return result;
}


template<class T>
void reverseQueue(Queue<T> &q) 
{
    Stack<T> s(q.Size());
    while (!q.IsEmpty()) {
        s.push(q.Front());
        q.pop();
    }
    while (!s.IsEmpty()) {
        q.push(s.Top());
        s.pop();
    }
}


void reverse_first_k_queue(Queue<int> &q, int k) 
{
    Stack<int> s(k);
    for (int i = 0; i < k; i++) {
        s.push(q.Front());
        q.pop();
    }
    while (!s.IsEmpty()) {
        q.push(s.Top());
        s.pop();
    }
    for (int i = 0; i < q.Size() - k; i++) {
        q.push(q.Front());
        q.pop();
    }
}


template<class T>
class DeQue
{
public:
    DeQue (int dequeCapacity = 10);
    bool IsEmpty() const;
    void Push_rear(const T& item); // add an item into the queue
    void Pop_front(); // delete an item
    void Push_front(const T& item); // add an item into the queue
    void Pop_rear(); // delete an item
    T& Front() const; // return top element of stack
    T& Rear() const; // return top element of stack
private:
    T* deque;
    int front, rear, capacity;
} ;