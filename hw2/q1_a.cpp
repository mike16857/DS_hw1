#include <iostream>
using namespace std;


class Bag
{ 
public:
    Bag(int bagCapacity = 10);
    // virtual     Bag();
    virtual int Size() const;
    virtual bool IsEmpty() const;
    virtual int Element() const;
    virtual void Push(const int);
    virtual void Pop();
protected:
    int *array;
    int top;
};

class Stack : public Bag
{
public:
    Stack (int stackCapacity = 10);
    ~Stack();
    int Top() const;
    void Pop();
};
