#include <iostream>
using namespace std;


template < class T >
class Queue
{ 
public:
    Queue (int queueCapacity = 0);
	~Queue();
	bool IsEmpty( ) const;
    void Push(const T& item);    // add an item into the queue
    void Pop( );    // delete an item 
    T& Front() const;    // return top element of stack
    T& Rear() const;    // return top element of stack
private:
	//omitted
} ;
