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

class Queue : public Bag
{
    
};
