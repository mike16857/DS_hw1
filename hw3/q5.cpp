#include <iostream>
using namespace std;


class DblList;  //forward declaration

class DblListNode 
{
    friend class DblList;
private:
   int data;
   DblListNode *left, *right;   
};

class DblList 
{
public:
    // List manipuation operations
    DblList();
    ~DblList();
    void Insert(DblListNode *p, DblListNode *x);
    void Delete(DblListNode *x);
private:
    DblListNode *head;  // points to header node
};
