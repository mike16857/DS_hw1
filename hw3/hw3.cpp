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