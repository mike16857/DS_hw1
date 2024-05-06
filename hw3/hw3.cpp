/* 2. */
template <class T>
void CircularList<T>::length() 
{
    int count = 1;
    CircularNode<T> *tmp = first;
    while (tmp->link != first) {
        count++;
        tmp = tmp->link;
    }
    return count;
}

template <class T>
void CircularList<T>::insertFront(T element) 
{
    CircularNode<T> *newNode = new CircularNode<T>(element);
    if (first == NULL) {
        first = newNode;
        first->link = first;
    } 
    else {
        newNode->link = first->link;
        first->link = newNode;
        newNode->data = first->data;
        first->data = element;
    }
}

template <class T>
void CircularList<T>::insertBack(T element) 
{
    CircularNode<T> *newNode = new CircularNode<T>(element);
    if (first == NULL) {
        first = newNode;
        first->link = first;
    } 
    else {
        newNode->link = first->link;
        first->link = newNode;
        newNode->data = first->data;
        first->data = element;
        first = newNode;
    }
}

template <class T>
void CircularList<T>::deleteFront() 
{
    if (first->link == first) {
        delete first;
        first = NULL;
    } 
    else {
        CircularNode<T> *toDel = first;
        CircularNode<T> *last = first;
        while (last->link != first) {
            last = last->link;
        }
        last->link = first->link;
        first = first->link;
        delete toDel;
    }
}

template <class T>
void CircularList<T>::deleteBack() 
{
    if (first->link == first) {
        delete first;
        first = NULL;
    } 
    else {
        CircularNode<T> *beforeNode = first;
        CircularNode<T> *last;
        while (beforeNode->link->link != first) {
            beforeNode = beforeNode->link;
        }
        last = beforeNode->link;
        beforeNode->link = first;
        delete last;
    }
}



////////////////////////////////////////////////////////////////////////////
/* 1. */

template <class T>
void Chain<T>::length() 
{
    int count = 0;
    ChainNode<T> *tmp = first;
    while (tmp != NULL) {
        count++;
        tmp = tmp->link;
    }
    return count;
}

template <class T> 
void Chain<T>::changeKthNode(int k, T element) 
{
    ChainNode<T> *tmp = first;
    for (int i = 1; i < k; i++) {
        tmp = tmp->link;
    }
    tmp->data = element;
}

template <class T>
void Chain<T>::insesertBeforeKthNode(int k, T element) 
{
    ChainNode<T> *newNode = new ChainNode<T>(element);
    if (k == 1) {
        newNode->link = first;
        first = newNode;
    } 
    else {
        ChainNode<T> *tmp = first;
        for (int i = 1; i < k - 1; i++) {
            tmp = tmp->link;
        }
        newNode->link = tmp->link;
        tmp->link = newNode;
    }
}

template <class T>
void Chain<T>::deleteOdd() 
{
    ChainNode<T> *tmp = first->link;
    ChainNode<T> *toDel;
    delete first;
    first = tmp;
    while (tmp != NULL) {
        toDel = tmp->link;
        tmp->link = toDel->link;
        if (toDel == NULL) {
            break;  // if number of nodes is even
        }
        delete toDel;
        tmp = tmp->link;
    }
}

template <class T>
void Chain<T>::divideMid(Chain<T> &subList)
{
    ChainNode<T> *tmp = first;
    int length = length();
    for (int i = 1; i < (length + 1) / 2; i++) {
        tmp = tmp->link;
    }
    subList.first = tmp->link;
    tmp->link = NULL;
}

template <class T>
void Chain<T>::split(ChainNode<T> *split) 
{
    ChainNode<T> *tmp = first;
    while (tmp->link != split) {
        tmp = tmp->link;
    }
    tmp->link = NULL;
}

template <class T>
void Chain<T>::merge(Chain<T> &List2)
{
    ChainNode<T> *curr1 = first;
    ChainNode<T> *curr2 = List2.first;
    ChainNode<T> *next1, *next2;

    while (curr1->link != NULL && curr2->link != NULL) {
        next1 = curr1->link;
        next2 = curr2->link;
        curr1->link = curr2;
        curr2->link = next1;
        curr1 = next1;
        curr2 = next2;
    }

    if (curr1->link == NULL) {
        curr1->link = curr2;
    } 
    else {
        next1 = curr1->link;
        curr1->link = curr2;
        curr2->link = next1;
    }
}


/* 6. */

template <class T>
void Chain<T>::insert(T x, ChainNode<T> *p) 
{
    ChainIterator<T> iterator = ChainIterator<T>(p);
    ChainNode<T> *newNode = new ChainNode<T>(x);
    newNode->link = iterator.current->link;
    --iterator; // move iterator to the previous node
    iterator.current->link = newNode;
}

template <class T>
void Chain<T>::remove(ChainNode<T> *p) 
{
    ChainIterator<T> iterator = ChainIterator<T>(p);
    ChainNode<T> *toDel;
    --iterator; // move iterator to the previous node
    toDel = iterator.current->link;
    iterator.current->link = toDel->link;
    delete toDel;
}
