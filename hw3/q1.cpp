#include <iostream>
using namespace std;

template < class T > class Chain;  // 前向宣告

template < class T >
class ChainNode 
{
    friend class Chain <T>;
private:
	T data;
	ChainNode<T>* link;
};

template <class T>
class Chain 
{
public:
	Chain( ) {first = last = 0;} // 建構子將first, last初始化成0
	~Chain(); //desctructor
    // 鏈的處理運算
	bool IsEmpty();
    int Size();
    void InsertHead(const T& e);
    void DeleteHead();
    const T& Front();
    const T& Back();
    void InsertBack(const T& e);
    void DeleteBack();
    T& Get(int index);
    T& Set(int index, const T& e);
    int IndexOf(const T& e) const;
    void Delete(int index);
    void Insert(int index, const T& e);
    void Concatenate(Chain<T>& b);
    void Reverse();
    void Delete(Position p);
    void Insert(Position p, const T& e); //Position means ChainNode*)
	class ChainIterator
    {
    public:

    };
    ChainIterator begin() {return ChainIterator(first);}
    ChainIterator end()  {return ChainIterator(0);}
private:
	ChainNode<T> * first, *last;
};
