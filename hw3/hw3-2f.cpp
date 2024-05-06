template <class T>
void CircularList<T>::length()
{
    int count = 0;
    ChainNode<T> *tmp = head;
    while (tmp->link != head) {
        count++;
        tmp = tmp->link;
    }
    return count;
}

template <class T>
void CircularList<T>::insertFront(T data)
{
    ChainNode<T> *newNode = new ChainNode(data);
    newNode->link = head->link;
    head->link = newNode;
}

template <class T>
void CircularList<T>::insertBack(T data)
{
    ChainNode<T> *newNode = new ChainNode(data);
    ChainNode<T> *tmp = head;
    while (tmp->link != head) {
        tmp = tmp->link;
    }
    tmp->link = newNode;
    newNode->link = head;
}

template <class T>
void CircularList<T>::deleteFront()
{
    ChainNode<T> *toDel = head->link;
    head->link = toDel->link;
    delete toDel;
}

template <class T>
void CircularList<T>::deleteBack()
{
    ChainNode<T> *tmp = head;
    ChainNode<T> *toDel;
    while (tmp->link->link != head) {
        tmp = tmp->link;
    }
    toDel = tmp->link;
    tmp->link = head;
    delete toDel;
}


////////////////////////////////////////////////////////////////////////////

template <class T>
void CircularList<T>::changeKthNode(int k, T data)
{
    ChainNode<T> *tmp = head;
    for (int i = 0; i < k; i++) {
        tmp = tmp->link;
    }
    tmp->data = data;
}

template <class T>
void CircularList<T>::insertBeforeKthNode(int k, T data)
{
    ChainNode<T> *newNode = new ChainNode(data);
    ChainNode<T> *tmp = head;
    for (int i = 0; i < k - 1; i++) {
        tmp = tmp->link;
    }
    newNode->link = tmp->link;
    tmp->link = newNode;
}

template <class T>
void CircularList<T>::deleteOdd()
{
    ChainNode<T> *tmp = head->link->link;
    ChainNode<T> *toDel = head->link;
    delete toDel;
    head->link = tmp;
    while (tmp != head) {
        toDel = tmp->link;
        if (toDel == head) {
            break; // if number of nodes is even
        }
        tmp->link = toDel->link;
        delete toDel;
        tmp = tmp->link;
    }
}

// subList is an empty list
template <class T>
void CircularList<T>::divideMid(CircularList<T> &subList)
{
    ChainNode<T> *tmp = head;
    ChainNode<T> *end = head;
    int length = length();
    for (int i = 0; i < (length + 1) / 2; i++) {
        tmp = tmp->link;
    }
    while (end->link != head) {
        end = end->link;
    }
    subList.head->link = tmp;
    end->link = subList.head;   // wrap around subList
    tmp->link = head;           // wrap around the original list
}

template <class T>
void CircularList<T>::split(CircularList<T> *split)
{
    ChainNode<T> *tmp = head;
    while (tmp->link != split){
        tmp = tmp->link;
    }
    tmp->link = head;
}


// merged list is stored in L1 with L1.merge(L2)
template <class T>
void CircularList<T>::merge(CircularList<T> &L2)
{
    ChainNode<T> *curr1 = head->link;
    ChainNode<T> *curr2 = L2.head->link;
    ChainNode<T> *next1, *next2;

    while (curr1->link != head && curr2->link != L2.head) {
        next1 = curr1->link;
        next2 = curr2->link;
        curr1->link = curr2;
        curr2->link = next1;
        curr1 = next1;
        curr2 = next2;
    }

    // if L1 is shorter
    if (curr1->link == head) { 
        curr1->link = curr2;
        while (curr2->link != L2.head) {
            curr2 = curr2->link;
        }
        curr2->link = head;    // wrap around
    }
    // if L2 is shorter
    else {                     
        next1 = curr1->link;
        curr1->link = curr2;
        curr2->link = next1;
        while (next1->link != head) {
            next1 = next1->link;
        }
        next1->link = head;   // wrap around
    }
}
